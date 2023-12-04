//***************************************************************************
//*
//*		Name		: WinBlitExplorer.cpp
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
#include "stdafx.h"
#include "WinBlitWebBand.h"
#include "WinBlitExplorer.h"
#include "ReportError.cpp"
#include <mshtml.h>

#include <ExDispID.h>

HINSTANCE g_hInst;
extern TCHAR* pszClassName;

#import "..\import\build\ATLLogApp.tlb"  no_namespace named_guids

#define CB_CLASS_NAME (TEXT("WinBlit Explorer Bar"))

///////////////////////////////////////////////////////////////////////////
//
// IOleInPlaceSite Methods
//

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::CanInPlaceActivate()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::CanInPlaceActivate(void)
{
    return S_OK;   
}

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::OnInPlaceActivate()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::OnInPlaceActivate(void)
{
   return S_OK;
}

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::OnUIActivate()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::OnUIActivate(void)
{
   return S_OK;
}

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::GetWindowContext()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::GetWindowContext(IOleInPlaceFrame** ppFrame, IOleInPlaceUIWindow** ppIIPUIWin, 
                                              LPRECT lprcPosRect, LPRECT lprcClipRect,
                                              LPOLEINPLACEFRAMEINFO lpFrameInfo)
{
   *ppFrame = NULL;
   *ppIIPUIWin = NULL;

   GetClientRect(m_hWnd, lprcPosRect);
   GetClientRect(m_hWnd, lprcClipRect);

   return S_OK;
}

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::Scroll()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::Scroll(SIZE scrollExtent)
{
    return E_NOTIMPL;   
}

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::OnUIDeactivate()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::OnUIDeactivate(BOOL fUndoable)
{
    
    return E_NOTIMPL;   
}

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::OnInPlaceDeactivate()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::OnInPlaceDeactivate(void)
{   
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::DiscardUndoState()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::DiscardUndoState(void)
{
    return E_NOTIMPL;   
}

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::DeactivateAndUndo()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::DeactivateAndUndo(void)
{
    return E_NOTIMPL;   
}

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::OnPosRectChange()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::OnPosRectChange(LPCRECT lprcPosRect) 
{
   return S_OK;
}
///////////////////////////////////////////////////////////////////////////
//
// IOleClientSite Methods
//

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::SaveObject()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::SaveObject()
{
   return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::GetMoniker()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, LPMONIKER* ppmk)
{
   return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::GetContainer()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::GetContainer(LPOLECONTAINER* ppContainer)
{
    *ppContainer = NULL;       
    return E_NOINTERFACE;
}

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::ShowObject()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::ShowObject()
{
   return S_OK;
}

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::OnShowWindow()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::OnShowWindow(BOOL fShow)
{
   return S_OK;
}

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::RequestNewObjectLayout()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::RequestNewObjectLayout()
{
   return E_NOTIMPL;
}



///////////////////////////////////////////////////////////////////////////
//
// IOleWindow Implementation
//

/**************************************************************************

   CWinBlitExplorer::GetWindow()
   
**************************************************************************/

STDMETHODIMP CWinBlitExplorer::GetWindow(HWND *phWnd)
{
	*phWnd = m_hWnd;
	return S_OK;
}

/**************************************************************************

   CWinBlitExplorer::ContextSensitiveHelp()
   
**************************************************************************/

STDMETHODIMP CWinBlitExplorer::ContextSensitiveHelp(BOOL fEnterMode)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////
//
// IDockingWindow Implementation
//

/**************************************************************************

   CWinBlitExplorer::ShowDW()
   
**************************************************************************/

STDMETHODIMP CWinBlitExplorer::ShowDW(BOOL fShow)
{
	ATL_TRACE1(e_LOGFLOW,"\n ShowDW called %d", fShow);
	if(m_hWnd)
	{
		if(fShow)
		{
			AdviseWBEventSink();

			ShowWindow(m_hWnd, SW_SHOW);
			//show our window
		}
		else
		{
			if (m_bLoaded) m_WinBlitWindow->Stop(); 
			UnadviseWBEventSink();
			//hide our window
			ATL_TRACE0 (e_LOGFLOW,"\n Showing window");
			ShowWindow(m_hWnd, SW_HIDE);
		}
	}
	ATL_TRACE0 (e_LOGDETAIL,"\n ShowDW returning");

	return S_OK;
}

/**************************************************************************

   CWinBlitExplorer::CloseDW()
   
**************************************************************************/

STDMETHODIMP CWinBlitExplorer::CloseDW(DWORD dwReserved)
{
	ShowDW(FALSE);

	if(IsWindow(m_hWnd))
		DestroyWindow(m_hWnd);

	m_hWnd = NULL;
   
	return S_OK;
}

/**************************************************************************

   CWinBlitExplorer::ResizeBorderDW()
   
**************************************************************************/

STDMETHODIMP CWinBlitExplorer::ResizeBorderDW(   LPCRECT prcBorder, 
                                          IUnknown* punkSite, 
                                          BOOL fReserved)
{
	/*
	This method is never called for Band Objects.
	*/
	return E_NOTIMPL;
}


///////////////////////////////////////////////////////////////////////////
//
// IOleControlSite Methods
//

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::OnControlInfoChanged()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::OnControlInfoChanged(void)
{
   return E_NOTIMPL;
}
     
///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::LockInPlaceActive()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::LockInPlaceActive(BOOL fLock)
{
   return E_NOTIMPL;
}
     
///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::GetExtendedControl()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::GetExtendedControl(LPDISPATCH* ppDisp)
{
   return E_NOTIMPL;
}
     
///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::TransformCoords()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::TransformCoords(POINTL* pPtlHimetric, POINTF* pPtfContainer, DWORD dwFlags)
{
   return E_NOTIMPL;
}
     
///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::TranslateAccelerator()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::TranslateAccelerator(LPMSG lpMsg, DWORD grfModifiers)
{
   return E_NOTIMPL;
}
     
///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::OnFocus()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::OnFocus(BOOL fGotFocus)
{
   ATL_TRACE1 (e_LOGDETAIL, "\n OnFocus: %d\n", fGotFocus );

   if (m_pSite)
      m_pSite->OnFocusChangeIS(static_cast<IInputObject*>(this), 
	                          fGotFocus);

   return S_OK;
}
     
///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::ShowPropertyFrame()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::ShowPropertyFrame(void)
{
   return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////
//
// IInputObject Implementation
//

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::UIActivateIO()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::UIActivateIO(BOOL fActivate, LPMSG lpMsg)
{
	ATL_TRACE1 (e_LOGDETAIL,"\n CWinBlitExplorer::UIActivateIO %d", fActivate);
	HRESULT hr = S_OK;

	if (m_wndView)
	{
		RECT  rc;
		GetClientRect(m_hwndParent, &rc);

		//
		// If the Explorer Bar is being activated, we must UI-activate 
		// the WebBrowser control for all accelerators to work.
		//
		CComQIPtr<IOleObject> pOleObj(m_WinBlitWindow); 
		if (fActivate)
		{
			hr = pOleObj->DoVerb(OLEIVERB_UIACTIVATE, lpMsg, this, 0, m_hwndParent, &rc);

			if (m_bLoaded == false) 
			{
				if (m_pFrameWB)
				{			
					CComPtr<IDispatch> pDispatch;
					m_pFrameWB->get_Document(&pDispatch); 

					// Check that it has an IHTMLDocument interface - 
					// if not it could well be an adobe document
					CComQIPtr<IHTMLDocument2> pHTMLDocument (pDispatch);

					if (pDispatch && pHTMLDocument.p)
					{
						CComBSTR bstrReadyState;
						hr = pHTMLDocument->get_readyState(&bstrReadyState); 
						if (	SUCCEEDED(hr)  &&
							   (0 == wcscmp(L"complete",    bstrReadyState) ||
								0 == wcscmp(L"interactive", bstrReadyState))  )
						{
							LoadDocument (pDispatch); 
						}
					}
				}
			}
		}
		else
		{
			hr = pOleObj->DoVerb(OLEIVERB_INPLACEACTIVATE, lpMsg, this, 0, m_hwndParent, &rc);
		}
    }
	ATL_TRACE1 (e_LOGDETAIL, " - returning %08lx ", hr); 
	return hr;
}

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::HasFocusIO()
//   
//   If this window or one of its decendants has the focus, return S_OK. Return 
//   S_FALSE if they don't have the focus.
//
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::HasFocusIO(void)
{
	ATL_TRACE0(e_LOGFLOW,"\n CWinBlitExplorer::HasFocusIO(void)");
   HWND hwnd = GetFocus();

   HWND hwndTmp
	   = m_wndView;


   // See whether the focus has been set to any of the children.
   //
   while (hwnd && hwndTmp)
   {
      if (hwnd == hwndTmp)
         return S_OK;

      hwndTmp = ::GetWindow(hwndTmp, GW_CHILD);
   }

   return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::TranslateAcceleratorIO()
//   
//   If the accelerator is translated, return S_OK. Return S_FALSE otherwise.
//
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::TranslateAcceleratorIO(LPMSG pMsg)
{
   _RPT0(_CRT_WARN, "TranslateAcceleratorIO\n");

   HRESULT hr = S_FALSE;

   CComQIPtr<IOleInPlaceActiveObject> pIPO (m_WinBlitWindow);

   if (pIPO)
   {
         hr = pIPO->TranslateAccelerator(pMsg);
   }

   return hr;
}

///////////////////////////////////////////////////////////////////////////
//
// IObjectWithSite implementations
//

/**************************************************************************

   CWinBlitExplorer::SetSite()
   
**************************************************************************/

STDMETHODIMP CWinBlitExplorer::SetSite(IUnknown* punkSite)
{
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
	ATL_TRACE1 (e_LOGFLOW,"\n CWinBlitExplorer::SetSite %d",punkSite);
	//If a site is being held, release it.

	//If punkSite is not NULL, a new site is being set.
	if(punkSite)	
	{
		if(m_pSite)
		{
			m_pSite->Release();
			m_pSite = NULL;
		}
		//Get the parent window.
		IOleWindow  *pOleWindow;

		m_hwndParent = NULL;
   
		if(SUCCEEDED(punkSite->QueryInterface(IID_IOleWindow, (LPVOID*)&pOleWindow)))
		{
			pOleWindow->GetWindow(&m_hwndParent);
			pOleWindow->Release();
		}

		if(!m_hwndParent) return E_FAIL;

		if(!RegisterAndCreateWindow())
		{
			ATL_TRACE0 (e_LOGDETAIL,"\n Failed to create window");
			return E_FAIL;
		}

		//Get and keep the IInputObjectSite pointer.
		if(!SUCCEEDED(punkSite->QueryInterface(IID_IInputObjectSite, (LPVOID*)&m_pSite)))
		{
			ATL_TRACE0 (e_LOGFLOW, "\n Failed to QI site");

			return S_FALSE;
		}

		IOleCommandTarget* pCmdTarget;
		HRESULT hr = punkSite->QueryInterface(IID_IOleCommandTarget,
                                    (LPVOID*)&pCmdTarget);
		if (SUCCEEDED(hr))
		{
			ATL_TRACE0 (e_LOGFLOW, "\n Found cmd target ");

			IServiceProvider* pSP;
			hr = pCmdTarget->QueryInterface(IID_IServiceProvider,
                                         (LPVOID*)&pSP);
		
			pCmdTarget->Release();
		
			if (SUCCEEDED(hr))
			{
				ATL_TRACE0 (e_LOGFLOW, "\n Found Service Provider ");

				if (m_pFrameWB)
		        {
					m_pFrameWB->Release();
					m_pFrameWB = NULL;
				}
		
				hr = pSP->QueryService(SID_SWebBrowserApp,
                                   IID_IWebBrowser2,
                                   (LPVOID*)&m_pFrameWB);
				if (SUCCEEDED (hr))
				{

					ATL_TRACE0 (2, "\n Got to Browser pointer");
					_ASSERT(m_pFrameWB);
			
					pSP->Release();		
			
				}
				m_bLoaded = false; 

			}
		}
		else 
		{
			ATL_TRACE0 (e_LOGERROR, "\n Failed to QI cpmmand target ");
		}

		//return E_FAIL;
	}

	return S_OK;
}

//**************************************************************************
//
//   CWinBlitExplorer::CreateControl
//   
//**************************************************************************/

void CWinBlitExplorer::CreateControl()
{
	if (!m_wndView) 
	{
		ATL_TRACE0 (e_LOGFLOW, "\n CWinBlitExplorer::CreateControl");

		AtlAxWinInit();
		CComBSTR bstr ("WinBlitReaderManager.WinBlitReader.1");
		USES_CONVERSION;

		RECT rc = { 0, 0, 0, 0 };
		GetClientRect(m_hWnd, &rc);

		IUnknown *pUnk; 
		m_wndView = m_hWnd;
		HRESULT hr = m_wndView.CreateControl(bstr, NULL,  &pUnk);
		if (SUCCEEDED(hr))
		{
			hr = m_wndView.QueryControl(IID_IWinBlitReader, (void**) &m_WinBlitWindow);
			if (SUCCEEDED(hr))
			{
				CPAKVal PakVal;
				m_iLic = PakVal.Val(eWinBlitWebBand, ciLatestVersion) * ciLicMultiplier;
				ATL_TRACE1 (e_LOGFLOW, "\n License number %d ",m_iLic);
			}
			else
			{
				Report_Error("System error occured starting WinBlit %0X \n If this problem persists please contact Product Support ", hr); 
			}
		}
		else
		{
			Report_Error("System error occured starting WinBlit %0X \n If this problem persists please contact Product Support ", hr); 
		}
	}
}

/**************************************************************************

   CWinBlitExplorer::GetSite()
   
**************************************************************************/

STDMETHODIMP CWinBlitExplorer::GetSite(REFIID riid, LPVOID *ppvReturn)
{
	*ppvReturn = NULL;
	ATL_TRACE1 (e_LOGFLOW, "\n CWinBlitExplorer::GetSite %d", m_pSite);
	HRESULT hr = E_FAIL; 
	if(m_pSite)
	{
		hr = m_pSite->QueryInterface(riid, ppvReturn);
		if (!SUCCEEDED(hr))
		{
			ATL_TRACE1 (e_LOGDETAIL, "Failed to get client interface %d ", hr); 
		}
	}
	
	return hr;
}

///////////////////////////////////////////////////////////////////////////
//
// IDeskBand implementation
//

#ifdef COMM_BAND

STDMETHODIMP CCommBand::GetBandInfo(DWORD dwBandID, DWORD dwViewMode, DESKBANDINFO* pdbi)
{
	if(pdbi)
	{
		ATL_TRACE0 (e_LOGFLOW, "CCommBand::GetBandInfo");

		m_dwBandID = dwBandID;
		m_dwViewMode = dwViewMode;

		if(pdbi->dwMask & DBIM_MINSIZE)
		{
			pdbi->ptMinSize.x = 0;
			pdbi->ptMinSize.y = 60;
		}

		if(pdbi->dwMask & DBIM_MAXSIZE)
		{
			pdbi->ptMaxSize.x = -1;
			pdbi->ptMaxSize.y = -1;
		}

		if(pdbi->dwMask & DBIM_INTEGRAL)
		{
			pdbi->ptIntegral.x = 1;
			pdbi->ptIntegral.y = 1;
		}

		if(pdbi->dwMask & DBIM_ACTUAL)
		{
			pdbi->ptActual.x = 0;
			pdbi->ptActual.y = 0;
		}

		if(pdbi->dwMask & DBIM_TITLE)		
		{
//			lstrcpyW(pdbi->wszTitle, L"WinBlit Comm Band");
			CComBSTR bstrTemp("WinBlit Comm Band"); 
			if (m_iLic <  (eFullLicense * ciLicMultiplier))
			{
				bstrTemp.Append(cbstrLicStat[m_iLic/ciLicMultiplier]);
			}
			lstrcpyW(pdbi->wszTitle, bstrTemp);

		}

		if(pdbi->dwMask & DBIM_MODEFLAGS)
		{      
			pdbi->dwModeFlags = DBIMF_VARIABLEHEIGHT;
		}
   
		if(pdbi->dwMask & DBIM_BKCOLOR)
		{
			//Use the default background color by removing this flag.
			pdbi->dwMask &= ~DBIM_BKCOLOR;
		}

		return S_OK;
	
	}	

	return E_INVALIDARG;
};

/**************************************************************************

   CWinBlitExplorer::GetClassID()
   
**************************************************************************/

STDMETHODIMP CCommBand::GetClassID(LPCLSID pClassID)
{
	*pClassID = CLSID_CommBand;

	return S_OK;
}


STDMETHODIMP CCommBand::SetDocument(IDispatch *pDisp)
{
	ATLTRACE("\n CCommBand::SetDocument");
	CComVariant var(pDisp); 
	return S_OK;
}

#endif	// COMM_BAND

#ifdef EXPLORER_BAND

STDMETHODIMP CExplorerBand::GetBandInfo(DWORD dwBandID, DWORD dwViewMode, DESKBANDINFO* pdbi)
{
	if(pdbi)
	{
		m_dwBandID = dwBandID;
		m_dwViewMode = dwViewMode;

		if(pdbi->dwMask & DBIM_MINSIZE)
		{
			pdbi->ptMinSize.x = 10;
			pdbi->ptMinSize.y = 10;
		}

		if(pdbi->dwMask & DBIM_MAXSIZE)
		{
			pdbi->ptMaxSize.x = -1;
			pdbi->ptMaxSize.y = -1;
		}

		if(pdbi->dwMask & DBIM_INTEGRAL)
		{
			pdbi->ptIntegral.x = 1;
			pdbi->ptIntegral.y = 1;
		}

		if(pdbi->dwMask & DBIM_ACTUAL)
		{
			pdbi->ptActual.x = 0;
			pdbi->ptActual.y = 0;
		}

		if(pdbi->dwMask & DBIM_TITLE)		
		{
			CComBSTR bstrTemp("WinBlit Explorer Band"); 
			if (m_iLic <  (eFullLicense * ciLicMultiplier))
			{
				bstrTemp.Append(cbstrLicStat[m_iLic/ciLicMultiplier]);
			}
			lstrcpyW(pdbi->wszTitle, bstrTemp);
		}

		if(pdbi->dwMask & DBIM_MODEFLAGS)
		{      
			pdbi->dwModeFlags = DBIMF_VARIABLEHEIGHT;
		}
   
		if(pdbi->dwMask & DBIM_BKCOLOR)
		{
			//Use the default background color by removing this flag.
			pdbi->dwMask &= ~DBIM_BKCOLOR;
		}

		return S_OK;
	
	}	

	return E_INVALIDARG;
};




///////////////////////////////////////////////////////////////////////////
//
// IPersistStream implementations
// 
// This is only supported to allow the desk band to be dropped on the 
// desktop and to prevent multiple instances of the desk band from showing 
// up in the shortcut menu. This desk band doesn't actually persist any data.
//

/**************************************************************************

   CWinBlitExplorer::GetClassID()
   
**************************************************************************/

STDMETHODIMP CExplorerBand::GetClassID(LPCLSID pClassID)
{
	*pClassID = CLSID_ExplorerBand;

	return S_OK;
}
#endif					  //  EXPLORER_BAND

/**************************************************************************

   CWinBlitExplorer::IsDirty()
   
**************************************************************************/

STDMETHODIMP CWinBlitExplorer::IsDirty(void)
{
	return S_FALSE;
}

/**************************************************************************

   CWinBlitExplorer::Load()
   
**************************************************************************/

STDMETHODIMP CWinBlitExplorer::Load(LPSTREAM pStream)
{
	return S_OK;
}

/**************************************************************************

   CWinBlitExplorer::Save()
   
**************************************************************************/

STDMETHODIMP CWinBlitExplorer::Save(LPSTREAM pStream, BOOL fClearDirty)
{
	return S_OK;
}

/**************************************************************************

   CWinBlitExplorer::GetSizeMax()
   
**************************************************************************/

STDMETHODIMP CWinBlitExplorer::GetSizeMax(ULARGE_INTEGER *pul)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////
//
// private method implementations
//

/**************************************************************************

   CWinBlitExplorer::WndProc()
   
**************************************************************************/

LRESULT CALLBACK CWinBlitExplorer::WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
CWinBlitExplorer  *pThis = (CWinBlitExplorer*)GetWindowLong(hWnd, GWL_USERDATA);

switch (uMessage)
	{
	case WM_NCCREATE:
      {
      LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
      pThis = (CWinBlitExplorer*)(lpcs->lpCreateParams);
      SetWindowLong(hWnd, GWL_USERDATA, (LONG)pThis);

      //set the window handle
		pThis->m_hWnd = hWnd;
		pThis->CreateControl();	  
	  }
      break;
   	  case WM_MOUSEACTIVATE :
			pThis->OnSetFocus(); 
			return MA_ACTIVATEANDEAT;

	case WM_KEYDOWN:
	   return pThis->OnKey(uMessage, wParam, lParam);

	case WM_PAINT:
      return pThis->OnPaint();
   
	case WM_COMMAND:
      return pThis->OnCommand(wParam, lParam);

	case WM_SIZE:
		  return pThis->OnSize();
   
	case WM_SETFOCUS:
      return pThis->OnSetFocus();

	case WM_KILLFOCUS:
      return pThis->OnKillFocus();
   }

	return DefWindowProc(hWnd, uMessage, wParam, lParam);
}

/**************************************************************************

   CWinBlitExplorer::OnKey()
   
**************************************************************************/

LRESULT CWinBlitExplorer::OnKey(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	HRESULT hr = S_FALSE; 

	ATL_TRACE0 (e_LOGDETAIL, "CWinBlitExplorer::OnKey"); 

	return hr;
}


//////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::OnSize()
//   
///////////////////////////////////////////////////////////////////////////

LRESULT CWinBlitExplorer::OnSize(void)
{	
	ATL_TRACE0 (e_LOGDETAIL,"\n CWinBlitExplorer::OnSize");

	return 0;
}

/**************************************************************************

   CWinBlitExplorer::OnPaint()
   
**************************************************************************/

LRESULT CWinBlitExplorer::OnPaint(void)
{
	ATL_TRACE0 (e_LOGDETAIL, "\n CWinBlitExplorer::OnPaint"); 
	PAINTSTRUCT ps;

	BeginPaint(m_hWnd, &ps);
	
	EndPaint(m_hWnd, &ps);
	
	return 0;
}

/**************************************************************************

   CWinBlitExplorer::OnCommand()
   
**************************************************************************/

LRESULT CWinBlitExplorer::OnCommand(WPARAM wParam, LPARAM lParam)
{
	ATL_TRACE0 (e_LOGDETAIL, "\n CWinBlitExplorer::OnCommand");
	return 0;
}

/**************************************************************************

   CWinBlitExplorer::FocusChange()
   
**************************************************************************/

void CWinBlitExplorer::FocusChange(BOOL bFocus)
{
	ATL_TRACE1 (e_LOGDETAIL, "\n nFocus: %d\n", bFocus );
   m_bFocus = bFocus;

	//inform the input object site that the focus has changed
	if(m_pSite)
	{
		HRESULT hr = m_pSite->OnFocusChangeIS((IDockingWindow*)this, bFocus);
	}
}

/**************************************************************************

   CWinBlitExplorer::OnSetFocus()
   
**************************************************************************/

LRESULT CWinBlitExplorer::OnSetFocus(void)
{
  _RPT0(_CRT_WARN, "CWinBlitExplorer::OnSetFocus\n");
	FocusChange(TRUE);

	return 0;
}

/**************************************************************************

   CWinBlitExplorer::OnKillFocus()
   
**************************************************************************/

LRESULT CWinBlitExplorer::OnKillFocus(void)
{
  _RPT0(_CRT_WARN, "CWinBlitExplorer::OnKillFocus\n");

	//FocusChange(FALSE);

	return 0;
}

/**************************************************************************

   CWinBlitExplorer::RegisterAndCreateWindow()
   
**************************************************************************/

BOOL CWinBlitExplorer::RegisterAndCreateWindow(void)
{
	//If the window doesn't exist yet, create it now.
	if(!m_hWnd)
	{
		//Can't create a child window without a parent.
		if(!m_hwndParent)
		{
			return FALSE;
		}

		//If the window class has not been registered, then do so.
		WNDCLASS wc;
		if(!GetClassInfo(g_hInst, CB_CLASS_NAME, &wc))
		{
			ZeroMemory(&wc, sizeof(wc));
			wc.style          = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS;
			wc.lpfnWndProc    = (WNDPROC)WndProc;
			wc.cbClsExtra     = 0;
			wc.cbWndExtra     = 0;
			wc.hInstance      = g_hInst;
			wc.hIcon          = NULL;
			wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
			wc.hbrBackground  = (HBRUSH)CreateSolidBrush(RGB(192, 192, 0));
			wc.lpszMenuName   = NULL;
			wc.lpszClassName  = CB_CLASS_NAME;
      
			if(!RegisterClass(&wc))
			{
				//If RegisterClass fails, CreateWindow below will fail.
			}
		}

		RECT  rc;

		GetClientRect(m_hwndParent, &rc);

		//Create the window. The WndProc will set m_hWnd.
		CreateWindowEx(   0,
                     CB_CLASS_NAME,
                     NULL,
                     //WS_CHILD | WS_CLIPSIBLINGS | WS_BORDER,
					 WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_EX_CLIENTEDGE,
                     0,
                     0,
                     0,
                     0,
                     m_hwndParent,
                     NULL,
                     g_hInst,
                     (LPVOID)this);
      
	}

	return (NULL != m_hWnd);
}

///////////////////////////////////////////////////////////////////////////
//
// CWBExplorerBar::AdviseWBEventSink()
//
///////////////////////////////////////////////////////////////////////////

void CWinBlitExplorer::AdviseWBEventSink(void)
{
	_ASSERT(m_pFrameWB);
	ATL_TRACE0 (e_LOGFLOW, "\n CWinBlitExplorer::AdviseWBEventSink"); 

	if (m_pFrameWB)
	{
		LPCONNECTIONPOINT pCP = NULL;

		// Sink WebBrowser Events.
		if (SUCCEEDED(GetConnectionPoint(m_pFrameWB, DIID_DWebBrowserEvents2, &pCP)))
		{
			pCP->Advise((IDispatch*)(this), &m_dwCookie);
			pCP->Release();
		}
		else
		{
			ATL_TRACE0 (e_LOGDETAIL, "\n GetConnectionPoint failed"); 
		}
	}
}

///////////////////////////////////////////////////////////////////////////
//
// CWinBlitExplorer::UnadviseWBEventSink()
//
///////////////////////////////////////////////////////////////////////////

void CWinBlitExplorer::UnadviseWBEventSink(void)
{
	_ASSERT(m_pFrameWB);
	ATL_TRACE0 (e_LOGFLOW,  "\n CWinBlitExplorer::UnadviseWBEventSink"); 

	if (m_pFrameWB)
	{
		LPCONNECTIONPOINT pCP = NULL;

		// Unadvise the WebBrowser Event Sink. 
		if (m_dwCookie)
		{
			if (SUCCEEDED(GetConnectionPoint(m_pFrameWB, DIID_DWebBrowserEvents2, &pCP)))
			{
				pCP->Unadvise(m_dwCookie);
				pCP->Release();
				--m_dwCookie;

			}
			else
			{
				ATL_TRACE0 (e_LOGERROR, "\n GetConnectionPoint failed"); 
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////
//
//   CWinBlitExplorer::Invoke()
//   
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitExplorer::Invoke_Base(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
                                    DISPPARAMS* pDispParams, VARIANT* pVarResult,
                                    EXCEPINFO* pExcepInfo, UINT* puArgErr)
{
	if (IID_NULL != riid)
		return DISP_E_UNKNOWNINTERFACE;

	if (!pDispParams)
		return DISP_E_PARAMNOTOPTIONAL;

	switch (dispIdMember)
	{
		//
		// The parameters for this DISPID:
		// [0]: New status bar text - VT_BSTR
		//
		case DISPID_STATUSTEXTCHANGE:
		{
			//ATL_TRACE1 ("\n Status text change ");
		}
        break;

		//
		// The parameters for this DISPID are as follows:
		// [0]: Cancel flag  - VT_BYREF|VT_BOOL
		// [1]: HTTP headers - VT_BYREF|VT_VARIANT
		// [2]: Address of HTTP POST data  - VT_BYREF|VT_VARIANT 
		// [3]: Target frame name - VT_BYREF|VT_VARIANT 
		// [4]: Option flags - VT_BYREF|VT_VARIANT
		// [5]: URL to navigate to - VT_BYREF|VT_VARIANT
		// [6]: An object that evaluates to the top-level or frame
		//      WebBrowser object corresponding to the event. 
		//
		// Note: In order to cause navigation to occur in the correct 
		//       window, I am doing a couple of things.  First, I sink
		//       events for all anchors on the page.  If an anchor
		//       is clicked, I navigate in the main window.  This works
		//       for pages that we have no control over.  For those
		//       pages over which you have control, you can use some
		//       sort of indicator in the URL to determine where you
		//       want the navigation to occur.  I am using a fragment
		//       identifier (otherwise known as a bookmark).  You cannot
		//       use the TARGET attribute.  Using TARGET cause Internet
		//       Explorer to open the link in a new window.
		//
		case DISPID_BEFORENAVIGATE2:
        {
        }
        break;

		case DISPID_SELECTIONCHANGED:
			ATL_TRACE0 (e_LOGDETAIL, "\n Selection changed ");
			break; 

		case DISPID_NAVIGATECOMPLETE2:
            break;
		case DISPID_DOCUMENTCOMPLETE:
		{
			ATL_TRACE1 (e_LOGDETAIL, "\n Loading doc with DISPID %d", m_iLic);
			CComPtr<IDispatch> pDispatch;
			m_pFrameWB->get_Document(&pDispatch); 
			CComQIPtr<IHTMLDocument2> pHTMLDocument (pDispatch);

			if (pDispatch && pHTMLDocument.p)
			{
				CComBSTR bstrReadyState;
				HRESULT hr = pHTMLDocument->get_readyState(&bstrReadyState); 
				if (	SUCCEEDED(hr)  &&
					   (0 == wcscmp(L"complete",    bstrReadyState) ||
						0 == wcscmp(L"interactive", bstrReadyState)  ))
				{
					USES_CONVERSION; 
					ATL_TRACE1 (e_LOGDETAIL,"Ready State %s", OLE2T(bstrReadyState));

					LoadDocument (pDispatch);
					
				}
			}
		}	
		break;

		default:

        return DISP_E_MEMBERNOTFOUND;
	}

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////
//
// CWBExplorerBar::GetConnectionPoint()
//
///////////////////////////////////////////////////////////////////////////

HRESULT CWinBlitExplorer::GetConnectionPoint(LPUNKNOWN pUnk, REFIID riid, LPCONNECTIONPOINT* ppCP)
{
	ATLASSERT(m_pFrameWB);
	ATL_TRACE0 (e_LOGFLOW, "\n CWinBlitExplorer::GetConnectionPoint");

	HRESULT hr = E_FAIL;
	IConnectionPointContainer* pCPC;

	if (m_pFrameWB)
	{	
		ATL_TRACE1 (e_LOGFLOW, "\n QueryInterface  %d",pUnk);

		hr = pUnk->QueryInterface(IID_IConnectionPointContainer, (LPVOID*)&pCPC);
		if (SUCCEEDED(hr))
		{

			hr = pCPC->FindConnectionPoint(riid, ppCP);

			pCPC->Release();
		}
	}
	ATL_TRACE0 (e_LOGDETAIL, "\n GetConnectionPoint returned");

	return hr;
}

///////////////////////////////////////////////////////////////////////////
//
// CWBExplorerBar::LoadDocument 
//
///////////////////////////////////////////////////////////////////////////

void CWinBlitExplorer::LoadDocument (IDispatch *pDispatch)
{
	HRESULT hr; 
	CComQIPtr<IHTMLDocument2> pHTMLDocument (pDispatch);

	ATL_TRACE0 (e_LOGFLOW," CWinBlitExplorer::LoadDocument ");

	long eOldState;
	m_WinBlitWindow->get_State(&eOldState); 

	CComVariant varDocument(pDispatch); 
	CComVariant varText; 
	if (eOldState == e_RUNNING || eOldState == e_PAUSED) 
	{
		m_WinBlitWindow->Stop();
	}
	m_WinBlitWindow->UnloadData();

	// Has the user selected some text in the browser window. 
	bool bSelection = false; 
	{
		CComQIPtr<IHTMLSelectionObject> pSelectionObject;
		hr = pHTMLDocument->get_selection(&pSelectionObject);
		if (SUCCEEDED(hr) && pSelectionObject.p)
		{
			CComDispatchDriver pDispatchDriver;
			pSelectionObject->createRange(&pDispatchDriver);
			if (SUCCEEDED(hr) && pDispatchDriver.p)
			{
				DISPID DispID_text		(0);
				pDispatchDriver.GetIDOfName(L"text", &DispID_text); 
				hr = pDispatchDriver.GetProperty(DispID_text, &varText);
				if (0 < ::SysStringLen(varText.bstrVal)) bSelection = true; 
			}
		}
	}
	if (bSelection)
	{
		hr = m_WinBlitWindow->LoadData(m_iLic+0, varText); 
	}
	else
	{
		hr = m_WinBlitWindow->LoadData(m_iLic+5, varDocument); 
	}

	if (SUCCEEDED(hr))
	{
		m_WinBlitWindow->Display(); 
		if (e_RUNNING == eOldState)	
		{
			m_WinBlitWindow->Stop();
			m_WinBlitWindow->Start(); 
		}
		m_bLoaded = true; 						
	}
	else 
	{
		ATL_TRACE0 (e_LOGERROR," Failed to LoadData ");
	}

	// Free up system memory if using text string 
	if (bSelection)
	{
		::SysFreeString(varText.bstrVal); 
	}
}