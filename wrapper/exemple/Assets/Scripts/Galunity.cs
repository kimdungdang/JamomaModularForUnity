using UnityEngine;
using System.Collections;
using System;
using System.Runtime.InteropServices;

using NSPValue    = System.IntPtr;
using BoolArray   = System.IntPtr;
using FloatArray  = System.IntPtr;
using IntArray    = System.IntPtr;
using StringArray = System.IntPtr;
using CString     = System.IntPtr;
using CCallback   = System.IntPtr;

public class Galunity : MonoBehaviour 
{
	
	public enum NSPStatus : int 
	{
		NO_ERROR, 
		INIT_ERROR, 
		RELEASE_ERROR, 
		INVALID_APPNAME, 
		INVALID_ADDRESS, 
		INVALID_ATTRIBUTE,
		FILE_NOTFOUND,
		XMLPARSING_ERROR,
		XMLFORMAT_ERROR,
		CS_WRAP_CREATE_ERROR,
		CS_WRAP_UNDEF_ERROR,
		CS_WRAP_ARGS_ERROR
	};
	
	public enum NSPIAttr : int 
	{
		Val,           
		Default,       
		Type,          
		Range, 
		RangeClipMode, 
		Step,
		Priority, 
		Desccription,  
		Repetition,    
		ReadOnly,      
		Dynamic,       
		InstanceBounds,
	};
	
	[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
	public delegate void NspCallback(IntPtr nspBaton, NSPValue nspValue); 
	
	//=================//
	//= DLL FUNCTIONS =//
	//=================//

	[DllImport("Galunity")] 
	public static extern bool NspToBool(NSPValue val);
	
	[DllImport("Galunity")]
	private static extern BoolArray NspToBoolList(NSPValue val);
	
	[DllImport("Galunity")]
	private static extern CString NspToCharArray(NSPValue val);
	
	[DllImport("Galunity")]
	private static extern StringArray NspToCharArrayArray(NSPValue val);
	
	[DllImport("Galunity")]
	public static extern float NspToFloat(NSPValue val);
	
	[DllImport("Galunity")]
	private static extern FloatArray NspToFloatList(NSPValue val);
	
	[DllImport("Galunity")]
	public static extern int NspToInt(NSPValue val);
	
	[DllImport("Galunity")]
	private static extern IntArray NspToIntList(NSPValue val);
	
	[DllImport("Galunity")]
	public static extern NSPValue BoolToNsp(bool val);
	
	[DllImport("Galunity")]
	private static extern NSPValue BoolArrayToNsp(BoolArray val, int size);
	
	[DllImport("Galunity")]
	private static extern NSPValue CharArrayToNsp(CString val);
	
	[DllImport("Galunity")]
	private static extern NSPValue CharArrayArrayToNsp(StringArray val, int size);
	
	[DllImport("Galunity")]
	public static extern NSPValue FloatToNsp(float val);
		
	[DllImport("Galunity")]
	private static extern NSPValue FloatArrayToNsp(FloatArray val, int size);
	
	[DllImport("Galunity")]
	public static extern NSPValue IntToNsp(int val);
	
	[DllImport("Galunity")]
	private static extern NSPValue IntArrayToNsp(IntArray val, int size);
	
	[DllImport("Galunity")]
	public static extern NSPValue NewNsp();
	
	[DllImport("Galunity")]
	private static extern int GetNspSize(NSPValue val);
	
	[DllImport("Galunity")]
	public static extern void FreeBoolArray(BoolArray val);
	
	[DllImport("Galunity")]
	private static extern void FreeCharArray(CString val);
	
	[DllImport("Galunity")]
	private static extern void FreeCharArrayArray(StringArray val, int size);
	
	[DllImport("Galunity")]
	private static extern void FreeFloatArray(FloatArray val);
	
	[DllImport("Galunity")]
	private static extern void FreeIntArray(IntArray val);
	
	[DllImport("Galunity")]
	public static extern void FreeNsp(NSPValue val);
	
	[DllImport("Galunity")]
	public static extern void InitInterface();
	
	[DllImport("Galunity")]
	private static extern int CreateNamespace(CString appName, CString appVersion, CString appCreator);
	
	[DllImport("Galunity")]
	public static extern void DeleteNamespace();
	
	[DllImport("Galunity")]
	public static extern int InitNamespace(bool useDeviceManager);
	
	[DllImport("Galunity")]
	public static extern int FreeNamespace();
	
	[DllImport("Galunity")]
	private static extern void SetAppName(CString appName);
	
	[DllImport("Galunity")]
	private static extern void SetAppVersion(CString appVersion);
	
	[DllImport("Galunity")]
	private static extern void SetAppCreator(CString appCreator);
	
	[DllImport("Galunity")]
	private static extern CString GetAppName();
	
	[DllImport("Galunity")]
	private static extern CString GetAppVersion();
	
	[DllImport("Galunity")]
	private static extern CString GetAppCreator();
	
	[DllImport("Galunity")]
	private static extern int CreateParameter(CString addr, int instNum);
	
	[DllImport("Galunity")]
	private static extern int SetParameter(CString addr, int inst, NSPIAttr attr, NSPValue val);
	
	[DllImport("Galunity")]
	private static extern int GetParameter(CString addr, int inst, NSPIAttr attr, NSPValue val);
	
	[DllImport("Galunity")]
	private static extern int CreateObserver(CString addr, int inst, NSPIAttr attr, CCallback valc, CCallback addrc);
	
	[DllImport("Galunity")]
	private static extern int SendValue(CString addr, int inst, NSPIAttr attr, NSPValue val);
	
	[DllImport("Galunity")]
	private static extern int SaveToXml(CString fp);
	
	[DllImport("Galunity")]
	private static extern int LoadFromXml(CString fp);
	
	[DllImport("Galunity")]
	private static extern int MappingFromXml(CString fp);
	
	[DllImport("Galunity")]
	private static extern int PresetsFromXml(CString fp);
	
	[DllImport("Galunity")]
	public static extern int PresetCall(int num);

	[DllImport("Galunity")]
	public static extern void CheckMemoryLeaks();
	
	private static ArrayList m_Handles = new ArrayList();
	
	//=====================//
	//= UTILITY FUNCTIONS =//
	//=====================//
	
	private static CString ToCpp (string arg)
	{ 
		return Marshal.StringToHGlobalAnsi(arg); 
	}
	
	private static CCallback ToCpp (NspCallback arg) 
	{ 
		return Marshal.GetFunctionPointerForDelegate(arg); 
	}
	
	private static IntPtr ToCpp (object arg) 
	{ 
		GCHandle h = GCHandle.Alloc(arg, GCHandleType.Pinned);
		m_Handles.Add(h);
		return h.AddrOfPinnedObject(); 
	}
	
	private static string GetString(CString ptr)
	{
		return Marshal.PtrToStringAnsi(ptr);
	}
	
	private static void FreeHandles()
	{
		foreach(GCHandle handle in m_Handles)
		{
			handle.Free();
		}
		m_Handles.Clear();
	}
	
	//=====================//
	//= WRAPPER FUNCTIONS =//
	//=====================//
	
	
	public static bool[] NspToBoolArray(NSPValue nspValue)
	{
		int size = GetNspSize(nspValue);
		bool[] cs_array = new bool[size];
		byte[] buffer = new byte[size];
		BoolArray cpp_array = NspToBoolList(nspValue);
		Marshal.Copy(cpp_array, buffer, 0, size);
		FreeFloatArray(cpp_array);
		for(int i = 0; i < size; i++)
		{
			if(buffer[i] == 1)
				cs_array[i] = true;
			else
				cs_array[i] = false;
		}
		return cs_array;	
	}
	
	public static string NspToString(NSPValue nspValue)
	{
		string cs_string;
		CString cpp_string = NspToCharArray(nspValue);
		cs_string = Marshal.PtrToStringAnsi(cpp_string);
		FreeCharArray(cpp_string);
		return cs_string;
	}
	
	public static string[] NspToStringArray(NSPValue nspValue)
	{
		int size = GetNspSize(nspValue);
		string[] cs_array = new string[size];
		CString[] buffer = new CString[size];
		StringArray cpp_array = NspToCharArrayArray(nspValue);
		Marshal.Copy(cpp_array, buffer, 0, size);
		for(int i = 0; i < size; i++)
		{
			cs_array[i] = Marshal.PtrToStringAnsi(buffer[i]);	
		}
		FreeCharArrayArray(cpp_array, size);
		return cs_array;
	}
	
	public static float[] NspToFloatArray(NSPValue nspValue)
	{
		int size = GetNspSize(nspValue);
		float[] cs_array = new float[size];
		FloatArray cpp_array = NspToFloatList(nspValue);
		Marshal.Copy(cpp_array, cs_array, 0, size);
		FreeFloatArray(cpp_array);
		return cs_array;
	}
	
	public static int[] NspToIntArray(NSPValue nspValue)
	{
		int size = GetNspSize(nspValue);
		int[] cs_array = new int[size];
		IntArray cpp_array = NspToIntList(nspValue);
		Marshal.Copy(cpp_array, cs_array, 0, size);
		FreeIntArray(cpp_array);
		return cs_array;
	}
	
	public static NSPValue BoolArrayToNsp(bool[] array)
	{
		int size = array.Length;
		byte[] buffer = new byte[size];
		for(int i = 0; i < size; i++)
		{
			if(array[i])
				buffer[i] = 1;
			else
				buffer[i] = 0;
		}
		NSPValue ret = BoolArrayToNsp(ToCpp(buffer), size);
		FreeHandles();
		return ret;
	}
	
	public static NSPValue StringToNsp(string str)
	{
		return CharArrayToNsp(ToCpp(str));
	}
	
	public static NSPValue StringArrayToNsp(string[] array)
	{
		int size = array.Length;
		IntPtr[] buffer = new IntPtr[size];
		for(int i = 0; i < size; i++)
		{
			buffer[i] = ToCpp(array[i]);	
		}
		NSPValue ret = CharArrayArrayToNsp(ToCpp(buffer), size);
		FreeHandles();
		return ret;
	}
	
	public static NSPValue FloatArrayToNsp(float[] array)
	{
		int size = array.Length;
		NSPValue ret = FloatArrayToNsp(ToCpp(array), size);
		FreeHandles();
		return ret;
	}
	
	public static NSPValue IntArrayToNsp(int[] array)
	{
		int size = array.Length;
		NSPValue ret = IntArrayToNsp(ToCpp(array), size);
		FreeHandles();
		return ret;
	}
	
	public static int CreateNamespace(string appName, string appVersion, string appCreator)
	{
		return CreateNamespace(ToCpp(appName), ToCpp(appVersion), ToCpp(appCreator));
	}
	
	public static void SetAppName(string appName)
	{
		SetAppName(ToCpp(appName));	
	}
	
	public static void SetAppVersion(string appVersion)
	{
		SetAppVersion(ToCpp(appVersion));
	}
	
	public static void SetAppCreator(string appCreator)
	{
		SetAppCreator(ToCpp(appCreator));
	}
	
	public static string GetApplicationName()
	{
		return GetString(GetAppName());	
	}
	
	public static string GetApplicationVersion()
	{
		return GetString(GetAppVersion());
	}
	
	public static string GetApplicationCreator()
	{
		return GetString(GetAppCreator());
	}
	
	public static int CreateParameter(string address, int count)
	{
		return CreateParameter(ToCpp(address), count);
	}
	
	public static int SetParameter(string address, int index, NSPIAttr attribute, NSPValue nspValue)
	{
		return SetParameter(ToCpp(address), index, attribute, nspValue);
	}
	
	public static int GetParameter(string address, int index, NSPIAttr attribute, NSPValue nspValue)
	{
		return GetParameter(ToCpp(address), index, attribute, nspValue);
	}
	
	public static int CreateObserver(string address, int index, NSPIAttr attribute, NspCallback valueC, NspCallback addressC)
	{
		return CreateObserver(ToCpp(address), index, attribute, ToCpp(valueC), ToCpp(addressC));
	}
	
	public static int SendValue(string address, int index, NSPIAttr attribute, NSPValue nspValue)
	{
		return SendValue(ToCpp(address), index, attribute, nspValue);
	}
	
	public static int SaveToXml(string filepath)
	{
		return SaveToXml(ToCpp(filepath));
	}
	
	public static int LoadFromXml(string filepath)
	{
		return LoadFromXml(ToCpp(filepath));
	}
	
	public static int MappingFromXml(string filepath)
	{
		return MappingFromXml(ToCpp(filepath));
	}
	
	public static int PresetsFromXml(string filepath)
	{
		return MappingFromXml(ToCpp(filepath));
	}
	
	void Start () {}
	void Update () {}
}