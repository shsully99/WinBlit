//***************************************************************************
//*
//*		Name		: Statistic.cpp
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

// Statistic.cpp : Implementation of CStatistic
#include "stdafx.h"
#include "WinBlitReaderManager.h"
#include "Statistic.h"

/////////////////////////////////////////////////////////////////////////////
// CStatistic

STDMETHODIMP CStatistic::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStatistic
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CStatistic::get_Type(long *pVal)
{
	*pVal = m_lType;
	return S_OK;
}

STDMETHODIMP CStatistic::put_Type(long newVal)
{
	m_lType = newVal;
	return S_OK;
}

STDMETHODIMP CStatistic::get_Quantity(long *pVal)
{
	*pVal = m_lQuantity;
	return S_OK;
}

STDMETHODIMP CStatistic::put_Quantity(long newVal)
{
	m_lQuantity = newVal;
	return S_OK;
}

STDMETHODIMP CStatistic::get_Name(BSTR *pVal)
{
	*pVal = ::SysAllocString (m_bstrName);
	return (NULL != *pVal? S_OK : E_OUTOFMEMORY); 
}

STDMETHODIMP CStatistic::put_Name(BSTR newVal)
{
	m_bstrName = newVal; 
	return S_OK;
}