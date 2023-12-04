//***************************************************************************
//*
//*		Name		: WinBlitExplorer.h
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
// WinBlitExplorer.h : Declaration of the CWinBlitExplorer

#ifndef __WINBLITEXPLORER_H_
#define __WINBLITEXPLORER_H_

//#define EXPLORER_BAND
#define COMM_BAND

#include "resource.h"       // main symbols
#include <shlobj.h>

#include <atlhost.h>

#include "WinBlitReaderManager_i.c"
#include "WinBlitReaderManager.h"

#include "PAKVal.h"

class ATL_NO_VTABLE CWinBlitExplorer : 
					public IDeskBand, 
					public IInputObject, 
					public IObjectWithSite,
					public IPersistStream,
					public IOleClientSite,
					public IOleInPlaceSite,
					public IOleControlSite
{
public:
	CWinBlitExplorer()
	{
		m_pSite = NULL;
		m_hWnd = NULL;
		m_pFrameWB = NULL; 
		m_iLic = 0; 
		m_dwCookie = 0;
	};
	//IOleWindow methods
	STDMETHOD (GetWindow) (HWND*) ;
	STDMETHOD (ContextSensitiveHelp) (BOOL) ;

	// IOleClientSite methods 
	STDMETHOD(SaveObject)();
	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, LPMONIKER* ppmk);
	STDMETHOD(GetContainer)(LPOLECONTAINER* ppContainer);
	STDMETHOD(ShowObject)();
	STDMETHOD(OnShowWindow)(BOOL fShow);
	STDMETHOD(RequestNewObjectLayout)();
	
	//IDockingWindow methods
	STDMETHOD (ShowDW) (BOOL fShow);
	STDMETHOD (CloseDW) (DWORD dwReserved);
	STDMETHOD (ResizeBorderDW) (LPCRECT prcBorder, IUnknown* punkToolbarSite, BOOL fReserved);

	//IDeskBand methods
	STDMETHOD (GetBandInfo) (DWORD, DWORD, DESKBANDINFO*) {return S_OK;};

	//IInputObject methods
	STDMETHOD (UIActivateIO) (BOOL, LPMSG);
	STDMETHOD (HasFocusIO) (void);
	STDMETHOD (TranslateAcceleratorIO) (LPMSG);

	//IObjectWithSite methods
	STDMETHOD (SetSite) (IUnknown*);
	STDMETHOD (GetSite) (REFIID, LPVOID*) ;;

	//IPersistStream methods
	STDMETHOD (GetClassID) (LPCLSID) {return S_OK;};
	STDMETHOD (IsDirty) (void) ;
	STDMETHOD (Load) (LPSTREAM) ;
	STDMETHOD (Save) (LPSTREAM, BOOL);
	STDMETHOD (GetSizeMax) (ULARGE_INTEGER*) ;	

	  // IOleControlSite Methods
	STDMETHOD(OnControlInfoChanged)(void);
	STDMETHOD(LockInPlaceActive)(BOOL fLock);
	STDMETHOD(GetExtendedControl)(LPDISPATCH* ppDisp);
	STDMETHOD(TransformCoords)(POINTL* pPtlHimetric, POINTF* pPtfContainer, DWORD dwFlags);
	STDMETHOD(TranslateAccelerator)(LPMSG lpMsg, DWORD grfModifiers);
	STDMETHOD(OnFocus)(BOOL fGotFocus);
	STDMETHOD(ShowPropertyFrame)(void);

	   // IOleInPlaceSite Methods
   STDMETHOD(CanInPlaceActivate)();
   STDMETHOD(OnInPlaceActivate)();
   STDMETHOD(OnUIActivate)();
   STDMETHOD(GetWindowContext)(IOleInPlaceFrame** ppFrame, IOleInPlaceUIWindow** ppDoc,
                               LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo);
   STDMETHOD(Scroll)(SIZE scrollExtent);
   STDMETHOD(OnUIDeactivate)(BOOL fUndoable);
   STDMETHOD(OnInPlaceDeactivate)();
   STDMETHOD(DiscardUndoState)();
   STDMETHOD(DeactivateAndUndo)();
   STDMETHOD(OnPosRectChange)(LPCRECT lprcPosRect); 
public :
	IInputObjectSite *m_pSite;
	BOOL m_bFocus;
	HWND m_hwndParent;
	HWND m_hWnd;
	DWORD m_dwViewMode;
	DWORD m_dwBandID;		

private:
	bool m_bLoaded; 
	DWORD m_dwCookie;
	IWebBrowser2*      m_pFrameWB;
	CComQIPtr<IWinBlitReader> m_WinBlitWindow;
	CAxWindow m_wndView;
	void FocusChange(BOOL);
	LRESULT OnKillFocus(void);
	LRESULT OnSetFocus(void);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	LRESULT OnPaint(void);
	LRESULT OnSize (void); 
	LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
	BOOL RegisterAndCreateWindow(void);
	// Event Helper Methods
	void AdviseWBEventSink(void);
	void UnadviseWBEventSink(void);
	void CreateControl(void);
	LRESULT OnKey ( UINT uMessage, WPARAM wParam, LPARAM lParam);
	void LoadDocument (IDispatch *pDispatch);


protected :
	int m_iLic; 
	void Cleanup ()
	{
	};

	HRESULT GetConnectionPoint(LPUNKNOWN pUnk, REFIID riid, LPCONNECTIONPOINT* pCP);
	STDMETHOD(Invoke_Base)(	DISPID dispIdMember, 
							REFIID riid, 
							LCID lcid, 
							WORD wFlags, 
							DISPPARAMS* pDispParams,
							VARIANT* pVarResult, 
							EXCEPINFO* pExcepInfo, 
							UINT* puArgErr);
};

#ifdef EXPLORER_BAND
	
/////////////////////////////////////////////////////////////////////////////
// CExplorerBand
class ATL_NO_VTABLE CExplorerBand : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IExplorerBand, &IID_IExplorerBand, &LIBID_WINBLITWEBBANDLib>,
	public CComCoClass<CExplorerBand, &CLSID_ExplorerBand>,
	public CWinBlitExplorer
{
public:
	CExplorerBand()
	{
	}
	//IDeskBand methods
	STDMETHOD (GetBandInfo) (DWORD, DWORD, DESKBANDINFO*);


DECLARE_REGISTRY_RESOURCEID(IDR_EXPLORERBAND)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CExplorerBand)
	COM_INTERFACE_ENTRY(IExplorerBand)
	COM_INTERFACE_ENTRY_IID(IID_IInputObject, IInputObject)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IPersistStream)
	COM_INTERFACE_ENTRY_IID(IID_IDeskBand, IDeskBand)
	COM_INTERFACE_ENTRY(IOleInPlaceSite)
	COM_INTERFACE_ENTRY(IOleClientSite)
	COM_INTERFACE_ENTRY(IOleControlSite)
	COM_INTERFACE_ENTRY_IID(IID_IDockingWindow, IDockingWindow)
	//COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
END_COM_MAP()


// IExplorerBand
public:
	void FinalRelease ()
	{
		Cleanup();
	}

	STDMETHOD (GetClassID) (LPCLSID);

	// IDispatch Methods - fowrard to base class
	STDMETHOD(Invoke)	   (DISPID dispidMember, 
							REFIID riid, 
							LCID lcid, 
							WORD wFlags,
							DISPPARAMS* pDispParams, 
							VARIANT* pvarResult,
							EXCEPINFO*  pExcepInfo,  
							UINT* puArgErr)
	{
		return Invoke_Base( dispidMember, riid, lcid, wFlags, pDispParams, pvarResult, pExcepInfo, puArgErr);
	};
};
#endif //  EXPLORER_BAND

#ifdef COMM_BAND
////////////////////////////////////////////////////////////////////////////
// CCommBand
class ATL_NO_VTABLE CCommBand : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ICommBand, &IID_ICommBand, &LIBID_WINBLITWEBBANDLib>,
	public CComCoClass<CCommBand, &CLSID_CommBand>,
	public CWinBlitExplorer
{
public:
	CCommBand()
	{
	}


DECLARE_REGISTRY_RESOURCEID(IDR_COMMBAND)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCommBand)
	COM_INTERFACE_ENTRY(ICommBand)
	COM_INTERFACE_ENTRY_IID(IID_IInputObject, IInputObject)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IPersistStream)
	COM_INTERFACE_ENTRY_IID(IID_IDeskBand, IDeskBand)
	COM_INTERFACE_ENTRY(IOleInPlaceSite)
	COM_INTERFACE_ENTRY(IOleClientSite)
	COM_INTERFACE_ENTRY(IOleControlSite)
	COM_INTERFACE_ENTRY_IID(IID_IDockingWindow, IDockingWindow)
	//COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
END_COM_MAP()

	void FinalRelease ()
	{
		Cleanup();
	}

	//IDeskBand methods
	STDMETHOD (GetBandInfo) (DWORD, DWORD, DESKBANDINFO*);

	STDMETHOD (GetClassID) (LPCLSID);


	// IDispatch Methods
	STDMETHOD(Invoke)	(	DISPID dispidMember, 
							REFIID riid, 
							LCID lcid, 
							WORD wFlags,
							DISPPARAMS* pDispParams, 
							VARIANT* pvarResult,
							EXCEPINFO*  pExcepInfo,  
							UINT* puArgErr)
	{
		return Invoke_Base( dispidMember, riid, lcid, wFlags, pDispParams, pvarResult, pExcepInfo, puArgErr);
	};


	// ICommBand
public:
	STDMETHOD(SetDocument)(IDispatch *pDisp);
};
#endif	//  COMM_BAND


#endif //__WINBLITEXPLORER_H_
