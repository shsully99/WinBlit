//***************************************************************************
//*
//*		Name		: WinBlitReader.h
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
//*		The WinBlitReader object - Wizard created class which implements 
//*		IWinBlitReader methods and handles windows messages and all 
//*		messages from the container.
//*		Also implements WinBlit's state machine 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

// WinBlitReader.h : Declaration of the CWinBlitReader

#ifndef __WinBlitReader_H_
#define __WinBlitReader_H_

#include "resource.h"       // main symbols

#include <atlctrls.h>
#include <atlctrlx.h>
#include <atldlgs.h>
#include <atlhost.h>

#include "TextWindow.h"
#include "WinBlitConstants.h"
#include "SettingsDialog.h"
#include "PropPage.h"
#include "WinBlitProperties.h"
#include "WinBlitRegistry.h"

//#include "TrackBarWindow.h"

//#include "CursorTypes.h"	

static const LPCSTR pszSTATEString [8] = {	"No Data loaded   ",
											"Loading data..   ", 
											"Data loaded      ",
											"Displaying data  ",
											"Moving Trackbar..", 
											"Speed Reading    ",
											"Paused           " };

static const CComVariant varDefault (VT_EMPTY); 


class CWinBlitLicense
{
public:
	static BOOL VerifyLicenseKey(BSTR bstrkey);
	static BOOL GetLicenseKey(DWORD dwRes,BSTR* pbstrKey);
	static BOOL IsLicenseValid();
};

/////////////////////////////////////////////////////////////////////////////
// CWinBlitReader
class ATL_NO_VTABLE CWinBlitReader : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CWinBlitReader, IWinBlitReader, &IID_IWinBlitReader, &LIBID_WINBLITREADERMANAGERLib>,
	public CComControl<CWinBlitReader>,
	public IPersistStreamInitImpl<CWinBlitReader>,
	public IOleControlImpl<CWinBlitReader>,
	public IOleObjectImpl<CWinBlitReader>,
	public IOleInPlaceActiveObjectImpl<CWinBlitReader>,
	public IViewObjectExImpl<CWinBlitReader>,
	public IOleInPlaceObjectWindowlessImpl<CWinBlitReader>,
	public ISupportErrorInfo,
	public IPersistStorageImpl<CWinBlitReader>,
	public ISpecifyPropertyPagesImpl<CWinBlitReader>,
	public IQuickActivateImpl<CWinBlitReader>,
	public IDataObjectImpl<CWinBlitReader>,
	public IProvideClassInfo2Impl<&CLSID_WinBlitReader, NULL,&LIBID_WINBLITREADERMANAGERLib>,
	public CComCoClass<CWinBlitReader, &CLSID_WinBlitReader>
{
public:
	CWinBlitReader();
	bool m_bUIActive;

	CToolBarCtrl m_ToolBar;
	CMultiPaneStatusBarCtrl m_sbar;
	CContainedWindowT<CTrackBarCtrl> m_TrackBar;
	//CAxWindow m_wndView;
	//CComPtr<IWinBlitReader> m_WinBlitReader; 
	HACCEL m_hAccel; 
	HWND m_hWndStatusBar;
	CWinBlitRegistry m_WinBlitRegistry;
	CWinBlitProperties m_WinBlitProperties;
	int m_iAppLic; 
	int m_iControlLic; 
	int m_iCallingApp; 
	bool m_bShowSpeedOnStatusBar;

DECLARE_REGISTRY_RESOURCEID(IDR_WINBLITREADER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_CLASSFACTORY2(CWinBlitLicense)

BEGIN_CATEGORY_MAP(CWinBlitReader)
	IMPLEMENTED_CATEGORY(CATID_SafeForScripting)
    IMPLEMENTED_CATEGORY(CATID_SafeForInitializing)
END_CATEGORY_MAP()

BEGIN_COM_MAP(CWinBlitReader)
	COM_INTERFACE_ENTRY(IWinBlitReader)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IID(CLSID_WinBlitReader, CWinBlitReader)
END_COM_MAP()

BEGIN_PROP_MAP(CWinBlitReader)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_MSG_MAP(CWinBlitReader)
	CHAIN_MSG_MAP(CComControl<CWinBlitReader>)
	MESSAGE_HANDLER(WM_TIMER, OnTimer)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	COMMAND_RANGE_HANDLER (ID_STARTBUTTON,		ID_SLOWER,			OnCommandRangeHandler); 
	COMMAND_RANGE_HANDLER (ID_CONFIG_ID_START,	ID_CONFIG_ID_END,	OnConfigurationChanged); 
	MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_MOUSEACTIVATE, OnMouseActivate)
	MESSAGE_HANDLER(WM_HELP, OnHelpCalled)
	NOTIFY_CODE_HANDLER(TTN_NEEDTEXT, OnToolbarNeedText)
	NOTIFY_CODE_HANDLER(TBN_DROPDOWN, OnToolbarDropDown)
	MESSAGE_HANDLER(WM_HSCROLL, OnHScrollTrackBar)
	DEFAULT_REFLECTION_HANDLER()
	ALT_MSG_MAP(1)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocusTrackBar)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocusTrackBar)
	END_MSG_MAP()
// Handler prototypes:

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IWinBlitReader,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)


// IWinBlitReader
public:
	STDMETHOD(get_State)(/*[out, retval]*/ long *pVal);
	STDMETHOD(ShowAbout)();
	STDMETHOD(get_DemoMode)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_DemoMode)(/*[in]*/ long newVal);
	STDMETHOD(get_SDKMode)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_SDKMode)(/*[in]*/ BOOL newVal);
	STDMETHOD(get_TemplateID)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_TemplateID)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Description)(/*[in]*/ BSTR newVal);
	STDMETHOD(ShowStatusBar)(/*[in]*/ BOOL bShowStatusBar);
	STDMETHOD(ShowMetafile)(BOOL bMetafile);
	STDMETHOD(ShowTrackBar)(/*[in]*/ BOOL bShowTrackBar);
	STDMETHOD(ShowControls)(BOOL bShow);
	STDMETHOD(get_Left)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Left)(/*[in]*/ long newVal);
	STDMETHOD(get_Right)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Right)(/*[in]*/ long newVal);
	STDMETHOD(get_Bottom)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Bottom)(/*[in]*/ long newVal);
	STDMETHOD(get_Top)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Top)(/*[in]*/ long newVal);
	STDMETHOD(get_Statistics)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(get_Settings)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(get_HighlightPeriod)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_HighlightPeriod)(/*[in]*/ long newVal);
	STDMETHOD(get_BaseTime)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_BaseTime)(/*[in]*/ long newVal);
	STDMETHOD(get_CursorHeight)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_CursorHeight)(/*[in]*/ long newVal);
	STDMETHOD(get_CursorWidth)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_CursorWidth)(/*[in]*/ long newVal);
	STDMETHOD(get_Cursor)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Cursor)(/*[in]*/ long newVal);
	STDMETHOD(get_ScreenBackColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_ScreenBackColor)(/*[in]*/ OLE_COLOR newVal);
	STDMETHOD(get_ScreenFillColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_ScreenFillColor)(/*[in]*/ OLE_COLOR newVal);
	STDMETHOD(get_ScreenTextColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_ScreenTextColor)(/*[in]*/ OLE_COLOR newVal);
	STDMETHOD(get_TextFont)(/*[out, retval]*/ IFontDisp** pVal);
	STDMETHOD(put_TextFont)(/*[in]*/ IFontDisp *pVal);
	STDMETHOD(get_BlackoutPeriod)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_BlackoutPeriod)(/*[in]*/ long newVal);
	STDMETHOD(get_DisplayPeriod)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_DisplayPeriod)(/*[in]*/ long newVal);
	STDMETHOD(get_CursorFillColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_CursorFillColor)(/*[in]*/ OLE_COLOR newVal);
	STDMETHOD(get_CursorTextColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_CursorTextColor)(/*[in]*/ OLE_COLOR newVal);

	STDMETHOD(SaveSettings)(BSTR bstrKey, long lType);
	STDMETHOD(LoadSettings)(BSTR bstrKey, long lType);

	eSTATE getState() {return m_eState;};
	STDMETHOD(Display)();
	STDMETHOD(Pause)();
	STDMETHOD(Stop)();
	STDMETHOD(Start)();
	STDMETHOD(Register)();
	STDMETHOD(ShowHelp)(long lHelpType);

	STDMETHOD(UnloadData)();
	STDMETHOD(LoadData)(/*[in]*/ long lDataSourceType, /*[in]*/ VARIANT varDataSource);
	STDMETHOD(PageDown)(/*[in]*/ long Pages);
	STDMETHOD(PageUp)(/*[in]*/ long Pages);
	STDMETHOD(LineDown)(/*[in]*/ long Lines);
	STDMETHOD(LineUp)(/*[in]*/ long LineUp);

	LRESULT OnCommandRangeHandler  (unsigned int,unsigned int,struct HWND__ *,int &);
	LRESULT OnConfigurationChanged (unsigned int,unsigned int,struct HWND__ *,int &);
	
	LRESULT OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	STDMETHOD ( TranslateAccelerator )( LPMSG pMsg );
	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKillFocusTrackBar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetFocusTrackBar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnToolbarNeedText(WPARAM, LPNMHDR pnmh, BOOL&);
	LRESULT OnToolbarDropDown(WPARAM, LPNMHDR pnmh, BOOL&);

	HRESULT FinalConstruct();
	void FinalRelease(); 

	HRESULT OnDraw(ATL_DRAWINFO& di);

	CComVariant m_varDataSource;			// Data source currently loaded
	eDATASOURCETYPE m_eDataSourceType;		// Type of data source (txt, html e.t.c)
	eSTATE m_eState;						// Current state of winblit
	int  m_iTrackBarPos;					// Current poistion of trackbar
	DWORD m_dwTickCount;					// DWORD for timer 
	CTextWindow m_TextWindow;				// 
	bool  m_bDisplayRequired;				// True if WinBlit needs to repaint itself
	vector<CSettingStrings> m_vecSettings;	// vector of all configurations 
	RECT m_SpeedRect;						// Speed rectangle
	long m_lDemoMode;						// Demo mode
	long m_lStartup;						// Start up tasks (tip of the day , demo). 

protected:
	void CheckAutoStart();
	int  LoadSettingsArray(); 
	void SetupConfigMenu(CMenu& menuConfig); 
	void ChangeTrackBarPos(int iTrackBarPos);
	void AboutBox(); 
	bool ChangeState(eSTATE eState, long lDataSourceType = 0, CComVariant varDataSource = varDefault);
	HRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void StartTimer(int iType);
	void StopTimer(int iType);
	void UpdateControls (RECT rc);
	void UpdateStatusBar (bool bUpdateStatistics = false); 
	LRESULT OnHScrollTrackBar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	BOOL m_bRepaintControls; 
	HWND m_hWndHelp; 
};
#endif //__WinBlitReader_H_