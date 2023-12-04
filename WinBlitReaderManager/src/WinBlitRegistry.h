//***************************************************************************
//*
//*		Name		: WinBlitRegistry.h
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
//*		Handles all WinBlit's interaction with the system registry
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

//////////////////////////////////////////////////////////////////////

#include "WinBlitProperties.h"
#include "WinBlitConstants.h"

#if !defined(AFX_WINBLITREGISTRY_H__54E134D3_6163_11D5_8611_82E94F000000__INCLUDED_)
#define AFX_WINBLITREGISTRY_H__54E134D3_6163_11D5_8611_82E94F000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <string>

using namespace std; 

class CSettingStrings
{
public:
	wstring m_wstrName;
	wstring m_wstrTemplateID;
	wstring m_wstrDescription; 
};

class CWinBlitRegistry  
{
public:
	int RemoveSettings (BSTR bstrRemove, int iKeyType = 0);
	int SaveSettings (BSTR bstrRegistry, CWinBlitProperties* m_pProperties, int iKeyType = 0);
	int LoadSettings (	BSTR bstrRegistry, 
						CWinBlitProperties* m_pProperties, 
						int iKeyType = 0,
						bool bBasicDetailsOnly = false);
	int GetAllSettings (vector<CSettingStrings>& vecName, 
						int iKeyType = 0);
	int RemoveRecurse(wstring& strKey,	wstring &strRemove, int iKeyType = 0);
	int SetDefaultName (wstring &strKey, int iKeyType = 0);
	int GetDefaultName (wstring &strKey, int iKeyType = 0);
	long GetStartupFlag ();
	void SetStartupFlag (long lStartup);
	//int GetDescription (string &strKey, LPSTR pszDescription, int iKeyType = 0);
	CWinBlitRegistry();
	virtual ~CWinBlitRegistry();
};

#endif // !defined(AFX_WINBLITREGISTRY_H__54E134D3_6163_11D5_8611_82E94F000000__INCLUDED_)
