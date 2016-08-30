/* Buildsupport is (c) 2008-2016 European Space Agency
 * contact: maxime.perrotin@esa.int
 * License is LGPL, check LICENSE file */
/* build_vdm_skeletons.c

   Generate code skeletons for VDM functions
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <assert.h>

#include "my_types.h"
#include "practical_functions.h"

static FILE *user_code = NULL, *interface = NULL;


/* Adds header to user_code.h and (if new) user_code.c */
void vdm_gw_preamble(FV * fv)
{
    assert (NULL != interface);

    fprintf(interface,
          "-- This file was generated automatically: DO NOT MODIFY IT ! \n\n");

    fprintf(interface,
            "class %s_Interface\n"
            "operations\n"
            "    public Startup: () ==> ()\n"
            "    Startup (-) is subclass responsibility\n\n",
            fv->name);


    if (NULL != user_code) {
        fprintf(user_code,
              "-- User code: This file will not be overwritten by TASTE.\n\n");

        fprintf(user_code,
            "class %s\n"
            "is subclass of %s_Interface\n"
            "operations\n"
            "    public Startup: () ==> ()\n"
            "    -- user: fill your code\n\n",
            fv->name,
            fv->name);
    }
}

/* Creates interface and if necessary user code template (if it did not exist) */
void Init_VDM_GW_Backend(FV *fv)
{
    char *path = NULL;
    char *filename = NULL;

    path     = make_string("%s/%s", OUTPUT_PATH, fv->name);
    filename = make_string("%s_interface.vdmpp", fv->name);
    create_file(path, filename, &interface);
    free(filename);
    filename = make_string("%s_code.vdmpp", fv->name);

    if (!file_exists(path, filename)) {
        create_file(path, filename, &user_code);
        free(filename);
    }

    free(path);
    vdm_gw_preamble(fv);
}


/* Add a Provided interface. Can contain in and out parameters
 * Write in user_code.h the declaration of the user functions
 * and if user_code.c is new, copy these declarations there too.
 */
void add_pi_to_vdm_gw(Interface * i)
{
    if (NULL == interface)
        return;

    char *signature = make_string("public PI_%s:",
                                  i->name);


    fprintf(interface, "%s", signature);

    if (NULL != user_code) {
        fprintf(user_code, "%s", signature);
    }

    char *sep = " * ";
    bool comma = false;
    char *params = " (";
    char *sep2 = ", ";

    FOREACH (p, Parameter, i->in, {
        char *sort = make_string("%s%s`%s",
                                 comma? sep: "",
                                 p->asn1_module,
                                 p->type);
        params = make_string("%s%s%s",
                             params,
                             comma? sep2: "",
                             p->name);
        fprintf(interface, "%s", sort);
        if(NULL != user_code) {
            fprintf(user_code, "%s",sort);
        }
        free(sort);
        comma = true;
    });

    params = make_string("%s)", params);

    if (NULL != i->out) {
        char *out = make_string(" ==> %s`%s",
                                i->out->value->asn1_module,
                                i->out->value->type);
        fprintf(interface, "%s", out);
        if(NULL != user_code) {
            fprintf(user_code, "%s", out);
        }
        free(out);
    }

    fprintf(interface,
            "\n"
            "%s%s == is subclass responsibility\n\n",
            i->name,
            NULL != i->in? " (-)" : "");

    if (NULL != user_code)

        fprintf(user_code,
                "\n"
                "%s%s == -- Write your code here\n\n",
                NULL != i->in? params: "",
                i->name);

    free(signature);
    free(sep2);
    free(params);
    free(sep);
}

/* Declaration of the RI */
void add_ri_to_vdm_gw(Interface * i)
{
    if (NULL == interface || NULL == i)
        return;
    // TODO
}


void End_VDM_GW_Backend(FV *fv)
{
    fprintf(interface, "end %s_Interface\n", fv->name);
    fprintf(user_code, "end %s\n", fv->name);
    close_file(&interface);
    close_file(&user_code);
}

/* Function to process one interface of the FV */
void GW_VDM_Interface(Interface * i)
{
    switch (i->direction) {
        case PI:
            add_pi_to_vdm_gw(i);
            break;

        case RI:
            /*
             * There can be duplicate RI name but one sync, the other async
             * In that case, discard the async one (generated by VT to allow
             * a mix of sync and async PI in one block
             */
            if (asynch == i->synchronism) {
                FOREACH(ri, Interface, i->parent_fv->interfaces, {
                    if (RI == ri->direction &&
                        !strcmp(ri->name, i->name) &&
                        synch == ri->synchronism) {
                        return;
                    }

                });
            }
            // RI not supported yet
            //add_ri_to_vdm_gw(i);
            break;
        default:
            break;
    }
}

/* External interface (the one and unique) */
void GW_VDM_Backend(FV * fv)
{
    if (fv->system_ast->context->onlycv)
        return;
    if (vdm == fv->language) {
        Init_VDM_GW_Backend(fv);
        FOREACH(i, Interface, fv->interfaces, {
            GW_VDM_Interface(i);
        });
        End_VDM_GW_Backend(fv);
    }
}
