//***************************************************************************
//*
//*		Name		: WordReader.cpp
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


// WordReader.cpp: implementation of the CWordReader class.
//
//////////////////////////////////////////////////////////////////////
	
#include "stdafx.h"		
#include "WordReader.h"
#include "resource.h"
#include "WinBlitDataError.h"
#include "BlitUtils.h"
#include "StringReader.h"

static DISPID DispID_Count		(0);		
static DISPID DispID_Item		(0);
static DISPID DispID_Range		(0);
static DISPID DispID_Text		(0);
static DISPID DispID_Documents	(0);
static DISPID DispID_Open		(0);
static DISPID DispID_Content	(0);
static DISPID DispID_Paragraphs	(0);
static DISPID DispID_Close		(0);
static DISPID DispID_Quit		(0);
static DISPID DispID_Application(0);
static DISPID DispID_Selection  (0);
static DISPID DispID_Words  (0);

static const ciMaxWords			(50000);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWordReader::~CWordReader()
{
	ATL_TRACE0 (1,"\n CWordReader::~CWordReader");
}

//=========================================================================== 
//						
//	Method :		Initialise
//						
//	Description :	Open doc file for processing for a given path name 
//					or document. 
//
//  Returns	:		0 if successful 
//					IDS_WORD_NOT_INSTALLED
//					IDS_WORD_FAILED_TO_START
//					IDS_FILE_OPEN_FAILED if failed to open doc file 
//
//============================================================================
//
int CWordReader::Initialise (VARIANT varDataSourceURL, CWinBlitData* pWinBlitData) 
{
	CReader::Initialise(varDataSourceURL, pWinBlitData); 
	ATL_TRACE0 (2,"\n CWordReader::Initialise");

	if (varDataSourceURL.vt != VT_DISPATCH &&
		varDataSourceURL.vt != VT_BSTR )
	{
		ReportError(IDS_OPENING_DATASOURCE, IDS_INVALID_DATASOURCE,  E_HANDLE);
		return 1;
	}

	int iRet = 0;		 // Subroutine return value 
	HRESULT hr;

	if (m_pDispDoc)
	{
		m_pDispDoc.Release(); 
		m_pDispDoc.p = NULL; 
	}
	if (m_pDispParagraphs)
	{
		m_pDispParagraphs.Release(); 
		m_pDispParagraphs.p = NULL; 
	}
	if (m_pDispApp)
	{
		m_pDispApp.Release(); 
		m_pDispApp.p = NULL; 
	}
	bool bSelection = false; 
	CComDispatchDriver pDispDocs;						// Documents IDispatch pointer.	
	if (e_WORD_OPENDOCUMENT == m_eDataSourceType)
	{
		m_pDispDoc = varDataSourceURL.pdispVal;

		// Get the item count for the Paragraphs collection
		CComVariant varResult;
		if (0 == DispID_Application)
		{
			m_pDispDoc.GetIDOfName(L"Application", &DispID_Application); 
		}

		hr = m_pDispDoc.GetProperty(DispID_Application, &varResult);

		if (SUCCEEDED(hr))
		{	
			m_pDispApp = varResult.pdispVal;

			// Get the application select object
			CComVariant varResult;
			if (0 == DispID_Selection)
			{
				m_pDispApp.GetIDOfName(L"Selection", &DispID_Selection); 
			}

			hr = m_pDispApp.GetProperty(DispID_Selection, &varResult);
			if (SUCCEEDED(hr))
			{
				CComDispatchDriver pSelection (varResult.pdispVal);
				CComVariant varResult;
				if (0 == DispID_Range)
				{
					pSelection.GetIDOfName(L"Range", &DispID_Range); 
				}

				hr = pSelection.GetProperty(DispID_Range, &varResult);
				if (SUCCEEDED(hr))
				{
					iRet = GetText(varResult.pdispVal, pWinBlitData) ;
				}
			}
		}
	}
	else 
	{
		CLSID       clsid;		// Holds CLSID of server
		::CoInitialize(NULL);
		hr = CLSIDFromProgID(L"Word.Application", &clsid);
		if(!SUCCEEDED(hr))
		{
			ReportError("StringError - Failed to start Word - \n Please check that Microsoft Word is properly installed on this computer -  \n", NULL,S_OK);
			iRet = 2;
		}
		else 
		{	
			// Todo - may need to be in proc server here. 
			// Should also try GetActiveObject	
			hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER|CLSCTX_INPROC_SERVER,
			    IID_IDispatch, (void **)&m_pDispApp);
			
			if (!SUCCEEDED(hr) || !m_pDispApp.p)
			{
				ReportError(IDS_OPENING_DATASOURCE, IDS_COCREATE, hr);
				iRet = 2;
			}
			else 
			{
				// Get IDispatch* for the Documents collection object
				CComVariant varResult;
				if (0 == DispID_Documents)
				{
					m_pDispApp.GetIDOfName(L"Documents", &DispID_Documents); 
				}
				hr = m_pDispApp.GetProperty(DispID_Documents, &varResult); 
				if (!SUCCEEDED(hr) || !varResult.pdispVal)
				{
					ReportError(IDS_OPENING_DATASOURCE, IDS_GETDOCUMENTS, hr);
					iRet = 2;
				}
				else
				{
					pDispDocs = varResult.pdispVal;	
					CComBSTR bstrDataSource;
					bstrDataSource.Attach(FileString(varDataSourceURL.bstrVal));
				
					// Call Documents.Open() to open our document file
					CComVariant varResult;
					CComVariant varParam(bstrDataSource);
				
					if (0 == DispID_Open)
					{
						pDispDocs.GetIDOfName(L"Open", &DispID_Open); 
					}
					hr = pDispDocs.Invoke1(DispID_Open, &varParam, &varResult);
					if (!SUCCEEDED (hr) || !varResult.pdispVal)
					{
						ReportError(IDS_OPENING_DATASOURCE, IDS_OPENDOCUMENT, hr);
						iRet = 2;
					}
					else
					{
						m_pDispDoc = varResult.pdispVal;
					}
					
					// Clear the BSTR returned from the FileString method
					::SysFreeString(bstrDataSource.Detach()); 

				}
			}
		}
	}


	if (0 == iRet && !m_bUseSubReader)
	{
		// How many words does this document contain. 
		CComVariant varResult;
		if (0 == DispID_Words)
		{
			m_pDispDoc.GetIDOfName(L"Words", &DispID_Words); 
		}
		hr = m_pDispDoc.GetProperty(DispID_Words, &varResult); 
		if (!SUCCEEDED(hr) || !varResult.pdispVal)
		{
			ReportError(IDS_OPENING_DATASOURCE, IDS_GETWORDS, hr);
			iRet = 2;
		}
		else
		{
			CComDispatchDriver pDispWords;
			pDispWords = varResult.pdispVal;

			// Get the item count for the Paragraphs collection
			CComVariant varResult;
			if (0 == DispID_Count)
			{
				pDispWords.GetIDOfName(L"Count", &DispID_Count); 
			}

			hr = pDispWords.GetProperty(DispID_Count, &varResult);
			if (SUCCEEDED(hr))
			{
				m_dwDataSourceSize = varResult.lVal;
				if (0 == m_dwDataSourceSize)
				{
					iRet = 1;
				}
				else if (ciMaxWords < m_dwDataSourceSize)
				{
					::MessageBox(GetFocus(), 
						"The document is too large to load into WinBlit \n Please select a portion of text to speed read then click the WinBlit icon again. ", "Error ", MB_OK); 
					iRet = 1;
				}
			}
		}
	}

	if (0 == iRet && !m_bUseSubReader)
	{
		ATL_TRACE0(1, " About to get Content "); 
		CComVariant varResultContent;	
		if (0 == DispID_Content)
		{
			m_pDispDoc.GetIDOfName(L"Content", &DispID_Content); 
		}
		hr = m_pDispDoc.GetProperty(DispID_Content, &varResultContent); 

		if (!SUCCEEDED (hr) || !varResultContent.pdispVal)
		{
			ReportError(IDS_OPENING_DATASOURCE, IDS_GETCONTENT, hr);
			iRet = 2;
		}
		else 
		{
			ATL_TRACE0(e_LOGDETAIL, " About to get Text "); 
			iRet = GetText (varResultContent.pdispVal, pWinBlitData); 
		}
	}

	// If no error so far and not using the string reader
	if (0 == iRet && !m_bUseSubReader)
	{
		// Call Document.Paragraphs to acccess our paragraphs
		CComVariant varResult;
		if (0 == DispID_Paragraphs)
		{
			m_pDispDoc.GetIDOfName(L"Paragraphs", &DispID_Paragraphs); 
		}
		hr = m_pDispDoc.GetProperty(DispID_Paragraphs, &varResult); 
		if (!SUCCEEDED(hr) || !varResult.pdispVal)
		{
			ReportError(IDS_OPENING_DATASOURCE, IDS_GETPARAGRAPHS, hr);
			iRet = 2;
		}
		else
		{
			m_pDispParagraphs = varResult.pdispVal;

			// Get the item count for the Paragraphs collection
			CComVariant varResult;
			if (0 == DispID_Count)
			{
				m_pDispParagraphs.GetIDOfName(L"Count", &DispID_Count); 
			}

			hr = m_pDispParagraphs.GetProperty(DispID_Count, &varResult);
			if (!SUCCEEDED(hr) || !varResult.pdispVal)
			{
				ReportError(IDS_OPENING_DATASOURCE, IDS_GETCOUNT, hr);
				iRet = 2;
			}
			else
			{
				m_dwDataSourceSize = varResult.lVal;
				if (0 == m_dwDataSourceSize)
				{
					iRet = 1;
				}
				else
				{
					// Clear our array of data offsets. 
					m_vdwOffsets.clear();
					m_vdwOffsets.resize(varResult.lVal); 
					for (int iA = 0; iA < m_dwDataSourceSize; iA++)
					{
						m_vdwOffsets[iA] = iA+1;
					}
					m_bArrayFull = true;
				}
			}
		}
	}

	ATL_TRACE0(e_LOGDETAIL, "\n Returning for Initialise "); 

	return iRet;
};



//=========================================================================== 
//						
//	Method :		ReadData
//						
//	Description :	For a given wordOffset class set up a block of text 
//					data from the paragraphs collection in the word document.
//
//  Returns	:		0 if successful 
//					1 if out of data 
//					2 if system error 
//					
//============================================================================
//
int CWordReader::ReadData(int* iWordOffset, BSTR* pbstrData, bool bPrevBuffer)
{
	ATL_TRACE0 (3, "\n CWordReader::ReadData");

	// Check we have been passed a free string 
	if (*pbstrData != NULL)
	{
		::SysFreeString(*pbstrData);
		*pbstrData = NULL; 
	}

	int iRet = 0;
	int iWordIndex = *iWordOffset;

	if (iWordIndex > m_dwDataSourceSize)
	{
		iRet = 1;
		m_bArrayFull = true;
	}
	else
	{
		// Get the range item for this Paragraph
		CComVariant varResult;
		CComVariant varParam (iWordIndex+1, VT_I4);

		if ( 0 == DispID_Item)
		{
			m_pDispParagraphs.GetIDOfName(L"Item", &DispID_Item); 
		}
		ATL_TRACE0 (e_LOGDETAIL, " Got Item ");

		HRESULT hr = m_pDispParagraphs.Invoke1(DispID_Item, &varParam, &varResult);  
		if (!SUCCEEDED(hr) || !varResult.pdispVal)
		{
			iRet = 2;
			ATL_TRACE1 (3, "\n Failed to access item in paragraph number %d ",iWordIndex+1);
			ReportError(IDS_GETDATA, IDS_GETITEM, hr);
		}
		else
		{
			m_pDispParagraph = varResult.pdispVal;

			// Get the range item for this Paragraph
			CComVariant varResult;
			if ( 0 == DispID_Range)
			{
				m_pDispParagraph.GetIDOfName(L"Range", &DispID_Range); 
			}
			hr = m_pDispParagraph.GetProperty(DispID_Range,  &varResult);
			ATL_TRACE0 (e_LOGDETAIL, " Range ");
			if (FAILED (hr))
			{
				iRet = 2;
				ATL_TRACE1 (3,"\n Failed to access Range on Paragraph number %d ",iWordIndex+1);
				ReportError(IDS_GETDATA, IDS_GETRANGE, hr);
			}
			else
			{
				m_pDispRange = varResult.pdispVal;

				// Get the range item for this Paragraph
				CComVariant varResult;
				if ( 0 == DispID_Text)
				{
					m_pDispRange.GetIDOfName(L"Text", &DispID_Text); 
				}

				hr = m_pDispRange.GetProperty(DispID_Text,&varResult);
				ATL_TRACE0 (e_LOGDETAIL, " Got Text ");

				if (FAILED (hr))
				{
					ATL_TRACE1 (3, "\n Failed to access Text on Paragraph number %d ",iWordIndex+1);
					ReportError(IDS_GETDATA, IDS_GETTEXT, hr);
					iRet = 2;
				}
				else 
				{
					*pbstrData = varResult.bstrVal;
					*iWordOffset = iWordIndex; 
					USES_CONVERSION;
				}
			}
		}
	}

	return iRet; 
}

//=========================================================================== 
//						
//	Method :		GetData
//						
//	Description :	Set up user supplied data buffer for a given buffer offset 
//
//  Returns	:		0 if successful 
//					1 if no data 
//					2 if system error
//					
//============================================================================
//
int CWordReader::GetData(long lDataBuffer, BSTR* pbstrData)
{
	ATL_TRACE0 (2, "\n CWordReader::GetData ");

	if (m_bUseSubReader)
	{
		return m_pSubReader->GetData (lDataBuffer, pbstrData); 
	}

	int iWordOffset = 0;
	int iRet = 0;
	if (lDataBuffer < m_vdwOffsets.size())
	{
		iWordOffset = m_vdwOffsets.at(lDataBuffer);

		iRet = ReadData(&iWordOffset, pbstrData);		
		// We should have back the same index as we previously stored 
		ATLASSERT (iWordOffset ==  m_vdwOffsets.at(lDataBuffer));
	}
	else 
	{
		for (int iA = m_vdwOffsets.size(); iA <= lDataBuffer; iA++)
		{
			iWordOffset = 0;
			if (m_vdwOffsets.size() > 0)
			{
				iWordOffset = m_vdwOffsets.at(iA-1) + 1;
			}

			iRet = ReadData(&iWordOffset, pbstrData);
			if (0 != iRet)
			{
				break;
			}
			else
			{
				if (m_iMaxChars != 0 && m_iTrialLastPara == -1)
				{
					CReader::TrialCheck(iA, ::SysStringLen(*pbstrData));
				}
				m_vdwOffsets.push_back(iWordOffset);
				ATL_TRACE2 (1, " -- %d %d ", iWordOffset, iA); 
			}
		}
	}

	return iRet;
}

//=========================================================================== 
//						
//	Method :		Uninitialise
//						
//	Description :	Uninitialise Word data source
//
//  Returns	:		0 if successful 
//					
//============================================================================

int CWordReader::Uninitialise ()
{
	ATL_TRACE0 (1, "\n CWordReader::Uninitialise");

	if (m_bUseSubReader ) 
	{
		m_pSubReader->Uninitialise(); 
	}

	HRESULT hr;

	// Release paragraphs pointer
	if (m_pDispParagraphs.p)
	{
		m_pDispParagraphs.Release();
		m_pDispParagraphs.p = NULL; 
	}

	// Close down our open document
	if (m_pDispDoc.p)
	{
		CComVariant varResult;
		CComVariant varParam(false);

		if (0 == DispID_Close)
		{
			hr = m_pDispDoc.GetIDOfName(L"Close", &DispID_Close); 
		}
		hr = m_pDispDoc.Invoke1(DispID_Close, &varParam, &varResult); 
		m_pDispDoc.Release();
		m_pDispDoc.p = NULL; 
	}

	// Quit the application 
	if (m_pDispApp.p)
	{
		CComVariant varResult;
		if (0 == DispID_Quit)
		{
			hr = m_pDispApp.GetIDOfName(L"Quit", &DispID_Quit); 
		}

		hr = m_pDispApp.Invoke0(DispID_Quit, &varResult);

		m_pDispApp.Release();
		m_pDispApp.p = NULL; 
	}

	// Free up memory 
	m_vdwOffsets.clear();

	// Base class uninitialise 
	CReader::Uninitialise();

	return 0;
}

//=========================================================================== 
//						
//	Method :		Uninitialise
//						
//	Description :	Uninitialise Word data source
//
//  Returns	:		0 if successful 
//					
//============================================================================

int CWordReader::GetText( IDispatch *pDispatch, CWinBlitData* pWinBlitData)
{
	int iRet = 0;
	CComDispatchDriver pResultContent (pDispatch);
	CComVariant varResultText;
	if (0 == DispID_Text)
	{
		pResultContent.GetIDOfName(L"Text", &DispID_Text); 
	}

	HRESULT hr = pResultContent.GetProperty( DispID_Text, &varResultText);
	if (SUCCEEDED (hr) &&  varResultText.bstrVal)
	{
		// Try and use the String Reader = do not report errors here 
		// If there is a failure we will continue without using the StringReader
		if (m_pSubReader == NULL) 
		{
			m_pSubReader = new CStringReader(e_STRING);
		}
		if (m_pSubReader)
		{
			// Use the string reader if we can
			ATL_TRACE0(1, " About to init string reader "); 

			if (0 == m_pSubReader->Initialise(varResultText, pWinBlitData)) 
			{
				ATL_TRACE0(1, " String reader initialised "); 

				m_bUseSubReader = true;
			}
			else
			{
				m_pSubReader->Uninitialise();
			}
		}
	}
	return iRet; 
}