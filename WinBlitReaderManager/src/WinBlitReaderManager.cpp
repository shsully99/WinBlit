//***************************************************************************
//*
//*		Name		: WinBlitReaderManager.cpp
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
//*		 : Implementation of DLL Exports.
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/



// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f WinBlitReaderManagerps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "WinBlitReaderManager.h"
#include "WinBlitReaderManager_i.c"
#include "WinBlitReader.h"
#include "WinBlitData.h"
#include "Setting.h"
#include "Settings.h"
#include "Statistic.h"
#include "Statistics.h"
#include "TextWindow.h"
#include "PropPage.h"
#include "WinBlitRegistry.h"
#include "BrowserWrapper.h"
#include "PAKVal.h"
#include <string>

using namespace std;

CComModule _Module;


BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_WinBlitReader,	CWinBlitReader)
	OBJECT_ENTRY(CLSID_WinBlitData,		CWinBlitData)
	OBJECT_ENTRY(CLSID_Setting,			CSetting)
	OBJECT_ENTRY(CLSID_Settings,		CSettings)
	OBJECT_ENTRY(CLSID_Statistic,		CStatistic)
	OBJECT_ENTRY(CLSID_Statistics,		CStatistics)
	OBJECT_ENTRY(CLSID_BrowserWrapper,	CBrowserWrapper)
END_OBJECT_MAP()

static const TCHAR* pszWinBlitReg = "\\WinBlit.reg";
/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_WINBLITREADERMANAGERLib);
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
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
	CPAKVal PAKVal; 
	PAKVal.FirstReg(); 
	HRESULT hr =  _Module.RegisterServer(TRUE);

	if (lLogLevel == -1)
	{
		IUnknown *pUnk;
		CLSID clsLogApp;
		CLSIDFromProgID(L"ATLLogApp.BlitLog.1", &clsLogApp);
		if (SUCCEEDED(GetActiveObject(clsLogApp,  NULL,  (IUnknown**)&pUnk)))
		{
			m_Log = pUnk;
			if (m_Log) m_Log->get_Level(&lLogLevel);
		}
	}


	if (SUCCEEDED (hr))
	{
		// Look for .reg file in our own folder by finding path name and stripping off the
		// end. 
		int iB = 999;
		TCHAR tchModule [_MAX_PATH];
		DWORD dwLength = GetModuleFileName(_Module.m_hInst, tchModule, _MAX_PATH);
		
		if (dwLength  <= 0)
		{
			// TODO - this is an error
		}
		else
		{
			for (int iA = dwLength; iA > 0; iA--)
			{
				TCHAR tchSlash (92);
				if (tchSlash == tchModule[iA])
				{
					iB = iA;
					break; 
				}
			}
		}
		string strParameter(" /s ");
		TCHAR tchQuote [2] = {34, 0};
		strParameter.append(tchQuote,1);
		strParameter.append(tchModule, iB);
		strParameter.append(pszWinBlitReg);
		strParameter.append(tchQuote,1);
		ATL_TRACE0(e_LOGDETAIL, "About to regedit"); 
		HINSTANCE hInst;
		hInst = ShellExecute(GetFocus(), NULL,"regedit.exe",strParameter.c_str(),NULL,SW_SHOWNORMAL);
		ATL_TRACE2(e_LOGDETAIL, "Finshed regedit %0x %d", hr,hInst); 
		::RegFlushKey(HKEY_LOCAL_MACHINE);
	}


	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}