#include <objbase.h>
#include <windows.h>                                    
#include <stdio.h>
#include <wbemidl.h>
#include <comdef.h>
#include <tchar.h>

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "comsuppw.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	IWbemLocator 	* pLocator = NULL;
	IWbemServices 	* pNamespace = 0;
	IWbemClassObject * pClass = NULL;
	IWbemClassObject * pInClass = NULL;
	IWbemClassObject * pInInst = NULL;
	IEnumWbemClassObject *pEnum = NULL;
	HRESULT hr = S_OK;

	BSTR path = SysAllocString(L"root\\wmi");
	BSTR ClassPath = SysAllocString(L"WmiMonitorBrightnessMethods");
	BSTR MethodName = SysAllocString(L"WmiSetBrightness");
	BSTR ArgName0 = SysAllocString(L"Timeout");
	BSTR ArgName1 = SysAllocString(L"Brightness");
	BSTR bstrQuery = SysAllocString(L"Select * from WmiMonitorBrightnessMethods");

	if (!path || ! ClassPath || !MethodName || ! ArgName0)
	{
		printf("SysAllocString failed. Out of memory.\n");
		{printf("\n[-] Err: xxx");goto cleanup;}
	}

	// Initialize COM and connect up to CIMOM

	hr = CoInitialize(0);
	if (FAILED(hr))
	{
		printf("CoInitialize returned 0x%x:", hr);
		{printf("\n[-] Err: CoInitialize");goto cleanup;}
	}

	//  NOTE:
	//  When using asynchronous WMI API's remotely in an environment where the "Local System" account
	//  has no network identity (such as non-Kerberos domains), the authentication level of
	//  RPC_C_AUTHN_LEVEL_NONE is needed. However, lowering the authentication level to
	//  RPC_C_AUTHN_LEVEL_NONE makes your application less secure. It is wise to
	// use semi-synchronous API's for accessing WMI data and events instead of the asynchronous ones.

	hr = CoInitializeSecurity(NULL,
		-1,
		NULL,
		NULL,
		RPC_C_AUTHN_LEVEL_DEFAULT,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL,
		EOAC_NONE, //change to EOAC_NONE if you change dwAuthnLevel to RPC_C_AUTHN_LEVEL_NONE
		NULL );
	if (FAILED(hr))
	{
		printf("CoInitializeSecurity returned 0x%x:", hr);
		{printf("\n[-] Err: CoInitializeSecurity");goto cleanup;}
	}

	hr = CoCreateInstance(CLSID_WbemLocator,
		0,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator,
		(LPVOID *) &pLocator);
	if (FAILED(hr))
	{
		printf("CoCreateInstance returned 0x%x:", hr);
		{printf("\n[-] Err: CoCreateInstance");goto cleanup;}
	}
	hr = pLocator->ConnectServer(path,
		NULL,
		NULL,
		NULL,
		0, 
		NULL,
		NULL, 
		&pNamespace);
	printf("\nConnectServer returned 0x%x:", hr);
	if(hr != WBEM_S_NO_ERROR)
	{printf("\n[-] Err: ConnectServer");goto cleanup;}

	hr = CoSetProxyBlanket(pNamespace,
		RPC_C_AUTHN_WINNT,
		RPC_C_AUTHZ_NONE,
		NULL,
		RPC_C_AUTHN_LEVEL_CALL,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL,
		EOAC_NONE);

	if(hr != WBEM_S_NO_ERROR)
	{printf("\n[-] Err: CoSetProxyBlanket");goto cleanup;}

	hr =pNamespace->ExecQuery(_bstr_t(L"WQL"), //Query Language
		bstrQuery, //Query to Execute
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, //Make a semi-synchronous call
		NULL, //Context
		&pEnum /*Enumeration Interface*/);

	if(hr != WBEM_S_NO_ERROR)
	{printf("\n[-] Err: ExecQuery");goto cleanup;}

	hr = WBEM_S_NO_ERROR;

	ULONG ulReturned;
	IWbemClassObject *pObj;
	DWORD retVal = 0;

	//Get the Next Object from the collection
	hr = pEnum->Next(WBEM_INFINITE, //Timeout
		1, //No of objects requested
		&pObj, //Returned Object
		&ulReturned /*No of object returned*/);

	if(hr != WBEM_S_NO_ERROR)
	{printf("\n[-] Err: Next");goto cleanup;}

	// Get the class object
	hr = pNamespace->GetObject(ClassPath, 0, NULL, &pClass, NULL);
	printf("\nGetObject returned 0x%x:", hr);
	if(hr != WBEM_S_NO_ERROR)
	{printf("\n[-] Err: GetObject");goto cleanup;}

	// Get the input argument and set the property
	hr = pClass->GetMethod(MethodName, 0, &pInClass, NULL);
	printf("\nGetMethod returned 0x%x:", hr);
	if(hr != WBEM_S_NO_ERROR)
	{printf("\n[-] Err: GetMethod");goto cleanup;}

	hr = pInClass->SpawnInstance(0, &pInInst);
	printf("\nSpawnInstance returned 0x%x:", hr);
	if(hr != WBEM_S_NO_ERROR)
	{printf("\n[-] Err: SpawnInstance");goto cleanup;}

	VARIANT var1;
	VariantInit(&var1);

	V_VT(&var1) = VT_BSTR;
	V_BSTR(&var1) = SysAllocString(L"0");
	hr = pInInst->Put(ArgName0,
		0,
		&var1,
		CIM_UINT32); //CIM_UINT64

	//var1.vt = VT_I4;
	//var1.ullVal = 0;
	//hr = pInInst->Put(ArgName0, 0, &var1, 0);
	printf("\nPut ArgName0 returned 0x%x:", hr);
	VariantClear(&var1);
	if(hr != WBEM_S_NO_ERROR)
	{printf("\n[-] Err: Put ArgName0");goto cleanup;}

	VARIANT var;
	VariantInit(&var);

	V_VT(&var) = VT_BSTR;
	V_BSTR(&var) = SysAllocString(L"100");
	hr = pInInst->Put(ArgName1,
		0,
		&var,
		CIM_UINT8); 

	//var.vt=VT_UI1;
	//var.uiVal = 100;
	//hr = pInInst->Put(ArgName1, 0, &var, 0); 
	VariantClear(&var);
	printf("\nPut ArgName1 returned 0x%x:", hr);
	if(hr != WBEM_S_NO_ERROR)
	{printf("\n[-] Err: Put ArgName1");goto cleanup;}
	// Call the method

	VARIANT pathVariable;
	VariantInit(&pathVariable);

	hr = pObj->Get(_bstr_t(L"__PATH"),
		0,
		&pathVariable,
		NULL,
		NULL);
	printf("\npObj Get returned 0x%x:", hr);
	if(hr != WBEM_S_NO_ERROR)
	{printf("\n[-] Err: Get");goto cleanup;}

	hr =pNamespace->ExecMethod(pathVariable.bstrVal,
		MethodName,
		0,
		NULL, 
		pInInst,
		NULL, 
		NULL);
	VariantClear(&pathVariable);
	printf("\nExecMethod returned 0x%x:", hr);
	if(hr != WBEM_S_NO_ERROR)
	{printf("\n[-] Err: ExecMethod");goto cleanup;}

	printf("Terminating normally\n");

	// Free up resources
cleanup:
	SysFreeString(path);
	SysFreeString(ClassPath);
	SysFreeString(MethodName);
	SysFreeString(ArgName0);
	SysFreeString(ArgName1);
	SysFreeString(bstrQuery);

	if (pClass)	pClass->Release();
	if (pInInst) pInInst->Release();
	if (pInClass) pInClass->Release();
	if (pLocator) pLocator->Release();
	if (pNamespace) pNamespace->Release();

	CoUninitialize();

	return 0;
}