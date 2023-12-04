//***************************************************************************
//*
//*		Name		: StringReader.h
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
//*		Implementation of reader object for Strings
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#if !defined(AFX_STRINGREADER_H__152CFDE3_4932_11D5_85E3_0E2D55000000__INCLUDED_)
#define AFX_STRINGREADER_H__152CFDE3_4932_11D5_85E3_0E2D55000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Reader.h"

class CStringReader : public CReader  
{
public:

	int Initialise (VARIANT varDataSourceURL, CWinBlitData* pWinBlitData);
	
	int Uninitialise () ;

	int GetData(long lDataOffset, BSTR* bstrData);

	int FindString(BSTR bstrSearchString, long lSearchOffset, long lSearchDirection, long *lStringOffset);

	CStringReader::CStringReader() : m_bstrStringBuffer(NULL) {};
	CStringReader(eDATASOURCETYPE eDataSourceType) 
		: CReader (eDataSourceType), m_bstrStringBuffer(NULL)
	{
	};

	BSTR m_bstrStringBuffer; 
	virtual ~CStringReader();
	
protected:
	int  ReadData(DWORD* dwTextOffset,	BSTR* pbstrData);

};
#endif // !defined(AFX_STRINGREADER_H__152CFDE3_4932_11D5_85E3_0E2D55000000__INCLUDED_)
