/* Buildsupport is (c) 2008-2016 European Space Agency
 * contact: maxime.perrotin@esa.int
 * License is LGPL, check LICENSE file */
/* build_c_skeletons.c

  this program generates empty C functions respecting the interfaces defined
  in the interface view. it provides functions to invoke RI.

  updated 10/06/2016: properly align params and use FOREACH
  updated 20/04/2009 to disable in case "-onlycv" flag is set
  updated 8/10/2009 to rename the user_code.h/c to FV_name.h/c like in the Ada backend
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <assert.h>

#include "my_types.h"
#include "practical_functions.h"

static FILE *user_code_py = NULL;

static bool gen_this_ri(Interface * i)
{
    /* 
     * There can be duplicate RI name but one sync, the other async
     * In that case, discard the async one (generated by VT to allow
     * a mix of sync and async PI in one block
     */
    if (asynch == i->synchronism) {
        FOREACH(interface, Interface, i->parent_fv->interfaces, {
            if (RI == interface->direction &&
                !strcmp(interface->name, i->name) &&
                synch == interface->synchronism) {
                return false;
            }

        });
    }

    return true;
}

/* Import the RI into the module-level namespace of the Python script */
void import_RI_to_MicroPython_skel(Interface * i)
{
    if (NULL == user_code_py)
        return;

    bool comma = false;

    fprintf(user_code_py, "# %s_RI_%s(", i->parent_fv->name, i->name);

    FOREACH (p, Parameter, i->in, {
        fprintf(user_code_py, "%sIN_%s: asn1Scc%s",
            comma ? ", " : "", p->name, p->type);
        comma = true;
    });

    FOREACH (p, Parameter, i->out, {
        fprintf(user_code_py,"%sOUT_%s: asn1Scc%s",
            comma ? ", " : "", p->name, p->type);
        comma = true;
    });

    fprintf(user_code_py, ")\n");

    fprintf(user_code_py, "from taste import %s_RI_%s\n", i->parent_fv->name, i->name);
}

/* Generate the preamble of the skeleton script */
void micropython_skel_preamble(FV * fv)
{
    int hasparam = 0;

    /* Check if any interface needs ASN.1 types */
    FOREACH(i, Interface, fv->interfaces, {
            CheckForAsn1Params(i, &hasparam);}
    );

    /* c. user_code.py preamble (if applicable) */
    if (NULL != user_code_py) {
        fprintf(user_code_py,
                "# User code: This file will not be overwritten by TASTE.\n\n");
        fprintf(user_code_py, "import micropython\n");
        fprintf(user_code_py, "from taste import * # import all ASN types\n\n");

        FOREACH(i, Interface, fv->interfaces, {
            if (i->direction == RI && gen_this_ri(i)) {
                import_RI_to_MicroPython_skel(i);
            }
        });
        fprintf(user_code_py, "\n");

        // TODO need to generate dummy variables for the types

        if (has_context_param(fv)) {
            char *fv_no_underscore =
                underscore_to_dash(fv->name, strlen(fv->name));
            fprintf(user_code_py,
                    "/* Function static data is declared in this file : */\n");
            fprintf(user_code_py, "#include \"Context-%s.h\"\n\n",
                    fv_no_underscore);
            free(fv_no_underscore);
        }

        fprintf(user_code_py, "def %s_startup():\n", fv->name);

        fprintf(user_code_py,
                "    # Write your initialization code here,\n"
                "    # but do not make any call to a required interface.\n"
                "    # It's recommended to lock the heap once initialisation is done, but\n"
                "    # note that without the heap some Python operations are not possible.\n"
                "    micropython.heap_lock()\n"
                "\n");
    }
}

/* Creates user_code.h, and if necessary user_code.c (if it did not exist) */
int Init_MicroPython_GW_Backend(FV * fv)
{
    char *path = NULL;
    char *filename = NULL;

    if (NULL != fv->system_ast->context->output) {
        build_string(&path, fv->system_ast->context->output,
                     strlen(fv->system_ast->context->output));
    }
    build_string(&path, fv->name, strlen(fv->name));
    build_string(&filename, fv->name, strlen(fv->name));
    build_string(&filename, ".h", strlen(".h"));

    filename[strlen(filename) - 1] = 'p';       /* change from .c to .p */
    build_string(&filename, "y", 1);            /* change from .p to .py */
    if (!file_exists(path, filename)) {
        printf("MicroPython: creating fresh skeleton %s/%s\n", path, filename);
        create_file(path, filename, &user_code_py);
    }

    free(path);

    micropython_skel_preamble(fv);

    return 0;
}


void close_micropython_skel_files()
{
    close_file(&user_code_py);
}

/* Add a Provided interface. Can contain in and out parameters
 * Write in user_code.h the declaration of the user functions
 * and if user_code.c is new, copy these declarations there too.
 */
void add_PI_to_MicroPython_skel(Interface * i)
{
    if (NULL == user_code_py)
        return;

    char *signature_py = make_string("def %s_PI_%s(",
                                     i->parent_fv->name,
                                     i->name);
    bool comma = false;

    fprintf(user_code_py, "%s", signature_py);

#if 1
    // This code generates type hints for the parameters
    FOREACH (p, Parameter, i->in, {
        fprintf(user_code_py, "%sIN_%s: asn1Scc%s",
            comma ? ", " : "", p->name, p->type);
        comma = true;
    });

    FOREACH (p, Parameter, i->out, {
        fprintf(user_code_py, "%sOUT_%s: asn1Scc%s",
            comma ? ", " : "", p->name, p->type);
        comma = true;
    });
#else
    // This code generates the parameter list without type hints.
    FOREACH (p, Parameter, i->in, {
        fprintf(user_code_py, "%sIN_%s", comma ? ", " : "", p->name);
        comma = true;
    });

    FOREACH (p, Parameter, i->out, {
        fprintf(user_code_py, "%sOUT_%s", comma ? ", " : "", p->name);
        comma = true;
    });
#endif

    fprintf(user_code_py, "):\n    # Write your code here!\n    pass\n\n");

    free(signature_py);
}

/* Add timer declarations to the C code skeletons */
void MicroPython_Add_timers(FV *fv)
{
    (void)fv;
}


void End_MicroPython_GW_Backend()
{
    close_micropython_skel_files();
}

/* External interface (the one and unique) */
void GW_MicroPython_Backend(FV * fv)
{
    if (get_context()->onlycv)
        return;
    if (micropython == fv->language) {
        Init_MicroPython_GW_Backend(fv);
        FOREACH(i, Interface, fv->interfaces, {
            if (i->direction == PI) {
                add_PI_to_MicroPython_skel(i);
            }
        });
        // If any timers, add declarations in code skeleton
        MicroPython_Add_timers(fv);

        End_MicroPython_GW_Backend();
    }
}
