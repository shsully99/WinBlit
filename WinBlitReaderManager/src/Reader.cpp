//***************************************************************************
//*
//*		Name		: Reader.cpp
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


#include "stdafx.h"
#include "resource.h"
#include "Reader.h"
#include "WinBlitData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReader::~CReader() {}

//=========================================================================== 
//						
//	Method :		GetPercentAtPara
//						
//	Description :	For a given paragraph number find its percentage 
//					position in the total file. 
//
//  Returns	:		void 
//					
//============================================================================
	
void CReader::GetPercentAtPara ( long* plPercent,  long lPara)
{	
	ATL_TRACE ("\n CReader::GetPercentAtPara - %d", lPara);

	if (m_bUseSubReader == true)
	{
		m_pSubReader->GetPercentAtPara ( plPercent,  lPara);
	}
	else
	{
		if (lPara >= m_vdwOffsets.size()) lPara = m_vdwOffsets.size()-1; 
		if (lPara>=0)
		{
			FLOAT fPara = (float) m_vdwOffsets.at(lPara) / 100.000;
			FLOAT fDataSourceSize = (float) m_dwDataSourceSize / 100.000;
			FLOAT fTemp = (fPara / fDataSourceSize) * 100.000;
			*plPercent = fTemp * 100;
		}
	}
	ATL_TRACE (" returns %d", *plPercent);
}	
	
//=========================================================================== 
//							
//	Method :		GetParaAtPercent
//							
//	Description :	For a given percentage through the total
//					file find the corresponding Paragraph number 
//	
//  Returns	:		void 
//						
//==============================================
	
void CReader::GetParaAtPercent (long lPercent, long* plPara, BOOL bRound)
{	
	ATL_TRACE ("\n CReader::GetParaAtPercent %d percent", lPercent);

	if (m_bUseSubReader == true)
	{
		m_pSubReader->GetParaAtPercent (lPercent, plPara, bRound);
	}
	else
	{
		m_bReturnData = false;

		if (lPercent == 0)
		{
			*plPara = 0;
		}
		else 
		{
			int iTotal = m_vdwOffsets.size(); 
			int iCount = 0;
			
			DWORD dwOffset = 0;
			BSTR bstrData;

			// Loop round looking for an offset one past the requested percentage. 
			// Look first in the existing offsets array (if iCount < iTotal).
			// If we dont find a suitable offset 
			// in the existing offsets array there then add to the offsets
			// array (using GetData) until we do find a match. 

			while (true)
			{
				// Check our offsets array until we have got to the end of the array. 
				if (iCount < iTotal)
				{
					dwOffset = m_vdwOffsets.at(iCount);
				}
				else if (!m_bArrayFull)
				{
					bstrData = NULL;
					int iRet = GetData(iCount, &bstrData);
					if (NULL != bstrData) ::SysFreeString (bstrData); 
					if (1 == iRet)
					{
						// Passed end of file or error - must break here and 
						// give the last one to the client. 
						iCount--; 
						break;
					}
					dwOffset = m_vdwOffsets.back();
				}
				else 
				{
					// Array is full - and still not found our paragraph - break here 
					// and give last one to the client. 
					iCount--;
					break;
				}
				// Calculate the percentage offset in the data source of the 
				// paragraph at iOffset. If it exceeds the requested percentage then break

				FLOAT fPara = (float) dwOffset / 100.000;
				FLOAT fDataSourceSize = (float) m_dwDataSourceSize / 100.000;
				FLOAT fTemp = (fPara / fDataSourceSize) * 100.000;
				long lA  = fTemp * 100;
				//long lA = (dwOffset * dwPercentage) / m_dwDataSourceSize; 
				if (lA > lPercent)
				{
					break;
				}
				iCount++;
			}
			// Round down if client requested it.
			if (!bRound && iCount > 0) iCount--;

			*plPara = iCount;
		}
	}
	m_bReturnData = true;
	ATL_TRACE (" Returns %d", *plPara); 
}

void CReader::ReportError(int nIDError, int nIDAdditionalInfo, HRESULT hr)
{
	TCHAR tchErrorDescription [20];
	sprintf (tchErrorDescription, " %d ", nIDError); 

	TCHAR tchAdditionalInfo [20];

	TCHAR* ptchAdditionalInfo = NULL;

	if (nIDAdditionalInfo > 0)
	{
		ptchAdditionalInfo = tchAdditionalInfo;
		wsprintf (ptchAdditionalInfo, " / %d", nIDAdditionalInfo); 
	}		

	ReportError(tchErrorDescription, ptchAdditionalInfo, hr); 
}

void CReader::TrialCheck  (int iPara, int iLength)
{
	if (-1 != m_iTrialLastPara ) return; 

	m_iTrialCharCount += iLength; 

	if (m_iTrialCharCount > ciMaxTrialCharacters)
	{
		m_iTrialLastPara = iPara; 
	}
}


void CReader::ReportError(LPTSTR pszErrorDescription, LPTSTR pszAdditionalInfo, HRESULT hr)
{
	ATL_TRACE0  (e_LOGERROR, "Reporting Error"); 

	if (0 == strcmp(pszErrorDescription, "GetLastError"))
	{
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL);
		USES_CONVERSION; 

		string str (((const char *)lpMsgBuf));

		MessageBox (GetFocus(), str.c_str(), "Error" ,MB_OK); 

		// Free the buffer.
		LocalFree( lpMsgBuf );
	}
	else if (0 == strcmp(pszErrorDescription, "StringError"))
	{
		MessageBox(GetFocus(), pszErrorDescription+ 11, "Error", MB_OK); 
	}
	else 
	{
		TCHAR tchHRESULT [20];
		TCHAR* ptchHRESULT = NULL;
		if (S_OK != hr)
		{
			ptchHRESULT = tchHRESULT; 
			wsprintf (ptchHRESULT, " / %0X   ", hr); 	
		}
		string strError ("WinBlit - Error Accessing Data "); 

		if (pszErrorDescription)
		{
			USES_CONVERSION;
			strError.append(pszErrorDescription); 
			if (pszAdditionalInfo)
			{
				strError.append(pszAdditionalInfo);
			}
			if (ptchHRESULT)
			{
				strError.append(ptchHRESULT); 
			}
			strError.append("\n If this problem persists please contact Product Support"); 
			MessageBox(GetFocus(), strError.c_str(), "Error", MB_OK);
		}
	}
}

