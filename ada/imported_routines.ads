--  *************************** buildsupport ****************************  --
--  (c) 2015-2020 European Space Agency - maxime.perrotin@esa.int
--  LGPL license, see LICENSE file

with Ocarina.Types;
with Interfaces.C;

package Imported_Routines is
   use Interfaces.C;

   procedure C_Set_OutDir (Dir : char_array);
   procedure C_Set_Stack  (Val : char_array);
   procedure C_Set_Timer_Resolution  (Val : char_array);
   procedure C_New_APLC   (Arg : char_array);
   procedure C_New_FV     (Arg : char_array; CS : char_array);

   procedure C_Set_PolyORBHI_C;

   procedure C_Add_PI (Arg : char_array);

   procedure C_Add_RI (Arg : char_array;
                       DistFV : char_array;
                       DistName : char_array);

   procedure C_Set_Property (Name    : char_array;
                             Val     : char_array);

   procedure C_Set_Distant_APLC (Arg : char_array);
   procedure C_End_IF;
   procedure C_End_FV;

   procedure C_Set_Root_Node (Arg : char_array);

   procedure C_New_Process (Arg           : char_array;
                            Id            : char_array;
                            Node_Name     : char_array;
                            Coverage      : Integer);

   procedure C_New_Processor (Name           : char_array;
                              Classifier     : char_array;
                              Platform       : char_array;
                              EnvVars        : char_array;
                              CFflags        : char_array;
                              LdFlags        : char_array);

   procedure C_New_Bus (Name           : char_array;
                        Classifier     : char_array);

   procedure C_New_Device (Name                         : char_array;
                           Classifier                   : char_array;
                           Associated_Processor         : char_array;
                           Configuration                : char_array;
                           Accessed_Bus                 : char_array;
                           Access_Port                  : char_array;
                           Asn1_Filename                : char_array;
                           Asn1_Typename                : char_array;
                           Asn1_Modulename              : char_array);

   procedure C_New_Connection (Src_System          : char_array;
                               Src_Port            : char_array;
                               Bus                 : char_array;
                               Dst_System          : char_array;
                               Dst_Port            : char_array);

   procedure C_Add_Binding (Arg : char_array);
   procedure C_End_Process;
   procedure C_End_Bus;
   procedure C_End_Device;
   procedure C_End_Connection;
   procedure C_Add_In_Param
     (name     : char_array;
      partype  : char_array;
      module   : char_array;
      filename : char_array);
   procedure C_Add_Out_Param
     (name     : char_array;
      partype  : char_array;
      module   : char_array;
      filename : char_array);
   procedure C_Add_Package (Name : char_array);
   procedure C_Set_Compute_Time
     (Lower_Bound    : Ocarina.Types.Unsigned_Long_Long;
      Lower_Unit     : char_array;
      Upper_Bound    : Ocarina.Types.Unsigned_Long_Long;
      Upper_Unit     : char_array);
   procedure C_Set_Context_Variable
     (varName : char_array;
      varType : char_array;
      varVal  : char_array;
      varMod  : char_array;
      varFile : char_array;
      fullName : char_array);
   procedure C_Set_Period (Period : Ocarina.Types.Unsigned_Long_Long);
   procedure C_Set_Interface_Queue_Size
       (Size : Ocarina.Types.Unsigned_Long_Long);
   procedure C_Set_Glue;
   procedure C_Set_SMP2;
   procedure C_Set_Interfaceview (Name : char_array);
   procedure C_Set_Dataview (Name : char_array);
   procedure C_Set_Zipfile (Name : char_array);
   procedure C_Set_Gateway;
   procedure C_Keep_case;
   procedure C_Set_Test;
   procedure C_Set_Future;
   procedure C_Set_OnlyCV;
   procedure C_Set_AADLV2;
   procedure C_Set_Language_To_SDL;
   procedure C_Set_Language_To_Simulink;
   procedure C_Set_Language_To_Other;
   procedure C_Set_Language_To_C;
   procedure C_Set_Language_To_QGenAda;
   procedure C_Set_Language_To_QGenC;
   procedure C_Set_Language_To_CPP;
   procedure C_Set_Language_To_VDM;
   procedure C_Set_Language_To_OpenGEODE;
   procedure C_Set_Language_To_BlackBox_Device;
   procedure C_Set_Language_To_RTDS;
   procedure C_Set_Language_To_Rhapsody;
   procedure C_Set_Language_To_Scade;
   procedure C_Set_Language_To_Ada;
   procedure C_Set_Language_To_GUI;
   procedure C_Set_Language_To_VHDL_BRAVE;
   procedure C_Set_Language_To_VHDL;
   procedure C_Set_Language_To_System_C;
   procedure C_Set_Language_To_MicroPython;
   procedure C_Set_Native_Encoding;
   procedure C_Set_UPER_Encoding;
   procedure C_Set_ACN_Encoding;
   procedure C_Set_Sync_IF;
   procedure C_Set_ASync_IF;
   procedure C_Set_Unknown_IF;
   procedure C_Set_Cyclic_IF;
   procedure C_Set_Sporadic_IF;
   procedure C_Set_Variator_IF;
   procedure C_Set_Protected_IF;
   procedure C_Set_Unprotected_IF;
   procedure C_Set_UndefinedKind_IF;
   procedure C_Init;
   procedure C_End;
   procedure C_Set_ASN1_BasicType_Sequence;
   procedure C_Set_ASN1_BasicType_SequenceOf;
   procedure C_Set_ASN1_BasicType_Enumerated;
   procedure C_Set_ASN1_BasicType_Set;
   procedure C_Set_ASN1_BasicType_SetOf;
   procedure C_Set_ASN1_BasicType_Integer;
   procedure C_Set_ASN1_BasicType_Boolean;
   procedure C_Set_ASN1_BasicType_Real;
   procedure C_Set_ASN1_BasicType_Choice;
   procedure C_Set_ASN1_BasicType_String;
   procedure C_Set_ASN1_BasicType_Unknown;
   procedure C_Set_ASN1_BasicType_OctetString;
   procedure C_Set_Debug_Messages;
   procedure C_New_Drivers_Section;
   procedure C_End_Drivers_Section;
   procedure C_Set_Instance_Of (Component : char_array);
   procedure C_Set_Is_Component_Type;

private
   pragma Import (C, C_Set_Instance_Of, "Set_Instance_Of");
   pragma Import (C, C_Set_Is_Component_Type, "Set_Is_Component_Type");
   pragma Import (C, C_New_Drivers_Section, "New_Drivers_Section");
   pragma Import (C, C_End_Drivers_Section, "End_Drivers_Section");
   pragma Import (C, C_Set_PolyORBHI_C, "Set_PolyorbHI_C");
   pragma Import (C, C_Set_Root_Node, "Set_Root_Node");
   pragma Import (C, C_New_Process, "New_Process");
   pragma Import (C, C_New_Connection, "New_Connection");
   pragma Import (C, C_New_Processor, "New_Processor");
   pragma Import (C, C_New_Bus, "New_Bus");
   pragma Import (C, C_New_Device, "New_Device");
   pragma Import (C, C_Add_Binding, "Add_Binding");
   pragma Import (C, C_End_Process, "End_Process");
   pragma Import (C, C_End_Bus, "End_Bus");
   pragma Import (C, C_End_Device, "End_Device");
   pragma Import (C, C_End_Connection, "End_Connection");
   pragma Import (C, C_Init, "C_Init");
   pragma Import (C, C_End, "C_End");
   pragma Import (C, C_Set_OutDir, "Set_OutDir");
   pragma Import (C, C_Set_Interfaceview, "Set_Interfaceview");
   pragma Import (C, C_Set_Dataview, "Set_Dataview");
   pragma Import (C, C_Set_Stack, "Set_Stack");
   pragma Import (C, C_Set_Timer_Resolution, "Set_Timer_Resolution");
   pragma Import (C, C_New_APLC, "New_APLC");
   pragma Import (C, C_New_FV, "New_FV");
   pragma Import (C, C_Add_PI, "Add_PI");
   pragma Import (C, C_Add_RI, "Add_RI");
   pragma Import (C, C_Set_Property, "Set_Property");
   pragma Import (C, C_Set_Distant_APLC, "Set_Distant_APLC");
   pragma Import (C, C_End_IF, "End_IF");
   pragma Import (C, C_End_FV, "End_FV");
   pragma Import (C, C_Add_In_Param, "Add_In_Param");
   pragma Import (C, C_Add_Out_Param, "Add_Out_Param");
   pragma Import (C, C_Set_Glue, "Set_Glue");
   pragma Import (C, C_Set_SMP2, "Set_SMP2");
   pragma Import (C, C_Set_Gateway, "Set_Gateway");
   pragma Import (C, C_Keep_case, "Set_keep_case");
   pragma Import (C, C_Set_Test, "Set_Test");
   pragma Import (C, C_Set_Future, "Set_Future");
   pragma Import (C, C_Set_OnlyCV, "Set_OnlyCV");
   pragma Import (C, C_Set_AADLV2, "Set_AADLV2");
   pragma Import (C, C_Set_Language_To_SDL, "Set_Language_To_SDL");
   pragma Import (C, C_Set_Language_To_Simulink, "Set_Language_To_Simulink");
   pragma Import (C, C_Set_Language_To_Other, "Set_Language_To_Other");
   pragma Import (C, C_Set_Language_To_C, "Set_Language_To_C");
   pragma Import (C, C_Set_Language_To_CPP, "Set_Language_To_CPP");
   pragma Import (C, C_Set_Language_To_VDM, "Set_Language_To_VDM");
   pragma Import (C, C_Set_Language_To_OpenGEODE, "Set_Language_To_SDL");
   pragma Import (C, C_Set_Language_To_BlackBox_Device,
     "Set_Language_To_BlackBox_Device");
   pragma Import (C, C_Set_Language_To_RTDS, "Set_Language_To_RTDS");
   pragma Import (C, C_Set_Language_To_Rhapsody, "Set_Language_To_Rhapsody");
   pragma Import (C, C_Set_Language_To_Ada, "Set_Language_To_Ada");
   pragma Import (C, C_Set_Language_To_QGenAda, "Set_Language_To_QGenAda");
   pragma Import (C, C_Set_Language_To_QGenC, "Set_Language_To_QGenC");
   pragma Import (C, C_Set_Language_To_Scade, "Set_Language_To_Scade");
   pragma Import (C, C_Set_Language_To_GUI, "Set_Language_To_GUI");
   pragma Import (C, C_Set_Language_To_VHDL_BRAVE,
                  "Set_Language_To_VHDL_BRAVE");
   pragma Import (C, C_Set_Language_To_VHDL, "Set_Language_To_VHDL");
   pragma Import (C, C_Set_Language_To_System_C, "Set_Language_To_System_C");
   pragma Import (C, C_Set_Language_To_MicroPython,
     "Set_Language_To_MicroPython");
   pragma Import (C, C_Set_UPER_Encoding, "Set_UPER_Encoding");
   pragma Import (C, C_Set_ACN_Encoding, "Set_ACN_Encoding");
   pragma Import (C, C_Set_Native_Encoding, "Set_Native_Encoding");
   pragma Import (C, C_Set_Sync_IF, "Set_Sync_IF");
   pragma Import (C, C_Set_ASync_IF, "Set_ASync_IF");
   pragma Import (C, C_Set_Unknown_IF, "Set_Unknown_IF");
   pragma Import (C, C_Set_Cyclic_IF, "Set_Cyclic_IF");
   pragma Import (C, C_Set_Sporadic_IF, "Set_Sporadic_IF");
   pragma Import (C, C_Set_Variator_IF, "Set_Variator_IF");
   pragma Import (C, C_Set_Protected_IF, "Set_Protected_IF");
   pragma Import (C, C_Set_Unprotected_IF, "Set_Unprotected_IF");
   pragma Import (C, C_Set_UndefinedKind_IF, "Set_UndefinedKind_IF");
   pragma Import (C, C_Set_Compute_Time, "Set_Compute_Time");
   pragma Import (C, C_Set_Period, "Set_Period");
   pragma Import (C, C_Set_Interface_Queue_Size, "Set_Interface_Queue_Size");
   pragma Import (C, C_Set_Context_Variable, "Set_Context_Variable");
   pragma Import (C, C_Set_Debug_Messages, "Set_Debug_Messages");
   pragma Import (C, C_Set_Zipfile, "Set_Zipfile");
   pragma Import (C, C_Set_ASN1_BasicType_Sequence,
                  "Set_ASN1_BasicType_Sequence");
   pragma Import (C, C_Set_ASN1_BasicType_SequenceOf,
                  "Set_ASN1_BasicType_SequenceOf");
   pragma Import (C, C_Set_ASN1_BasicType_Enumerated,
                  "Set_ASN1_BasicType_Enumerated");
   pragma Import (C, C_Set_ASN1_BasicType_Set,
                  "Set_ASN1_BasicType_Set");
   pragma Import (C, C_Set_ASN1_BasicType_SetOf,
                  "Set_ASN1_BasicType_SetOf");
   pragma Import (C, C_Set_ASN1_BasicType_Integer,
                  "Set_ASN1_BasicType_Integer");
   pragma Import (C, C_Set_ASN1_BasicType_Boolean,
                  "Set_ASN1_BasicType_Boolean");
   pragma Import (C, C_Add_Package,
                  "Add_Package");
   pragma Import (C, C_Set_ASN1_BasicType_Real, "Set_ASN1_BasicType_Real");
   pragma Import (C, C_Set_ASN1_BasicType_Choice, "Set_ASN1_BasicType_Choice");
   pragma Import (C, C_Set_ASN1_BasicType_String, "Set_ASN1_BasicType_String");
   pragma Import (C, C_Set_ASN1_BasicType_Unknown,
                  "Set_ASN1_BasicType_Unknown");
   pragma Import (C, C_Set_ASN1_BasicType_OctetString,
                  "Set_ASN1_BasicType_OctetString");

end Imported_Routines;
