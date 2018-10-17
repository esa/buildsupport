/* Buildsupport is (c) 2008-2016 European Space Agency
 * contact: maxime.perrotin@esa.int
 * License is LGPL, check LICENSE file */
#ifndef __C_AST_CONSTRUCTION_H__
#define __C_AST_CONSTRUCTION_H__


Parameter *FindInParameter(Interface *i, char *param_name);
Parameter *FindOutParameter(Interface *i, char *param_name);
Interface *FindInterface(FV *fv,char *interface_name);
Interface *FindCorrespondingRI(FV *remote, Interface *pi);
void CompareIFname(Interface *i,Interface **result);
void CompareFVname(FV *fv_local,FV **result);
void SetSearchName(char *name);
void End_FV();
void End_IF();
void Add_Out_Param(char *name,
                   char *type,
                   char *module,
                   char *filename);

void Add_In_Param(char *, char *, char *, char*);
void Add_RI(char *ri, char *dist_fv, char *dist_name);
void Add_PI(char *pi);
void New_Interface(char *name,char *dist_fv, char *dist_name, IF_type direction);
FV *New_FV(char *fv_name, char *caseSensitive);
FV *FindFV(char *fv_name);
void LookForRI(Interface *i, Interface **check);
FV_list *Find_All_Calling_FV(Interface *i);
void Add_Binding(char *b);
void Set_Current_Process(Process *p);
void End_Process();
void New_Drivers_Section();
void End_Drivers_Section();
void New_Processor (char *name,
                    char *classifier,
                    char* platform,
                    char *envvars,
                    char *cflags,
                    char *ldflags);
void New_Process(char *, char *, char *, bool);
void Set_OutDir(char *o);
void Set_Interfaceview (char *name);
void Set_Dataview (char *name);
void Set_Test();
void Set_Timer_Resolution(char *val);
void Set_Future();
void Set_OnlyCV();
void Set_AADLV2();
void Set_Gateway();
void Set_keep_case();
void Set_Glue();
Context *get_context();
void Set_Compute_Time (uint64_t lower, char *unitlower,
                       uint64_t upper, char *unitupper);
void Set_Context_Variable (char *name, char *type,
                           char *def, char *mod, char *file, char *nameWithCase);

void Set_Period(long long p);
void Set_UndefinedKind_PI();
void Set_Unprotected_IF();
void Set_Protected_IF();
void Set_Variator_IF();
void Set_Sporadic_IF();
void Set_Cyclic_IF();
void Set_Unknown_IF();
void Set_ASync_IF();
void Set_Sync_IF();
void Set_Property (char *name, char *val);
void Set_Language_To_GUI();
void Set_Language_To_CPP();
void Set_Language_To_VDM();
void Set_Language_To_OpenGEODE();
void Set_Language_To_BlackBox_Device();
void Set_Language_To_Ada();
void Set_Language_To_QGenAda();
void Set_Language_To_QGenC();
void Set_Language_To_Scade();
void Set_Language_To_Rhapsody();
void Set_Language_To_RTDS();
void Set_Language_To_C();
void Set_Language_To_Other();
void Set_Language_To_Simulink();
void Set_Language_To_SDL();
void Set_Language_To_MicroPython();
void Set_ASN1_BasicType_Unknown();
void Set_ASN1_BasicType_OctetString();
void Set_ASN1_BasicType_Choice();
void Set_ASN1_BasicType_String();
void Set_ASN1_BasicType_Real();
void Set_ASN1_BasicType_Boolean();
void Set_ASN1_BasicType_Integer();
void Set_ASN1_BasicType_SetOf();
void Set_ASN1_BasicType_Set();
void Set_ASN1_BasicType_Enumerated();
void Set_ASN1_BasicType_SequenceOf();
void Set_ASN1_BasicType_Sequence();
void Set_UPER_Encoding();
void Set_Native_Encoding();
void Set_Zipfile (char *file);
void Set_Root_Node(char *name);
void Set_PolyorbHI_C();
void Set_Instance_Of(char *component);
void Set_Is_Component_Type();
System *get_system_ast();
void Delete_System_AST();
void C_Init();
void New_Connection(char *src_system,
                    char *src_port,
                    char *bus,
                    char *dst_system,
                    char *dst_port);
void End_Connection();
Connection *Get_Connection();
char *getASN1DataView();
char *getDataViewPath();

/* 
  Debug functions
*/
void Print_Interface (Interface *i);
void Dump_Interfaces (Interface_list *l);

void Set_Interface_Queue_Size (const unsigned long long int);

#endif
