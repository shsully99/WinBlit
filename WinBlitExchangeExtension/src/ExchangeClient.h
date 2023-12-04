//***************************************************************************
//*
//*		Name		: ExchangeClient.cpp
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


#ifndef __EXCHANGECLIENT_H_
#define __EXCHANGECLIENT_H_

#include "resource.h"       // main symbols
#include <COMMCTRL.H>
#include <MAPIX.H>
#include <MAPIUTIL.H>
#include <MAPITAGS.H>
#include <MAPIFORM.H>
#include <MAPIDEFS.H>
#include <EXCHEXT.H>
#include "Outlook.h"

#include "WinBlitDialog.h"


#ifndef __IOutlookExtCallback_INTERFACE_DEFINED__
#define __IOutlookExtCallback_INTERFACE_DEFINED__

EXTERN_C const IID IID_IOutlookExtCallback;
    interface DECLSPEC_UUID("0006720D-0000-0000-C000-000000000046")
    IOutlookExtCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetObject( 
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk) = 0;       
        virtual HRESULT STDMETHODCALLTYPE GetOfficeCharacter( 
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppmsotfc) = 0;
};
 #endif  /* __IOutlookExtCallback_INTERFACE_DEFINED__ */


///////////////////////////////////////////////////////////////////////////////
//    prototypes
//void GetFolderStats(LPMAPIFOLDER lpFolder, ULONG FAR * ulSubFolders, 
//                    ULONG FAR * ulReadMsgs, ULONG FAR * ulUnReadMsgs);

///////////////////////////////////////////////////////////////////////////////
//    forward declarations
class MyExchExt;
class MyExchExtCommands;
class MyExchExtUserEvents;

extern "C"
{
   __declspec(dllexport) LPEXCHEXT CALLBACK ExchEntryPoint(void);
}

class MyExchExt : public IExchExt
{
 
public:
    MyExchExt ();
    STDMETHODIMP QueryInterface
                    (REFIID                     riid,
                     LPVOID *                   ppvObj);
    inline STDMETHODIMP_(ULONG) AddRef
                    () { ++m_cRef; return m_cRef; };
    inline STDMETHODIMP_(ULONG) Release
                    () { ULONG ulCount = --m_cRef;
                         if (!ulCount) { delete this; }
                         return ulCount;};
    STDMETHODIMP Install (LPEXCHEXTCALLBACK pmecb, 
                        ULONG mecontext, ULONG ulFlags);

private:
    ULONG m_cRef;
    UINT  m_context;

    MyExchExtCommands * m_pExchExtCommands;
    MyExchExtUserEvents * m_pExchExtUserEvents;
};

class MyExchExtCommands : public IExchExtCommands
{
public:

	MyExchExtCommands () 
        { m_cRef = 0; m_context = 0; 
          m_cmdid = 0;  m_itbb = 0; m_itbm = 0;  m_hWnd = 0; };
	STDMETHODIMP QueryInterface
                    (REFIID                     riid,
                     LPVOID *                   ppvObj);
	inline STDMETHODIMP_(ULONG) AddRef
                    () { ++m_cRef; return m_cRef; };
	inline STDMETHODIMP_(ULONG) Release
                    () { ULONG ulCount = --m_cRef;
                         if (!ulCount) { delete this; }
                         return ulCount;};
	STDMETHODIMP InstallCommands(LPEXCHEXTCALLBACK pmecb, 
                                HWND hwnd, HMENU hmenu,
                                UINT FAR * cmdidBase, LPTBENTRY lptbeArray,
                                UINT ctbe, ULONG ulFlags);                                                                              

    STDMETHODIMP DoCommand(LPEXCHEXTCALLBACK pmecb, UINT mni);
    STDMETHODIMP_(VOID) InitMenu(LPEXCHEXTCALLBACK pmecb);
    STDMETHODIMP Help(LPEXCHEXTCALLBACK pmecb, UINT mni);
    STDMETHODIMP QueryHelpText(UINT mni, ULONG ulFlags, LPTSTR sz, UINT cch);
    STDMETHODIMP QueryButtonInfo(ULONG tbid, UINT itbb, LPTBBUTTON ptbb,
                                LPTSTR lpsz, UINT cch, ULONG ulFlags);
    STDMETHODIMP ResetToolbar(ULONG tbid, ULONG ulFlags);

    inline VOID SetContext
                (ULONG eecontext) { m_context = eecontext; };
    inline UINT GetCmdID() { return m_cmdid; };

private:

    ULONG m_cRef;
    ULONG m_context;

    UINT  m_cmdid;     // cmdid for menu extension command
    UINT  m_cmdid2;
    UINT  m_cmdid3;
    UINT  m_cmdid4;

    UINT  m_itbb;      // toolbar
    UINT  m_itbm;
    UINT  m_itbb2;     // toolbar2
    UINT  m_itbm2;
    UINT  m_itbb3;     // toolbar3
    UINT  m_itbm3;
    UINT  m_itbb4;     // toolbar3
    UINT  m_itbm4;

    HWND  m_hWnd;          

};

class MyExchExtUserEvents : public IExchExtUserEvents
{
public:
    MyExchExtUserEvents() { m_cRef = 0; m_context = 0;
                            m_pExchExt = NULL; };
    STDMETHODIMP QueryInterface
                (REFIID                     riid,
                 LPVOID *                   ppvObj);
    inline STDMETHODIMP_(ULONG) AddRef
                () { ++m_cRef; return m_cRef; };
    inline STDMETHODIMP_(ULONG) Release
                () { ULONG ulCount = --m_cRef;
                     if (!ulCount) { delete this; }
                     return ulCount;};

    STDMETHODIMP_(VOID) OnSelectionChange(LPEXCHEXTCALLBACK pmecb);
    STDMETHODIMP_(VOID) OnObjectChange(LPEXCHEXTCALLBACK pmecb);

    inline VOID SetContext
                (ULONG eecontext) { m_context = eecontext; };
    inline VOID SetIExchExt
                (MyExchExt * pExchExt) { m_pExchExt = pExchExt; };

private:
    ULONG m_cRef;
    ULONG m_context;
    
    MyExchExt * m_pExchExt;

};

/////////////////////////////////////////////////////////////////////////////
// CExchangeClient
class ATL_NO_VTABLE CExchangeClient : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExchangeClient, &CLSID_ExchangeClient>,
	public IDispatchImpl<IExchangeClient, &IID_IExchangeClient, &LIBID_WINBLITEXCHANGEEXTENSIONLib>, 
	public MyExchExt
{
public:
	CExchangeClient()
	{
	}
			
DECLARE_REGISTRY_RESOURCEID(IDR_EXCHANGECLIENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CExchangeClient)
	COM_INTERFACE_ENTRY(IExchangeClient)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IExchangeClient
public:
};

#endif //__EXCHANGECLIENT_H_
