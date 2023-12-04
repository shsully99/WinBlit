//***************************************************************************
//*
//*		Name		: BrowserWrapper.h
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

#include "resource.h"
#include "ExDisp.h"
#include "stdafx.h"
/////////////////////////////////////////////////////////////////////////////
// CBrowserWrapper
class ATL_NO_VTABLE CBrowserWrapper : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBrowserWrapper, &CLSID_BrowserWrapper>,
	public CWindowImpl<CBrowserWrapper>,
	public IDispatchImpl<IBrowserWrapper, &IID_IBrowserWrapper, &LIBID_WINBLITREADERMANAGERLib>,
	public IOleClientSite,
	public IOleInPlaceSite
{
public:
//	Construction
	CBrowserWrapper();
	bool m_bInPlaceActive;

DECLARE_REGISTRY_RESOURCEID(IDR_BROWSERWRAPPER)

// Interface Map
BEGIN_COM_MAP(CBrowserWrapper)
	COM_INTERFACE_ENTRY(IBrowserWrapper)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IOleClientSite)
	COM_INTERFACE_ENTRY(IOleWindow)
	COM_INTERFACE_ENTRY(IOleInPlaceSite)
END_COM_MAP()


// Message Map
BEGIN_MSG_MAP(CBrowserWrapper)
	MESSAGE_HANDLER(WM_CREATE,     OnCreate)
END_MSG_MAP()

// IBrowserWrapper Methods
public:
	STDMETHOD(Stop)();
	STDMETHOD(GetDoc)(/*[out]*/ VARIANT_BOOL* bLoaded, /*[out.retval]*/ IDispatch ** pDispatch);
	STDMETHOD(Run)(BSTR bstrDataSource);
	HRESULT FinalConstruct();

protected:
	BOOL  m_bEnableCtxMenus;
	BOOL  m_bLoaded;
	DWORD m_dwDLControl;
	DWORD m_dwCookie;
	
	CComQIPtr<IWebBrowser2, &IID_IWebBrowser2> m_spWebBrowser;
	CComQIPtr<IOleInPlaceObject, &IID_IOleInPlaceObject> m_spInPlaceObject;
	CComPtr<IOleObject> spOleObject;


	LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL&);

private:

// IDispatch Methods
private:
   STDMETHOD(Invoke)(DISPID dispidMember,REFIID riid, LCID lcid, WORD wFlags,
                     DISPPARAMS * pdispparams, VARIANT * pvarResult,
                     EXCEPINFO * pexcepinfo, UINT * puArgErr);

// IOleClientSite Methods
private:


	STDMETHOD(SaveObject)(void)
	{
		ATLTRACENOTIMPL(_T("IOleClientSite::SaveObject"));
	}

	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk)
	{
		ATLTRACENOTIMPL(_T("IOleClientSite::GetMoniker"));
	}

	STDMETHOD(GetContainer)(IOleContainer **ppContainer)
	{
		ATLTRACENOTIMPL(_T("IOleClientSite::GetContainer"));
	}

	STDMETHOD(ShowObject)(void)
	{
		ATLTRACENOTIMPL(_T("IOleClientSite::ShowObject"));
	}

	STDMETHOD(OnShowWindow)(BOOL fShow)
	{
		ATLTRACENOTIMPL(_T("IOleClientSite::OnShowWindow"));
	}

	STDMETHOD(RequestNewObjectLayout)(void)
	{
		ATLTRACENOTIMPL(_T("IOleClientSite::RequestNewObjectLayout"));
	}


// IOleWindow
private:
	STDMETHOD(GetWindow)(HWND *phwnd)
	{
		*phwnd = m_hWnd;
		return S_OK;
	}

	STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode)
	{
		ATLTRACENOTIMPL(_T("IOleWindow::CanInPlaceActivate"));
	}

// IOleInPlaceSite
private:
	STDMETHOD(CanInPlaceActivate)(void)
	{
		return S_OK;
	}

	STDMETHOD(OnInPlaceActivate)(void)
	{
		m_bInPlaceActive = TRUE;
		return S_OK;
	}

	STDMETHOD(OnUIActivate)(void)
	{
		ATLTRACENOTIMPL(_T("IOleInPlaceSite::OnUIActivate"));
	}

	STDMETHOD(GetWindowContext)(IOleInPlaceFrame **ppFrame, IOleInPlaceUIWindow **ppDoc,
	                            LPRECT lprcPosRect, LPRECT lprcClipRect,
                               LPOLEINPLACEFRAMEINFO lpFrameInfo)
	{
		GetClientRect(lprcPosRect);
		GetClientRect(lprcClipRect);
		return S_OK;
	}

	STDMETHOD(Scroll)(SIZE scrollExtant)
	{
		ATLTRACENOTIMPL(_T("IOleInPlaceSite::Scroll"));
	}

	STDMETHOD(OnUIDeactivate)(BOOL fUndoable)
	{
		ATLTRACENOTIMPL(_T("IOleInPlaceSite::OnUIDeactivate"));
	}

	STDMETHOD(OnInPlaceDeactivate)( void)
	{
		m_bInPlaceActive = FALSE;
		return S_OK;
	}

	STDMETHOD(DiscardUndoState)( void)
	{
		ATLTRACENOTIMPL(_T("IOleInPlaceSite::DiscardUndoState"));
	}

	STDMETHOD(DeactivateAndUndo)( void)
	{
		ATLTRACENOTIMPL(_T("IOleInPlaceSite::DeactivateAndUndo"));
	}

	STDMETHOD(OnPosRectChange)(LPCRECT lprcPosRect)
	{
		ATLTRACENOTIMPL(_T("IOleInPlaceSite::OnPosRectChange"));
	}
};	 //__BROWSERWRAPPER_H_
