// BlitScript.h : Declaration of the CBlitScript

#ifndef __BLITSCRIPT_H_
#define __BLITSCRIPT_H_

#include "resource.h"       // main symbols
#include <atlctl.h>

// main symbols
#include "WinBlitReaderManager_i.c"
#include "WinBlitReaderManager.h"

/////////////////////////////////////////////////////////////////////////////
// CBlitScript
class ATL_NO_VTABLE CBlitScript : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IBlitScript, &IID_IBlitScript, &LIBID_WINBLITSCRIPTLib>,
	public CComControl<CBlitScript>,
	public IPersistStreamInitImpl<CBlitScript>,
	public IOleControlImpl<CBlitScript>,
	public IOleObjectImpl<CBlitScript>,
	public IOleInPlaceActiveObjectImpl<CBlitScript>,
	public IViewObjectExImpl<CBlitScript>,
	public IOleInPlaceObjectWindowlessImpl<CBlitScript>,
	public CComCoClass<CBlitScript, &CLSID_BlitScript>
{
public:
	CBlitScript()
	{
	}

	DECLARE_GET_CONTROLLING_UNKNOWN()

	DECLARE_REGISTRY_RESOURCEID(IDR_BLITSCRIPT)

	DECLARE_PROTECT_FINAL_CONSTRUCT()


	BEGIN_COM_MAP(CBlitScript)
		COM_INTERFACE_ENTRY(IBlitScript)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IWinBlitReader, m_pInnerUnk) 
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
	END_COM_MAP()

	BEGIN_PROP_MAP(CBlitScript)
		PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
		PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
		// Example entries
		// PROP_ENTRY("Property Description", dispid, clsid)
		// PROP_PAGE(CLSID_StockColorPage)
	END_PROP_MAP()

	BEGIN_MSG_MAP(CBlitScript)
		CHAIN_MSG_MAP(CComControl<CBlitScript>)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IBlitScript
public:
	STDMETHOD(Display)();
	STDMETHOD(UnloadData)();
	STDMETHOD(LoadData)(/*[in]*/ long lDataSourceType, /*[in]*/ VARIANT varDataSource);
    LPUNKNOWN m_pInnerUnk;

	CComQIPtr<IWinBlitReader> m_WinBlitReader; 

	HRESULT FinalConstruct()
	{
		HRESULT hr;
		CLSID   clsidInner;

		hr = CLSIDFromProgID(L"WinBlitReaderManager.WinBlitReader.1", &clsidInner);
		if (hr == S_OK)
		{
			CComPtr<IUnknown> pUnk = GetControllingUnknown();
			hr = CoCreateInstance	(clsidInner, NULL,
									CLSCTX_SERVER, IID_IUnknown,
									(void**)&m_pInnerUnk);
		}
		m_WinBlitReader = m_pInnerUnk;
		return hr;
	}
	void FinalRelease()
	{
		m_pInnerUnk->Release();
	} 

};

#endif //__BLITSCRIPT_H_
