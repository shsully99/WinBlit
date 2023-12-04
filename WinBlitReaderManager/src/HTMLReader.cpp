//***************************************************************************
//*
//*		Name		:HTMLReader.cpp
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
//*		Implementation of reader object for HTML data source 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#include "stdafx.h"
#include "HTMLReader.h"
#include "resource.h"
#include "Registry.h"
#include "StringReader.h"
#include "WinBlitDataError.h"
#include <shlobj.h>
#include <mshtml.h>
#include <ExDispID.h>



static int iLevel(0);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHTMLReader::~CHTMLReader()
{

}

//=========================================================================== 
//						
//	Method :		Initialise
//						
//	Description :	Initialise HTML data source for supplied URL
//
//  Returns	:		0  if successful 
//					1  if no data
//					2  if system error
//					
//============================================================================
//

int CHTMLReader::Initialise (VARIANT varDataSourceURL, CWinBlitData* pWinBlitData)
{
	ATL_TRACE ("\nCHTMLReader::Initialise"); 

	if (varDataSourceURL.vt != VT_DISPATCH || !varDataSourceURL.pdispVal)
	{
		ReportError(IDS_OPENING_DATASOURCE, IDS_INVALID_DATASOURCE,  E_HANDLE);
		return 2;
	}

	HRESULT hr;
	int iRet = 0;									// Assume success

	CReader::Initialise(varDataSourceURL, pWinBlitData); 

	CComQIPtr<IHTMLDocument2> pHTMLDocument (varDataSourceURL.pdispVal);
	if (pHTMLDocument.p)
	{			
		CComBSTR bstrReadyState;
		
		hr = pHTMLDocument->get_readyState(&bstrReadyState); 
		if (S_OK != hr || !bstrReadyState)
		{
			ReportError(IDS_OPENING_DATASOURCE, IDS_INVALID_READYSTATE,  E_HANDLE);
			iRet = 2;
		}
		// If the state is not complete then there is no cause to continue
		else if ( (0 != wcscmp(L"complete",    bstrReadyState)) &&
				  (0 != wcscmp(L"interactive", bstrReadyState)) )
		{
			iRet = 1;
		}
		else
		{
			CComBSTR bstrHTMLText;

			//CComPtr<IHTMLWindow2> pHTMLWindow;
			//pHTMLDocument->get_parentWindow(&pHTMLWindow);

			if (S_OK == hr && 0 == RecurseFrames(bstrHTMLText, varDataSourceURL.pdispVal))
			{
				if (bstrHTMLText.Length() > 1)
				{
					if (NULL == m_pSubReader) 
					{
						m_pSubReader = new CStringReader(e_STRING); 
					}
					if (m_pSubReader)
					{
						if (0 == m_pSubReader->Initialise(CComVariant(bstrHTMLText.m_str), m_pWinBlitData))
						{		
							m_bUseSubReader = true; 
						}
					}
				}
			}
			if (bstrHTMLText) bstrHTMLText.Empty();			
		}
	}	

	if (0 == iRet &&  !m_bUseSubReader)
	{
				// If here we have failed to allocate enough memory so will not be using
		// the string reader API. 

		// Get the Collection interface for this documents collection 

		hr = pHTMLDocument->get_all(&m_pHTMLElementCollection);
		if (FAILED(hr) || NULL == m_pHTMLElementCollection.p)
		{
			ReportError(IDS_OPENING_DATASOURCE, IDS_ALL_COLLECTION,  hr);
			iRet = 2; 
		}			
		else 
		{
			// Get the item count for the Paragraphs collection
			long lLength;
			hr = m_pHTMLElementCollection->get_length(&lLength);
			m_dwDataSourceSize = lLength;
			if (0 == m_dwDataSourceSize)
			{
				ReportError(IDS_DATASOURCE_EMPTY, NULL);
				iRet = 1;
			}
		}
	}

	if (0 == iRet)
	{
		CRegistry RegCurrent; 
		RegCurrent.SetRootKey(HKEY_LOCAL_MACHINE);

		// Read the HTML Properties from the registry
		USES_CONVERSION; 
		if (RegCurrent.SetKey (OLE2T(cbstrWinBlitKey [0]), FALSE))
		{
			CComBSTR bstrHTMLTagsAllowed;	
			if (!RegCurrent.ReadString("HTMLTagsAllowed", &bstrHTMLTagsAllowed))
			{
				bstrHTMLTagsAllowed = "<*>"; 
			}
			m_wstrHTMLTagsAllowed.assign(bstrHTMLTagsAllowed);

			CComBSTR bstrHTMLTagsBarred;
			if (!RegCurrent.ReadString("HTMLTagsBarred", &bstrHTMLTagsBarred))
			{
				bstrHTMLTagsBarred = ""; 
			}
			m_wstrHTMLTagsBarred.assign(bstrHTMLTagsBarred);

			BOOL bHTMLDuplicateTags; 
			if (RegCurrent.ReadBool("HTMLDuplicateTags", bHTMLDuplicateTags))
			{
				(bHTMLDuplicateTags  == FALSE) ? m_bHTMLDuplicateTags = false : m_bHTMLDuplicateTags = true;
			}
			else 
			{
				m_bHTMLDuplicateTags = true; 
			}

			BOOL bHTMLShowTags; 
			RegCurrent.ReadBool("HTMLShowTags", bHTMLShowTags); 
			(bHTMLShowTags  == FALSE) ? m_bHTMLShowTags = false : m_bHTMLShowTags = true;
		}
	}

	return iRet;
};

//=========================================================================== 
//						
//	Method :		Uninitialise
//						
//	Description :	Uninitialise HTML data source
//
//  Returns	:		0 if successful 
//					
//============================================================================

int CHTMLReader::Uninitialise ()
{
	if (m_bUseSubReader ) 
	{
		m_pSubReader->Uninitialise(); 
	}

	ATL_TRACE ("\nCHTMLReader::Uninitialise"); 
	m_pHTMLElementCollection.Release();
	m_pHTMLElementCollection.p = NULL;

	// Free up memory 
	m_vdwOffsets.clear(); 

	CReader::Uninitialise();

	return 0;
}


//=========================================================================== 
//						
//	Method :		GetData
//						
//	Description :	Set up user supplied data buffer for a given buffer offset 
//
//  Returns	:		0 if successful 
//					1 out of range 
//					2 system error 
//					
//============================================================================
//
int CHTMLReader::GetData(long lDataBuffer, BSTR *pbstrData)
{
	if (m_bUseSubReader)
	{
		return m_pSubReader->GetData (lDataBuffer, pbstrData); 
	}

	ATL_TRACE1 (1, "\n CHTMLReader::GetData %d ", lDataBuffer);
	int iRet = 0;
	int iHTMLOffset = 0;

	if (lDataBuffer < m_vdwOffsets.size())
	{
		iHTMLOffset = m_vdwOffsets.at(lDataBuffer);

		ReadData(&iHTMLOffset, pbstrData, false);
		USES_CONVERSION; 
		ATL_TRACE (" \n Getting.. %d %d %.64s ",::SysStringLen(*pbstrData),  lDataBuffer, OLE2T(*pbstrData));

		// We should have back the same index as we previously stored 
		ATLASSERT (iHTMLOffset ==  m_vdwOffsets.at(lDataBuffer));
	}
	else 
	{
		// Read the previous buffer in for comparison. 
		if (!m_bHTMLDuplicateTags && m_vdwOffsets.size() > 0)
		{
 			iHTMLOffset = m_vdwOffsets.at(m_vdwOffsets.size()-1);
			m_bstrPreviousString.Empty(); 
			ReadData(&iHTMLOffset, &m_bstrPreviousString);
		}
		for (int iA = m_vdwOffsets.size(); iA <= lDataBuffer; iA++)
		{
			iHTMLOffset = 0;
			bool bPrevBuffer = false; 
			if (m_vdwOffsets.size() > 0)
			{
				iHTMLOffset = m_vdwOffsets.at(iA-1) + 1;
			}
			iRet = ReadData(&iHTMLOffset, pbstrData);
			if (0 != iRet)
			{
				break;
			}
			else
			{
				USES_CONVERSION;
				ATL_TRACE (" \n Pushing back.. %d %d %.64s ",::SysStringLen(*pbstrData),  iA, OLE2T(*pbstrData));
				
				// Check for duplicates 
				if (!m_bHTMLDuplicateTags)
				{
					m_bstrPreviousString.Empty(); 
					m_bstrPreviousString = *pbstrData; 
				}
				if (m_iMaxChars != 0 && m_iTrialLastPara == -1)
				{
					CReader::TrialCheck(iA, ::SysStringLen(*pbstrData));
				}

				m_vdwOffsets.push_back(iHTMLOffset);
				iRet = 0;
			}
		}
	}
	return iRet;
}

//=========================================================================== 
//						
//	Method :		ReadData
//						
//	Description :	For a given htmlOffset class set up a block of text 
//					data from the tags in the HTML document.
//
//  Returns	:		0 if successful 
//					1 out of range 
//					2 system error 
//				
//============================================================================

int CHTMLReader::ReadData(int* iHTMLOffset, BSTR* pbstrData, bool bPerformChecks)
{
	ATL_TRACE ("\nCHTMLReader::ReadData"); 
	int iRet = 0;
	HRESULT hr;

	// Check we have been passed a free string 
	if (*pbstrData != NULL)
	{
		::SysFreeString(*pbstrData);
		*pbstrData = NULL; 
	}

	// Set up our starting index 

	int iWordIndex = *iHTMLOffset;

	if (m_dwDataSourceSize == 0 || iWordIndex > m_dwDataSourceSize)
	{
		iRet = 1;
		m_bArrayFull = true;
	}
	else if (iRet == 0)
	{
		iRet = -1;

		while (	-1 == iRet && 
				iWordIndex <= m_dwDataSourceSize)
		{
			// Get the tag at this offset 			
			CComPtr<IDispatch> pItemDispatch;
			CComVariant varIndex(iWordIndex, VT_I4 );
			CComVariant varEmpty; 
			varEmpty.vt = VT_EMPTY; 
			hr = m_pHTMLElementCollection->item(varIndex, varEmpty, &pItemDispatch);
			if (!SUCCEEDED (hr))
			{
				ATL_TRACE ("\n Failed to access Item in paragraph number %d ",m_dwDataSourceSize);
				ReportError (IDS_GETDATA, IDS_GETITEM, hr);
				iRet = 2;
			}
			else if (pItemDispatch.p)
			{
				CComQIPtr<IHTMLElement> pDispHTMLElement(pItemDispatch); 

				// Get the tag 
				CComBSTR bstrTagName;
				hr = pDispHTMLElement->get_tagName(&bstrTagName);
				if (!SUCCEEDED(hr))
				{
					ATL_TRACE ("\n System error - Failed to access tag on Element number %d ",iWordIndex+1);
					ReportError (IDS_GETDATA, IDS_TAGNAME, hr);
					iRet = 2;
				}
				else
				{
					CComBSTR bstrTag;
					bstrTag = "<";
					bstrTag.AppendBSTR(bstrTagName);
					bstrTag.Append(">");

					// Is this one of the tags we want 	
					if (	(!bstrTag) ||													// Bad tag
							(m_wstrHTMLTagsBarred.find(bstrTag) != std::wstring::npos) ||	// Tag in barred list 
							(															
								(m_wstrHTMLTagsAllowed.compare(L"<*>") != 0) &&
								(m_wstrHTMLTagsAllowed.find(bstrTag)  != std::wstring::npos) 
							)
						)
					{
						USES_CONVERSION; 
						ATL_TRACE ("\n Rejected tag %s", OLE2T(bstrTag)); 
					}
					else
					{
						// Get the text for this tag
						CComBSTR bstrInnerText; 
						hr = pDispHTMLElement->get_innerText(&bstrInnerText);
						if (!SUCCEEDED(hr))
						{
							ATL_TRACE ("\n System error - Failed to access inner Text on Element number %d ",iWordIndex+1);
							ReportError (IDS_GETDATA, IDS_INNERTEXT, hr);
							iRet = 2;
						}
						else 
						{
							if (bstrInnerText.Length() <= 0)
							{
								// If empty reject the tag 
							}
							else if (	bPerformChecks &&
										!m_bHTMLDuplicateTags && 
										IsSameAsPreviousString(bstrInnerText) )
							{
								// If a duplicate then reject the tag 
								USES_CONVERSION; 
								ATL_TRACE ("\n Duplicate tag %s", OLE2T(bstrTag)); 
							}
							else
							{
								if (m_bHTMLShowTags)
								{
									CComBSTR bstrTemp(bstrTag); 
									bstrTemp.AppendBSTR(bstrInnerText);
									*pbstrData = ::SysAllocString(bstrTemp.m_str);
								}
								else
								{
									*pbstrData = bstrInnerText;
								}
								*iHTMLOffset = iWordIndex;

								USES_CONVERSION;							
								ATL_TRACE("\n<<%s>> [[%.100s]]", OLE2T(bstrTag), OLE2T(*pbstrData));
								iRet = 0;
							}
						}
					}
				}
			}
			// No tag found so increment count 
			if (-1 == iRet) iWordIndex++;
		}

		if (-1 == iRet &&
			iWordIndex >= m_dwDataSourceSize) 
		{
			m_bArrayFull =  true; 
			iRet = 1;
		}
	}
	return iRet; 
}


//=========================================================================== 
//							
//	Method :		IsSameAsPreviousString
//							
//	Description :	See if this is the BSTR in the input parameter is the 
//					same as the previous string
//
//  Returns	:		bool
//						
//===========================================================================

bool CHTMLReader::IsSameAsPreviousString (BSTR bstrData)
{
	// Find start and end point for comparison 
	int iCurrentStart = 0;
	int iPreviousStart = 0; 
	int iPreviousEnd = m_bstrPreviousString.Length();
	int iCurrentEnd = ::SysStringLen(bstrData);

	if (iPreviousEnd <= 0 || iCurrentEnd <= 0) return false; 

	// Move start point for comparison to the  first not whitespace char in both strings 
	while (iPreviousStart < iPreviousEnd )
	{
		if (!IsWhiteSpace(m_bstrPreviousString[iPreviousStart]))
		{
			break; 
		}
		iPreviousStart++;
	}

	while (iCurrentStart < iCurrentEnd)
	{
		if (!IsWhiteSpace(bstrData[iCurrentStart]))
		{
			break; 
		}
		iCurrentStart++;
	}

	// Move end point for comparison from end of strings back to first non-whitespace char
	while (iPreviousEnd > iPreviousStart)
	{
		if (!IsWhiteSpace(m_bstrPreviousString[iPreviousEnd]))
		{
			break; 
		}
		iPreviousEnd--;
	}

	while (iCurrentEnd > iCurrentStart)
	{
		if (!IsWhiteSpace(bstrData[iCurrentEnd]))
		{
			break; 
		}
		iCurrentEnd--;
	}

	if (iCurrentEnd - iCurrentStart <= 0) return false; 

	if ( (iCurrentEnd - iCurrentStart) != (iPreviousEnd - iPreviousStart)) return false; 
	
	if (0 != wcsncmp(&bstrData[iCurrentStart], &m_bstrPreviousString.m_str[iPreviousStart],iCurrentEnd-iCurrentStart)) return false;

	return true; 
}

//=========================================================================== 
//							
//	Method :		RecurseFrames
//							
//	Description :	Append document text to the supplies string parameter for 
//					a given window. 
// 
//  Returns	:		0 if successful
//						
//===========================================================================


int CHTMLReader::RecurseFrames (CComBSTR& bstrBodyString, IDispatch* _pHTMLDispatch)
{
	ATL_TRACE("\nCHTMLReader::RecurseFrames %d\n", iLevel); 
	iLevel++;

	int iRet = 0; 
	CComQIPtr<IDispatch> pHTMLDispatch(_pHTMLDispatch);

	// Get the IDispatch of the document
	if (pHTMLDispatch.p)
	{
		CComQIPtr<IOleContainer> pContainer;

		// Get the container
		HRESULT hr = pHTMLDispatch->QueryInterface(IID_IOleContainer,
                                   (void**)&pContainer);

		if (FAILED(hr)) 	return hr;

		CComPtr<IEnumUnknown> pEnumerator;

		// Get an enumerator for the frames
		hr = pContainer->EnumObjects(OLECONTF_EMBEDDINGS, &pEnumerator);

		if (FAILED(hr)) return hr;

		CComPtr<IUnknown> pUnk;
		ULONG uFetched;

		// Enumerate and refresh all the frames
		for (UINT i = 0; S_OK == pEnumerator->Next(1, &pUnk, &uFetched); i++)
		{
			// QI for IWebBrowser here to see if we have an embedded browser
			CComPtr<IWebBrowser2> pBrowser;

			hr = pUnk->QueryInterface(IID_IWebBrowser2, (void**)&pBrowser);

			if (SUCCEEDED(hr))
			{
				CComPtr<IDispatch> pDispatch;
				if (SUCCEEDED(pBrowser->get_Document(&pDispatch)))
				{
					if (pDispatch.p)
					{
						RecurseFrames(bstrBodyString, pDispatch); 
					}	
				}
			}
			pUnk.Release();
		}

		CComQIPtr<IHTMLDocument2> pHTMLDocument (pHTMLDispatch);
		if (pHTMLDocument.p)
		{
			CComPtr<IHTMLElement> pHTMLElement;
			CComBSTR bstrTemp; 
			pHTMLDocument->get_fileSize(&bstrTemp);
			USES_CONVERSION; 
			ATL_TRACE("\n File Size %s",OLE2T(bstrTemp));
			hr = pHTMLDocument->get_body( &pHTMLElement); 
			if (S_OK == hr && pHTMLElement.p)
			{
				CComBSTR bstrInnerText;
				hr = pHTMLElement->get_innerText( &bstrInnerText); 
				{
					ATL_TRACE("\n Text Size %d",bstrInnerText.Length());
					// TODO should not do 2 appends here. 
					bstrBodyString.AppendBSTR (bstrInnerText); 
					bstrBodyString.Append    (cawchNewLine); 
				}
			}
		}
	}		

	iLevel--; 
	return 0; 
}

//=========================================================================== 
//							
//	Method :		RecurseFrames
//							
//	Description :	Append document text to the supplies string parameter for 
//					a given window. 
// 
//  Returns	:		0 if successful
//						
//===========================================================================

/*int CHTMLReader::RecurseFrames (CComBSTR& bstrBodyString, IHTMLWindow2* _pHTMLWindow2)
{
	int iRet = 0; 
	HRESULT hr;

	ATL_TRACE("\nCHTMLReader::RecurseFrames %d\n", iLevel); 
	iLevel++;

	CComPtr<IHTMLWindow2> pHTMLWindow(_pHTMLWindow2);

	CComPtr<IHTMLFramesCollection2> pHTMLFramesCollection;
	hr = pHTMLWindow->get_frames(&pHTMLFramesCollection);

	if (S_OK == hr && pHTMLFramesCollection.p)
	{
		long lLength;
		HRESULT hr = pHTMLFramesCollection->get_length( &lLength);		
 		if (S_OK == hr && 0 < lLength)
		{
			ATL_TRACE(" - number of frames %d \n", lLength);
			if (lLength > 0)
			{
				for (int iA = 0; iA < lLength ; iA++)
				{
					USES_CONVERSION;
					CComVariant varIndex(iA, VT_I4);;	
					CComVariant varItem;	
						
					hr = pHTMLFramesCollection->item(&varIndex, &varItem); 
					if (S_OK == hr) 
					{
						CComQIPtr<IHTMLWindow2> pHTMLWindow2 (varItem.pdispVal); 
						if (pHTMLWindow2.p)
						{
							RecurseFrames(bstrBodyString, pHTMLWindow2);
						}
					}
				}
			}
		}
		else 
		{
			ATL_TRACE("\nCHTMLReader::RecurseFrames - Failed to get length pointer "); 
		}
	}

	CComPtr<IHTMLDocument2> pHTMLDocument;
	hr = pHTMLWindow->get_document(&pHTMLDocument);
	if (S_OK == hr && pHTMLDocument.p)
	{
		CComPtr<IHTMLElement> pHTMLElement;
		CComBSTR bstrTemp; 
		pHTMLDocument->get_fileSize(&bstrTemp);
		USES_CONVERSION; 
		ATL_TRACE("\n File Size %s",OLE2T(bstrTemp));

		hr = pHTMLDocument->get_body( &pHTMLElement); 
		if (S_OK == hr && pHTMLElement.p)
		{
			CComBSTR bstrInnerText;
			hr = pHTMLElement->get_innerText( &bstrInnerText); 
			{
				ATL_TRACE("\n Text Size %d",bstrInnerText.Length());
				// TODO should not do 2 appends here. 
				bstrBodyString.AppendBSTR (bstrInnerText); 
				bstrBodyString.Append    (cawchNewLine); 
			}
		}
	}
	iLevel--;
	return iRet;
}*/