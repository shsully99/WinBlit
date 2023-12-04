//***************************************************************************
//*
//*		Name		: BrowserWrapper.cpp
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
//*		Used by WinBlitPad to load HTML data source. 
//*		Contains an event sink for the Browser to inform
//*		when the document is loaded 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#include "BrowserWrapper.h"

/////////////////////////////////////////////////////////////////////////////
// CBrowserWrapper

#include "stdafx.h"
#include "WinBlitReaderManager.h"
#include "BrowserWrapper.h"
#include "ExDispID.h"
#include "ReportError.cpp"

HRESULT CBrowserWrapper::FinalConstruct ()
{
	m_spWebBrowser.p = NULL; 
	if (lLogLevel == -1)
	{
		IUnknown *pUnk;
		CLSID clsLogApp;
		CLSIDFromProgID(L"ATLLogApp.BlitLog.1", &clsLogApp);
		if (SUCCEEDED(GetActiveObject(clsLogApp,  NULL,  (IUnknown**)&pUnk)))
		{
			m_Log = pUnk;
			if (m_Log) m_Log->get_Level(&lLogLevel);
			ATL_TRACE0 (1, "Started logging in BrowserWrapper "); 
		}
	}
	return S_OK; 
};



LRESULT CBrowserWrapper::OnCreate(UINT, WPARAM, LPARAM, BOOL&)
{
   return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CBrowserWrapper
CBrowserWrapper::CBrowserWrapper() :
   m_dwCookie((DWORD)0),
   m_bInPlaceActive(FALSE), 
   m_bLoaded(false)
{
}

//===========================================================================
//
//	Method :		Run
//		
//	Description :	Called by client to Load a HTML file 
//					Instantiates the web browser control. 
//
//	Returns :		S_OK if successful
//
//===========================================================================

STDMETHODIMP CBrowserWrapper::Run(BSTR bstrDataSource)
{
	ATL_TRACE0 ( 2, "\n CBrowserWrapper::Run "); 
	// Create and show the window
	HRESULT hr;
	m_bLoaded = false; 
	int iErrorCode = 0; 

	if (!m_spWebBrowser.p)
	{
		//
		RECT rcClient = { CW_USEDEFAULT, 0, 0, 0 };
 
		ATL_TRACE0 (e_LOGDETAIL, " 111 ");
		Create(GetDesktopWindow(), rcClient, _T("ATL Browser"), WS_VISIBLE | WS_OVERLAPPEDWINDOW, 0);
		// 
		//ShowWindow(SW_SHOWNORMAL);
     
		//
		// Create the WebBrowser control
		//
		//CComPtr<IOleObject> spOleObject;
		hr = CoCreateInstance(CLSID_WebBrowser, NULL, CLSCTX_INPROC, IID_IOleObject,
									 (void**)&spOleObject);
		if (SUCCEEDED (hr))
		{
			ATL_TRACE0 (e_LOGDETAIL, " 222 ");

			hr = spOleObject->SetClientSite(this) != S_OK;

			if (SUCCEEDED(hr))
			{
				ATL_TRACE0 (e_LOGDETAIL, " 333 ");

				// 
				// In-place activate the WebBrower control
				//
				MSG msg;
				GetClientRect(&rcClient);

				hr = spOleObject->DoVerb(OLEIVERB_INPLACEACTIVATE, &msg, this, 0, m_hWnd, &rcClient);
				if (SUCCEEDED(hr))
				{
					ATL_TRACE0 (e_LOGDETAIL, " 444 ");

					//
					// Get the pointer to the WebBrowser control.  Note that setting a CComQIPtr
					// equal to a pointer of another type cause CComQIPtr to call QueryInterface.
					//
					m_spWebBrowser = spOleObject;

					//
					// QI for the in-place object to set the size.
					//
					m_spInPlaceObject = m_spWebBrowser;

					if (m_spInPlaceObject) 
					{
						ATL_TRACE0 (e_LOGDETAIL, " 555 ");

						m_spInPlaceObject->SetObjectRects(&rcClient, &rcClient);

						hr = AtlAdvise(m_spWebBrowser, GetUnknown(), DIID_DWebBrowserEvents2, &m_dwCookie);
						if (SUCCEEDED(hr))
						{
							ATL_TRACE0 (e_LOGDETAIL, " 666 ");

							CComVariant vurl(bstrDataSource); 
							CComVariant vtEmpty(0, VT_EMPTY);
							hr = m_spWebBrowser->Navigate2(&vurl, &vtEmpty, &vtEmpty, &vtEmpty, &vtEmpty);
							if (SUCCEEDED(hr))
							{
								ATL_TRACE0 (e_LOGDETAIL, " 777 ");
							}
							else 
							{
								iErrorCode = IDS_WBNAVOGATEFAILED; 
							}
						}
						else
						{
							iErrorCode = IDS_ATLADVISEFAILED; 
						}
					}
					else
					{
						iErrorCode = IDS_QIFORINPLACEFAILED; 
					}
				}
				else
				{
					iErrorCode = IDS_INPLACEACTIVATEFAILED; 
				}
			}			
			else
			{
				iErrorCode = IDS_SETSITEFAILED; 
			}
		}
		else
		{
			iErrorCode = IDS_COCREATEWBFAILED;
		}
	}

	if ( 0 != iErrorCode)
	{
		// Some serious error - inform the user. 
		Report_Error (" WinBlit Failed to open html document due to a system error %d / %x \n If this problem persists please contact Product Support", iErrorCode, hr); 
	}
	ATL_TRACE0 (e_LOGDETAIL, " 888 ");

	return hr;
}

//
// IDispatch Methods
//
//===========================================================================
//
//	Method :		Invoke
//
//	Description :	Called by web browser following creation of event sink
//					
//
//===========================================================================

STDMETHODIMP CBrowserWrapper::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags,
                               DISPPARAMS* pDispParams, VARIANT* pvarResult,
                               EXCEPINFO*  pExcepInfo,  UINT* puArgErr)
{
   USES_CONVERSION;
	   ATL_TRACE1 (e_LOGDETAIL, "CBrowserWrapper::Invoke %d ", dispidMember); 


   switch (dispidMember)
   {
      case DISPID_DOCUMENTCOMPLETE:
		  // Web Browser has loaded document 
		  // Set member variable to say so
		 m_bLoaded = true; 
         break;

      case DISPID_DOWNLOADBEGIN:
         break;

      case DISPID_NAVIGATECOMPLETE:
         break;

      case DISPID_DOWNLOADCOMPLETE:

         break;
      case DISPID_STATUSTEXTCHANGE:
         break;
      case DISPID_TITLECHANGE:
         break;
      default:
         return DISP_E_MEMBERNOTFOUND;
   }

   return S_OK;
}

//===========================================================================
//
//	Method :		GetDoc
//
//	Description:	Called by client to retrieve document pointer 
//
//	Returns :		S_OK
//
//===========================================================================

STDMETHODIMP CBrowserWrapper::GetDoc(VARIANT_BOOL* bLoaded, IDispatch **pDispatch)
{
	ATL_TRACE0 (2,  "\n CBrowserWrapper::GetDoc "); 

	if (m_bLoaded)
	{
		m_spWebBrowser->get_Document(pDispatch);
		*bLoaded = VARIANT_TRUE; 
	}
	else
	{
		*bLoaded = VARIANT_FALSE; 
	}
	ATL_TRACE1(1, "\n Have we a document %d ", *bLoaded ); 

	return S_OK;
}

//===========================================================================
//
//	Method :		Stop
//
//	Description:	Kill off the event sink
//
//	Returns :		S_OK
//
//===========================================================================

STDMETHODIMP CBrowserWrapper::Stop()
{
	ATL_TRACE0 ( 2, "\n CBrowserWrapper::Stop "); 

	if  (!m_spWebBrowser) return E_FAIL; 

	HRESULT hr = AtlUnadvise(m_spWebBrowser, DIID_DWebBrowserEvents2, m_dwCookie);

	if (FAILED(hr)) ATL_TRACE1(3, "\n Failed to Unadvise %0x", hr);
	
	return hr;
}