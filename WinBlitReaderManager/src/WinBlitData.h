//***************************************************************************
//*
//*		Name		: WinBlitData.h
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
//*		Implements interfaces for WinBlitData object.Creates and forwards 
//*		calls to the appropriate reader object 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

// WinBlitData.h : Declaration of the CWinBlitData

#ifndef __WINBLITDATA_H_
#define __WINBLITDATA_H_

#include "resource.h"       // main symbols
#include "WinBlitConstants.h"


class CReader;

/////////////////////////////////////////////////////////////////////////////
// CWinBlitData
class ATL_NO_VTABLE CWinBlitData : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CWinBlitData, &CLSID_WinBlitData>,
	public IDispatchImpl<IWinBlitData, &IID_IWinBlitData, &LIBID_WINBLITREADERMANAGERLib>,
	public ISupportErrorInfo
{
public:
	CWinBlitData();


	void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_WINBLITDATA)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CWinBlitData)
	COM_INTERFACE_ENTRY(IWinBlitData)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IWinBlitData,
	};
	for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i], riid))
			return S_OK;
	}
	return S_FALSE;

}

// IWinBlitData
public:
	STDMETHOD(GetPercentAtPara)(/*[in,out]*/ long* lPercent, /*[in]*/ long lPara);
	STDMETHOD(GetParaAtPercent)(/*[in]*/ long lPercent, /*[in,out]*/ long* lPara, BOOL bRound);
	STDMETHOD(Uninitialise)();
	STDMETHOD(FindString)(/*[in]*/ BSTR bstrSearchString, /*[in]*/ long lSearchOffset, /*[in]*/ long lSearchDirection, /*[out,retval]*/ long* lStringOffset);
	STDMETHOD(GetData)(/*[in]*/ long lDataOffset, /*[in,out]*/ BSTR* bstrData);
	STDMETHOD(Initialise)(/*[in]*/ long lDataSourceType, /*[in]*/ VARIANT varDataSourceURL, /*[in]*/ VARIANT varConfig);
private:

	eDATASOURCETYPE m_eDataSourceType;
	CReader* m_pReader;
};

#endif //__WINBLITDATA_H_