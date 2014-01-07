#ifndef UNITY_INTERFACE_H
#define UNITY_INTERFACE_H
//--------------------------------------------------------------------------------------------------//
// +API CONST DEFINITION                                                                            //
//--------------------------------------------------------------------------------------------------//
#ifdef UNITY_EXPORTS
#define UNITY_INTERFACE extern "C" __declspec(dllexport)
#else
#define UNITY_INTERFACE extern "C" __declspec(dllimport)
#endif
//--------------------------------------------------------------------------------------------------//
// +INCLUDES                                                                                        //
//--------------------------------------------------------------------------------------------------//
#include <stdio.h>
#include <windows.h>  
#include "Namespace.h"
//--------------------------------------------------------------------------------------------------//
// +MACROS DEFINITIONS                                                                              //
//--------------------------------------------------------------------------------------------------//
#define NSP_CS_WRAP_UNDEF_STR "Namespace is not defined"
#define NSP_CS_WRAP_CREATE_ERROR 9
#define NSP_CS_WRAP_UNDEF_ERROR 10
#define NSP_CS_WRAP_ARGS_ERROR 11
//--------------------------------------------------------------------------------------------------//
// +ENUMS                                                                                           //
//--------------------------------------------------------------------------------------------------//
enum NSPIAttr
{
	Attr_Val,
	Attr_Default,
	Attr_Type,
	Attr_Range, 
	Attr_RangeClipMode, 
	Attr_Step,
	Attr_Priority, 
	Attr_Desccription,  
	Attr_Repetition,    
	Attr_ReadOnly,    
	Attr_Dynamic,
	Attr_InstanceBounds,
	Attr_Count
};
//--------------------------------------------------------------------------------------------------//
// +TYPE DEFS                                                                                    //
//--------------------------------------------------------------------------------------------------//
typedef unsigned char byte_bool;
//--------------------------------------------------------------------------------------------------//
// +GLOBALS VARS                                                                                    //
//--------------------------------------------------------------------------------------------------//
static   Namespace*                      gNamespace;
static   char                            gStringBuffer[500];
static   char*                           gStringPointer;
static   unsigned int                    gAllocated;
//--------------------------------------------------------------------------------------------------//
// +UTILS                                                                                           //
//--------------------------------------------------------------------------------------------------//
char* ToCs (const char* str)   
{ 
	sprintf_s(gStringBuffer, "%s", str); 
	return gStringPointer; 
}
//--------------------------------------------------------------------------------------------------//
// +INTERFACE                                                                                       //
//--------------------------------------------------------------------------------------------------//
UNITY_INTERFACE   bool    	  NspToBool(NSPValue* val);
UNITY_INTERFACE   byte_bool*  NspToBoolList(NSPValue* val);
UNITY_INTERFACE   char*       NspToCharArray(NSPValue* val);
UNITY_INTERFACE   char**      NspToCharArrayArray(NSPValue* val);
UNITY_INTERFACE   float   	  NspToFloat(NSPValue* val);
UNITY_INTERFACE   float*   	  NspToFloatList(NSPValue* val);
UNITY_INTERFACE   long int    NspToInt(NSPValue* val);
UNITY_INTERFACE   long int*   NspToIntList(NSPValue* val);
UNITY_INTERFACE   NSPValue*   BoolToNsp(bool val);
UNITY_INTERFACE   NSPValue*   BoolArrayToNsp(byte_bool* val, int size);
UNITY_INTERFACE   NSPValue*   CharArrayToNsp(char* val);
UNITY_INTERFACE   NSPValue*   CharArrayArrayToNsp(char** val, int size);
UNITY_INTERFACE	  NSPValue*   FloatToNsp(float val);
UNITY_INTERFACE   NSPValue*   FloatArrayToNsp(float* val, int size);
UNITY_INTERFACE   NSPValue*   IntToNsp(int val);
UNITY_INTERFACE   NSPValue*   IntArrayToNsp(int* val, int size);
UNITY_INTERFACE   NSPValue*   NewNsp();
UNITY_INTERFACE   int         GetNspSize(NSPValue* val);
UNITY_INTERFACE   void        FreeBoolArray(byte_bool* val);
UNITY_INTERFACE   void        FreeCharArray(char* val);
UNITY_INTERFACE   void        FreeCharArrayArray(char** val, int size);
UNITY_INTERFACE   void        FreeFloatArray(float* val);
UNITY_INTERFACE   void        FreeIntArray(int* val);
UNITY_INTERFACE   void        FreeNsp(NSPValue* val);
UNITY_INTERFACE   void        InitInterface();
UNITY_INTERFACE   int         CreateNamespace(char* appName, char* appVersion, char* appCreator);
UNITY_INTERFACE   void        DeleteNamespace();
UNITY_INTERFACE   int         InitNamespace(bool useDeviceManager = false);
UNITY_INTERFACE   int         FreeNamespace();
UNITY_INTERFACE   void        SetAppName(char* appName);
UNITY_INTERFACE   void        SetAppVersion(char* appVersion);
UNITY_INTERFACE   void        SetAppCreator(char* appCreator);
UNITY_INTERFACE   char*       GetAppName();
UNITY_INTERFACE   char*       GetAppVersion();
UNITY_INTERFACE   char*       GetAppCreator();
UNITY_INTERFACE   int         CreateParameter(char* addr, int instNum);
UNITY_INTERFACE   int         SetParameter(char* addr, int inst, NSPIAttr attr, NSPValue* val);
UNITY_INTERFACE   int         GetParameter(char* addr, int inst, NSPIAttr attr, NSPValue& val);
UNITY_INTERFACE   int         CreateObserver(char* addr, int inst, NSPIAttr attr, void (*val)(void*, NSPValue&), void (*add)(void*, NSPValue&));
UNITY_INTERFACE   int         SendValue(char* addr, int inst, NSPIAttr attr, NSPValue* val);
UNITY_INTERFACE   int         SaveToXml(char* fp);
UNITY_INTERFACE   int         LoadFromXml(char* fp);
UNITY_INTERFACE   int         MappingFromXml(char* fp);
UNITY_INTERFACE   int         PresetsFromXml(char* fp);
UNITY_INTERFACE   int         PresetCall(int num);
UNITY_INTERFACE   void        CheckMemoryLeaks();
//TO DO: Remplacer tous les Array par des List dans les signatures 
#endif //UNITY_INTERFACE_H