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
//*		 implementation of exchange client
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/
#include "stdafx.h"
#include "WinBlitExchangeExtension.h"
#include "ExchangeClient.h"
#include "ReportError.cpp"

/////////////////////////////////////////////////////////////////////////////
// CExchangeClient

#define INITGUID
#define USES_IID_IExchExt
#define USES_IID_IExchExtAdvancedCriteria
#define USES_IID_IExchExtAttachedFileEvents
#define USES_IID_IExchExtCommands
#define USES_IID_IExchExtMessageEvents
#define USES_IID_IExchExtPropertySheets
#define USES_IID_IExchExtSessionEvents
#define USES_IID_IExchExtUserEvents
#define USES_IID_IMAPIFolder
#include "ExchangeClient.h"

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#endif

#include <atlimpl.cpp>
#include <MAPIX.h>

///////////////////////////////////////////////////////////////////////////////
// data
//static HINSTANCE ghInstDLL = NULL;  // instance handle of DLL

///////////////////////////////////////////////////////////////////////////////
//    FUNCTION: DLLMain()
//
//    Purpose
//    Do initilization processesing
//
//    Return Value
//    TRUE - DLL successfully loads and LoadLibrary will succeed.
//    FALSE - will cause an Exchange error message saying it cannot locate
//            the extension DLL.
//
//    Comments
//    We only need to get a copy of the DLL's HINSTANCE
//
/*BOOL WINAPI DllMain(
    HINSTANCE  hinstDLL,
    DWORD  fdwReason,   
    LPVOID  lpvReserved) 
{
 if (DLL_PROCESS_ATTACH == fdwReason)
 {
    ghInstDLL = hinstDLL;
 }
 return TRUE;
}*/


///////////////////////////////////////////////////////////////////////////////
//    MyExchExt::MyExchExt()
//
//    Parameters - none
//
//    Purpose
//    Constructor. Initialize members and create supporting interface objects
//
//    Comments
//    Each context of Exchange gets its own set of interface objects.
//    Furthermore, interface objects per context are kept track of by Exchange
//    and the interface methods are called in the proper context.
//    
MyExchExt::MyExchExt () 
{ 
	 m_cRef = 1; 
	m_context = 0;
  
	m_pExchExtCommands = new MyExchExtCommands;
	m_pExchExtUserEvents = new MyExchExtUserEvents;

	// in MyExchExtUserEvents methods I need a reference to MyExchExt
	m_pExchExtUserEvents->SetIExchExt(this);

}


///////////////////////////////////////////////////////////////////////////////
//  IExchExt virtual member functions implementation
//

///////////////////////////////////////////////////////////////////////////////
//    MyExchExt::QueryInterface()
//
//    Parameters
//    riid   -- Interface ID.
//    ppvObj -- address of interface object pointer.
//
//    Purpose
//    Called by Exchage to request for interfaces
//
//    Return Value
//    S_OK  -- interface is supported and returned in ppvObj pointer
//    E_NOINTERFACE -- interface is not supported and ppvObj is NULL
//
//    Comments
//    Exchange client calls QueryInterface for each object.  Only
//    Need to support objects that apply to the extension.  QueryInterface
//    is called onces for each IID for each context.  We support two
//    contexts in this example so QueryInterface is called twice for
//    each IID.
//    
STDMETHODIMP MyExchExt::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
    HRESULT hr = S_OK;

    *ppvObj = NULL;

    if ( (IID_IUnknown == riid) || (IID_IExchExt == riid) )
    {
        *ppvObj = (LPUNKNOWN)this;
    }
    else if ( IID_IExchExtCommands == riid)
    {
        *ppvObj = (LPUNKNOWN)m_pExchExtCommands;
        m_pExchExtCommands->SetContext(m_context);
    }
    else if ( IID_IExchExtUserEvents == riid)
    {
        *ppvObj = (LPUNKNOWN)m_pExchExtUserEvents;
        m_pExchExtUserEvents->SetContext(m_context);
    }
    else
        hr = E_NOINTERFACE;

    if (NULL != *ppvObj)
        ((LPUNKNOWN)*ppvObj)->AddRef();

    return hr;
}



///////////////////////////////////////////////////////////////////////////////
//    MyExchExt::Install()
//
//    Parameters
//    peecb     -- pointer to Exchange Extension callback function
//    eecontext -- context code at time of being called.
//    ulFlags   -- flag to say if install is for modal or not
//
//    Purpose
//    Called once for each new contexted that is entered.  Proper version 
//    number is checked here.  
//
//    Return Value
//    S_OK -- object supported in the requested context
//    S_FALSE -- object is not supported in teh requested context
//
//    Comments
//
STDMETHODIMP MyExchExt::Install (LPEXCHEXTCALLBACK pmecb, 
                         ULONG mecontext, ULONG ulFlags)
{
    ULONG ulBuildVersion;
    HRESULT hr;

    m_context = mecontext;

    // make sure this is the right version 
    pmecb->GetVersion(&ulBuildVersion, EECBGV_GETBUILDVERSION);
    if (EECBGV_BUILDVERSION_MAJOR != (ulBuildVersion & EECBGV_BUILDVERSION_MAJOR_MASK))
        return S_FALSE;

    switch (mecontext)
    {
        case EECONTEXT_VIEWER:
		case EECONTEXT_REMOTEVIEWER:
        case EECONTEXT_SEARCHVIEWER:
		case EECONTEXT_ADDRBOOK:
	    case EECONTEXT_SENDNOTEMESSAGE:
		case EECONTEXT_SENDPOSTMESSAGE:
		case EECONTEXT_SENDRESENDMESSAGE:
		case EECONTEXT_READNOTEMESSAGE:
		case EECONTEXT_READPOSTMESSAGE:
		case EECONTEXT_READREPORTMESSAGE:
		case EECONTEXT_PROPERTYSHEETS:
		case EECONTEXT_ADVANCEDCRITERIA:
            hr = S_OK;
            break;
        default:
            hr = S_FALSE;
            break;
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
//  IExchExtCommands virtual member functions implementation
//

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::QueryInterface()
//
//    Parameters
//    riid   -- Interface ID.
//    ppvObj -- address of interface object pointer.
//
//    Purpose
//    Exchange Client does not call IExchExtCommands::QueryInterface().  
//    So return nothing.
//
//    Return Value - none
//

STDMETHODIMP MyExchExtCommands::QueryInterface(REFIID riid, LPVOID FAR * ppvObj)          
{
	*ppvObj = NULL;
	if ( (riid == IID_IExchExtCommands) || (riid == IID_IUnknown) )
    {
        *ppvObj = (LPVOID)this;
        // Increase usage count of this object
        AddRef();
        return S_OK;
    }
    return E_NOINTERFACE;
}

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::InstallCommands()
//
//    Parameters
//    pmecb  -- Exchange Callback Interface
//    hWnd   -- window handle to main window of context
//    hMenu  -- menu handle to main menu of context
//    lptbeArray -- array of toolbar button entries
//    ctbe   -- count of button entries in array
//    ulFlags -- reserved
//
//    Purpose
//    This function is called when commands are installed for each context
//    the extension services.
//
//    Return Value
//    S_FALSE means the commands have been handled.
//
//    Comments
//    The hWnd and hMenu are in context.  If the context is for the SENDNOTE 
//    dialog, then the hWnd is the window handle to the dialog and the hMenu is
//    the main menu of the dialog.
//    
//    Call ResetToolbar so that Exchange will show it's toolbar
//


STDMETHODIMP MyExchExtCommands::InstallCommands(LPEXCHEXTCALLBACK pmecb, 
                            HWND hWnd, HMENU hMenu,
                            UINT FAR * pcmdidBase, LPTBENTRY lptbeArray,
                            UINT ctbe, ULONG ulFlags)
{
	HRESULT hr = S_FALSE;
	HMENU hMenuTools;
	//HBITMAP hbmp;    // handle to Notepad bitmap
	ATL_TRACE2 (e_LOGFLOW, " \n MyExchExtCommands::InstallCommands %d %d ",m_context, lLogLevel); 
	
	if (lLogLevel == -1)
	{
		IUnknown *pUnk;
		CLSID clsLogApp;
		CLSIDFromProgID(L"ATLLogApp.BlitLog.1", &clsLogApp);
		if (SUCCEEDED(GetActiveObject(clsLogApp,  NULL,  (IUnknown**)&pUnk)))
		{
			m_Log = pUnk;
			if (m_Log) m_Log->get_Level(&lLogLevel);
			ATL_TRACE0(e_LOGFLOW," Started logging in ExchangeClient"); 
		}
	}

	if (EECONTEXT_READNOTEMESSAGE == m_context)
	{
		// -------  install the new menu commands, append to end of Tools menu. ----
		m_hWnd = hWnd;
		pmecb->GetMenuPos(EECMDID_ToolsCustomizeToolbar, &hMenuTools, NULL, NULL, 0);

		//hbmp = LoadBitmap(ghInstDLL, MAKEINTRESOURCE(IDB_BITMAP2)); 

		// add a menu separator
		AppendMenu(hMenuTools, MF_SEPARATOR, 0, NULL);

		// add our extension command for Wordpad
		/*AppendMenu(hMenuTools, MF_BYPOSITION | MF_STRING, *pcmdidBase, "Launch Wordpad");
		m_cmdid = *pcmdidBase;
		(*pcmdidBase)++;

		// add a menu separator
		//AppendMenu(hMenuTools, MF_SEPARATOR, 0, NULL);

		// add our extension command for Notepad
		AppendMenu(hMenuTools, MF_BYPOSITION | MF_STRING, *pcmdidBase, "Launch Notepad");

		//AppendMenu(hMenuTools, MF_BITMAP, *pcmdidBase, (LPCTSTR) hbmp); 
		m_cmdid2 = *pcmdidBase;
		(*pcmdidBase)++;

		// add a menu separator
		//AppendMenu(hMenuTools, MF_SEPARATOR, 0, NULL);

		// add our extension command for Paintbrush
		AppendMenu(hMenuTools, MF_BYPOSITION | MF_STRING, *pcmdidBase, "Launch Paintbrush");
		m_cmdid3 = *pcmdidBase;
		(*pcmdidBase)++;*/

		// Add our extension command for WinBlit
		AppendMenu(hMenuTools, MF_BYPOSITION | MF_STRING, *pcmdidBase, "&WinBlit");
		m_cmdid4 = *pcmdidBase;
		(*pcmdidBase)++;
	}

	if (EECONTEXT_READNOTEMESSAGE == m_context)
	{
		// --------------  install the new toolbar buttons --------------

		// walk through the toolbars and find the standard toolbar
  
		int tbindx;
		HWND hwndToolbar = NULL;
		for (tbindx = ctbe-1; (int) tbindx > -1; --tbindx)
		{
			if (EETBID_STANDARD == lptbeArray[tbindx].tbid)
			{
				hwndToolbar = lptbeArray[tbindx].hwnd;
				m_itbb = lptbeArray[tbindx].itbbBase++;
				m_itbb2 = lptbeArray[tbindx].itbbBase++;
				m_itbb3 = lptbeArray[tbindx].itbbBase++;
				m_itbb4 = lptbeArray[tbindx].itbbBase++;
				break;
			}
		}

		// add our button's bitmaps to the toolbar's set of buttons
		if (hwndToolbar)
		{
			TBADDBITMAP tbab;
			tbab.hInst = _Module.m_hInst;
		/*	tbab.nID = IDB_BITMAP2;
			m_itbm = SendMessage(hwndToolbar, TB_ADDBITMAP, 1, (LPARAM)&tbab);
			tbab.nID = IDB_BITMAP3;
			m_itbm2 = SendMessage(hwndToolbar, TB_ADDBITMAP, 1, (LPARAM)&tbab);
			tbab.nID = IDB_BITMAP4;
			m_itbm3 = SendMessage(hwndToolbar, TB_ADDBITMAP, 1, (LPARAM)&tbab);*/
			tbab.nID = IDB_BITMAP5;
			m_itbm4 = SendMessage(hwndToolbar, TB_ADDBITMAP, 1, (LPARAM)&tbab);
		}
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::DoCommand()
//
//    Parameters
//    pmecb -- pointer to Exchange Callback Interface
//
//    Purpose
//    This method is called by Exchange for each WM_COMMAND is sent to the
//    window in context. 
//
//    Return Value
//    S_OK if command is handled
//    S_FALSE if command is not handled
//
//    Comments
//    Use this function to either respond to the command item (menu or toolbar)
//    added or modify an existing command in Exchange.  Return S_OK to let
//    Exchange know the command was handled.  Return S_OK on commands you are
//    taking over from Exchange.  Return S_FALSE to let Exchange know you want
//    it to carry out its command, even if you modify its action.
//
                                                                                                          
STDMETHODIMP MyExchExtCommands::DoCommand(LPEXCHEXTCALLBACK pmecb, UINT cmdid)
{

/*	HRESULT hr = S_FALSE;	// assume it is not our command
	HWND hWnd;
    TCHAR szFileName[_MAX_PATH];

	strcpy(szFileName,"None");
	if (m_cmdid == cmdid)
		strcpy(szFileName,"Write.exe");
	if (m_cmdid2 == cmdid)
		strcpy(szFileName,"Notepad.exe");
	if (m_cmdid3 == cmdid)
		strcpy(szFileName,"Pbrush.exe");*/
	HRESULT hr = S_FALSE;	// assume it is not our command

	ATL_TRACE2 (e_LOGFLOW," \n MyExchExtCommands::DoCommand %d %d ",m_cmdid,cmdid); 

	if (lLogLevel == -1)
	{
		IUnknown *pUnk;
		CLSID clsLogApp;
		CLSIDFromProgID(L"ATLLogApp.BlitLog.1", &clsLogApp);
		if (SUCCEEDED(GetActiveObject(clsLogApp,  NULL,  (IUnknown**)&pUnk)))
		{
			m_Log = pUnk;
			if (m_Log) m_Log->get_Level(&lLogLevel);
			ATL_TRACE0(e_LOGFLOW," Started logging in ExchangeClient"); 
		}
	}

	ATL_TRACE0 (e_LOGDETAIL," \n After logging"); 

	int iErrorCode = 0;
	if (m_cmdid4 == cmdid)
	{		
		ATL_TRACE0 (e_LOGDETAIL," \n A"); 

		CComPtr<IUnknown> pUnk;
		CComPtr<IDispatch> pDispOutlook;

		CComPtr<IOutlookExtCallback> pOutlookExtCallback;

		hr = pmecb->QueryInterface(IID_IOutlookExtCallback, (void **) &pOutlookExtCallback);
		// If you're running Outlook, then prGetObj will not be NULL.
		if (SUCCEEDED(hr))
		{
			ATL_TRACE0 (e_LOGDETAIL," \n B"); 

			hr = pOutlookExtCallback->GetObject(&pUnk);
			if (SUCCEEDED(hr))
			{
				ATL_TRACE0 (e_LOGDETAIL," \n C"); 

				hr = pUnk->QueryInterface(IID_IDispatch, (void **) &pDispOutlook);
				if (SUCCEEDED(hr)) 
				{
					ATL_TRACE0 (e_LOGDETAIL," \n D"); 

					CComDispatchDriver pDispOL(pDispOutlook); 
					CComVariant varApp;
					hr = pDispOL.GetPropertyByName(L"Application", &varApp);
					if (SUCCEEDED(hr))
					{
						ATL_TRACE0 (e_LOGDETAIL," \n E"); 

						CComDispatchDriver pDispApp(varApp.pdispVal); 
						CComVariant varAI; 

						hr = pDispApp.GetPropertyByName(L"ActiveInspector", &varAI);
						if (SUCCEEDED(hr))
						{
							ATL_TRACE0 (e_LOGDETAIL," \n F"); 

							CComDispatchDriver pDispAI(varAI.pdispVal); 
							CComVariant varCI;
							hr = pDispAI.GetPropertyByName(L"CurrentItem", &varCI);
							if (SUCCEEDED(hr))
							{
								ATL_TRACE0 (e_LOGDETAIL," \n G"); 

								RECT rc;
								{
									HWND hWnd = GetFocus(); 
									HWND hWndTemp = GetFocus(); 
									while (hWndTemp)
									{
										hWndTemp = GetParent(hWnd);
										if (hWndTemp) hWnd = hWndTemp;
									}
									GetWindowRect(hWnd, &rc);
								}
								ATL_TRACE0 (e_LOGDETAIL,"\n H"); 

								CComDispatchDriver pDispCI (varCI.pdispVal);
								if (pDispCI)
								{
									CComVariant varBody;
									::VariantClear(&varBody);
									hr = pDispCI.GetPropertyByName(L"Body", &varBody);
									CComBSTR bstr(varBody.bstrVal); 

									ATL_TRACE0 (e_LOGDETAIL,"\n I"); 

									if (SUCCEEDED (hr))
									{
										ATL_TRACE0 (e_LOGDETAIL,"\n J"); 

										CWinBlitDialog* m_pWinBlitDialog = new CWinBlitDialog;

										ATL_TRACE0 (e_LOGDETAIL,"\n K"); 

										// Give dialog box our text string and display rectangle
										if (0 == m_pWinBlitDialog->LoadData(bstr, rc))
										{
											m_pWinBlitDialog->DoModal(m_hWnd); 
											hr = S_OK;
										}
										delete 	m_pWinBlitDialog;
									}
									else
									{
										iErrorCode = IDS_BODY;
									}
									hr = S_OK;
								}
								else
								{
									iErrorCode = IDS_BODY;
								}
							}
							else
							{
								iErrorCode = IDS_CURRENTITEM; 
							}
						}
						else
						{
							iErrorCode = IDS_ACTIVEINSPECTOR; 
						}
					}
					else
					{
						iErrorCode = IDS_APPLICATION; 
					}				
				}
				else
				{
					iErrorCode = IDS_DISPOUTLOOK;
				}				
			}
			else
			{
				iErrorCode = IDS_GETOBJECT;
			}				
		}
		else
		{
			iErrorCode = IDS_EXCHANGECALLBACK; 
		}				

		if ( 0 != iErrorCode)
		{
			// Some serious error - inform the user. 
			Report_Error (" Failed to open docuemnt due to system error %d / %x \n If this problem persists please contact Product Support", iErrorCode, hr); 
		}
	}

	return hr;
}
///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::InitMenu()
//
//    Parameters
//    pmecb -- pointer to Exchange Callback Interface
//
//    Purpose
//    This method is called by Exchange when the menu of context is about to
//    be activated.  See WM_INITMENU in the Windows API Reference for more
//    information.
//
//    Return Value - none
//

STDMETHODIMP_(VOID) MyExchExtCommands::InitMenu(LPEXCHEXTCALLBACK pmecb)
{
 // do nothing

}

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::Help()
//
//    Parameters
//    pmecb -- pointer to Exchange Callback Interface
//    cmdid -- command id
//
//    Purpose
//    Respond when user presses F1 while custom menu item is selected.
//
//    Return Value
//    S_OK -- recognized the command and provided help
//    S_FALSE -- not our command and we didn't provide help
//

STDMETHODIMP MyExchExtCommands::Help(LPEXCHEXTCALLBACK pmecb, UINT cmdid)
{
	HRESULT hr;

	hr = S_FALSE;

 return hr;
}


///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::QueryHelpText()
//
//    Parameters
//    cmdid -- command id corresponding to menu item activated
//    ulFlags -- identifies either EECQHT_STATUS or EECQHT_TOOLTIP
//    psz -- pointer to buffer to be populated with text to display
//    cch -- count of characters available in psz buffer
//
//    Purpose
//    Exchange calls this function each time it requires to update the status
//    bar text or if it is to display a tooltip on the toolbar.
//
//    Return Value
//    S_OK to indicate our command was handled
//    S_FALSE to tell Exchange it can continue with its function
//

STDMETHODIMP MyExchExtCommands::QueryHelpText(UINT cmdid, ULONG ulFlags, 
	                                            LPTSTR psz, UINT cch)
{

	HRESULT hr = S_FALSE;

	if (cmdid == m_cmdid4)
	{
		if (ulFlags == EECQHT_STATUS)
			lstrcpyn(psz, "WinBlit Reader", cch);
  
		if (ulFlags == EECQHT_TOOLTIP)
			lstrcpyn(psz, "Launch WinBlitReader", cch);
		hr = S_OK;
	}
 
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::QueryButtonInfo()
//
//    Parameters
//    tbid    -- toolbar identifier
//    itbb    -- toolbar button index
//    ptbb    -- pointer to toolbar button structure -- see TBBUTTON structure
//    lpsz    -- point to string describing button
//    cch     -- maximum size of lpsz buffer
//    ulFlags -- EXCHEXT_UNICODE may be specified
//
//    Purpose
//    For Exchange to find out about toolbar button information.
//
//    Return Value
//    S_FALSE - not our button
//    S_OK    - we filled information about our button
//
//    Comments
//    Called for every button installed for toolbars when IExchExtCommands
//    is installed for each context. The lpsz text is used when the Customize
//    Toolbar dialog is displayed.  The text will be displayed next to the
//    button.
//

STDMETHODIMP MyExchExtCommands::QueryButtonInfo (ULONG tbid, UINT itbb, 
                            LPTBBUTTON ptbb, LPTSTR lpsz, UINT cch, 
                            ULONG ulFlags)
{
	ATL_TRACE0 (2," \n MyExchExtCommands::QueryButtonInfo  "); 

	HRESULT hr = S_FALSE;

	if (m_itbb4 == itbb)
	{
		ptbb->iBitmap = m_itbm4;             // see InstallCommands in this source file
		ptbb->idCommand = m_cmdid4;
		ptbb->fsState = TBSTATE_ENABLED;
		ptbb->fsStyle = TBSTYLE_BUTTON;
		ptbb->dwData = 0;
		ptbb->iString = -1;
		lstrcpyn(lpsz, "WinBlit", cch);
		hr = S_OK;
	}
	return hr;
}


///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::ResetToolbar()
//
//    Parameters
//    tbid
//    ulFlags
//
//    Purpose
//
//    Return Value  S_OK always
//
STDMETHODIMP MyExchExtCommands::ResetToolbar(ULONG tbid, ULONG ulFlags)
{
 return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//  IExchExtUserEvents virtual member functions implementation
//

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtUserEvents::QueryInterface()
//
//    Parameters
//    riid   -- Interface ID.
//    ppvObj -- address of interface object pointer.
//
//    Purpose
//    Exchange Client does not call IExchExtUserEvents::QueryInterface().  
//    So return nothing.
//
//    Return Value - none
//

STDMETHODIMP MyExchExtUserEvents::QueryInterface(REFIID riid, LPVOID FAR * ppvObj)          
{
    *ppvObj = NULL;
    if (( riid == IID_IExchExtUserEvents) || (riid == IID_IUnknown) )
    {
        *ppvObj = (LPVOID)this;
        // Increase usage count of this object
        AddRef();
        return S_OK;
    }
    return E_NOINTERFACE;
}

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtUserEvents::OnSelectionChange()
//
//    Parameters
//    pmecb  -- pointer to Exchange Callback Object
//    
//
//    Purpose
//    This function is called when the selection in the UI is changed.
//
//    Return Value - none
//
//    Comments
//    OnSelectionChange is called whenever the selection changes either within
//    a pane or is changed between panes.
//

STDMETHODIMP_(VOID) MyExchExtUserEvents::OnSelectionChange(LPEXCHEXTCALLBACK pmecb)
{
	 // no need to handle this one
}


///////////////////////////////////////////////////////////////////////////////
//    MyExchExtUserEvents::OnObjectChange()
//
//    Parameters
//    pmecb  -- pointer to Exchange Callback Object
//    
//
//    Purpose
//    This function is called when the selection in the UI is to a different
//    of object on the left pane.
//
//    Return Value - none
//
//    Comments
//    OnObjectChange is called whenever the selection is changed between 
//    objects in the left pane only.  Change in selection between folders, 
//    subfolders or container object in the left pane will be reflected with a
//    call to OnObjectChange.  Change in selection between objects (messages, 
//    subfolders) in the right pane will not call OnObjectChange, only 
//    OnSelectionChange.
//

STDMETHODIMP_(VOID) MyExchExtUserEvents::OnObjectChange(LPEXCHEXTCALLBACK pmecb)
{
 // no need to handle this one
}

