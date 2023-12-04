//***************************************************************************
//*
//*		Name		: TXTReader.h
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

// TXTReader.h: interface for the CTXTReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TXTREADER_H__0E9E0E63_190E_11D5_859E_6CA415000000__INCLUDED_)
#define AFX_TXTREADER_H__0E9E0E63_190E_11D5_859E_6CA415000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Reader.h"
#include <fstream>

using namespace std;

class CTXTReader : public CReader  
{
public:

	int Initialise (VARIANT varDataSourceURL, CWinBlitData* pWinBlitData);
	
	int Uninitialise () ;

	int GetData(long lDataOffset, BSTR* bstrData);

	int FindString(BSTR bstrSearchString, long lSearchOffset, long lSearchDirection, long *lStringOffset);

	CTXTReader::CTXTReader(){};
	CTXTReader(eDATASOURCETYPE eDataSourceType) 
		: CReader (eDataSourceType) 
	{
		m_bstrReadBuffer = NULL; 
	};

	ifstream  m_cfstream;			
	wifstream m_wfstream;
	BSTR m_bstrReadBuffer;
	virtual ~CTXTReader();

protected:

	int  ReadData(DWORD* dwTextOffset,	BSTR* pbstrData);
};

#endif // !defined(AFX_TXTREADER_H__0E9E0E63_190E_11D5_859E_6CA415000000__INCLUDED_)
