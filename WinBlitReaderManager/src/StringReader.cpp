//***************************************************************************
//*
//*		Name		: StringReader.cpp
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
//*		Implementation of reader object for string data source 
//* 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

// StringReader.cpp: implementation of the CStringReader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StringReader.h"
#include "resource.h"
#include "WinBlitDataError.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringReader::~CStringReader()
{
}

//=========================================================================== 
//						
//	Method :		Uninitialise
//						
//	Description :	Uninitialise txt data source
//
//  Returns	:		0 if successful 
//					
//============================================================================

int CStringReader::Uninitialise () 
{
	ATL_TRACE0 (1,"\n CStringReader::Uninitialise");

	// Clean up memory
	m_vdwOffsets.erase(m_vdwOffsets.begin(), m_vdwOffsets.end());

	if (m_bstrStringBuffer)
	{
		::SysFreeString(m_bstrStringBuffer); 
		m_bstrStringBuffer = NULL; 
	}

	CReader::Uninitialise();

	return 0;
}

//=========================================================================== 
//						
//	Method :		Initialise
//						
//	Description :	Open txt file for processing for a given path name 
//
//  Returns	:		0  if successful 					
//					1  if no data 
//					2  if system error
//
//============================================================================
//
int CStringReader::Initialise (VARIANT varDataSourceURL, CWinBlitData* pWinBlitData) 
{
	ATL_TRACE1 (2, "\n CStringReader::Initialise  %d", m_bReturnData);

	int iRet = 0;				// Assume success

	if (m_bstrStringBuffer)
	{
		::SysFreeString(m_bstrStringBuffer); 
		m_bstrStringBuffer = NULL; 
	}

	iRet = CReader::Initialise(varDataSourceURL, pWinBlitData); 
	if (0 == iRet)
	{
		// Clear our array of data offsets. 
		m_vdwOffsets.clear();

		// Copy parameter string to member variable

		m_bstrStringBuffer = SysAllocString(varDataSourceURL.bstrVal); 
		if (NULL == m_bstrStringBuffer )
		{
			ReportError(IDS_OUTOFMEMORY, NULL, E_OUTOFMEMORY);
			iRet = 2;
		}
		else 
		{
			m_dwDataSourceSize = ::SysStringLen(m_bstrStringBuffer);
			if (0 == m_dwDataSourceSize)
			{
				iRet = 1;
			}
		}
	}

	return iRet;
};

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
int CStringReader::GetData (long lDataBuffer,		// Data buffer to return to user
						 BSTR* pbstrData)
{
	ATL_TRACE1 (1,"\n CStringReader::GetData %d", m_bReturnData);

	int iRet = 0;
	DWORD dwDataOffset;

	if (lDataBuffer < m_vdwOffsets.size())
	{
		// Our offset is the end of the  previous buffer in the array.
		if (lDataBuffer == 0) 
		{
			dwDataOffset = 0;
		}
		else 
		{
			dwDataOffset = m_vdwOffsets.at(lDataBuffer-1);
		}
		ReadData(&dwDataOffset, pbstrData);		
	}
	else 
	{
		dwDataOffset = 0;
		if (m_vdwOffsets.size() > 0)
		{
			dwDataOffset = m_vdwOffsets.at(m_vdwOffsets.size()-1);
		}		
		
		for (int iA = m_vdwOffsets.size(); iA <= lDataBuffer; iA++)
		{
			iRet = ReadData(&dwDataOffset, pbstrData);

			if (iRet > 0)
			{
				break;
			}
			else
			{
				if (m_iMaxChars != 0 && m_iTrialLastPara == -1)
				{
					CReader::TrialCheck(iA, abs(iRet));
				}
				m_vdwOffsets.push_back(dwDataOffset);
			}
		}
	}
	ATL_TRACE1 (1,"\n CStringReader::GetData return value %d", iRet);

	return iRet;
};

//=========================================================================== 
//						
//	Method :		ReadData
//						
//	Description :	Set up client buffer for a given offset 
//
//  Returns			<=0 If successful 
//					1 Buffer out of range 
//					2 System error
//
//============================================================================
//
int CStringReader::ReadData(DWORD* pdwDataOffset,	BSTR* pbstrData)
{
	ATL_TRACE3 (1,"\n CStringReader::ReadData %d %d %d ",*pdwDataOffset ,::SysStringLen(m_bstrStringBuffer), m_bReturnData);
	int iRet = 0;		
	int iReadBuffer = 0; 
	USES_CONVERSION; 

	// Check we have been passed a free string 
	if (*pbstrData != NULL)
	{
		::SysFreeString(*pbstrData);
		*pbstrData = NULL; 
	}

	DWORD dwTemp = *pdwDataOffset;

	if (dwTemp < ::SysStringLen(m_bstrStringBuffer))
	{
		// First look for carriage return
		WCHAR* pwchNextPos = m_bstrStringBuffer + dwTemp;

        while (*pwchNextPos && (*pwchNextPos != cwchCR && *pwchNextPos != cwchLF)) 
		{
			pwchNextPos++;
		}
		int iLineFeed = 0;

		if (NULL  == pwchNextPos) 
		{
			// Carriage return not found so take remainder of string
			pwchNextPos = m_bstrStringBuffer + ::SysStringLen(m_bstrStringBuffer);
		}
		else
		{
			if (*(pwchNextPos+1) == cwchLF)
			{
				iLineFeed = 1;
			}
		}
		int iAlloc = pwchNextPos - m_bstrStringBuffer - *pdwDataOffset + iLineFeed;

		*pdwDataOffset = pwchNextPos - m_bstrStringBuffer  + 1 + iLineFeed;

		if (m_bReturnData)
		{
			if (0 != iAlloc)
			{
				*pbstrData = ::SysAllocStringLen(m_bstrStringBuffer +dwTemp,iAlloc + iLineFeed);
			}
			else
			{
				*pbstrData = ::SysAllocStringLen(&cwchSpace,1);
			}
			if (*pbstrData == NULL)
			{
				ATL_TRACE0 (3, " Memory error - Failed to allocate buffer  "); 
				ReportError(IDS_GETDATA, IDS_OUTOFMEMORY);
				iRet = 2;
			}
		}

		if (0 == iRet)
		{	
			iRet = 0-iAlloc; 
		}
	}
	else
	{
		m_bArrayFull = true; 
		iRet = 1;
	}

	ATL_TRACE2 (1, " returning Length %d data buffer %.60s ", iRet, OLE2T(*pbstrData)); 

	return iRet; 
}

int CStringReader::FindString(BSTR bstrSearchString, long lSearchOffset, long lSearchDirection, long *lStringOffset)
{
	ATL_TRACE0 (1, "\n CStringReader::FindString");
	return 0;
};