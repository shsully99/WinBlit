//***************************************************************************
//*
//*		Name		: Setting.cpp
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

#include "stdafx.h"
#include "WinBlitReaderManager.h"
#include "Setting.h"

/////////////////////////////////////////////////////////////////////////////
// CSetting

STDMETHODIMP CSetting::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISetting
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSetting::get_Rule(long *pVal)
{
	*pVal = m_lRule; 

	return S_OK;
}

STDMETHODIMP CSetting::put_Rule(long newVal)
{
	m_lRule = newVal; 
	return S_OK;
}

STDMETHODIMP CSetting::get_Period(long *pVal)
{
	*pVal = m_lPeriod; 
	return S_OK;
}

STDMETHODIMP CSetting::put_Period(long newVal)
{
	m_lPeriod = newVal; 
	return S_OK;
}

STDMETHODIMP CSetting::get_Value(BSTR *pVal)
{
	*pVal = SysAllocString (m_bstrValue);
	return S_OK;
}

STDMETHODIMP CSetting::put_Value(BSTR newVal)
{
	m_bstrValue = newVal; 
	return S_OK;
}

STDMETHODIMP CSetting::get_Name(BSTR *pVal)
{
	*pVal = SysAllocString (m_bstrName);
	return (NULL != *pVal? S_OK : E_OUTOFMEMORY); 
}

STDMETHODIMP CSetting::put_Name(BSTR newVal)
{	
	m_bstrName = newVal; 
	return S_OK;
}