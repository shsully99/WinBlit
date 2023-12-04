//***************************************************************************
//*
//*		Name		: Settings.h
//*							
//*		$Revision:$
//*
//*		Date        : 20-Feb-2002
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
//*		COM collection container for all of the Setting objects 
//* 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

// Settings.h : Declaration of the CSettings

#ifndef __SETTINGS_H_
#define __SETTINGS_H_

#include "resource.h"       // main symbols
#include <vector>
#include "Setting.h"

using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CSettings
class ATL_NO_VTABLE CSettings : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSettings, &CLSID_Settings>,
	public ISupportErrorInfo,
	public IDispatchImpl<ISettings, &IID_ISettings, &LIBID_WINBLITREADERMANAGERLib>
{
public:
	CSettings()
	{
	}
DECLARE_REGISTRY_RESOURCEID(IDR_SETTINGS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSettings)
	COM_INTERFACE_ENTRY(ISettings)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISettings
public:
	STDMETHOD(get_ItemCustom)(VARIANT Index, ISetting** ppSetting);

	std::vector <ISetting*> m_vecSettings;

	STDMETHOD(get_Item)(VARIANT Index, VARIANT* pVal);

	STDMETHOD(get_Count)(long* pVal);

	STDMETHOD(Add)(	BSTR bstrKey,
					long lIndex,
					long lRule,
					BSTR bstrValue,
					long lPeriod );
	
	STDMETHOD(Remove)(VARIANT Index);

	STDMETHOD(Clear)();

	STDMETHOD(get__NewEnum)(/*[out, retval]*/ LPUNKNOWN *pVal);

	void FinalRelease();

};
#endif //__SETTINGS_H_