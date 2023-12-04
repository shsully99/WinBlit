//***************************************************************************
//*
//*		Name		: HTMLReader.h
//*							
//*		$Revision:$
//*
//*		Date        : 20-Feb-2002
//*
//*		Author      : Sean Sullivan
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
//*		Implementation of reader object for HTML data source 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

// HTMLReader.h: interface for the CHTMLReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTMLREADER_H__0E9E0E62_190E_11D5_859E_6CA415000000__INCLUDED_)
#define AFX_HTMLREADER_H__0E9E0E62_190E_11D5_859E_6CA415000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Reader.h"
#include <string>
#include <mshtml.h>

using namespace std;

class CHTMLReader : public CReader  
{
public:

	int Initialise (VARIANT varDataSourceURL, CWinBlitData* pWinBlitData);

	int Uninitialise ();

	int GetData (long lDataBuffer, BSTR *pbstrData);
	int FindString(BSTR bstrSearchString, long lSearchOffset, long lSearchDirection, long *lStringOffset)
	{
		return 0;
	};

	CHTMLReader::CHTMLReader() 
	{
		ATLTRACE ("\n CHTMLReader::CHTMLReader - Custom call");
	};

	CHTMLReader (eDATASOURCETYPE eDataSourceType)
		:	CReader(eDataSourceType) ,
			m_bHTMLDuplicateTags(false), 
			m_bHTMLShowTags(false),
			m_bstrPreviousString(""),
			m_pHTMLElementCollection(NULL)
	{
		ATLTRACE ("\n CHTMLReader::CHTMLReader ");
	};
	//int RecurseFrames     (CComBSTR& bstrString, IHTMLWindow2 *pHTMLWindow2); 
	int RecurseFrames     (CComBSTR& bstrString, IDispatch *pDispatch); 

	virtual ~CHTMLReader();

protected:

	int ReadData(int* iHTMLOffset, BSTR* pbstrData, bool bPerformChecks = true);
	bool IsSameAsPreviousString (BSTR pbstrData); 
	bool IsWhiteSpace(WCHAR wch)
	{
		for (int iA = 0; iA < ciWhiteSpaceArraySize; iA++)
		{
			if (wch == cawchWhiteSpaceArray[iA]) return true; 
			if (static_cast<int>(wch) < 32 || static_cast<int>(wch) > 126) return true; 
		}
		return false; 
	}

	CComBSTR m_bstrPreviousString; 
	CComPtr<IHTMLElementCollection> m_pHTMLElementCollection;
	wstring m_wstrHTMLTagsBarred;
	wstring m_wstrHTMLTagsAllowed;
	bool m_bHTMLDuplicateTags;
	bool m_bHTMLShowTags;
};

#endif // !defined(AFX_HTMLREADER_H__0E9E0E62_190E_11D5_859E_6CA415000000__INCLUDED_)
