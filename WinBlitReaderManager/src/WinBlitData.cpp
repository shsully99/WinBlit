//***************************************************************************
//*
//*		Name		: WinBlitData.cpp
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

#include "stdafx.h"
#include "WinBlitReaderManager.h"
#include "WinBlitData.h"
#include "Reader.h"
#include "TXTReader.h"
#include "HTMLReader.h"
#include "WordReader.h"
#include "StringReader.h"

/////////////////////////////////////////////////////////////////////////////
// CWinBlitData


//=========================================================================== 
//						
//	CWinBlitData constructor
//						
//============================================================================
//

CWinBlitData::CWinBlitData() : m_pReader(NULL)
{
	ATL_TRACE ("\n CWinBlitData::CWinBlitData");	
}

void CWinBlitData::FinalRelease()
{
	ATL_TRACE ("\n CWinBlitData::FinalRelease");
	if (m_pReader != NULL) delete m_pReader;
	m_pReader = NULL; 
}

//=========================================================================== 
//						
//	Method :		Initialise 
//						
//	Description :	For a given datasource URL and datasource type 
//					create and initialise the required reader object 
//
//	Returns			HRESULT S_OK or S_FALSE
//
//============================================================================
//
STDMETHODIMP CWinBlitData::Initialise(long lDataSourceType, VARIANT varDataSourceURL, VARIANT varConfig)
{
	ATL_TRACE ("\n CWinBlitData::Initialise");

	HRESULT hr = S_OK;

	if (m_pReader)
	{ 
		delete m_pReader;	
		m_pReader = NULL; 
	}

	m_eDataSourceType = (eDATASOURCETYPE) lDataSourceType;

	// Create the reader type we need 
	switch (m_eDataSourceType)
	{
		case e_STRING:
		{
			m_pReader = new CStringReader(e_STRING); 
			break;
		}		
		case e_TXTFILEASCII:
		{
			m_pReader = new CTXTReader(e_TXTFILEASCII); 
			break;
		}
		case e_TXTFILEUNICODE:
		{
			m_pReader = new CTXTReader(e_TXTFILEUNICODE); 
			break;
		}
		case e_HTML_FILE:
		{
			m_pReader = new CHTMLReader(e_HTML_FILE); 
			break;
		}	
		case e_HTML_OPENDOCUMENT:
		{
			m_pReader = new CHTMLReader(e_HTML_OPENDOCUMENT); 
			break;
		}
		case e_WORD_FILE:
		{
			m_pReader = new CWordReader(e_WORD_FILE); 
			break;
		}
		case e_WORD_OPENDOCUMENT:
		{
			m_pReader = new CWordReader(e_WORD_OPENDOCUMENT); 
			break;
		}
		default:
			hr = E_INVALIDARG;
			break;
	}

	if (hr == E_INVALIDARG )
	{
	}
	else if (!m_pReader)
	{
		hr = E_OUTOFMEMORY; 
	}
	else 
	{
		int iRet = 0; 
		iRet = m_pReader->Initialise(varDataSourceURL, this);

		if (2 == iRet)
		{
			// System error 
			ATL_TRACE0 (e_LOGERROR, "Returned from Initialise with exception"); 
			hr = DISP_E_EXCEPTION; 
		}
		else if (1 == iRet)
		{
			//Data Source empty 
			hr = S_FALSE; 
		}
		else 
		{
			m_pReader->SetMaxChars(varConfig.lVal); 
		}
	}
	return hr;
};

//=========================================================================== 
//						
//	Method :		GetData
//						
//	Description :	For a given dataoffset set up the client supplied data 
//					buffer 
//	
//	Returns			HRESULT S_OK
//					S_FALSE if no more data 
///					DISP_E_EXCEPTION if error encountered 
//	
//============================================================================
//	
STDMETHODIMP CWinBlitData::GetData(long lDataOffset, BSTR* pbstrDataIn)
{
	ATL_TRACE ("\n CWinBlitData::GetData");

	if (m_pReader->GetMaxChars() > 0)
	{
		// If there is a limit on maximum characters check to see if this para is past the limit
		if ( m_pReader->GetTrialLastPara () > -1 &&
			lDataOffset > m_pReader->GetTrialLastPara ())
		{
			ATL_TRACE0(e_LOGDETAIL, "End of document"); 
			*pbstrDataIn  = ::SysAllocString(L" ***  To speed read the whole document you must purchase the full version of WinBlit. The trial version only allows viewing of a portion of large documents  *** "); 
			return S_OK; 
		}
	}

	HRESULT hr = S_OK; 
	int iRet = m_pReader->GetData(lDataOffset,  pbstrDataIn);
	if (1 == iRet)
	{
		hr = S_FALSE;						// Out of data 
	}
	else if (2 == iRet)
	{
		hr = DISP_E_EXCEPTION;
	}
	
	return hr;
}

//=========================================================================== 
//						
//	Method :		FindString
//						
//	Description :	Locate a string in the datasource 
//					
//	Returns			HRESULT S_OK or S_FALSE
//
//============================================================================

STDMETHODIMP CWinBlitData::FindString(BSTR bstrSearchString, long lSearchOffset, long lSearchDirection, long *lStringOffset)
{
	// TODO: Add your implementation code here

	return S_OK;
}

//=========================================================================== 
//						
//	Method :		Uninitialise
//						
//	Description :	Uninitialise the reader object and delete it 
// 
//	Returns			HRESULT S_OK or S_FALSE
//
//============================================================================

STDMETHODIMP CWinBlitData::Uninitialise()
{
	ATL_TRACE ("\n CWinBlitData::Uninitialise");

	if (m_pReader) m_pReader->Uninitialise();
	delete m_pReader;

	m_pReader = NULL; 
	return S_OK;
}

//=========================================================================== 
//						
//	Method :		GetParaAtPercent
//						
//	Description :	For a given paragraph find how far it
//					is into the data source 
// 
//	Returns			HRESULT S_OK or S_FALSE
//
//===========================================================================

STDMETHODIMP CWinBlitData::GetParaAtPercent(long lPercent, long *plPara, BOOL bRound)
{
	m_pReader->GetParaAtPercent(lPercent, plPara, bRound);
	return S_OK; 
}

//=========================================================================== 
//						
//	Method :		GetPercentAtPara
//						
//	Description :	For a given percentage throught the data source 
//					Find which data source closest matches it. 
// 
//	Returns			HRESULT S_OK or S_FALSE
//
//===========================================================================

STDMETHODIMP CWinBlitData::GetPercentAtPara(long* plPercent, long lPara)
{
	m_pReader->GetPercentAtPara(plPercent, lPara);

	return S_OK; 
}
