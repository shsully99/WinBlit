//***************************************************************************
//*
//*		Name		: WinBlitWebBand.cpp
//*							
//*		$Revision:$
//*
//*		Date        : 21-Feb-2002
//*
//*		Author      : Sean Sullivan
//*
//*
//*		Copyright (c) Pata-Sucia Ltd 2001
//*		All rights reserved
//*
//*		This document contains matter that is confidential,
//*		proprietary information of Pata-Sucia 
//*
//***************************************************************************

//***************************************************************************
//*		M O D U L E   D E S C R I P T I O N
//***************************************************************************
//* 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/
// WinBlitWebBand.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f WinBlitWebBandps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include <shlguid.h>
#include "WinBlitWebBand.h"
#include "registry.h"
// ATL_TRACE_CATEGORY 0xFFFFFFFF 
//#define ATL_TRACE_LEVEL 4 
#include "WinBlitWebBand_i.c"
#include "WinBlitExplorer.h"

BOOL RegisterComCat(CLSID, CATID);
BOOL UnRegisterComCat(CLSID, CATID);

static const int ciMaxKeys (3); 

static const TCHAR* pszRootKeys [3] = {"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Discardable\\PostSetup\\Component Categories\\{00021493-0000-0000-C000-000000000046}",
										 "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Discardable\\PostSetup\\Component Categories\\{00021494-0000-0000-C000-000000000046}",
										 "Component Categories\\{00021492-0000-0000-C000-000000000046}"};

static const HKEY hDeleteKeys  [3] = {HKEY_CURRENT_USER, 
									 HKEY_CURRENT_USER,
									 HKEY_CLASSES_ROOT};




CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)

#ifdef EXPLORER_BAND
	OBJECT_ENTRY(CLSID_ExplorerBand, CExplorerBand)
#endif

#ifdef COMM_BAND
	OBJECT_ENTRY(CLSID_CommBand, CCommBand)
#endif

END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_WINBLITWEBBANDLib);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	ATL_TRACE0 (e_LOGFLOW, "\nCWinBlitWebBand::DllGetClassObject");
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	ATL_TRACE0 (e_LOGFLOW, "\nCWinBlitWebBand::DllRegisterServer");

    // registers object, typelib and all interfaces in typelib
    HRESULT hr = S_OK;
#ifdef COMM_BAND 
	hr = _Module.RegisterServer(TRUE, &CLSID_CommBand);
	hr = _Module.RegisterServer(TRUE, &CLSID_CommBand);
	RegisterComCat(CLSID_CommBand, CATID_CommBand);
#endif

#ifdef EXPLORER_BAND 
	hr = _Module.RegisterServer(TRUE, &CLSID_ExplorerBand);
	hr = _Module.RegisterServer(TRUE, &CLSID_ExplorerBand);
	RegisterComCat(CLSID_ExplorerBand, CATID_InfoBand);
#endif 
	
	// Delete registry keys to clear the cache 
	// See Q247705 
	for (int iA = 0; iA < ciMaxKeys; iA++)
	{
		CRegistry RegCurrent; 
		if (RegCurrent.SetRootKey(hDeleteKeys[iA]))
		{
			RegCurrent.DeleteKey(pszRootKeys[iA], "Enum");
		}
	}

	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	HRESULT hr = S_OK;

	ATL_TRACE0 (e_LOGFLOW, "\nCWinBlitWebBand::DllUnregisterServer");

	#ifdef COMM_BAND 
	hr = _Module.UnregisterServer(TRUE, &CLSID_CommBand);
	hr = _Module.UnregisterServer(TRUE, &CLSID_CommBand);
	UnRegisterComCat(CLSID_CommBand, CATID_CommBand);
	#endif

	#ifdef EXPLORER_BAND 
	hr = _Module.UnregisterServer(TRUE, &CLSID_ExplorerBand);
	hr = _Module.UnregisterServer(TRUE, &CLSID_ExplorerBand);
	UnRegisterComCat(CLSID_ExplorerBand, CATID_InfoBand);
	#endif 

	return hr;
}

BOOL RegisterComCat(CLSID clsid, CATID CatID)
{
   ICatRegister* pcr;
   HRESULT hr = S_OK ;
    
   CoInitialize(NULL);

   hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,
                         NULL,
                         CLSCTX_INPROC_SERVER, 
                         IID_ICatRegister,
                         (LPVOID*)&pcr);

   if (SUCCEEDED(hr))
   {
      hr = pcr->RegisterClassImplCategories(clsid, 1, &CatID);
      pcr->Release();
   }
        
   CoUninitialize();

   return SUCCEEDED(hr);
}

BOOL UnRegisterComCat(CLSID clsid, CATID CatID)
{
   ICatRegister* pcr;
   HRESULT hr = S_OK ;
    
   CoInitialize(NULL);

   hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,
                         NULL,
                         CLSCTX_INPROC_SERVER, 
                         IID_ICatRegister,
                         (LPVOID*)&pcr);

   if (SUCCEEDED(hr))
   {
      hr = pcr->UnRegisterClassImplCategories(clsid, 1, &CatID);
      pcr->Release();
   }
        
   CoUninitialize();

   return SUCCEEDED(hr);
}