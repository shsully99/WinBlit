//***************************************************************************
//*
//*		Name		: Setting.h
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
//*		A setting object is a container of properties 
//*		which adds further customisation to WinBlit
//*		Gets/puts the properties of a setting. 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

// Setting.h : Declaration of the CSetting

#ifndef __SETTING_H_
#define __SETTING_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSetting
class ATL_NO_VTABLE CSetting : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSetting, &CLSID_Setting>,
	public ISupportErrorInfo,
	public IDispatchImpl<ISetting, &IID_ISetting, &LIBID_WINBLITREADERMANAGERLib>

{
public:
	CSetting()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SETTING)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSetting)
	COM_INTERFACE_ENTRY(ISetting)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISetting
public:
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Value)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Value)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Period)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Period)(/*[in]*/ long newVal);
	STDMETHOD(get_Rule)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Rule)(/*[in]*/ long newVal);

	CComBSTR m_bstrName;
	CComBSTR m_bstrValue;
	long m_lPeriod;
	long m_lRule; 
};

#endif //__SETTING_H_
