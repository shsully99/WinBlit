//***************************************************************************
//*
//*		Name		: Statistics.h
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
//*	Wizard created ATL class for interface IStatistics. It is a COM read only 
//*	collection container for all the Stastistic objects. 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/
// Statistics.h : Declaration of the CStatistics

#ifndef __STATISTICS_H_
#define __STATISTICS_H_

#include "resource.h"       // main symbols
#include "Statistic.h"

#include <vector>
#include "WinBlitConstants.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CStatistics
class ATL_NO_VTABLE CStatistics : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStatistics, &CLSID_Statistics>,
	public ISupportErrorInfo,
	public IDispatchImpl<IStatistics, &IID_IStatistics, &LIBID_WINBLITREADERMANAGERLib>
{
public:
	CStatistics()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STATISTICS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStatistics)
	COM_INTERFACE_ENTRY(IStatistics)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IStatistics
public:
	STDMETHOD(get_ItemCustom)(/*[in]*/ VARIANT Index, /*[out,retval]*/ IStatistic** ppStatistic);

	HRESULT FinalConstruct();

	std::vector <IStatistic*> m_vecStatistics;

	STDMETHOD(get_Item)(VARIANT Index, VARIANT* pVal);

	STDMETHOD(get_Count)(long* pVal);

	STDMETHOD(Reset)();

	STDMETHOD(get__NewEnum)(/*[out, retval]*/ LPUNKNOWN *pVal);

	void FinalRelease();


};

#endif //__STATISTICS_H_
