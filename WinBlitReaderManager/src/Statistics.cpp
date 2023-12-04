//***************************************************************************
//*
//*		Name		: Statistics.cpp
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

// Statistics.cpp : Implementation of CStatistics
#include "stdafx.h"
#include "WinBlitReaderManager.h"
#include "Statistics.h"

/////////////////////////////////////////////////////////////////////////////
// CStatistics

STDMETHODIMP CStatistics::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStatistics
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CStatistics::FinalConstruct()
{
	// Add the 3 standard statistic objects which we will use. 
	for (int iA = 0; iA < 3; iA++)
	{
		CComObject< CStatistic>* pTemp = NULL;
 		CComObject< CStatistic>::CreateInstance(&pTemp);

		IStatistic* pIStatistic;
		pTemp->QueryInterface(IID_IStatistic,
			reinterpret_cast<void**>(&pIStatistic));
		
		pIStatistic->put_Name(bstrStatisticNames[iA]);
		pIStatistic->put_Quantity(0);
		pIStatistic->put_Type(iA+1);
		if (pIStatistic) m_vecStatistics.push_back(pIStatistic);
	}
	return S_OK; 
}

STDMETHODIMP CStatistics::get_Item(VARIANT Index, VARIANT* pVal)
{
	HRESULT hr = E_INVALIDARG;
	CComPtr<IStatistic> pStatistic; 
	
	if (S_OK == get_ItemCustom(Index, &pStatistic))
	{
		CComQIPtr<IDispatch> pDisp(pStatistic);
		pVal->vt = VT_DISPATCH;
		pVal->pdispVal = pDisp;
		pVal->pdispVal->AddRef();		
		hr = S_OK;
	}
	return hr; 
}

STDMETHODIMP CStatistics::get_ItemCustom(VARIANT Index, IStatistic** ppStatistic)
{
	HRESULT hr = E_INVALIDARG;

	int iIndex = 0; 

	// First try numeric 
	if (Index.vt == VT_I4)
	{
		iIndex = Index.lVal;
	}
	else if (Index.vt == VT_I2)
	{
		iIndex = Index.iVal;
	}

	if (iIndex > 0)	
	{
		if (iIndex >= 1 || iIndex <= m_vecStatistics.size())
		{
			*ppStatistic  = m_vecStatistics.at(iIndex-1);
			(*ppStatistic)->AddRef();
			hr = S_OK;
		}
	}
	else if (Index.vt == VT_BSTR)
	{
		std::vector <IStatistic*>::iterator itStatistics;

		for (itStatistics = m_vecStatistics.begin(); itStatistics!=m_vecStatistics.end(); ++itStatistics)
		{
			CComPtr<IStatistic> pStatistic(*itStatistics);
			CComBSTR bstrTemp;
			pStatistic->get_Name(&bstrTemp);
			if (0 == wcscmp (bstrTemp, Index.bstrVal) )
			{
				*ppStatistic = pStatistic; 
				hr = S_OK;
			}
		}
	}
	return S_OK; 
}

STDMETHODIMP CStatistics::get_Count (long* pVal)
{
	*pVal = m_vecStatistics.size();
	return S_OK; 
}

STDMETHODIMP CStatistics::Reset()
{
	std::vector<IStatistic*>::iterator itStatistics;

	for (itStatistics = m_vecStatistics.begin(); itStatistics!=m_vecStatistics.end(); ++itStatistics)
	{
		CComPtr<IStatistic> pStatistic(*itStatistics);
		long lVal = 0;
		pStatistic->put_Quantity(lVal);
	}
	return S_OK;
}

STDMETHODIMP CStatistics::get__NewEnum(/*[out, retval]*/ LPUNKNOWN *pVal)
{
	int nSize = m_vecStatistics.size();
	VARIANT* pVT = new VARIANT[nSize];
	for(int i=0;i<nSize;i++)
	{
		pVT[i].vt = VT_DISPATCH;
		CComPtr<IStatistic> pStatistic(m_vecStatistics.at(i));
		pStatistic->QueryInterface(IID_IDispatch,(void **) &pVT[i].pdispVal);
	}

	typedef CComObject< 
		CComEnum< IEnumVARIANT, &IID_IEnumVARIANT, 
				  VARIANT, _Copy<VARIANT> > > enumVariant;

	enumVariant* pEnumVar = new enumVariant;
	pEnumVar->Init(&pVT[0], &pVT[nSize], NULL, AtlFlagCopy);
	delete [] pVT;
	return pEnumVar->QueryInterface(IID_IUnknown, 
		reinterpret_cast<void**>(pVal));
};

void CStatistics::FinalRelease()
{
	std::vector<IStatistic*>::iterator itStatistics;
	for(itStatistics = m_vecStatistics.begin(); itStatistics < m_vecStatistics.end();itStatistics++)	
	{
		IStatistic* pStatistic = *itStatistics;
		pStatistic->Release();
		pStatistic = NULL;
	}
	m_vecStatistics.clear();
}
