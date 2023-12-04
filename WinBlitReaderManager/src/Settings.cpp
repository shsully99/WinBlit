//***************************************************************************
//*
//*		Name		: Settings.cpp
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
//*		COM collection container for all of the Setting objects 
//*		Supports all of the standard collection method calls  
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#include "stdafx.h"
#include "WinBlitReaderManager.h"
#include "Settings.h"

/////////////////////////////////////////////////////////////////////////////
// CSettings

STDMETHODIMP CSettings::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISettings
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CSettings::get_ItemCustom (VARIANT Index, ISetting** ppSetting)
{
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
		if (iIndex >= 1 || iIndex <= m_vecSettings.size())
		{
			*ppSetting  = m_vecSettings.at(iIndex-1);
			(*ppSetting)->AddRef(); 
			return S_OK;
		}
	}
	else if (Index.vt == VT_BSTR)
	{
		std::vector <ISetting*>::iterator itSettings;
		for (itSettings = m_vecSettings.begin(); itSettings!=m_vecSettings.end(); ++itSettings)
		{
			CComPtr<ISetting> pSetting(*itSettings);
			CComBSTR bstrTemp;
			pSetting->get_Name(&bstrTemp);
			USES_CONVERSION; 
			ATL_TRACE2 (e_LOGDETAIL, " Comparing %s %s ",OLE2T(bstrTemp), OLE2T(Index.bstrVal)); 

			if (0 == wcscmp (bstrTemp, Index.bstrVal))
			{
				ATL_TRACE0 (e_LOGDETAIL, " Compare successful "); 

				*ppSetting = pSetting; 				
				(*ppSetting)->AddRef(); 
				return S_OK;
			}
		}
	}
	return E_INVALIDARG;			
}

STDMETHODIMP CSettings::get_Item (VARIANT Index, VARIANT* pVal)
{
	HRESULT hr = E_INVALIDARG;

	CComPtr<ISetting> pSetting; 
	if (S_OK == get_ItemCustom(Index, &pSetting))
	{
		CComQIPtr<IDispatch> pDisp(pSetting);
		pVal->vt = VT_DISPATCH;
		pVal->pdispVal = pDisp;
		pVal->pdispVal->AddRef();
		hr = S_OK;
	}
	return hr; 
}

STDMETHODIMP CSettings::get_Count(long* pVal)
{
	*pVal = m_vecSettings.size();
	return S_OK; 
}

STDMETHODIMP CSettings::Add(BSTR bstrKey,
				long lIndex,
				long lRule,
				BSTR bstrValue,
				long lPeriod )
{
	HRESULT hr = E_INVALIDARG;
	// If the client has specified a key make sure that it is not duplicated
	if (bstrKey)
	{
		std::vector <ISetting*>::iterator itSettings;

		for (itSettings = m_vecSettings.begin(); itSettings!=m_vecSettings.end(); ++itSettings)
		{
			CComPtr<ISetting> pSetting(*itSettings);
			CComBSTR bstrTemp;
			pSetting->get_Name(&bstrTemp);
			if (0 == wcscmp  (bstrTemp, bstrKey) )
			{
				return AtlReportError(GetObjectCLSID(), _T("A Setting with this name already exists "), GUID_NULL, 0);
			}
		}
	}

	CComObject< CSetting >* pTemp = NULL;
	CComObject< CSetting>::CreateInstance(&pTemp);
	if (pTemp)
	{
		ISetting* pSetting;
		pTemp->QueryInterface(IID_ISetting,
			reinterpret_cast<void**>(&pSetting));

		pSetting->put_Name(bstrKey);
		pSetting->put_Rule(lRule);
		pSetting->put_Value(bstrValue);
		pSetting->put_Period(lPeriod);

		m_vecSettings.push_back(pSetting);
		hr = S_OK;
	}
	return hr;
}

STDMETHODIMP CSettings::Remove(VARIANT Index)
{
	ATL_TRACE ("\n Setting::Remove"); 
	// First try numeric 
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
		if (Index.lVal < 1 || Index.lVal > m_vecSettings.size())
			return E_INVALIDARG;			
	
		std::vector <ISetting*>::iterator it;
	
		int iA = 0;
		for (it = m_vecSettings.begin(); it != m_vecSettings.end(); ++it)
		{
			if (iA == Index.lVal-1)
			{										
				CComPtr<ISetting> pSetting = *it;  
				pSetting.Release();
				pSetting = NULL;
				m_vecSettings.erase(it);
				return S_OK;
			}
			iA++;
		}
	}
	else if (Index.vt == VT_BSTR)
	{
		std::vector <ISetting*>::iterator itSettings;

		for (itSettings = m_vecSettings.begin(); itSettings!=m_vecSettings.end(); ++itSettings)
		{
			CComPtr<ISetting> pSetting(*itSettings);
			CComBSTR bstrTemp;
			pSetting->get_Name(&bstrTemp);
			if (0 == wcscmp (bstrTemp, Index.bstrVal) )
			{
				pSetting.Release();
				pSetting = NULL;
				m_vecSettings.erase(itSettings);
				return S_OK;
			}
		}
	}

	return E_INVALIDARG;
}

STDMETHODIMP CSettings::Clear()
{
	std::vector<ISetting*>::iterator itSettings;

	for (itSettings = m_vecSettings.begin(); itSettings!=m_vecSettings.end(); ++itSettings)
	{
		CComPtr<ISetting> pSetting(*itSettings);
		pSetting.Release();
		pSetting =NULL; 
	}
	m_vecSettings.clear(); 
	return S_OK;
}

STDMETHODIMP CSettings::get__NewEnum(/*[out, retval]*/ LPUNKNOWN *pVal)
{
	int nSize = m_vecSettings.size();
	VARIANT* pVT = new VARIANT[nSize];
	for(int i=0;i<nSize;i++)
	{
		pVT[i].vt = VT_DISPATCH;
		CComPtr<ISetting> pSetting(m_vecSettings.at(i));
		pSetting->QueryInterface(IID_IDispatch,(void **) &pVT[i].pdispVal);
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

void CSettings::FinalRelease()
{
	std::vector<ISetting*>::iterator itSettings;
	for(itSettings = m_vecSettings.begin(); itSettings < m_vecSettings.end();itSettings++)	
	{
		ISetting* pSetting = *itSettings;
		pSetting->Release();
		pSetting = NULL;
	}
	m_vecSettings.clear();
}
