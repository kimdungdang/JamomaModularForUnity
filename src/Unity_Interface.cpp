#include "Unity_Interface.h"
/*--------------------------------------------------------------------------------------------*/
/*-Convert NSPValue to boolean                                                               -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
bool NspToBool(NSPValue* val)
{
	if(val != NULL)
	{
		bool ret;
		val->get(0, ret);
		return ret;
	}
	return false;
}
/*--------------------------------------------------------------------------------------------*/
/*-Convert NSPValue to boolean array                                                         -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
byte_bool* NspToBoolList(NSPValue* val)
{
	if(val != NULL)
	{
		int size = val->getSize();
		byte_bool* ret = new byte_bool[size];
		gAllocated++;
		bool buf;
		for(int i = 0; i < size; i++)
		{
			val->get(i, buf);
			if(buf)
				ret[i] = 1;
			else
				ret[i] = 0;
		}  
		return ret;
	}
	return false;
}
/*--------------------------------------------------------------------------------------------*/
/*-Convert NSPValue to char array                                                            -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
char* NspToCharArray(NSPValue* val)
{
	if(val != NULL)
	{
		NSPSymbol symbol;
		val->get(0, &symbol);
		char* str = new char[strlen(symbol->getCString()) + 1];
		gAllocated++;
		sprintf(str, "%s", symbol->getCString());
		return str;
	}
	return NULL;
}
/*--------------------------------------------------------------------------------------------*/
/*-Convert NSPValue to array of char array                                                   -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
char** NspToCharArrayArray(NSPValue* val)
{
	if(val != NULL)
	{
		int size = val->getSize();
		NSPSymbol symbol;
		char** ret = new char*[size];
		for(int i = 0; i < size; i++)
		{
			val->get(i, &symbol);
			ret[i] = new char[strlen(symbol->getCString()) + 1];
			gAllocated++;
			sprintf(ret[i], "%s", symbol->getCString());
		}
		return ret;
	}
	return NULL;
}
/*--------------------------------------------------------------------------------------------*/
/*-Convert NSPValue to float                                                                 -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
float NspToFloat(NSPValue* val)
{
	if(val != NULL)
	{
		float ret;
		val->get(0, ret);
		return ret;
	}
	return 0.0f;
}
/*--------------------------------------------------------------------------------------------*/
/*-Convert NSPValue to floats array                                                          -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
float* NspToFloatList(NSPValue* val)
{
	if(val != NULL)
	{
		int size = val->getSize();
		float* ret = new float[size];
		gAllocated++;
		val->getArray(ret, size);  
		return ret;
	}
	return NULL;
}
/*--------------------------------------------------------------------------------------------*/
/*-Convert NSPValue to int                                                                   -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
long int NspToInt(NSPValue* val)
{
	if(val != NULL)
	{
		long int ret;
		val->get(0, ret);
		return ret;
	}
	return 0;
}
/*--------------------------------------------------------------------------------------------*/
/*-Convert NSPValue to integers array                                                        -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
long int* NspToIntList(NSPValue* val)
{
	if(val != NULL)
	{
		int size = val->getSize();
		long int* ret = new long int[size];
		gAllocated++;
		val->getArray(ret, size);  
		return ret;
	}
	return NULL;
}
/*--------------------------------------------------------------------------------------------*/
/*-Convert bool to NSPValue                                                                  -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
NSPValue* BoolToNsp(bool val)
{
	gAllocated++;
	return new NSPValue(val);
}
/*--------------------------------------------------------------------------------------------*/
/*-Convert bool array to NSPValue                                                            -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
NSPValue* BoolArrayToNsp(byte_bool* val, int size)
{
	if(val != NULL && size > 1)
	{
		bool b = (val[0] == 1) ? true : false;
		NSPValue* value = new NSPValue(b);
		gAllocated++;
		for(int i = 1; i < size; i++)
		{
			b = (val[i] == 1) ? true : false;
			value->append(b);
		}
		return value;
	}
	return NULL;
}
/*--------------------------------------------------------------------------------------------*/
/*-Convert char array to NSPValue                                                            -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
NSPValue* CharArrayToNsp(char* val)
{
	if(val != NULL)
	{
		gAllocated++;
		return new NSPValue(TT(val));
	}
	return NULL;
}
/*--------------------------------------------------------------------------------------------*/
/*-Convert array of char array to NSPValue                                                   -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
NSPValue* CharArrayArrayToNsp(char** val, int size)
{
	if(val != NULL && size > 1)
	{
		NSPValue* value = new NSPValue(TT(val[0]));
		gAllocated++;
		for(int i = 1; i < size; i++)
		{
			value->append(TT(val[i]));	
		}
		return value;
	}
	return NULL;
}
/*--------------------------------------------------------------------------------------------*/
/*-Convert float to NSPValue                                                                 -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
NSPValue* FloatToNsp(float val)
{
	gAllocated++;
	return new NSPValue(val);
}
/*--------------------------------------------------------------------------------------------*/
/*-Convert floats array to NSPValue                                                          -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
NSPValue* FloatArrayToNsp(float* val, int size)
{
	if(val != NULL && size > 1)
	{
		NSPValue* value = new NSPValue(val[0]);
		gAllocated++;
		for(int i = 1; i < size; i++)
			value->append(val[i]);
		return value;
	}
	return NULL;
}
/*--------------------------------------------------------------------------------------------*/
/*-Convert int to NSPValue                                                                   -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
NSPValue* IntToNsp(int val)
{
	gAllocated++;
	return new NSPValue(val);
}
/*--------------------------------------------------------------------------------------------*/
/*-Convert integers array to NSPValue                                                        -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
NSPValue* IntArrayToNsp(int* val, int size)
{
	if(val != NULL && size > 1)
	{
		NSPValue* value = new NSPValue(val[0]);
		gAllocated++;
		for(int i = 1; i < size; i++)
			value->append(val[i]);
		return value;
	}
	return NULL;
}
/*--------------------------------------------------------------------------------------------*/
/*-Create empty NSPValue                                                                     -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
NSPValue* NewNsp()
{
	gAllocated++;
	return new NSPValue();
}
/*--------------------------------------------------------------------------------------------*/
/*-Create empty NSPValue                                                                     -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
int GetNspSize(NSPValue* val)
{
	if(val != NULL)
	{
		return val->getSize();
	}
	return 0;
}
/*--------------------------------------------------------------------------------------------*/
/*-Free a bool array                                                                         -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
void FreeBoolArray(byte_bool* val)
{
	if(val != NULL)
	{
		delete[] val;
		gAllocated--;
	}
}
/*--------------------------------------------------------------------------------------------*/
/*-Free a char array                                                                         -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
void FreeCharArray(char* val)
{
	if(val != NULL)
	{
		delete[] val;
		gAllocated--;
	}
}
/*--------------------------------------------------------------------------------------------*/
/*-Free array of char array                                                                  -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
void FreeCharArrayArray(char** val, int size)
{
	if(val != NULL)
	{
		for(int i = 0; i < size; i++)
		{
			delete[] val[i];
			gAllocated--;
		}
		delete[] val;
	}
}
/*--------------------------------------------------------------------------------------------*/
/*-Free a floats array                                                                       -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
void FreeFloatArray(float* val)
{
	if(val != NULL)
	{
		delete[] val;
		gAllocated--;
	}
}
/*--------------------------------------------------------------------------------------------*/
/*-Free an integers array                                                                    -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
void FreeIntArray(int* val)
{
	if(val != NULL)
	{
		delete[] val;
		gAllocated--;
	}
}
/*--------------------------------------------------------------------------------------------*/
/*-Free a NSPValue in Dll                                                                    -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
void FreeNsp(NSPValue* val)
{
	if(val != NULL)
	{
		delete val;
		gAllocated--;
	}
}
/*--------------------------------------------------------------------------------------------*/
/*-Init everything before creating and using namespaces                                      -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
void InitInterface()
{
	gNamespace = NULL;	
	gStringPointer = &gStringBuffer[0];
	gAllocated = 0;
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to Namespace()                                                                    -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
int CreateNamespace(char* appName, char* appVersion, char* appCreator)
{
	if(gNamespace == NULL)
	{
		gNamespace = new Namespace(appName, appVersion, appCreator);
		return NSP_NO_ERROR;
	}
	else
		return NSP_CS_WRAP_CREATE_ERROR;
	
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to ~Namespace()                                                                   -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
void DeleteNamespace()
{
	if(gNamespace != NULL)
	{
		delete gNamespace;
		gNamespace = NULL;
	}
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to namespaceInit()                                                                -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
int InitNamespace(bool useDeviceManager)
{
	if(gNamespace != NULL)
		return gNamespace->namespaceInit(useDeviceManager);
	else
		return NSP_CS_WRAP_UNDEF_ERROR;
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to namespaceFree()                                                                -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
int FreeNamespace()
{
	if(gNamespace != NULL)
		return gNamespace->namespaceFree();
	else
		return NSP_CS_WRAP_UNDEF_ERROR;
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to setAppName()                                                                   -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
void SetAppName(char* appName)
{
	if(gNamespace != NULL)
		gNamespace->setAppName(appName);
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to setAppVersion()                                                                -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
void SetAppVersion(char* appVersion)
{
	if(gNamespace!= NULL)
		gNamespace->setAppVersion(appVersion);
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to setCreatorName()                                                               -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
void SetAppCreator(char* appCreator)
{
	if(gNamespace != NULL)
		gNamespace->setCreatorName(appCreator);
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to getAppName()                                                                   -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
char* GetAppName()
{
	if(gNamespace != NULL)
		return ToCs(gNamespace->getAppName());
	else
		return ToCs(NSP_CS_WRAP_UNDEF_STR);
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to getAppVersion()                                                                -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
char* GetAppVersion()
{
	if(gNamespace != NULL)
		return ToCs(gNamespace->getAppVersion());
	else
		return ToCs(NSP_CS_WRAP_UNDEF_STR);
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to getCreatorName()                                                               -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
char* GetAppCreator()
{
	if(gNamespace != NULL)
		return ToCs(gNamespace->getCreatorName());
	else
		return ToCs(NSP_CS_WRAP_UNDEF_STR);
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to namespaceParameterCreate()                                                     -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
int CreateParameter(char* addr, int instNum)
{
	if(gNamespace != NULL)
	{
		return gNamespace->namespaceParameterCreate(addr);	
	}
	return NSP_CS_WRAP_UNDEF_ERROR;
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to namespaceAttributeSet();                                                       -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
int SetParameter(char* addr, int inst, NSPIAttr attr, NSPValue* val)
{
	if(addr == NULL || attr >= Attr_Count || val == NULL)
		return NSP_CS_WRAP_ARGS_ERROR;
	
	//Get attribute
	NSPSymbol attribute;
	switch(attr)
	{
		case Attr_Val:
			attribute = NSPAttr_VAL;                      
			break;
		case Attr_Default:
			attribute = NSPAttr_DEFAULT;                  
			break;
		case Attr_Type:
			attribute = NSPAttr_TYPE;                     
			break;
		case Attr_Range:
			attribute = NSPAttr_RANGE;                    
			break;
		case Attr_RangeClipMode:
			attribute = NSPAttr_RANGECLIPMODE;            
			break;
		case Attr_Step:
			attribute = NSPAttr_STEP;                     
			break;
		case Attr_Priority:
			attribute = NSPAttr_PRIORITY;                 
			break;
		case Attr_Desccription:
			attribute = NSPAttr_DESCRIPTION;              
			break;
		case Attr_Repetition:
			attribute = NSPAttr_REPETITION;               
			break;
		case Attr_ReadOnly:
			attribute = NSPAttr_READONLY;				  
			break;
		case Attr_Dynamic:
			attribute = NSPAttr_DYNAMIC_INSTANCE_ENABLED; 
			break;
		case Attr_InstanceBounds:
			attribute = NSPAttr_DYNAMIC_INSTANCE_BOUNDS;  
			break;
	}

	NSPValue value;
	if(attribute == NSPAttr_TYPE)
	{
		NSPSymbol s;
		val->get(0, &s);
		const char* str = s->getCString();
		if(strcmp(str, "array") == 0)
			value = NSPType_ARRAY;
		else if(strcmp(str, "bool") == 0)
			value = NSPType_BOOL;
		else if(strcmp(str, "float") == 0)
			value = NSPType_FLOAT;
		else if(strcmp(str, "int") == 0)
			value = NSPType_INT;
		else if(strcmp(str, "string") == 0)
			value = NSPType_STRING;
	}
	else if(attribute == NSPAttr_RANGE)
	{
		if(val->getSize() != 2)
			return NSP_CS_WRAP_ARGS_ERROR;
		float ftab[2];
		val->getArray(&ftab[0], 2);
		value = NSPValue(ftab[0], ftab[1]);
	}
	else
		value = *val;
	
	return gNamespace->namespaceAttributeSet(addr, attribute, value, inst); 
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to namespaceAttributeGet()                                                        -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
int GetParameter(char* addr, int inst, NSPIAttr attr, NSPValue& val)
{
	if(addr == NULL || attr >= Attr_Count)
		return NSP_CS_WRAP_ARGS_ERROR;
	
	//Get attribute
	NSPSymbol attribute;
	switch(attr)
	{
		case Attr_Val:
			attribute = NSPAttr_VAL;                      
			break;
		case Attr_Default:
			attribute = NSPAttr_DEFAULT;                  
			break;
		case Attr_Type:
			attribute = NSPAttr_TYPE;                     
			break;
		case Attr_Range:
			attribute = NSPAttr_RANGE;                    
			break;
		case Attr_RangeClipMode:
			attribute = NSPAttr_RANGECLIPMODE;            
			break;
		case Attr_Step:
			attribute = NSPAttr_STEP;                     
			break;
		case Attr_Priority:
			attribute = NSPAttr_PRIORITY;                 
			break;
		case Attr_Desccription:
			attribute = NSPAttr_DESCRIPTION;              
			break;
		case Attr_Repetition:
			attribute = NSPAttr_REPETITION;               
			break;
		case Attr_ReadOnly:
			attribute = NSPAttr_READONLY;				  
			break;
		case Attr_Dynamic:
			attribute = NSPAttr_DYNAMIC_INSTANCE_ENABLED;
			break;
		case Attr_InstanceBounds:
			attribute = NSPAttr_DYNAMIC_INSTANCE_BOUNDS; 
			break;
	}

	return gNamespace->namespaceAttributeGet(addr, attribute, val, inst); 
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to namespaceObserverCreate()                                                      -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
int CreateObserver(char* addr, int inst,  NSPIAttr attr, void (*val)(void*, NSPValue&), void (*add)(void*, NSPValue&))
{
	if(addr == NULL || attr >= Attr_Count || val == NULL || add == NULL)
		return NSP_CS_WRAP_ARGS_ERROR;
	
	//Get attribute
	NSPSymbol attribute;
	switch(attr)
	{
		case Attr_Val:
			attribute = NSPAttr_VAL;                      
			break;
		case Attr_Default:
			attribute = NSPAttr_DEFAULT;                  
			break;
		case Attr_Type:
			attribute = NSPAttr_TYPE;                     
			break;
		case Attr_Range:
			attribute = NSPAttr_RANGE;                    
			break;
		case Attr_RangeClipMode:
			attribute = NSPAttr_RANGECLIPMODE;            
			break;
		case Attr_Step:
			attribute = NSPAttr_STEP;                     
			break;
		case Attr_Priority:
			attribute = NSPAttr_PRIORITY;                 
			break;
		case Attr_Desccription:
			attribute = NSPAttr_DESCRIPTION;              
			break;
		case Attr_Repetition:
			attribute = NSPAttr_REPETITION;               
			break;
		case Attr_ReadOnly:
			attribute = NSPAttr_READONLY;				  
			break;
		case Attr_Dynamic:
			attribute = NSPAttr_DYNAMIC_INSTANCE_ENABLED;
			break;
		case Attr_InstanceBounds:
			attribute = NSPAttr_DYNAMIC_INSTANCE_BOUNDS; 
			break;
	}

	return gNamespace->namespaceObserverCreate(addr, attribute, NULL, val, add, inst);
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to namespaceValueSend()                                                           -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
int SendValue(char* addr, int inst, NSPIAttr attr, NSPValue* val)
{
	if(addr == NULL || attr >= Attr_Count || val == NULL)
		return NSP_CS_WRAP_ARGS_ERROR;

	
	//Get attribute
	NSPSymbol attribute;
	switch(attr)
	{
		case Attr_Val:
			attribute = NSPAttr_VAL;                      
			break;
		case Attr_Default:
			attribute = NSPAttr_DEFAULT;                  
			break;
		case Attr_Type:
			attribute = NSPAttr_TYPE;                     
			break;
		case Attr_Range:
			attribute = NSPAttr_RANGE;                    
			break;
		case Attr_RangeClipMode:
			attribute = NSPAttr_RANGECLIPMODE;            
			break;
		case Attr_Step:
			attribute = NSPAttr_STEP;                     
			break;
		case Attr_Priority:
			attribute = NSPAttr_PRIORITY;                 
			break;
		case Attr_Desccription:
			attribute = NSPAttr_DESCRIPTION;              
			break;
		case Attr_Repetition:
			attribute = NSPAttr_REPETITION;               
			break;
		case Attr_ReadOnly:
			attribute = NSPAttr_READONLY;				  
			break;
		case Attr_Dynamic:
			attribute = NSPAttr_DYNAMIC_INSTANCE_ENABLED;
			break;
		case Attr_InstanceBounds:
			attribute = NSPAttr_DYNAMIC_INSTANCE_BOUNDS; 
			break;
	}

	return gNamespace->namespaceValueSend(addr, attribute, *val, inst);
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to namespaceSaveToXml()                                                           -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
int SaveToXml(char* fp)
{
	if(gNamespace != NULL)
		return gNamespace->namespaceSaveToXml(fp);
	return NSP_CS_WRAP_UNDEF_ERROR;
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to namespaceLoadFromXml()                                                         -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
int LoadFromXml(char* fp)
{
	if(fp == NULL)
		return NSP_CS_WRAP_ARGS_ERROR;
	if(gNamespace != NULL)
		return gNamespace->namespaceLoadFromXml(fp);
	return NSP_CS_WRAP_UNDEF_ERROR;
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to namespaceMappingLoadFromXml()                                                  -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
int MappingFromXml(char* fp)
{
	if(fp == NULL)
		return NSP_CS_WRAP_ARGS_ERROR;
	if(gNamespace != NULL)
		return gNamespace->namespaceMappingLoadFromXml(fp);
	return NSP_CS_WRAP_UNDEF_ERROR;
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to namespacePresetsLoadFromXml()                                                  -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
int PresetsFromXml(char* fp)
{
	if(fp == NULL)
		return NSP_CS_WRAP_ARGS_ERROR;
	if(gNamespace != NULL)
		return gNamespace->namespacePresetsLoadFromXml(fp);
	return NSP_CS_WRAP_UNDEF_ERROR;
}
/*--------------------------------------------------------------------------------------------*/
/*-Wrapper to namespacePresetCall()                                                          -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
int PresetCall(int num)
{
	if(gNamespace != NULL)
	{
		return gNamespace->namespacePresetCall(num);
	}
	return NSP_CS_WRAP_UNDEF_ERROR;
}
/*--------------------------------------------------------------------------------------------*/
/*-Display a message box if there are memory leaks                                           -*/
/*-Status : [OK]                                                                             -*/
/*--------------------------------------------------------------------------------------------*/
void CheckMemoryLeaks()
{
	if(gAllocated > 0)
		MessageBox(NULL, "Memory leaks detected.", "Error", MB_OK);
}