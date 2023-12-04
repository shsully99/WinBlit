//***************************************************************************
//*
//*		Name		: WordReader.h
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
//*	
//*
//* 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

// WordReader.h: interface for the CWordReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORDREADER_H__0E9E0E64_190E_11D5_859E_6CA415000000__INCLUDED_)
#define AFX_WORDREADER_H__0E9E0E64_190E_11D5_859E_6CA415000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Reader.h"


class CWordReader : public CReader  
{
public:

	int Initialise (VARIANT varDataSourceURL, CWinBlitData* pWinBlitData);

	int Uninitialise ();

	int GetData(long lDataOffset, BSTR* bstrData);

	int ReadData(int* iwordOffset, BSTR* pbstrData, bool bPrevBuffer = false);

	int FindString(BSTR bstrSearchString, long lSearchOffset, long lSearchDirection, long *lStringOffset){return 0;};

	CWordReader::CWordReader() {};
	CWordReader(eDATASOURCETYPE eDataSourceType) 
		: CReader(eDataSourceType)
	{
	};
	virtual ~CWordReader();
protected:
	int GetText( IDispatch *pDispatch, CWinBlitData* pWinBlitData);

	CComDispatchDriver m_pDispParagraphs;
	CComDispatchDriver m_pDispApp;
	CComDispatchDriver m_pDispDoc;
	CComDispatchDriver m_pDispParagraph; 
	CComDispatchDriver m_pDispRange;
};

#endif // !defined(AFX_WORDREADER_H__0E9E0E64_190E_11D5_859E_6CA415000000__INCLUDED_)
