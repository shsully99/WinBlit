//***************************************************************************
//*
//*		Name		: WinBlitExchangeExtension.cpp
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
//*		 Implementation of CExchangeClient
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
//      run nmake -f WinBlitExchangeExtensionps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "WinBlitExchangeExtension.h"

#include "WinBlitExchangeExtension_i.c"
#include "ExchangeClient.h"

extern "C"
{
   __declspec(dllexport) LPEXCHEXT CALLBACK ExchEntryPoint(void);
}

CAppModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_ExchangeClient, CExchangeClient)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

///////////////////////////////////////////////////////////////////////////////
//    FUNCTION: ExchEntryPoint
//
//    Parameters - none
//
//    Purpose
//    The entry point which Exchange calls.  
//
//    Return Value
//    Pointer to Exchange Extension Object
//
//    Comments
//    This is called for each context entry.  Create a new MyExchExt object
//    every time so each context will get its own MyExchExt interface.
//
__declspec(dllexport) LPEXCHEXT CALLBACK ExchEntryPoint(void)
{
    return new MyExchExt;
}



extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_WINBLITEXCHANGEEXTENSIONLib);
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
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}