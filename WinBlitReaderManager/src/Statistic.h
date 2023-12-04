//***************************************************************************
//*
//*		Name		: Statistic.h
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
//*	Wizard created ATL class for interface IStatistic. 
//*	A statistic object contains a named statistic field.
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/
// Statistic.h : Declaration of the CStatistic

#ifndef __STATISTIC_H_
#define __STATISTIC_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CStatistic
class ATL_NO_VTABLE CStatistic : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStatistic, &CLSID_Statistic>,
	public ISupportErrorInfo,
	public IDispatchImpl<IStatistic, &IID_IStatistic, &LIBID_WINBLITREADERMANAGERLib>
{
public:
	CStatistic()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STATISTIC)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStatistic)
	COM_INTERFACE_ENTRY(IStatistic)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IStatistic
public:
	STDMETHOD(get_Quantity)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Quantity)(/*[in]*/  long pVal);
	STDMETHOD(get_Type)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Type)(/*[in]*/  long pVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
	long m_lType; 
	long m_lQuantity; 
	BSTR m_bstrName;
};

#endif //__STATISTIC_H_
