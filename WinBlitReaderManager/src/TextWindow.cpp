//***************************************************************************
//*
//*		Name		: TextWindow.cpp
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
//*		Screen display object.  Contains as member vars DC for drawing,
//*		and all of the  classes which cooperate in the drawing and 
//*		flashing cursors
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

//////////////////////////////////////////////////////////////////////
//
// TextWindow.cpp: implementation of the CTextWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TextWindow.h"
#include "WinBlitConstants.h"
#include "WinBlitReaderManager.h"
#include "WinBlitReader.h"
#include "Settings.h"
#include "Statistics.h"
#include "WinBlitProperties.h"
#include <time.h>
#include "ReportError.cpp"

enum eLicStat
{
	eUnLicensed = 0,					
	eBetaLicense = 1,					
	eTrialLicense = 2, 
	eFullLicense = 3,
	eUnknownLicenseWord	= 10					// Word App requests license
};

int compare_values( const CBlt* pBltA, const CBlt* pBltB );

/////////////////////////////////////////////////////////////////////////////
//
//	WinBlit Properties
//
/////////////////////////////////////////////////////////////////////////////


//===========================================================================
//
//	Method :			ResetBlits
//
//	Description:		Reset Blit counter to the beginning if it is already at end 
// 
//	Returns :			void
//
//===========================================================================

void CTextWindow::ResetBlits()
{
	// Position at beginning of cursor state machine 
	if (m_listBltCurrentIterator == m_listBlts.end())
	{
		m_vecCursorStateIterator = m_vecCursorStates.begin();
		m_listBltCurrentIterator = m_listBlts.begin();

		m_listBltPreviousIterator = NULL; 
		m_dwTickTock = 0; 
	}
}



//===========================================================================
//
//	Method :	:		ReDisplayOnTimer
//
//	Description:		Set flag to redisplay the full screen
//						next time there is an opportunity to
//						do so 
//
//	Returns :			void
//
//===========================================================================

void CTextWindow::ReDisplayOnTimer()
{
	// Set flag to redisplay the full screen next time there 
	// is an opportunity to do so 
	if (m_pProp->m_ePropUpdate != e_REBUILD_PAGE) m_pProp->m_ePropUpdate = e_PAINT_LEAVE_CURSOR;
}

//===========================================================================
//
//	Method :	:		ReDisplayOnTimer
//
//	Description:		Set flag to redisplay the full screen
//						next time there is an opportunity to
//						do so 
//
//	Returns :			void
//
//===========================================================================

HRESULT CTextWindow::get_Statistics(IDispatch **pVal)
{
	m_pStatistics->QueryInterface(IID_IDispatch, (void**) pVal); 
	return (NULL != *pVal? S_OK : E_FAIL);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextWindow::CTextWindow() :m_bInitialised (false)
{
	m_ClientTextRect.left = -9999;
	m_PreviousRect.left = -9999;
}

CTextWindow::~CTextWindow()
{
}

//=========================================================================== 
//						
//	Method :		MakePage
//						
//	Description :	Create a new page of paragraphs.
// 
//	Returns			0 if successful
//					
//============================================================================

int  CTextWindow::MakePage()
{	
	int iRet = 0; 

	ATL_TRACE0 (e_LOGFLOW,  "\n CTextWindow::MakePage");

	// Clear out the existing paragraphs array 	
	if (m_Paras.size() > 0) m_Paras.clear(); 

	// Keep adding paragraphs  until we have filled 
	// up a page or hit the end of the file. 
	int iParaCount = m_iCurrentFirstParagraph;
	int iLineCount = 0;

	do 
	{ 
		iRet = MakeParagraph (iParaCount, 1); 
		ATL_TRACE3 (e_LOGDETAIL, "\n Return from MakeParagraph %d %d %d", iRet,iLineCount, m_iScreenHeight );
		if (iRet > 0) 
		{
			iLineCount += iRet;

			if (iParaCount == m_iCurrentFirstParagraph)
			{
				iLineCount -= GetLineNumberforWord(m_Paras.begin(), m_iCurrentFirstWord);
			}

			iParaCount++;
		}

	}
	while (iLineCount < m_iScreenHeight && 0 <= iRet);

	SortParagraphs();

	return iRet; 	
}
//=========================================================================== 
//						
//	Method :		MovePage
//						
//	Description :	Move a page up or down a number of lines 
//
//	Returns			0 if successful
//									
//============================================================================
//
int CTextWindow::MovePage(int	iLineMove) 		// +ve = move down X lines 
{			
	ATL_TRACE1  (e_LOGDETAIL, "\n CTextWindow::MovePage %d ", iLineMove);

	int iRet = 0;

	ATLASSERT (m_iScreenHeight >= abs(iLineMove));

	LISTPARAGRAPHSITERATOR pit = m_Paras.begin(); 

	// The first word in the display is on line iA of the 
	// the first paragraph
	int iCurrentFirstLineNumber = GetLineNumberforWord(m_Paras.begin(), m_iCurrentFirstWord);

	int iCurrentFirstWord = -1;
	int iCurrentFirstParagraph = -1;

	if (iLineMove <  0)
	{
		if (iCurrentFirstLineNumber + iLineMove >= 0)
		{		
			// We are moving up but our new first line is on this para 
			// No need to add new paragraphs
			m_iCurrentFirstWord = GetWordforLineNumber(m_Paras.begin(), iCurrentFirstLineNumber + iLineMove); 
		}		
		else		
		{			
			// We must add paragraphs to the front or back 
			// on the paras to cope with the move. 
			int iParagraphNumber = pit->m_iParagraphNumber;
			int iRetPara;
			int iLineAdder;

			iLineAdder = abs(iLineMove) - iCurrentFirstLineNumber;

			while (iLineAdder > 0)
			{
				iParagraphNumber -=1;				
				iRetPara = MakeParagraph (iParagraphNumber, 0); 

				if (iRetPara < 0) 
				{
					pit = m_Paras.begin(); 
					iCurrentFirstWord = 0; 
					iCurrentFirstParagraph = pit->m_iParagraphNumber;
					iLineAdder = 0; 
					break;
				}

				if (iLineAdder-iRetPara <= 0)
				{
					pit = m_Paras.begin(); 
					iCurrentFirstWord = GetWordforLineNumber(pit, iRetPara-iLineAdder); 
					iCurrentFirstParagraph = pit->m_iParagraphNumber;
					iLineAdder = 0; 
					break; 
				}
				iLineAdder -= iRetPara; 
			}
		}
	}
	else
	{
		int iParagraphNumber = m_iCurrentFirstParagraph; 
		int iLineTotal = iLineMove + m_iScreenHeight;
		int iLineCount = 0;
		int iLinesOnParaCount = iCurrentFirstLineNumber; 
		int iCurrentLastParagraph = m_Paras.back().m_iParagraphNumber;

		while (iLineCount < iLineTotal)
		{
			if (-1 == iLinesOnParaCount)
			{
				iLinesOnParaCount = 0;
				// Read in another paragraph if we have exhausted line count on this one.
				iParagraphNumber+=1;				
				if (iParagraphNumber <= iCurrentLastParagraph)
				{
					pit++;
				}
				else
				{
					int iA = MakeParagraph (iParagraphNumber, 1);
					pit = m_Paras.end(); pit--;
					if (iA < 0)
					{
						// No more paragraphs
						if (-1 == iCurrentFirstWord)
						{
							iCurrentFirstParagraph = pit->m_iParagraphNumber;
							iCurrentFirstWord = GetWordforLineNumber(pit, pit->m_iLineCount-1); 
						}
						break;
					}
				}
			}

			while (iLinesOnParaCount < pit->m_iLineCount &&
				   iLineCount        < iLineTotal)
			{
				if (iLineCount  == iLineMove)
				{
					iCurrentFirstWord = GetWordforLineNumber(pit, iLinesOnParaCount); 
					iCurrentFirstParagraph = pit->m_iParagraphNumber;
				}

				// We have added enough paragraphs to fill up the screen. 
				if (iLineCount == iLineTotal)
				{
					break;
				}
				iLineCount++; 
				iLinesOnParaCount++;
			}
			iLinesOnParaCount = -1;
		}
	}			

	// Change member variables if we have moved successfully 
	if (-1 != iCurrentFirstWord  && 0 == iRet)
	{
		m_iCurrentFirstWord = iCurrentFirstWord;
		m_iCurrentFirstParagraph = iCurrentFirstParagraph;
	}
	else
	{
		return 1; 
	}

	SortParagraphs ();
	
	return iRet; 
}

//=========================================================================== 
//						
//	Method :		MovePercentage
//						
//	Description :	Move to a percentage of the total data source
//
//	Returns			0 if successful
//									
//============================================================================
//
int CTextWindow::MovePercentage (int iPercentage) 	
{
	ATL_TRACE0  (e_LOGFLOW,  "\n CTextWindow::MovePercentage");

	int iRet = 0; 

	// Clear out the existing paragraphs array 	
	if (m_Paras.size() > 0) m_Paras.clear(); 

	bool bRound = true;
	if (iPercentage < 0) bRound = false; 
	long lParaCount = 0; 
	m_pWinBlitData->GetParaAtPercent(abs(iPercentage), &lParaCount, bRound);  

	m_iCurrentFirstWord = 0;
	m_iCurrentFirstParagraph = lParaCount; 

	// Keep adding paragraphs  until we have filled 
	// up a page or hit the end of the file. 
	int iLineCount = 0; 
	do 
	{ 
		iRet = MakeParagraph (lParaCount, 1); 
		if (iRet > 0) 
		{
			iLineCount += iRet;
			lParaCount++;
		}
	}
	while (iLineCount < m_iScreenHeight && 0 <= iRet);

	SortParagraphs ();

	return iRet; 
}

//=========================================================================== 
//						
//	Method :		SortParagraphs
//						
//	Description :	Remove unnecessary paragraphs from the paragraphs list 
//					and set up member variables
//
//============================================================================
int CTextWindow::SortParagraphs ()	
{
	ATL_TRACE0 (e_LOGFLOW, "\n CTextWindow::SortParagraphs");

	// Iterator for removing unnecessary paras
	LISTPARAGRAPHSITERATOR pit = m_Paras.begin();
	if (pit->m_iParagraphNumber < m_iCurrentFirstParagraph)
	{
		// Remove all paragraphs whose paragraph number is 
		// less than the  current first paragraph number. 
		while (pit != m_Paras.end() && 
			   pit->m_iParagraphNumber < m_iCurrentFirstParagraph)
		{
			pit++;
		}
		m_Paras.erase(m_Paras.begin(), pit);
		pit = m_Paras.begin();
	}

	// Now remove all paragraphs beyond the end of the screen display 
	// Start the line count from the first line offset in first paragraph
	int iLineCount = 0;
	int iLineOffset = GetLineNumberforWord(pit, m_iCurrentFirstWord);

	if (pit == m_Paras.end())
	{
		ATL_TRACE1 (e_LOGDETAIL, " End of paras %d ", m_Paras.size());
	}

	while (iLineCount <= m_iScreenHeight && pit != m_Paras.end())
	{
		ATL_TRACE2 (e_LOGDETAIL, "\n Counting lines -- %d %d", iLineOffset, pit->m_iLineCount);
		iLineCount += pit->m_iLineCount - iLineOffset;
		iLineOffset = 0;
		pit++;
		if (pit == m_Paras.end())
		{
			ATL_TRACE0 (e_LOGDETAIL, "\n End of Para"); 
		}

	}
	m_iDisplayCount = iLineCount; 

	ATL_TRACE2 (e_LOGDETAIL, "\n *** In SortParagraphs page *** %d %d ", m_iScreenHeight, m_iDisplayCount);

	if (pit != m_Paras.end())
	{
		m_Paras.erase(pit, m_Paras.end()); 
	}
	
	return 0;
}

//=========================================================================== 
//						
//	Method :		MakeParagraph
//						
//	Description :	Create a paragraph and add it to 
//					the front or back of the paragraphs list 
// 
//	Returns			Nos of lines in paragraph if >=0
//					-ve if error 
//
//============================================================================

int CTextWindow::MakeParagraph (int iParagraphNumber,	// Paragraph number to add 
								int iLocation)			// Hardware device context
{
	ATL_TRACE1 (e_LOGFLOW, "\n CTextWindow::Making Paragraph No, ---  %d  --- ", iParagraphNumber);
	if (iParagraphNumber < 0) 
	{
		return -1;
	}

	BSTR bstrVal = NULL; 

	HRESULT hr;

	if (1 == m_pWinBlitReader->m_lDemoMode)
	{
		hr= m_pWinBlitData->GetData(0, &bstrVal);
	}
	else
	{
		hr= m_pWinBlitData->GetData(iParagraphNumber, &bstrVal);
	}

	if (DISP_E_EXCEPTION == hr) 
	{
		return -1; 
	}
	else if (!SUCCEEDED(hr))
	{
		Report_Error("WinBlit - An error occured reading from the data source - Code %X \n If this problem persists please report it to Product Support. ", hr);
		return -1; 
	}
	else if (!bstrVal || 0 == ::SysStringLen(bstrVal))
	{
		ATL_TRACE2 (e_LOGDETAIL, "\n Error %d  %d ",hr, ::SysStringLen(bstrVal));
		return -1;			// End of file or error. 
	}

	// Initialise return value
	int iLineCount = -1; 
	int iTempb = ::SysStringLen(bstrVal); 

	// Add our new paragraph to the front or back of the Paragraphs list 
	if (0 == iLocation)
	{
		m_Paras.push_front(CParagraph(iParagraphNumber, bstrVal));
	}
	else 
	{
		m_Paras.push_back(CParagraph(iParagraphNumber , bstrVal));
	}

	LISTPARAGRAPHSREFERENCE lref = (0 == iLocation) ? m_Paras.front() : m_Paras.back();	

	int iTempc = ::SysStringLen(bstrVal); 
	::SysFreeString(bstrVal); 

	lref.m_vecWords.clear(); 

	int iCharTotal = lref.m_str.size();
	int iCharCount = -1;
	int iLineWidth = m_iLineWidth;
	int iWordWidth = 0;
	int iWordLength = 0;
	int iWordCount = 0;
	int iOldLineCount = -1;

	eWORDSTATE eWordState;

	bool bNewLineFound = false; 
	lref.m_bWhitespace = true;					// Assume that para is all non-whitespace 

	while (++iCharCount < iCharTotal)
	{
		if (static_cast<int>(lref.m_str[iCharCount]) < 0 || static_cast<int>(lref.m_str[iCharCount]) > 256) 
			lref.m_str[iCharCount] = ' ';

		short sChar = static_cast<short>(lref.m_str[iCharCount]); 

		if (sChar == icr && iCharTotal != iCharCount+1 && iCharTotal != iCharCount+2) bNewLineFound = true;

		if (sChar < 32 || sChar > 126) 
		{
			sChar = 32;
			lref.m_str[iCharCount] = static_cast<WCHAR>(' '); 
		}

		if (0 == iCharCount)
		{
			if (cwchSpace == lref.m_str[0])
			{
				eWordState = EAT_WHITESPACE_BEFORE_WORD; 
			}
			else 
			{
				eWordState = EAT_WORD_UNTIL_WHITESPACE; 
			}
		}

		iWordWidth += m_Ascii2Ext[sChar];
		iWordLength++;
		
		// Look at the next character to determine if this is the end of the word
		if (cwchNull    == lref.m_str[iCharCount+1] || 
			cwchCR      == lref.m_str[iCharCount+1])		// End of string 
		{
			eWordState = FINISHED_EATING;
		}
		else if (cwchSpace != lref.m_str[iCharCount+1] && eWordState == EAT_WHITESPACE_BEFORE_WORD)
		{
			eWordState = EAT_WORD_UNTIL_WHITESPACE;
		}		
		else if (cwchSpace == lref.m_str[iCharCount+1] && eWordState == EAT_WORD_UNTIL_WHITESPACE)
		{
			eWordState = EAT_WHITESPACE_AFTER_WORD; 
		}
		else if (cwchSpace != lref.m_str[iCharCount+1]  && eWordState == EAT_WHITESPACE_AFTER_WORD)
		{
			eWordState = FINISHED_EATING;
		}

		if (eWordState == FINISHED_EATING)
		{

			if ( (iLineWidth == m_iLineWidth) ||		
				 (iLineWidth  - iWordWidth <= 0  && iWordCount != 1) ||
				 (true == bNewLineFound) ) 
			{
				iLineCount++;
				iLineWidth = m_iLineWidth;
				iWordWidth = 0-iWordWidth;
				iWordCount = 1; 
			}

			short sSentenceEnd = 0;
			// If this is the end of a sentence - add this word to the sentences array.  
			if (cwchPeriod == lref.m_str[iCharCount-1])
			{
				sSentenceEnd = -1;
			}

			// Add word to words array for this paragraph 
			lref.m_vecWords.push_back(	CWord(	iCharCount+1, iWordWidth, sSentenceEnd));
			

			iLineWidth -= abs(iWordWidth);
			iWordCount+=1;
			iWordWidth = 0;
			iWordLength = 0; 

			eWordState = EAT_WORD_UNTIL_WHITESPACE;
			bNewLineFound = false; 
		}

		// If whitespace flag is still set then clear it. 
		if (lref.m_bWhitespace && cwchSpace != lref.m_str[iCharCount])
		{
			lref.m_bWhitespace = false; 
		}
	}
	// 


	if (lref.m_bWhitespace == false)
	{
		// Add all of the settings to the cursor actions collection. 
		long lTotal;
		CComPtr<IDispatch> pDispatch; 
		HRESULT hr = m_pProp->get_Settings(&pDispatch); 
		if (S_OK == hr)
		{
			CComQIPtr<ISettings> pSettings(pDispatch); 
			if (pSettings.p)
			{
				pSettings->get_Count(&lTotal);
				long lCount = 1;
				while (lCount <= lTotal)
				{
					CComQIPtr<ISetting> pSetting;
					HRESULT hr = pSettings->get_ItemCustom(CComVariant(lCount),  &pSetting);
					if (S_OK == hr && pSetting.p)
					{
						BSTR bstrString;
						long lPeriod = 0;
						long lRule = 0;	
						
						pSetting->get_Value	 ( &bstrString	);
						pSetting->get_Period ( &lPeriod		);
						pSetting->get_Rule	 ( &lRule		);
						
						if (1 == lRule || 2 == lRule)
						{
							int iNextOffset = 0; 
							// If we find this string in this paragraph then add a cursor
							// action for it. 
							do 
							{
								iNextOffset = lref.m_str.find(bstrString, iNextOffset);
								if (-1 != iNextOffset)
								{
									lref.m_listCursorAction.push_back(CCursorAction(iNextOffset, lRule, lPeriod));
									iNextOffset += ::SysStringLen(bstrString);
									if (iNextOffset >= lref.m_str.size() )
									{
										iNextOffset = -1; 
									}
								}
							}while (-1 != iNextOffset);
						}
						::SysFreeString(bstrString);
					}
					lCount++;
				}
			}
		}
	}
	ATL_TRACE1 (e_LOGDETAIL,  " Line Count %d", iLineCount); 
	lref.m_iLineCount = iLineCount+1; 

	return iLineCount+1;
}

//=========================================================================== 
//						
//	Method :		UnLoadData
//						
//	Description :	Ininitialise the data driver 
// 
//	Returns			0 if successful
//					1 could not allocate memory 
//					2 could not create datasource object 
//					3 system failure. 
//
//============================================================================

void CTextWindow::UnLoadData ()
{
	m_pWinBlitData->Uninitialise();
	m_Paras.clear(); 
	m_bInitialised = false; 
}

//=========================================================================== 
//						
//	Method :		LoadData
//						
//	Description :	Ininitialise the data driver 
// 
//	Returns			0 if successful
//					1 could not allocate memory 
//					2 could not create datasource object 
//					3 system failure. 
//
//============================================================================

int CTextWindow::LoadData (	eDATASOURCETYPE eDataSourceType, 
							VARIANT varDataSource)
{
	ATL_TRACE0  (e_LOGFLOW,  "\n CTextWindow::LoadData"); 
	
	int iRet = 0;				
	USES_CONVERSION;
	// Create the data object
	CLSID clsid;
	HRESULT hr;
	hr = CLSIDFromProgID(OLESTR("WinBlitDataManager.WinBlitData.1"), &clsid);
	if (SUCCEEDED(hr)) 
	{
		LPUNKNOWN pUnk;
		hr = CoCreateInstance(clsid, NULL, 
				CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pUnk);
		if (SUCCEEDED(hr) && pUnk)
		{
			m_pWinBlitData = pUnk;
			if (m_pWinBlitData.p)
			{
				CComVariant var (0);
				if (eTrialLicense == m_pWinBlitReader->m_iAppLic)
				{
					var.lVal = ciMaxTrialCharacters;
				}
				hr = m_pWinBlitData->Initialise(eDataSourceType,varDataSource, var);
				if (S_OK == hr)
				{
					m_bInitialised = true; 
					m_iCurrentFirstWord = 0;
					m_iCurrentFirstParagraph = 0;
					m_iDisplayCount = 0; 
				}
				else if (S_FALSE == hr)
				{
					//Report_Error ("WinBlit - No Data found in data source");  
					iRet = 2;
				}
				else if (DISP_E_EXCEPTION == hr) 
				{
					// The error is reported in the Data object 

					/*CComPtr<ISupportErrorInfo> pSupportErrorInfo;
					HRESULT hr = m_pWinBlitData.p->QueryInterface(IID_ISupportErrorInfo, (void **) &pSupportErrorInfo); 
					if (pSupportErrorInfo.p && S_OK == hr)
					{
						USES_CONVERSION; 
						CComPtr<IErrorInfo> pErrorInfo; 
						HRESULT hr = GetErrorInfo(0, &pErrorInfo);
						CComBSTR bstrDescription; 
						if (S_OK == hr)
						{
							pErrorInfo->GetDescription(&bstrDescription); 

							// If the error message came from GetLastError then just output the string 
							if (0 == wcsncmp(L"GetLastError", bstrDescription, 12))
							{
								Report_Error (OLE2T(&bstrDescription[12]));  
								iRet = 2;
							}
							else if (0 == wcsncmp(L"StringError", bstrDescription, 11))
							{
								Report_Error (OLE2T(&bstrDescription[11]));  
								iRet = 2;
							}
							else
							{
								iRet = 2;
							}
						}
						else
						{
							ATL_TRACE1 (e_LOGERROR, " Does not support error info A %0x", hr); 
						}
					}
					else 
					{
						ATL_TRACE1 (e_LOGERROR, " Does not support error info B %0x", hr); 	
					}*/
					iRet = 2;
					m_pWinBlitData->Uninitialise(); 
				}
			}
			else 
			{
				Report_Error ("WinBlit - Could not load data source - a system error occured - Code NULL POINTER \n If this problem persists please report it to Product Support. ",hr);  
				iRet = 3; 
			}
		}
		else 
		{
			Report_Error ("WinBlit - Could not load data source - a system error occured - Code CoCreate %0x. \n If this problem persists please report it to Product Support. ",hr);  
			iRet = 3; 
		}
	}
	else 
	{
		Report_Error ("WinBlit - Could not load data source - a system error occured - Code CLSID %0x. \n If this problem persists please report it to Product Support. ",hr);  
		iRet = 3; 
	}
	
	if (m_vecCursorStates.size() > 0  ) 
	{		
		m_vecCursorStates.clear();
	}
	m_vecCursorStateIterator = NULL; 

	if (m_listBlts.size() > 0) m_listBlts.clear();	

	if (m_Paras.size() > 0) 
	{
		m_Paras.clear(); 
	}

	return iRet; 
};

//=========================================================================== 
//						
//	Method :		Display
//						
//	Description :	Display routine for text window 
//
//	Parameters		
//				
// 	Type	Description					Quantity
//	----	-----------					--------
//	-1		Show banner page			N/A
//	0		Build page					N/A
//	1		Redisplay page				N/A 
//	2		Move Up	Lines				Number of lines
//	3		Move Down Lines				Number of lines
//	4		Move Up	 Pages				Number of pages
//	5		Move Down Pages				Number of pages
//	6		Move Down 1 page			(called while timer on)
//	7		Move with trackbar			Integer value between 0 & 1000
//										representing 0% - 100%
//
//	Returns	0
//		
//============================================================================

int CTextWindow::Display (int iType, int iQuantity)
{
	ATL_TRACE2  (e_LOGFLOW," CTextWindow::Display %d %d ", iType,iQuantity);

	HDC hdc = ::GetDC(m_hWnd);

	if (m_ClientTextRect.left == -9999)
	{
		// No window yet. 
		return -1;
	}

	if ( (e_REBUILD_PAGE  == m_pProp->m_ePropUpdate && iType > 0) ||
						0 == iType )
	{
		ATL_TRACE0  (e_LOGFLOW,"\n Rebuilding page ");

		// Called at beginning of program or whenm some property 
		// (such as Font or Screen Size) required a full redraw of the screen,
		// Calculate the height of the text of the current font
		HFONT hStockFont=NULL,	hOldFont=NULL;

		CComPtr<IFontDisp> pFontDisp; 
		m_pProp->get_TextFont(&pFontDisp); 
		CComQIPtr<IFont,&IID_IFont> pFont(pFontDisp);
		if(pFont)pFont->get_hFont(&hStockFont);

		// Create 2 Compatible DCs and bitmaps 
		if (!m_DCCursor.IsNull()) m_DCCursor.DeleteDC();

		if (!m_DCScreen.IsNull()) m_DCScreen.DeleteDC();

		if (!m_BitMapScreen.IsNull()) m_BitMapScreen.DeleteObject(); 

		m_BitMapScreen.CreateCompatibleBitmap(hdc, 
									m_OffScreenDisplayRect.right, 
									m_OffScreenDisplayRect.bottom);

		if (!m_BitMapCursor.IsNull()) m_BitMapCursor.DeleteObject();
		
		m_BitMapCursor.CreateCompatibleBitmap(hdc, 
									m_OffScreenDisplayRect.right, 
									m_OffScreenDisplayRect.bottom);

		m_DCScreen.CreateCompatibleDC(hdc);
		m_DCCursor.CreateCompatibleDC(hdc);

		::SelectObject(m_DCScreen,m_BitMapScreen);
		::SelectObject(m_DCCursor,m_BitMapCursor);

		if(hStockFont) SelectObject(m_DCScreen, hStockFont);
		if(hStockFont) SelectObject(m_DCCursor,	hStockFont);

		TEXTMETRIC tm;
		GetTextMetrics(m_DCScreen, &tm);
		
		SetTextColor	(m_DCScreen, m_pProp->ScreenTextColor());
		SetBkColor		(m_DCScreen, m_pProp->ScreenFillColor());

		SetTextColor	(m_DCCursor, m_pProp->CursorTextColor());
		SetBkColor		(m_DCCursor, m_pProp->CursorFillColor());

		HBRUSH hBrush = CreateSolidBrush(m_pProp->ScreenBackColor());
		FillRect(m_DCScreen,	 &m_OffScreenDisplayRect,	hBrush);
		FillRect(m_DCCursor,	 &m_OffScreenDisplayRect,	hBrush);
		DeleteObject (hBrush);
	
		m_iCharHeight = tm.tmHeight;
		m_iScreenHeight = (m_OffScreenTextRect.bottom - m_OffScreenTextRect.top) / m_iCharHeight;
		m_iLineWidth    = m_OffScreenTextRect.right - m_OffScreenTextRect.left;

		ATL_TRACE2 (e_LOGDETAIL, "\n *** In Display *** %d %d ", m_iScreenHeight, m_iDisplayCount);
		SIZE sz; 
		for ( short sB = 0; sB < 256; sB++)
		{
			WCHAR wch = static_cast<WCHAR>(sB);
			::GetTextExtentPoint32W(m_DCScreen, &wch, 1, &sz);
			m_Ascii2Ext[sB] = sz.cx;		
		}
		m_iOverhang = tm.tmOverhang;

		MakePage(); 

		// Rebuild cursor required 
		MakeBlts();

		// Set up the cursor states
		m_vecCursorStates.clear();
		if (m_pProp->HighlightPeriod() != 0)
		{
			m_vecCursorStates.push_back(e_HIGHLIGHTCURSOR);
		}
		if (m_pProp->DisplayPeriod() != 0)
		{
			m_vecCursorStates.push_back(e_DISPLAYCURSOR);
		}
		if (m_pProp->BlackoutPeriod() != 0)
		{
			m_vecCursorStates.push_back(e_BLACKOUTCURSOR);
		}
		
		SetupTimePeriods();

		// Position at beginning of cursor state machine 
		m_vecCursorStateIterator = m_vecCursorStates.begin();
		m_listBltCurrentIterator = m_listBlts.begin();

		m_listBltPreviousIterator = NULL; 
		m_dwTickTock = 0; 
		m_pProp->m_ePropUpdate = e_NOREPAINT;
		iType = 1;
	}

	// Move page if required
	if ( iType >=2 && iType <= 7   )
	{
		if		(2 == iType)	MovePage (0 - iQuantity);
		else if (3 == iType)	MovePage (    iQuantity);
		else if (4 == iType)	MovePage (0 - iQuantity * m_iScreenHeight);
		else if (5 == iType)	MovePage (    iQuantity * m_iScreenHeight);
		else if (6 == iType)
		{
			// If currently displaying less than the number of lines on screen
			// we cannot move page 
			ATL_TRACE2 (e_LOGDETAIL, "\n *** In Move down page *** %d %d ", m_iScreenHeight, m_iDisplayCount);

			if (m_iDisplayCount < m_iScreenHeight) 
			{
				ReleaseDC(m_hWnd, hdc); 
				return -1;
			}

			int iRet = MovePage (	  iQuantity * m_iScreenHeight);
		}
		else if (7 == iType)
		{
			MovePercentage (iQuantity); 
		}

		HBRUSH hBrush = CreateSolidBrush(m_pProp->ScreenBackColor());
		FillRect(m_DCScreen,	 &m_OffScreenDisplayRect,	hBrush);
		FillRect(m_DCCursor,	 &m_OffScreenDisplayRect,	hBrush);
		DeleteObject (hBrush);

		// Rebuild cursor required 
		MakeBlts();

		// Position at beginning of cursor state machine 
		m_vecCursorStateIterator = m_vecCursorStates.begin();
		m_listBltCurrentIterator = m_listBlts.begin();
		m_listBltPreviousIterator = NULL; 

		m_dwTickTock = 0; 
		m_pProp->m_ePropUpdate = e_NOREPAINT;
		iType = 1;
	}

	// Just redisplay the screen 
	if (1 == iType) 
	{
		if (cTachistoscopicCursor & m_pProp->Cursor() ||
			cSlowHandCursor   & m_pProp->Cursor())
		{
			// Blt the changes to the screen DC.
			BitBlt(	hdc,
					m_ClientDisplayRect.left, 
					m_ClientDisplayRect.top,
					m_OffScreenDisplayRect.right  - m_OffScreenDisplayRect.left, 
					m_OffScreenDisplayRect.bottom - m_OffScreenDisplayRect.top, 
					m_DCScreen,
					m_OffScreenDisplayRect.left,
					m_OffScreenDisplayRect.top,
					SRCCOPY);

			// Redisplay cursor if not at the beginning of the blit if 
			// we are running or paused. 
			if (m_pWinBlitReader->getState() == e_PAUSED ||
				m_pWinBlitReader->getState() == e_RUNNING)
			{
				if (m_vecCursorStateIterator != m_vecCursorStates.begin() ||
				m_listBltCurrentIterator != m_listBlts.begin())
				{
					DisplayCurrentCursor (hdc); 
				}
			}
		}
		else
		{
			// Fill rect with correct background color. 
			HBRUSH hBrush = CreateSolidBrush(m_pProp->ScreenBackColor());
			FillRect(hdc,	 &m_ClientDisplayRect,	hBrush);
			DeleteObject (hBrush);
			// Redisplay cursor 
			DisplayCurrentCursor (hdc); 

			// Display metafile if required.
			if (m_pProp->ShowMetafile())
			{
				// Blt the changes to the screen DC.
				int iX = m_ClientTextRect.left + ((m_ClientTextRect.right - m_ClientTextRect.left)/4);
				int iY = m_ClientTextRect.top  + ((m_ClientTextRect.bottom - m_ClientTextRect.top)/2);
				ATL_TRACE1 (e_LOGDETAIL, "\n Client y %d ", iY);  
				SetStretchBltMode (hdc, COLORONCOLOR); 
				StretchBlt(	hdc,
						iX, 
						iY,
						(m_OffScreenTextRect.right  - m_OffScreenTextRect.left)/2 , 
						(m_OffScreenTextRect.bottom - m_OffScreenTextRect.top )/2  , 
						m_DCScreen,
						m_OffScreenTextRect.left,
						m_OffScreenTextRect.top,
						m_OffScreenTextRect.right - m_OffScreenTextRect.left,
						m_OffScreenTextRect.bottom -  m_OffScreenTextRect.top,
						SRCCOPY);
			}
		}
		m_pProp->m_ePropUpdate = e_NOREPAINT;
		
	}

	if (-1 == iType)
	{
		// Create Compatible DC
		if (!m_DCScreen.IsNull()) m_DCScreen.DeleteDC();

		if (!m_BitMapScreen.IsNull()) m_BitMapScreen.DeleteObject(); 
		m_BitMapScreen.CreateCompatibleBitmap(hdc, 
									m_ClientDisplayRect.right, 
									m_ClientDisplayRect.bottom);

		m_DCScreen.CreateCompatibleDC(hdc);

		::SelectObject(m_DCScreen,m_BitMapScreen);

		// Calculate the height of the text of the current font
		HFONT hStockFont=NULL,	hOldFont=NULL;
		if(hStockFont) SelectObject(m_DCScreen, hStockFont);

		TEXTMETRIC tm;
		GetTextMetrics(m_DCScreen, &tm);

		// Display banner page
		// Just output the appropriate text in the middle of the screen.
		// Todo should blit to screen to avoid flicker
		TCHAR chTextA [] =   "WinBlit";
		TCHAR chTextB [] =  "\\\\   //";
		TCHAR chTextC [] =    "\\\\//";
		TCHAR chTextD [] =	    "\\/";
		TCHAR chTextE [] =    "2.4";

		Rectangle(m_DCScreen,
						0, 
						0, 
						m_ClientDisplayRect.right - m_ClientDisplayRect.left,
						m_ClientDisplayRect.bottom - m_ClientDisplayRect.top);

		HBRUSH hBrush;

		hBrush = CreateSolidBrush(m_pProp->ScreenBackColor());
		FillRect(m_DCScreen, &m_ClientDisplayRect, hBrush);
		DeleteObject (hBrush);

		CComPtr<IFontDisp> pFontDisp; 
		m_pProp->get_TextFont(&pFontDisp); 
		CComQIPtr<IFont,&IID_IFont> pFont(pFontDisp);

		if(pFont)pFont->get_hFont(&hStockFont);

		if(hStockFont) hOldFont = (HFONT) SelectObject(m_DCScreen, hStockFont);

		SetTextColor	(m_DCScreen, m_pProp->ScreenTextColor());
		SetBkColor		(m_DCScreen, m_pProp->ScreenFillColor());

		SIZE size;
		GetTextExtentPoint32 (m_DCScreen, chTextA, strlen(&chTextA[0]), &size); 

		SetTextAlign(m_DCScreen, TA_CENTER|TA_BASELINE);
		TextOut(m_DCScreen, (m_ClientDisplayRect.left + m_ClientDisplayRect.right) / 2,
					((m_ClientDisplayRect.top  + m_ClientDisplayRect.bottom) / 2) - size.cy * 2 , 
					&chTextA[0], 
					strlen(&chTextA[0]));

		TextOut(m_DCScreen, (m_ClientDisplayRect.left + m_ClientDisplayRect.right) / 2,
				    ((m_ClientDisplayRect.top  + m_ClientDisplayRect.bottom) / 2) - size.cy * 1 , 
					&chTextB[0], 
					strlen(&chTextB[0]));

		SetTextColor (m_DCScreen,	m_pProp->CursorTextColor());
		SetBkColor	 (m_DCScreen,	m_pProp->CursorFillColor());

		TextOut(m_DCScreen, (m_ClientDisplayRect.left + m_ClientDisplayRect.right) / 2, 
					((m_ClientDisplayRect.top  + m_ClientDisplayRect.bottom) / 2) , 
					&chTextC[0], 
					strlen(&chTextC[0]));

		SetTextColor	(m_DCScreen, m_pProp->ScreenTextColor());
		SetBkColor		(m_DCScreen, m_pProp->ScreenFillColor());

		SetTextAlign(m_DCScreen, TA_CENTER|TA_BASELINE);
		TextOut(m_DCScreen, (m_ClientDisplayRect.left + m_ClientDisplayRect.right) / 2,
					((m_ClientDisplayRect.top  + m_ClientDisplayRect.bottom) / 2) + size.cy * 1 , 
					&chTextD[0], 
					strlen(&chTextD[0]));

		TextOut(m_DCScreen, (m_ClientDisplayRect.left + m_ClientDisplayRect.right) / 2,
				    ((m_ClientDisplayRect.top  + m_ClientDisplayRect.bottom) / 2) + size.cy * 2 , 
					&chTextE[0], 
					strlen(&chTextE[0]));
		
		SelectObject(m_DCScreen, hOldFont);

		ATL_TRACE1 (e_LOGDETAIL, " \n Display rect %d", m_ClientDisplayRect.top);
		// Blt the changes to the screen DC.
		BitBlt(	hdc,
				m_ClientDisplayRect.left, 
				m_ClientDisplayRect.top,
				m_ClientDisplayRect.right  - m_ClientDisplayRect.left, 
				m_ClientDisplayRect.bottom - m_ClientDisplayRect.top, 
				m_DCScreen,
				m_ClientDisplayRect.left,
				m_ClientDisplayRect.top,
				SRCCOPY);
	}

	ReleaseDC(m_hWnd, hdc); 

	return 0;
}

//=========================================================================== 
//						
//	Method :		Initialise
//						
//	Description	:	Initialisation for TextWindow object 
//
//	Returns			void 
//		
//============================================================================

void CTextWindow::Initialise(CWinBlitProperties* pWinBlitProperties,
							 CWinBlitReader*		pWinBlitReader)
{
	ATL_TRACE0 (e_LOGFLOW,"\n CTextWindow::Initialise "); 
	m_iCurrentFirstWord = 0;
	m_iCurrentFirstParagraph = 0;

	m_pProp = pWinBlitProperties;
	m_pProp->m_ePropUpdate = e_NOREPAINT;
	m_pWinBlitReader = pWinBlitReader; 

	{
		CComObject< CStatistics>* pTemp = NULL;
		CComObject< CStatistics>::CreateInstance(&pTemp);
		m_pStatistics = pTemp;
	}
}

void CTextWindow::Uninitialise()
{
	// Release collection pointers
	m_pStatistics.Release();

	// Release DCs
	if (m_DCCursor !=NULL) DeleteDC	(m_DCCursor); 
	if (m_DCScreen !=NULL) DeleteDC	(m_DCScreen); 
	m_DCCursor = NULL;
	m_DCScreen = NULL;
		
}

void CTextWindow::SetWindow	(HWND hWnd)
{
	m_hWnd = hWnd; 
}	


RECT CTextWindow::GetRect	(void)
{
	return m_ClientDisplayRect;
}


//=========================================================================== 
//						
//	Method :		SetRect
//						
//	Description	:	Sets the drawing are rectangles
//
//	Returns			void 
//		
//============================================================================

void CTextWindow::SetRect	(RECT rc)
{
	ATL_TRACE2 (e_LOGFLOW, "CTextWindow::SetRect %d %d", rc.right, rc.bottom);

	// Client display rect is that portion of the screen
	// not occupied by toolbars so adjust it pot cope with
	// appearance of controls, status bar, trackbar and metafile.

	if (m_pProp->ShowControls())
	{
		rc.top = rc.top + ciToolBarHeight + 1; 
	}
	
	if (m_pProp->ShowStatusBar())
	{
		RECT rcTemp; 
		::GetClientRect(m_pWinBlitReader->m_hWndStatusBar, &rcTemp);
		rc.bottom = rc.bottom - rcTemp.bottom - rcTemp.top - 1;
	}

	if ( m_pProp->ShowTrackBar())
	{
		rc.bottom = rc.bottom - ciTrackBarHeight - 1; 
	}

	if (m_PreviousRect.left != rc.left	||
		m_PreviousRect.top  != rc.top	||
		m_PreviousRect.right != rc.right ||
		m_PreviousRect.bottom != rc.bottom)
	{
		if (m_PreviousRect.left != -9999)
		{	
			m_pProp->m_ePropUpdate = e_REBUILD_PAGE;
		}
		m_PreviousRect = rc; 
	}

	m_ClientDisplayRect = rc;

	// Todo - set these default properties somewhere else. 
	m_pProp->put_Left(8);
	m_pProp->put_Top(8);
	m_pProp->put_Bottom(8);
	m_pProp->put_Right(8);

	// Client text rect is that potion of the clients screen text can be
	// drawn om 6
	m_ClientTextRect.left   =  m_ClientDisplayRect.left   + m_pProp->Left();
	m_ClientTextRect.top    =  m_ClientDisplayRect.top    + m_pProp->Top();
	m_ClientTextRect.bottom =  m_ClientDisplayRect.bottom - m_pProp->Bottom();
	m_ClientTextRect.right  =  m_ClientDisplayRect.right  - m_pProp->Right();
	
	// Offscreen display rect is a rect used by the offscreen buffer for display
	m_OffScreenDisplayRect.left = 0;
	m_OffScreenDisplayRect.top = 0;
	m_OffScreenDisplayRect.bottom = m_ClientDisplayRect.bottom - m_ClientDisplayRect.top;
	m_OffScreenDisplayRect.right  = m_ClientDisplayRect.right  - m_ClientDisplayRect.left;

	// Text display in that portion of the offscreen buffer which displays text.
	m_OffScreenTextRect.left   =  m_OffScreenDisplayRect.left   + m_pProp->Left();
	m_OffScreenTextRect.top    =  m_OffScreenDisplayRect.top    + m_pProp->Top();
	m_OffScreenTextRect.bottom =  m_OffScreenDisplayRect.bottom - m_pProp->Bottom();
	m_OffScreenTextRect.right  =  m_OffScreenDisplayRect.right  - m_pProp->Right();
}	

//=========================================================================== 
//						
//	Method :		MakeBlts
//						
//	Description :	Create a bacon, lettuce and tomato sandwich.
//					  
//============================================================================
	
void CTextWindow::MakeBlts()
{	
	LISTPARAGRAPHSITERATOR	pit;				// Iterator of currewnt paragraph
	VECWORDSITERATOR vit;						// Iterator of words array in paragraph
	VECWORDSITERATOR vitStart;					// 1st word on a line 
	VECWORDSITERATOR vitEnd;					// Lasr word on a line 

	pit = m_Paras.begin(); 
	ATL_TRACE0 (e_LOGFLOW, "\n CTextWindow::MakeBlts "); 

	// Initialise blit creator object
	m_BltCreator.Initialise(m_pProp, m_iLineWidth, m_iScreenHeight, &m_listBlts, m_Ascii2Ext[32], m_iOverhang); 

	int iLineCount = 0;							// Line count 
	int iTotalExtent;							// Count of pixels on aline
	int iLineOffsetStart;						// Offset into the paragraph text buffer

	while (pit != m_Paras.end() && iLineCount < m_iScreenHeight)
	{	
		// Calculate the first word in this paragraph
		if (pit == m_Paras.begin())
		{
			// 1st paragraph the 1st offset comes from member variable 
			// as the first line may be some way into the paragraph. 
			vit = pit->m_vecWords.begin() + m_iCurrentFirstWord;
			iLineOffsetStart = GetOffsetforWord(pit,m_iCurrentFirstWord );
		}
		else 
		{
			// Subsequent paragraphs lines start at offset 0 
			vit = pit->m_vecWords.begin(); 
			iLineOffsetStart = 0; 
		}

		if (pit->m_bWhitespace)
		{
			// If paragraph just containes whitespace increment linecount and ignore it. 
			iLineCount++;	
		}
		else 
		{
			// Loop over all words on this paragraph stopping when the screen is filled
			// The iterators vitStart and vitEnd are set to the first and last word 
			// on a line. 
			vitStart = NULL;
			vitEnd   = NULL; 
			while (vit		 < pit->m_vecWords.end() && 
				  iLineCount < m_iScreenHeight)
			{	
				if (NULL == vitStart) 
				{
					vitStart = vit;
					iTotalExtent = 0;
					if (iLineCount >= m_iScreenHeight) break;
				}
				iTotalExtent += abs(vit->m_sTextExtent);

				// Is the next word on this line - negative extent means the 
				// start of a line. 
				vitEnd = vit+1;
				if ( vitEnd == pit->m_vecWords.end() ||  vitEnd->m_sTextExtent < 0)				 
				{
					// We have a line so pass it to bltcreator 
					m_BltCreator.AddLine(iTotalExtent,
									 vitStart,
									 vit,
									 pit , 
									 iLineOffsetStart,
									 iLineCount);

					// Now output all of the words on this line
					VECWORDSITERATOR vitOut = vitStart;
					int iPosX = 0,  xExtent = 0;
					int iPosY = (iLineCount+1) * m_iCharHeight; 
					int iOffset = iLineOffsetStart;
					do 
					{
						SetTextAlign(m_DCScreen, TA_LEFT | TA_BOTTOM);  

						iPosX+=vitOut->m_sFiller;
						{
						//	TEXTMETRIC tm; 
						//	GetTextMetrics(m_DCScreen, &tm); 
						//	SIZE size; 
						//	GetTextExtentPoint32W (m_DCScreen, pit->m_str.c_str()+iOffset, vitOut->m_iOffset - iOffset, &size); 
						//	ATL_TRACE5 (1, "\n Real Extent %d Actual extent %d Output at %d length %d - overhang %d ",  size.cx, abs(vitOut->m_sTextExtent), iPosX, (vitOut->m_iOffset - iOffset), tm.tmOverhang); 
						//	ATL_TRACE1 (1, " Italic %d ", tm.tmItalic); 
						}

						// Output the line into our 2 device contexts
						TextOutW (m_DCScreen,  
								  m_OffScreenTextRect.left + iPosX,	
								  m_OffScreenTextRect.top + iPosY, 
								  pit->m_str.c_str()+iOffset,
								  vitOut->m_iOffset - iOffset);

						SetTextAlign(m_DCCursor, TA_LEFT | TA_BOTTOM); 

						TextOutW (m_DCCursor,
								  m_OffScreenTextRect.left + iPosX,	
								  m_OffScreenTextRect.top + iPosY, 
								  pit->m_str.c_str()+iOffset,
								  vitOut->m_iOffset - iOffset);		

						iPosX+=abs(vitOut->m_sTextExtent); 
						iOffset = vitOut->m_iOffset;	
						vitOut++;

					}while (vitOut <= vit);

					iLineCount++; 

					vitStart = NULL; 
					iLineOffsetStart = vit->m_iOffset;
				}		
				vit++;
			}						//(vit		 < pit->m_vecWords.end() &&   iLineCount < m_iScreenHeight)
		}		
		pit++; 
	}								//while (pit != m_Paras.end() && iLineCount < m_iScreenHeight)

	m_BltCreator.Sort(--iLineCount);
}

//=========================================================================== 
//						
//	Method :		Blit To Screen
//						
//	Description :	Blit from offscreen buffer to client DC 
//					
//============================================================================

void CTextWindow::BlitToScreen(	HDC hdcTo,					// Client DC
								eCURSOR e_CursorState,		// State of blit 
								HDC hdcFrom,				// Offscreen DC
								LISTBLTITERATOR lblt)		// Blit details 
{
	ATL_TRACE0 (e_LOGDETAIL, "\n BlitToScreen "); 
	int iIndex = lblt->m_sIndex; 

	HBRUSH hBrush;

	if (e_CursorState == e_BLACKOUTCURSOR)	hBrush = CreateSolidBrush(m_pProp->ScreenBackColor());

	if (cRSVPCursor & m_pProp->Cursor() ||
		cRandomCursor & m_pProp->Cursor())	
	{
		// We have one or more blits of the same index which may come 
		// from different lines in the offscreen buffer. As it is a 
		// static cursor we want to display as one centered line. So 
		// work out all of the extents and out them into the vecextents 
		// array which we will use when deciding where to blit to.
		
		LISTBLTITERATOR lbltTemp = lblt; 
		vector<int> vecExtents; 
		vector<int>::iterator vecExtentsIterator; 
		int iLineTemp  = lbltTemp->m_sLineNumber;
		vecExtents.push_back(0); 
		int iHeight = m_iCharHeight; 
		int iWidth = 0; 
		do 
		{
			if (m_pProp->CursorHeight() > 1 && iLineTemp != lbltTemp->m_sLineNumber ) 
			{
				vecExtents.push_back(0); 
				iHeight += m_iCharHeight; 
			}
			vecExtents[vecExtents.size()-1] += lbltTemp->m_sxExt;
			if (vecExtents[vecExtents.size()-1] > iWidth) iWidth = vecExtents[vecExtents.size()-1];
			lbltTemp++;
		}
		while (lbltTemp != m_listBlts.end()  &&  iIndex == lbltTemp->m_sIndex );

		int iCentreX;
		int iCentreY;

		// Seed the random number if random cursor
		if ( cRandomCursor & m_pProp->Cursor())
		{
			if  (0 == lblt->m_sRand) 
			{
				srand( (unsigned)time( NULL ) );
				lblt->m_sRand = rand();
			}
            int iX  = m_OffScreenTextRect.right  - m_OffScreenTextRect.left - iWidth;
			int iY  = m_OffScreenTextRect.bottom - m_OffScreenTextRect.top  - iHeight;
			if (iX <= 0) iX = 2; 
			if (iY <= 0) iY = 2; 

			// Make it a bit more random 
			if (0 == lblt->m_sRand  % 3)
			{
				iY =  (lblt->m_sRand / 5) % iY;
				iX =  (lblt->m_sRand / 7) % iX;
			}
			else if (0 == lblt->m_sRand  % 2)
			{
				iY = (lblt->m_sRand * 3) % iY;
				iX = (lblt->m_sRand / 2) % iX;
			}
			else 
			{
				iY = (lblt->m_sRand / 15) % iY;
				iX  =(lblt->m_sRand * 2) % iX;
			}

			iCentreX = m_OffScreenTextRect.left + iX + (iWidth  / 2);
			iCentreY = m_OffScreenTextRect.top  + iY + (iHeight / 2);
		}
		else
		{
			// If showing metafile blit to 25% of way down 
			// screen else blit half way down the screen.
			if (m_pProp->ShowMetafile())
			{
				iCentreX = m_OffScreenTextRect.left + ((m_OffScreenTextRect.right  - m_OffScreenTextRect.left)/2);
				iCentreY = m_OffScreenTextRect.top  + ((m_OffScreenTextRect.bottom - m_OffScreenTextRect.top)/5);
			}
			else
			{
				iCentreX = m_OffScreenTextRect.left + ((m_OffScreenTextRect.right  - m_OffScreenTextRect.left)/2);
				iCentreY = m_OffScreenTextRect.top  + ((m_OffScreenTextRect.bottom - m_OffScreenTextRect.top)/2);
			}
		}

		vecExtentsIterator = vecExtents.begin();

		// Calculate positions to start blitting from. 
		int iBltXPos = iCentreX - (*vecExtentsIterator)/2;
		int iBltYPos = iCentreY - (vecExtents.size() * m_iCharHeight / 2);

		iLineTemp  = lblt->m_sLineNumber;
		while (lblt != m_listBlts.end()  &&  iIndex == lblt->m_sIndex )
		{
			if (m_pProp->CursorHeight() > 1 && iLineTemp != lblt->m_sLineNumber) 
			{
				vecExtentsIterator++;
				iBltXPos = iCentreX - (*vecExtentsIterator)/2;
				iBltYPos+= m_iCharHeight;
			}
			if (iBltXPos < 0 ) iBltXPos  = 0;
			RECT rt;
			rt.left   = m_ClientTextRect.left + iBltXPos;
			rt.top    = m_ClientTextRect.top  + iBltYPos,
			rt.right  = m_ClientTextRect.left + iBltXPos + lblt->m_sxExt;
			rt.bottom = m_ClientTextRect.top  + iBltYPos + m_iCharHeight; 

			// Blit it to metafile if required 
			int iX = m_ClientTextRect.left + ((m_ClientTextRect.right   - m_ClientTextRect.left) /4 ) + (lblt->m_sxPos )/2;
			int iY = m_ClientTextRect.top  + ((m_ClientTextRect.bottom  - m_ClientTextRect.top) / 2 ) +  ((lblt->m_sLineNumber * m_iCharHeight)/2); 

			if (e_CursorState == e_BLACKOUTCURSOR)
			{
				// Blackout cursor means we just fill a rectangle
				FillRect(hdcTo,	 &rt,	hBrush);

				if (m_pProp->ShowMetafile())
				{
					ATL_TRACE1 (1, " \n Client at blt %d ", iY); 
					SetStretchBltMode (hdcTo, COLORONCOLOR); 				
					StretchBlt (hdcTo,
								iX,	
								iY,
								lblt->m_sxExt/2,
								m_iCharHeight/2,
								hdcFrom,
								m_OffScreenTextRect.left + lblt->m_sxPos,	
								m_OffScreenTextRect.top  + lblt->m_sLineNumber * m_iCharHeight,
								lblt->m_sxExt,
								m_iCharHeight,
								SRCCOPY);
				}
			}
			else
			{
				// Blit from offscreen buffer

				BitBlt(	hdcTo,
						rt.left,	
						rt.top,
						lblt->m_sxExt,
						m_iCharHeight,
						hdcFrom,
						m_OffScreenTextRect.left + lblt->m_sxPos,	
						m_OffScreenTextRect.top  + lblt->m_sLineNumber * m_iCharHeight,
						SRCCOPY);

				if (m_pProp->ShowMetafile())
				{
					ATL_TRACE1 (e_LOGDETAIL, " \n Client at blt %d ", iY); 
					SetStretchBltMode (hdcTo, COLORONCOLOR); 				
					StretchBlt (hdcTo,
								iX,	
								iY,
								lblt->m_sxExt/2,
								m_iCharHeight/2,
								hdcFrom,
								m_OffScreenTextRect.left + lblt->m_sxPos,	
								m_OffScreenTextRect.top  + lblt->m_sLineNumber * m_iCharHeight,
								lblt->m_sxExt,
								m_iCharHeight,
								SRCCOPY);
				}
			}
			iBltXPos += lblt->m_sxExt;

			if (e_CursorState == e_HIGHLIGHTCURSOR) 
			{
				m_lWordCount+=lblt->m_sWordCount;
			}
			lblt++;
		}
	}
	else
	{
		while (lblt != m_listBlts.end()  &&  iIndex == lblt->m_sIndex ) 
		{
	ATL_TRACE4 (e_LOGDETAIL, " -From Index %d XPos %d YPos %d Extent %d ",	iIndex,
																	m_OffScreenTextRect.left + lblt->m_sxPos,	
																	m_OffScreenTextRect.top  + (lblt->m_sLineNumber * m_iCharHeight),
																	lblt->m_sxExt);							
			if (e_CursorState == e_BLACKOUTCURSOR)
			{
				// Blackout by filling rectangle
				RECT rt;
				rt.left   = m_ClientTextRect.left + lblt->m_sxPos;
				rt.top    = m_ClientTextRect.top  + lblt->m_sLineNumber * m_iCharHeight,
				rt.right  = m_ClientTextRect.left + lblt->m_sxExt + lblt->m_sxPos;
				rt.bottom = m_ClientTextRect.top  + (lblt->m_sLineNumber * m_iCharHeight) + m_iCharHeight;
				FillRect(hdcTo,	 &rt,	hBrush);
			}
			else
			{
				// Blit to screen from offscreen DC.
				BitBlt(	hdcTo,
						m_ClientTextRect.left + lblt->m_sxPos,	
						m_ClientTextRect.top  + lblt->m_sLineNumber * m_iCharHeight,
						lblt->m_sxExt,	m_iCharHeight,
						hdcFrom,
						m_OffScreenTextRect.left + lblt->m_sxPos,	
						m_OffScreenTextRect.top  + (lblt->m_sLineNumber * m_iCharHeight),
						SRCCOPY);
				// Blit to screen DC if we wish the cursor colour to be left on the screen

				if (cLeaveCursorHighlighted & m_pProp->Cursor())
				{
					BitBlt(	m_DCScreen,
						m_OffScreenTextRect.left + lblt->m_sxPos,	
						m_OffScreenTextRect.top   + lblt->m_sLineNumber * m_iCharHeight,
						lblt->m_sxExt,	m_iCharHeight,
						hdcFrom,
						m_OffScreenTextRect.left + lblt->m_sxPos,	
						m_OffScreenTextRect.top  + (lblt->m_sLineNumber * m_iCharHeight),
						SRCCOPY);

				}
			}
			if (e_CursorState == e_HIGHLIGHTCURSOR)
			{
				m_lWordCount+=lblt->m_sWordCount;
			}
			lblt++;
		}
	}
	if (e_CursorState == e_BLACKOUTCURSOR)	DeleteObject (hBrush);
}

//=========================================================================== 
//	 					
//	Method :		OnBeforeTimerStart
//						
//	Description :	Called just before the timer starts
//					  
//===========================================================================

void CTextWindow::OnBeforeTimerStart (int iType)	// 0 = 1st time start, 1 = start after pause
{		
	m_lWordCount = 0;
	if (0 == iType) m_dwElapsedTickCount = GetTickCount(); 
	m_dwReadTickCount = GetTickCount(); 

	m_bSoundClick = false; 
	if (cCursorSound & m_pProp->Cursor())
	{
		// Sound resource bound within executable.
			
		if (m_hWaveRes = FindResource(_Module.GetModuleInstance(),"CLICK",_T("Sound")))

		{   // Resource intact; load into GLOBAL MEMORY/GMEM_SHARED memory

			if (m_hGlobMem = LoadResource(_Module.GetModuleInstance(),m_hWaveRes))

			{	
				m_bSoundClick = true;
				// Load resource into global memory and play.

				// Play sound resource via sndPlaySound() using
				//  SND_MEMORY flag.

				// Application waits until sndPlaySound completes
				//  given SND_SYNC.
				// SND_MEMORY (first parameter is ptr to memory image
				//  vs. filename).

				sndPlaySound((LPSTR)LockResource(m_hGlobMem),
													   SND_ASYNC | SND_MEMORY);


			}  // Load resource into global memory and play.		
			else 
			{
			}
		}  // Resource found.
		else 
		{
		}
	}
}

//========================================================================== 
//						
//	Method :		OnAfterTimerStop
//						
//	Description :	Called just after ther timer stops 
//					  
//==========================================================================

void CTextWindow::OnAfterTimerStop (int iType)	// 0 = Pause , 1 = Stop, 2 = New Page
{
	DWORD dwTickCount = ::GetTickCount();

	// Set up the statistics varaibles from the member variables 
	if (1 == iType)
	{
		CComPtr<IStatistic> pStat;
		long lElapsedTime;
		CComVariant cvar(cElapsedTime);
		m_pStatistics->get_ItemCustom(cvar, &pStat);
		pStat->get_Quantity(&lElapsedTime);
		BSTR bstr;
		pStat->get_Name(&bstr);
		lElapsedTime += (dwTickCount - m_dwElapsedTickCount);
		pStat->put_Quantity(lElapsedTime);
	}
	{
		CComPtr<IStatistic> pStat;
		long lReadTime;
		CComVariant cvar(cReadTime);
		m_pStatistics->get_ItemCustom(cvar, &pStat);
		pStat->get_Quantity(&lReadTime);
		lReadTime += (dwTickCount - m_dwReadTickCount);
		BSTR bstr;
		pStat->get_Name(&bstr);
		pStat->put_Quantity(lReadTime);
	}
	{
		CComPtr<IStatistic> pStat;
		long lWordCount;
		CComVariant cvar(cWordCount);
		m_pStatistics->get_ItemCustom(cvar, &pStat);
		pStat->get_Quantity(&lWordCount);
		ATL_TRACE1 (e_LOGDETAIL, "\n Word count before %d ",lWordCount); 
		lWordCount += m_lWordCount;
		pStat->put_Quantity(lWordCount);
		ATL_TRACE1 (e_LOGDETAIL, "\n Word count after %d ",lWordCount); 

	}
}

//=========================================================================== 
//						
//	Method :		TickTock
//						
//	Description :	Blt cursor to the screen
//
//	Parameters		
// 
//	bReDisplay - if true TickTock is called when state machine is stopped
//  or pauses to output the current cursor position. 
//
//	Returns 
//		
//	-1 when finished processing.  
//  -2 when pause condition encountered.in blit class
// 					  
//============================================================================

int CTextWindow::TickTock(bool bRedisplay)
{
	//ATL_TRACE0 (e_LOGDETAIL, "\n CTextWindow::TickTock");

	if (m_pProp->m_ePropUpdate == e_PAINT_LEAVE_CURSOR || 
		m_pProp->m_ePropUpdate == e_REBUILD_PAGE) Display (1);  

	int iRet = 0;

	DWORD dwTickTock = ::GetTickCount();
	if (0 == m_dwTickTock )
	{
		m_dwTickTock = dwTickTock;	
		// 1st time in - Set timer interval. 
		if		(e_DISPLAYCURSOR   == *m_vecCursorStateIterator) m_dwTickTockInterval = m_lActualDisplayPeriod;
		else if (e_HIGHLIGHTCURSOR == *m_vecCursorStateIterator) m_dwTickTockInterval = m_lActualHighlightPeriod;
		else if (e_BLACKOUTCURSOR  == *m_vecCursorStateIterator) m_dwTickTockInterval = m_lActualBlackoutPeriod;
	}
	else if (m_dwTickTockInterval > (dwTickTock - m_dwTickTock))
	{
		// Interval not expired 
		return 0;
	}
	else
	{
		if (++m_vecCursorStateIterator >= m_vecCursorStates.end())
		{
			m_vecCursorStateIterator = m_vecCursorStates.begin();
			m_listBltPreviousIterator = m_listBltCurrentIterator;

			// Find next iterator position by skipping all with 
			// the current index and all which have nothing to display 
			int iIndex = m_listBltCurrentIterator->m_sIndex;  
			while (	(iIndex == m_listBltCurrentIterator->m_sIndex ||
						  0 == m_listBltCurrentIterator->m_sxExt)  &&
						m_listBltCurrentIterator != m_listBlts.end() )
			{
				m_listBltCurrentIterator++;
			}
			if (m_listBltCurrentIterator == m_listBlts.end() )
			{
				iRet = -1;
			}			
		}

		// Set timer interval. 
		if (e_DISPLAYCURSOR == *m_vecCursorStateIterator)
		{
			m_dwTickTockInterval = m_lActualDisplayPeriod; 
		}
		else if (e_HIGHLIGHTCURSOR == *m_vecCursorStateIterator)
		{
			m_dwTickTockInterval = m_lActualHighlightPeriod;
		}
		else if (e_BLACKOUTCURSOR == *m_vecCursorStateIterator)
		{
			m_dwTickTockInterval = m_lActualBlackoutPeriod;
		}
	}

	HDC hdc = ::GetDC(m_hWnd);

	DisplayCurrentCursor(hdc); 

	if (cCursorSound & m_pProp->Cursor())
	{
		sndPlaySound((LPCTSTR)::LockResource(m_hGlobMem), SND_MEMORY|SND_ASYNC|SND_NODEFAULT); 
	}

	ReleaseDC(m_hWnd, hdc); 

	m_dwTickTock = ::GetTickCount();

	if (e_HIGHLIGHTCURSOR == *m_vecCursorStateIterator)
	{
		LISTBLTITERATOR lblt = m_listBltCurrentIterator;

		BOOL bPause = FALSE;
		int iDelay = 0;

		// Loop through all blits with the current index and see if there 
		// are any actions set up for them. 
		while (lblt								  != m_listBlts.end() && 
			   m_listBltCurrentIterator->m_sIndex == lblt->m_sIndex    &&
			   FALSE                              == bPause)
		{
			bPause = lblt->m_bPause;
			iDelay = lblt->m_iDelay;
			lblt++;
		}

		if (bPause ) 			
		{
			// Return status code to enter paused state 
			iRet = -2;
		}
		else if (0 !=  iDelay)
		{
			// Adjust interval period to the length of the delay
			if (iDelay  < 0 && 	m_pProp->BaseTime() > 0)
			{
				m_dwTickTockInterval = (iDelay * m_pProp->BaseTime() ) / 100;
			}
			else 
			{
				m_dwTickTockInterval= abs(iDelay);
			}
		}
	}
	
	return iRet;
}

//=========================================================================== 
//						
//	Method :		DisplayCurrentCursor	
//						
//	Description :	For a given DC display the cursor at
//					its current position  on the screen 
//
//	Returns			void 
//		
//============================================================================

void CTextWindow::DisplayCurrentCursor (HDC hdc)
{
	if (!m_vecCursorStateIterator) return; 

	if (e_HIGHLIGHTCURSOR == *m_vecCursorStateIterator)
	{
		// We are hightlighting 
		// Redisplay or clear the previous blit if we are after the 1st output 
		if (m_listBltPreviousIterator != NULL && 
			!(cLeaveCursorHighlighted & m_pProp->Cursor()))
		{
			if (cTachistoscopicCursor & m_pProp->Cursor() ||
				cSlowHandCursor   & m_pProp->Cursor())
			{
				BlitToScreen(	hdc,
								e_DISPLAYCURSOR, 
								m_DCScreen,
								m_listBltPreviousIterator);
			}
			else
			{
				BlitToScreen(	hdc,
								e_BLACKOUTCURSOR, 
								m_DCScreen,
								m_listBltPreviousIterator);
			}				
		}
		BlitToScreen	(	hdc,
							e_HIGHLIGHTCURSOR, 
							m_DCCursor,
							m_listBltCurrentIterator);	
	}
	else if (e_DISPLAYCURSOR == *m_vecCursorStateIterator)
	{
		BlitToScreen	(	hdc,
							e_DISPLAYCURSOR, 
							m_DCScreen,
							m_listBltCurrentIterator);	
	}
	else if (e_BLACKOUTCURSOR == *m_vecCursorStateIterator)
	{
		BlitToScreen	(	hdc,
							e_BLACKOUTCURSOR, 
							NULL,
							m_listBltCurrentIterator);	
	}
}

//=========================================================================== 
//						
//	Method :		GetPercentage
//						
//	Description :	Find the percentage through the data source 
//					of the first paragraph currently displaying 
//					on the screen. 
//
//	Returns			DWORD 
//		
//============================================================================

int CTextWindow::GetCurrentPercentage()
{
	long lPercent; 
	if (m_Paras.size() > 0)
	{
		m_pWinBlitData->GetPercentAtPara ( &lPercent, m_Paras.begin()->m_iParagraphNumber );
	}
	else 
	{
		lPercent = 0; 
	}

	return lPercent;
}

//=========================================================================== 
//						
//	Method :		GetCurrentStats 
//						
//	Description :	Return the current statistics 
//
//	Returns			void  
//		
//============================================================================

void CTextWindow::GetCurrentStatistics (long& lReadTime, long& lWordCount)
{
	{
		CComPtr<IStatistic> pStat;
		CComVariant cvar(cReadTime);
		m_pStatistics->get_ItemCustom(cvar, &pStat);
		pStat->get_Quantity(&lReadTime);
	}
	{
		CComPtr<IStatistic> pStat;
		CComVariant cvar(cWordCount);
		m_pStatistics->get_ItemCustom(cvar, &pStat);
		pStat->get_Quantity(&lWordCount);
	}

	// If the state machine is running we need to add 
	// in the current word count and readtime
	if (m_pWinBlitReader->m_eState == e_RUNNING)
	{
		lWordCount += m_lWordCount; 
		lReadTime += ::GetTickCount() - m_dwReadTickCount;
	}
}

//=========================================================================== 
//						
//	Method :		GetLineNumberForWord
//						
//	Description :	For a given word index in the paragraph words 
//					vector 	return the line number in the paragraph it 
//					appears on. 
//
//	Returns			>= 0 success
//		
//============================================================================

CTextWindow::GetLineNumberforWord(LISTPARAGRAPHSITERATOR pit, int iWord)
{
	if (iWord == 0 || iWord == -1) return 0; 

	int iLineNumber = -1;
	{ 
		VECWORDSITERATOR wit = pit->m_vecWords.begin(); 
		int iA = 0;
		while (iA <= iWord)
		{
			if (wit->m_sTextExtent < 0)
			{
				iLineNumber++;
			}
			wit++; 
			iA++; 
		}
	}
	return iLineNumber; 
}


//=========================================================================== 
//						
//	Method :		GetWordforLineNumber
//						
//	Description :	For a given line number in the paragraph 
//					return the offset in the word array of the 
//					first word that appears on the line.
//
//	Returns			>= 0 success
//		
//============================================================================

int CTextWindow::GetWordforLineNumber(LISTPARAGRAPHSITERATOR pit, int iLineNumber)
{
	if (iLineNumber == 0) return 0;

	int iWord = -1;
	{
		int iA = -1;
		VECWORDSITERATOR wit = pit->m_vecWords.begin(); 
		while (iA < iLineNumber)
		{
			if (wit->m_sTextExtent < 0 )
			{
				iA++;
			}
			wit++; 
			iWord++;
		}
	}
	return iWord; 
}

//=========================================================================== 
//						
//	Method :		GetOffsetforWord
//						
//	Description :	For a given offset in the Words vector of the 
//					the supplied paragraphs iterator return the offset
//					in the test string which correspons to that word
//					
//	Returns			>= 0 success
//					
//============================================================================

int CTextWindow::GetOffsetforWord(LISTPARAGRAPHSITERATOR pit, int iWord)
{
	if (iWord == 0) return 0; 

	return pit->m_vecWords[iWord-1].m_iOffset;
}

//=========================================================================== 
//						
//	Method :		SetupTimePeriods
//						
//	Description :	Set up the member variables which determine 
//					time between blits 
// 
//	Returns			void
//					
//============================================================================

void CTextWindow::SetupTimePeriods()
{
	if (m_pProp->HighlightPeriod() != 0)
	{
		if (m_pProp->HighlightPeriod()  < 0 && 	m_pProp->BaseTime() > 0)
		{
			m_lActualHighlightPeriod = (abs(m_pProp->HighlightPeriod()) * m_pProp->BaseTime()) / 100;
		}
		else 
		{
			m_lActualHighlightPeriod = abs(m_pProp->HighlightPeriod());
		}
	}
	else 
	{
		m_lActualHighlightPeriod = 0;
	}

	if (m_pProp->DisplayPeriod() != 0)
	{
		if (m_pProp->DisplayPeriod()  < 0 && 	m_pProp->BaseTime() > 0)
		{
			m_lActualDisplayPeriod = (abs(m_pProp->DisplayPeriod()) * m_pProp->BaseTime()) / 100;
		}
		else 
		{
			m_lActualDisplayPeriod = abs(m_pProp->DisplayPeriod());
		}
	}
	else 
	{
		m_lActualDisplayPeriod = 0;
	}

	if (m_pProp->BlackoutPeriod() != 0)
	{
		if (m_pProp->BlackoutPeriod()  < 0 && 	m_pProp->BaseTime() > 0)
		{
			m_lActualBlackoutPeriod = (abs(m_pProp->BlackoutPeriod()) * m_pProp->BaseTime()) / 100;
		}
		else 
		{
			m_lActualBlackoutPeriod = abs(m_pProp->BlackoutPeriod());
		}
	}
	else
	{
		m_lActualBlackoutPeriod = 0;
	}
}