//***************************************************************************
//*
//*		Name		: Reader.h
//*							
//*		$Revision:$
//*
//*		Date        : 20-Feb-2002
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
//*		Abstract base class which defines the interface for the specific reader objects
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/
#if !defined(AFX_READER_H__0E9E0E61_190E_11D5_859E_6CA415000000__INCLUDED_)
#define AFX_READER_H__0E9E0E61_190E_11D5_859E_6CA415000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WinBlitConstants.h"
#include "WinBlitProperties.h"

#include <vector>
using namespace std;

class CWinBlitData;

class CReader  
{
public:
	virtual int Initialise (VARIANT varDataSourceURL, CWinBlitData* pWinBlitData) 
	{
		m_bUseSubReader = false; 
		m_bArrayFull = false; 
		m_pWinBlitData = pWinBlitData;
		m_iTrialCharCount = 0; 
		m_iTrialLastPara = -1;
		return 0;
	};

	virtual int GetData(long lDataOffset, BSTR* bstrData) {return 0;};

	virtual int FindString(BSTR bstrSearchString, long lSearchOffset, long lSearchDirection, long *lStringOffset) {return 0;};

	virtual int Uninitialise ()  
	{
		m_bUseSubReader = false; 
		m_bArrayFull = false; 
		m_pWinBlitData = NULL;
		return 0;
	};

	CReader::CReader()
	{
		CReader::CReader(e_STRING); 
	};

	CReader(eDATASOURCETYPE eDataSourceType):
		m_eDataSourceType	(eDataSourceType), 
		m_dwDataSourceSize(0),
		m_bArrayFull(false), 
		m_bUseSubReader(false), 
		m_pSubReader(NULL), 
		m_bReturnData(true),
		m_pWinBlitData(NULL),
		m_iMaxChars(0),
		m_iTrialCharCount(0),
		m_iTrialLastPara(-1)
		{
			ATL_TRACE1 (3, "CReader::CReader  %d ",m_bReturnData); 
		};

	void GetPercentAtPara (/*[in,out]*/ long* lPercent, /*[in]*/ long lPara);

	void GetParaAtPercent (/*[in]*/ long lPercent, /*[in,out]*/ long* lPara, BOOL bRound);
		
	virtual ~CReader();
	bool m_bReturnData;

	void SetMaxChars (int iMaxChars) 
	{
		if (m_bUseSubReader)
		{
			m_pSubReader->SetMaxChars(iMaxChars);
		}
		else
		{
			m_iMaxChars = iMaxChars; 
		}
	};

	int  GetMaxChars	  ()	
	{
		if (m_bUseSubReader)
		{
			return m_pSubReader->GetMaxChars();
		}
		else
		{
			return m_iMaxChars; 
		}
	}; 

	int	 GetTrialLastPara ()	
	{
		if (m_bUseSubReader)
		{
			return m_pSubReader->GetTrialLastPara();
		}
		else
		{
			return m_iTrialLastPara; 
		}
	}; 

protected:
	void ReportError(int nIDError, int nIDAdditionalInfo= 0 , HRESULT hr = E_INVALIDARG );
	void ReportError(LPTSTR pszErrorDescription, LPTSTR pszAdditionalInfo = NULL, HRESULT hr = E_INVALIDARG);
	void TrialCheck  (int iPara, int iLength); 
	bool m_bArrayFull;
	DWORD m_dwDataSourceSize;
	eDATASOURCETYPE m_eDataSourceType;		
	CWinBlitProperties *m_pWinBlitProperties; 
	vector<DWORD> m_vdwOffsets;
	bool m_bUseSubReader; 
	CReader* m_pSubReader; 
	CWinBlitData* m_pWinBlitData; 
	int m_iMaxChars; 
	int m_iTrialCharCount; 
	int m_iTrialLastPara; 
};

#endif // !defined(AFX_READER_H__0E9E0E61_190E_11D5_859E_6CA415000000__INCLUDED_)