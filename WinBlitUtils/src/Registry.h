//***************************************************************************
//*
//*		Name		: Registry.h
//*							
//*		$Revision:$
//*
//*		Date        : 20-Jul-2001
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
//*		Wrapper around the Windows registry API calls  
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#ifndef __REGISTRY_H__
#define __REGISTRY_H__
#include "stdafx.h"

#include <string>

using namespace std;

class CRegistry
{
public:
	CRegistry();
	~CRegistry();

int m_nLastError;

// CRegistry properties	
protected:
	HKEY m_hRootKey;
	BOOL m_bLazyWrite;
	string m_strCurrentPath;

public:
	inline BOOL PathIsValid() {
		return (m_strCurrentPath.size() > 0); }
	inline LPCTSTR GetCurrentPath() {
		return m_strCurrentPath.c_str(); }
	inline HKEY GetRootKey() {
		return m_hRootKey; }
	inline void SetLazyWrite (BOOL bLazyWrite) {
		m_bLazyWrite = bLazyWrite;
	}



//CRegistry	methods
public:
	BOOL ClearKey();
	BOOL SetRootKey(HKEY hRootKey);
	BOOL CreateKey(LPCTSTR strKey);
	BOOL DeleteKey(LPCTSTR  strKey, LPCTSTR strDeleteKey);
	BOOL DeleteValue(LPCTSTR strName);
	int GetSubKeyCount();
	int GetValueCount();
	BOOL SetKey(LPCTSTR strKey, BOOL bCanCreate);
	BOOL EnumKey(DWORD dwIndex, LPSTR strName); 

	// data reading functions
	BOOL ReadString(LPCTSTR strName,	BSTR* strDefault);
	BOOL ReadString(LPCTSTR strName,	LPCTSTR strDefault);

	BOOL ReadBool(LPCTSTR strName,		BOOL& bDefault);

	BOOL ReadBytes(LPCTSTR strName,		unsigned char* pByteArray, DWORD& dwSize);

	BOOL ReadInt(LPCTSTR strName,		INT& n);
	BOOL ReadInt(LPCTSTR strName,		long& n);
	BOOL ReadInt(LPCTSTR strName,		short& nDefault);
	BOOL ReadInt(LPCTSTR strName,		DWORD& dwDefault);

	// data writing functions
	BOOL WriteString(LPCTSTR strName,	LPCTSTR strValue, int iLength );
	BOOL WriteString(LPCTSTR strName,	BSTR bstrValue, int iLength );

	BOOL WriteBool(LPCTSTR strName,		BOOL bValue);

	BOOL WriteBytes (LPCTSTR strName,	unsigned char* pByteArray, DWORD dwSize);

	BOOL WriteInt(LPCTSTR strName,		DWORD dwValue);

protected:
	DWORD GetDataType(LPCTSTR  strValueName);

	BOOL KeyExists(LPCTSTR strKey, HKEY hRootKey = NULL);


};// end of CRegistry class definition

#endif