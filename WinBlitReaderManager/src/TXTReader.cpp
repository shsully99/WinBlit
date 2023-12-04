//***************************************************************************
//*
//*		Name		: TXTReader.cpp
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

// TXTReader.cpp: implementation of the CTXTReader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TXTReader.h"
#include "resource.h"
#include "BlitUtils.h"
#include "StringReader.h"
#include "WinBlitDataError.h"
#include "ReportError.cpp"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTXTReader::~CTXTReader()
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

int CTXTReader::Uninitialise () 
{
	if (m_bUseSubReader ) 
	{
		m_pSubReader->Uninitialise(); 
	}

	ATL_TRACE ("\n CTXTReader::Uninitialise");
	if (m_eDataSourceType == e_TXTFILEASCII)
	{
		m_cfstream.close();
	}
	else 
	{
		m_wfstream.close();
	}

	// Clean up memory
	m_vdwOffsets.clear();

	if (m_bstrReadBuffer) ::SysFreeString(m_bstrReadBuffer); 

	CReader::Uninitialise();

	return 0;
}

//=========================================================================== 
//						
//	Method :		Initialise
//						
//	Description :	Open txt file for processing for a given path name 
//
//  Returns	:		0 if successful 
//					>0 if failire
//
//============================================================================
//
int CTXTReader::Initialise (VARIANT varDataSourceURL, CWinBlitData* pWinBlitData) 
{
	ATL_TRACE ("\n CTXTReader::Initialise ");

	int iRet = 0;				// Assume success
	
	iRet = CReader::Initialise(varDataSourceURL, pWinBlitData); 

	if (0 == iRet)
	{
		CComBSTR bstrDataSource;

		bstrDataSource.Attach(FileString(varDataSourceURL.bstrVal));

		USES_CONVERSION;
		// Use the WIN32 api funcions to detrermine file size 
		HANDLE hFile = CreateFile(OLE2T(varDataSourceURL.bstrVal), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			ReportError("GetLastError");
			iRet = 2; 
		}
		else 
		{
			m_dwDataSourceSize = GetFileSize(hFile, NULL); 
			if (0 == m_dwDataSourceSize)
			{
				iRet = 1;
			}
			else
			{
				int iCharCount;													// No of chars in file 

				CloseHandle(hFile);

				bool bIsOpen = false;
				// Try and open streams on the files
				if (m_eDataSourceType == e_TXTFILEASCII)
				{
					m_cfstream.open(OLE2T(varDataSourceURL.bstrVal),			// File Descriptor
								ios::in);									// Open for input - fail if it is not there
		
					bIsOpen = m_cfstream.is_open();
					iCharCount = m_dwDataSourceSize;
				}
				else 
				{
					m_wfstream.open(OLE2T(bstrDataSource),						// File Descriptor
								ios::in);									// Open for input - fail if it is not there
					bIsOpen = m_wfstream.is_open();
					iCharCount = m_dwDataSourceSize/2;
				}

				// Clear the BSTR returned from the FileString method
				::SysFreeString(bstrDataSource.Detach()); 
				if (!bIsOpen)
				{
					ReportError(IDS_OPENING_STREAM); 
					iRet = 2;
				}
				else
				{
					// First try and use the string reader.
					// We do not report errors encoutered here as if we fail here 
					// to allocate memory for the whole string we use the TXT Reader object
					// rather than the string reader. 

					BSTR bstrTemp = ::SysAllocStringLen(NULL, iCharCount);
					m_bUseSubReader = false; 
					if (NULL != bstrTemp)
					{
						if (m_eDataSourceType == e_TXTFILEASCII)
						{
							// To save memory read it into a TCHAR then convert to a BSTR manually 
							m_cfstream.read( (TCHAR*)bstrTemp, iCharCount);	
							int iLength = m_cfstream.gcount(); 
							bstrTemp[iLength] = cwchNull; 
							for (int iA = iLength-1; iA >= 0; iA--)
							{
								TCHAR* ptch = ((TCHAR*)bstrTemp) + iA;  
								bstrTemp[iA] = WCHAR(*ptch); 
							}
						}
						else
						{
							m_wfstream.read(bstrTemp, iCharCount);
						}

						if (m_pSubReader == NULL) 
						{
							m_pSubReader = new CStringReader(e_STRING);
						}

						if (m_pSubReader)
						{
							if (0 == m_pSubReader->Initialise(CComVariant(bstrTemp), pWinBlitData))
							{
								m_bUseSubReader = true;
							}
							else 
							{
								m_pSubReader->Uninitialise();
							}

						}
						::SysFreeString(bstrTemp); 
					}
				}
			}
		}
	}

	if (0 == iRet && !m_bUseSubReader)
	{
		// If we opened the file successfully but did not manage to use the string 
		// reader we try and use this object instead. 

		// Clear our array of data offsets. 
		m_vdwOffsets.clear();

		// Allocate buffer to read text into 
		m_bstrReadBuffer = SysAllocStringLen(NULL,   cdwTXTReadBufferLength); 
		if (!m_bstrReadBuffer)
		{
			ReportError(IDS_OUTOFMEMORY, NULL, E_OUTOFMEMORY);
			iRet = 2;
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
//  Returns	:		0 if successful else error
//					
//============================================================================
//
int CTXTReader::GetData (long lDataBuffer,	BSTR* pbstrData)
{
	ATL_TRACE ("\n CTXTReader::GetData ");

	if (m_bUseSubReader)
	{
		return m_pSubReader->GetData (lDataBuffer, pbstrData); 
	}

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
				m_vdwOffsets.push_back(dwDataOffset);
			}
		}
	}
	return iRet;
};

//=========================================================================== 
//						
//	Method :		ReadData
//						
//	Description :	Set up client buffer for a given offset 
//
//  Returns			0 If successful 
//					1 Buffer out of range 
//					2 System error
//
//============================================================================
//
int CTXTReader::ReadData(DWORD* pdwDataOffset,	BSTR* pbstrData)
{
	ATL_TRACE ("\n CTXTReader::ReadData");
	int iRet = 0;		
	int iReadBuffer = 0; 
	USES_CONVERSION; 
	const WCHAR cwchNewLine ('\n'); 

	// Check we have been passed a free string 
	if (*pbstrData != NULL)
	{
		::SysFreeString(*pbstrData);
		*pbstrData = NULL; 
	}

	CComBSTR bstrTemp; 

	if (e_TXTFILEASCII == m_eDataSourceType)
	{
		m_cfstream.clear();
		m_cfstream.seekg(*pdwDataOffset);
		DWORD dwOffset = 0 ;
		DWORD dwBufCount = 0; 
		TCHAR tch (' '); 
		
		bool bLineEndFound = false; 
		bool bMemoryOK = true; 

		// Move through the file looking for an end of file or and end of line character
		while (!bLineEndFound  && bMemoryOK)
		{
			tch = m_cfstream.get();
  
			if (m_cfstream.eof()) break; 

			// Break if new line character read 
			if (tch == cwchNewLine ) 
			{
				bLineEndFound = true; 
				tch = ' '; 
			}

			dwOffset++;
			m_bstrReadBuffer[dwOffset-1] = static_cast<WCHAR>(tch); 

			if (dwOffset == cdwTXTReadBufferLength)
			{	
				if (E_OUTOFMEMORY == bstrTemp.Append (m_bstrReadBuffer))
				{
					bMemoryOK = false;
				}
				else
				{
					dwBufCount++;
					dwOffset = 0; 
				}
			}
		}

		if (false == bMemoryOK)
		{
			iRet = 2;
			ReportError(IDS_GETDATA, IDS_OUTOFMEMORY);
		}
		else if (0 < (dwBufCount * cdwTXTReadBufferLength + dwOffset) )
		{
			bstrTemp.Append(m_bstrReadBuffer, dwOffset); 
			*pbstrData = bstrTemp.Detach(); 
			// Set next file position as 1 char after this buffer . 
			*pdwDataOffset += dwBufCount * cdwTXTReadBufferLength + dwOffset + 1;
		}
		else 
		{
			iRet = 1;					// Reached end of file 
			m_bArrayFull = true; 
		}
	}
	else 
	{
	}	

	return iRet; 
}

int CTXTReader::FindString(BSTR bstrSearchString, long lSearchOffset, long lSearchDirection, long *lStringOffset)
{
	ATL_TRACE ("\n CTXTReader::FindString");

	return 0;
};