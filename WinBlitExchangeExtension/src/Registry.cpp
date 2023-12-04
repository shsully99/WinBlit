//***************************************************************************
//*
//*		Name		: Registry.cpp
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
//*	
//*		Class Wrapper around the Windows registry API calls 
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

#include "Registry.h"

#define CLASS_NAME_LENGTH 255

/* IMPORTANT NOTES ABOUT CREGISTRY:
	
	CRegistry never keeps a key open past the end of a function call.
	This is in case the application crashes before the next call to close
	the registry 
	
	KEY NAMES:
	Key names must not begin with a \ and only absolute strings are accepted
	
*/

CRegistry::CRegistry()
{
	m_hRootKey = HKEY_LOCAL_MACHINE;
	m_bLazyWrite = TRUE;
	m_nLastError = ERROR_SUCCESS;
}

CRegistry::~CRegistry()
{
	ClearKey();
}

BOOL CRegistry::ClearKey()
{
	//ATL_TRACE ("\n CRegistry::ClearKey");
	/* Call CloseKey to write the current key to the registry and close the 
	key. An application should not keep keys open any longer than necessary. 
	Calling CloseKey when there is no current key has no effect.*/

	m_strCurrentPath.erase();
	m_hRootKey = HKEY_LOCAL_MACHINE;
	m_bLazyWrite = TRUE;
	return TRUE;
}

BOOL CRegistry::SetRootKey(HKEY hRootKey)
{
	//ATL_TRACE ("\n CRegistry::SetRootKey");
	// sets the root key
	// make sure to set it to a valid key
	if (hRootKey != HKEY_CLASSES_ROOT &&
			hRootKey != HKEY_CURRENT_USER &&
			hRootKey != HKEY_LOCAL_MACHINE &&
			hRootKey != HKEY_USERS) return FALSE;

	m_hRootKey = hRootKey;
	return TRUE;
}

BOOL CRegistry::CreateKey(LPCTSTR strKey)
{
	//ATL_TRACE ("\n CRegistry::CreateKey");
	/* Use CreateKey to add a new key to the registry. 
		Key is the name of the key to create. Key must be 
		an absolute name. An absolute key 
		begins with a backslash (\) and is a subkey of 
		the root key. */

	ATLASSERT(strKey[0] != '\\');
	HKEY hKey;

	DWORD dwDisposition = 0;

	if (::RegCreateKeyEx(m_hRootKey, LPCTSTR(strKey), 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey,
			&dwDisposition)	!= ERROR_SUCCESS) return FALSE;
	
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	m_strCurrentPath = strKey;
	return TRUE;
}


BOOL CRegistry::DeleteKey(LPCTSTR strKey, LPCTSTR strDeleteKey)
{
	//ATL_TRACE ("if (::RegCreateKeyEx");
	/* Call DeleteKey to remove a specified key and its associated data, 
	if any, from the registry. Returns FALSE is there are subkeys
	Subkeys must be explicitly deleted by separate calls to DeleteKey.
	DeleteKey returns True if key deletion is successful. On error, 
	DeleteKey returns False. */
	
	// need to open the key first with RegOpenKeyEx
	bool bRet = FALSE; 
	ATLASSERT(strKey[0] != '\\');
	if (!KeyExists(strKey)) return FALSE;
	HKEY hKey;
	if (::RegOpenKeyEx(m_hRootKey,strKey,0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS)
	{
		if (::RegDeleteKey(hKey, strDeleteKey) == ERROR_SUCCESS) 
		{
			bRet = TRUE;
		}
	}

	return bRet;
}



BOOL CRegistry::DeleteValue(LPCTSTR strName)
{
	//ATL_TRACE ("\n CRegistry::DeleteValue");
	/* Call DeleteValue to remove a specific data value 
		associated with the current key. Name is string 
		containing the name of the value to delete. Keys can contain 
		multiple data values, and every value associated with a key 
		has a unique name. */

	ATLASSERT(m_strCurrentPath.size() > 0);
	HKEY hKey;
	LONG lResult;

	if (::RegOpenKeyEx(m_hRootKey, m_strCurrentPath.c_str(), 0,
		KEY_SET_VALUE, &hKey) != ERROR_SUCCESS) return FALSE;

	lResult = ::RegDeleteValue(hKey, strName);
	::RegCloseKey(hKey);

	if (lResult == ERROR_SUCCESS) return TRUE;
	return FALSE;
}

DWORD CRegistry::GetDataType(LPCTSTR strValueName)
{
	//ATL_TRACE ("\n CRegistry::GetDataType");
	HKEY hKey;
	ATLASSERT(m_strCurrentPath.size() > 0);

	m_nLastError = ::RegOpenKeyEx(m_hRootKey, m_strCurrentPath.c_str(), 0,
		KEY_QUERY_VALUE, &hKey);

	if (m_nLastError != ERROR_SUCCESS) return 0;

	DWORD dwType = 1;
	m_nLastError = ::RegQueryValueEx(hKey, LPCTSTR(strValueName),
		NULL, &dwType, NULL, NULL);
	::RegCloseKey(hKey);		

	if (m_nLastError == ERROR_SUCCESS) return dwType;

	return 0;
}

BOOL CRegistry::EnumKey(DWORD dwIndex, LPSTR strName)
{
//	ATL_TRACE ("\n CRegistry::EnumKey %s",m_strCurrentPath.c_str());
	HKEY hKey;
	long lA = ::RegOpenKeyEx(m_hRootKey, m_strCurrentPath.c_str(), 0,
		KEY_ALL_ACCESS, &hKey);
	
	if (lA != ERROR_SUCCESS) 
	{
		//ATL_TRACE ("\n ::RegOpenKeyEx failed %d", lA); 
		return FALSE;
	}

	DWORD dwLength = 255; 
	lA = ::RegEnumKeyEx(hKey, dwIndex, strName, &dwLength, NULL, NULL, NULL, NULL );
	if (lA != ERROR_SUCCESS) 
	{
		//ATL_TRACE ("\n ::RegEnumKeyEx failed %d", lA); 
		return FALSE;
	}
	else 
	{
		return TRUE; 
	}

}



int CRegistry::GetSubKeyCount()
{
	//ATL_TRACE ("\n CRegistry::GetSubKeyCount");
	/* Call this function to determine the number of subkeys.
		the function returns -1 on error */
	HKEY hKey;
	ATLASSERT(m_strCurrentPath.size() > 0);

	if (::RegOpenKeyEx(m_hRootKey, m_strCurrentPath.c_str(), 0,
		KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) return -1;

	LONG lResult;
	DWORD dwSubKeyCount, dwValueCount, dwClassNameLength,
		dwMaxSubKeyName, dwMaxValueName, dwMaxValueLength;
	FILETIME ftLastWritten;

	_TCHAR szClassBuffer[CLASS_NAME_LENGTH];
		
	dwClassNameLength = CLASS_NAME_LENGTH;
	lResult = ::RegQueryInfoKey(hKey, szClassBuffer, &dwClassNameLength,
		NULL, &dwSubKeyCount, &dwMaxSubKeyName, NULL, &dwValueCount,
		&dwMaxValueName, &dwMaxValueLength, NULL, &ftLastWritten);
				
	::RegCloseKey(hKey);
	if (lResult != ERROR_SUCCESS) return -1;

	return (int)dwSubKeyCount;
}

int CRegistry::GetValueCount()
{
	ATL_TRACE ("\n CRegistry::GetValueCount");
	/* Call this function to determine the number of subkeys.
		the function returns -1 on error */
	HKEY hKey;
	ATLASSERT(m_strCurrentPath.size() > 0);

	if (::RegOpenKeyEx(m_hRootKey, m_strCurrentPath.c_str(), 0,
		KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) return -1;

	LONG lResult;
	DWORD dwSubKeyCount, dwValueCount, dwClassNameLength,
		dwMaxSubKeyName, dwMaxValueName, dwMaxValueLength;
	FILETIME ftLastWritten;

	_TCHAR szClassBuffer[CLASS_NAME_LENGTH];
		
	dwClassNameLength = CLASS_NAME_LENGTH;
	lResult = ::RegQueryInfoKey(hKey, szClassBuffer, &dwClassNameLength,
		NULL, &dwSubKeyCount, &dwMaxSubKeyName, NULL, &dwValueCount,
		&dwMaxValueName, &dwMaxValueLength, NULL, &ftLastWritten);
				
	::RegCloseKey(hKey);
	if (lResult != ERROR_SUCCESS) return -1;

	return (int)dwValueCount;
}


BOOL CRegistry::KeyExists(LPCTSTR strKey, HKEY hRootKey)
{
	//ATL_TRACE ("\n CRegistry::KeyExists");
	/* Call KeyExists to determine if a key of a specified name exists.
		 Key is the name of the key for which to search. */

	ATLASSERT(strKey[0] != '\\');
	HKEY hKey;

	if (hRootKey == NULL) hRootKey = m_hRootKey;
	
	LONG lResult = ::RegOpenKeyEx(hRootKey, LPCTSTR(strKey), 0,
		KEY_ALL_ACCESS, &hKey);
	::RegCloseKey(hKey);
	if (lResult == ERROR_SUCCESS) return TRUE;
	return FALSE;
}

BOOL CRegistry::SetKey(LPCTSTR strKey, BOOL bCanCreate)
{
	/* Call SetKey to make a specified key the current key. Key is the 
		name of the key to open. If Key is null, the CurrentKey property 
		is set to the key specified by the RootKey property.

		CanCreate specifies whether to create the specified key if it does 
		not exist. If CanCreate is True, the key is created if necessary.

		Key is opened or created with the security access value KEY_ALL_ACCESS. 
		OpenKey only creates non-volatile keys, A non-volatile key is stored in 
		the registry and is preserved when the system is restarted. 

		OpenKey returns True if the key is successfully opened or created */

	ATLASSERT(strKey[0] != '\\');
	HKEY hKey;

	// close the current key if it is open
	if (strKey == NULL)
	{
		m_strCurrentPath.erase();
		return TRUE;
	}

	DWORD dwDisposition;
	if (bCanCreate) // open the key with RegCreateKeyEx
	{
		if (::RegCreateKeyEx(m_hRootKey, LPCTSTR(strKey), 0, NULL, 
			REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey,
				&dwDisposition) != ERROR_SUCCESS) return FALSE;
		m_strCurrentPath = strKey;
		if (!m_bLazyWrite) ::RegFlushKey(hKey);
		::RegCloseKey(hKey);	
		return TRUE;
	}

	// otherwise, open the key without creating
	// open key requires no initial slash
	m_nLastError = ::RegOpenKeyEx(m_hRootKey, LPCTSTR(strKey), 0,
		KEY_ALL_ACCESS, &hKey);
	if (m_nLastError != ERROR_SUCCESS) return FALSE;
	m_strCurrentPath = strKey;
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return TRUE;
}

BOOL CRegistry::ReadString(LPCTSTR strName, BSTR* bstrString)
{
	BOOL  bRet = FALSE; 
	USES_CONVERSION;
	CHAR pszString [255];
	bRet = ReadString(strName, pszString);
	if (bRet) *bstrString = ::SysAllocString(T2OLE(pszString));
	return bRet;
}


BOOL CRegistry::ReadString(LPCTSTR strName, LPCTSTR strString)
{
	BOOL bRet = FALSE;
	DWORD dwType = REG_SZ;
	DWORD dwSize = 255;
	HKEY hKey;
								 
	ATLASSERT(m_strCurrentPath.size() > 0);

	// make sure it is the proper type
	dwType = GetDataType(strName);
	
	if (dwType == REG_SZ || dwType == REG_EXPAND_SZ)
	{
		m_nLastError = ::RegOpenKeyEx(m_hRootKey, m_strCurrentPath.c_str(), 0,
			KEY_READ, &hKey);
		if (m_nLastError == ERROR_SUCCESS) 
		{
			m_nLastError = ::RegQueryValueEx(hKey, strName, NULL,
			&dwType, (LPBYTE)strString, &dwSize);
			if (m_nLastError == ERROR_SUCCESS) 
			{
				bRet = TRUE;
			}
			::RegCloseKey(hKey);	
		}
	}
	return bRet;
}

BOOL CRegistry::ReadBytes(LPCTSTR strName, unsigned char* pByteArray, DWORD& dwSize)
{
	DWORD dwOldSize   = dwSize; 
	bool bRet = FALSE; 
	DWORD dwType = REG_BINARY;
	HKEY hKey;

	ATLASSERT(m_strCurrentPath.size() > 0);
	if (::RegOpenKeyEx(m_hRootKey, m_strCurrentPath.c_str(), 0,
		KEY_READ, &hKey) == ERROR_SUCCESS) 
	{

		if (::RegQueryValueEx(hKey, strName, NULL,
			&dwType, (LPBYTE)pByteArray, &dwSize) == ERROR_SUCCESS)
		{
			bRet = TRUE; 
			if (dwSize < dwOldSize) pByteArray[dwSize] = '\0'; 
		}
		::RegCloseKey(hKey);
	}	
	return bRet;
}

BOOL CRegistry::ReadInt(LPCTSTR strName, short& nl)
{
	int ni = nl;
	BOOL  bRet = ReadInt(strName, ni);
	nl = static_cast<short>(ni); 
	return bRet;
}

BOOL CRegistry::ReadInt(LPCTSTR strName, long& nl)
{
	INT ni = nl; 
	BOOL  bRet = ReadInt(strName, ni);
	nl = ni; 
	return bRet; 
}

BOOL CRegistry::ReadInt(LPCTSTR strName, DWORD& dw)
{
	INT ni = dw; 
	BOOL  bRet = ReadInt(strName, ni);
	dw = ni; 
	return bRet; 
}

BOOL CRegistry::ReadBool(LPCTSTR strName, BOOL& b)
{
	BOOL bRet = FALSE; 
	INT ni = 0;
	bRet = ReadInt(strName, ni);
	if (0 == ni) 
	{
		b = FALSE;
	}
	else
	{
		b = TRUE; 
	}
	return bRet; 
}

BOOL CRegistry::ReadInt(LPCTSTR strName, INT& n)
{
	bool bRet = FALSE; 
	
	DWORD dwType = REG_DWORD;
	DWORD dwSize = sizeof(n);
	HKEY hKey;

	ATLASSERT(m_strCurrentPath.size() > 0);
	if (::RegOpenKeyEx(m_hRootKey, m_strCurrentPath.c_str(), 0,
		KEY_READ, &hKey) == ERROR_SUCCESS) 
	{
		if (::RegQueryValueEx(hKey, strName, NULL,
			&dwType, (LPBYTE)&n, &dwSize) == ERROR_SUCCESS)
		{
			bRet = TRUE; 
		}
		::RegCloseKey(hKey);
	}	
	return bRet;
}

BOOL CRegistry::WriteString(LPCTSTR strName, BSTR bstrValue, int iLength)
{
	USES_CONVERSION;
	return WriteString (strName, OLE2T(bstrValue),iLength);
}

BOOL CRegistry::WriteString(LPCTSTR strName, LPCTSTR strValue, int iLength)
{
	ATLASSERT(m_strCurrentPath.size() > 0);
	bool bRet = FALSE; 
	HKEY hKey;
	
	if (iLength > 254) return FALSE;

	if (::RegOpenKeyEx(m_hRootKey, m_strCurrentPath.c_str(), 0,
		KEY_WRITE, &hKey) == ERROR_SUCCESS) 
	{
	
		if (::RegSetValueEx(hKey, strName, 0,	REG_SZ, (LPBYTE)strValue, iLength + 1)
		 == ERROR_SUCCESS) 
		{
			bRet = TRUE;
		}
		if (!m_bLazyWrite) ::RegFlushKey(hKey);
		::RegCloseKey(hKey);
	}
	return bRet;
}

BOOL CRegistry::WriteBool(LPCTSTR strName, BOOL bValue)
{
	DWORD dw;
	if (TRUE == bValue)
	{
		dw = 1;
	}
	else 
	{
		dw = 0;
	}
	BOOL  bRet = WriteInt(strName, dw);
	return bRet;
}

BOOL CRegistry::WriteInt(LPCTSTR strName, DWORD dwValue)
{
	ATLASSERT(m_strCurrentPath.size() > 0);
	bool bRet = FALSE; 
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, m_strCurrentPath.c_str(), 0,
		KEY_WRITE, &hKey) == ERROR_SUCCESS) 
	{
		if (::RegSetValueEx(hKey, strName, 0,
			REG_DWORD, (LPBYTE)&dwValue, sizeof(dwValue))
			 == ERROR_SUCCESS)
		{
			bRet = TRUE;
		}		
		if (!m_bLazyWrite) ::RegFlushKey(hKey);
		::RegCloseKey(hKey);
	}
	return bRet;
}


BOOL CRegistry::WriteBytes (LPCTSTR strName, unsigned char* pByteArray, DWORD dwSize)
{
	ATLASSERT(m_strCurrentPath.size() > 0);
	bool bRet = FALSE; 
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, m_strCurrentPath.c_str(), 0,
		KEY_WRITE, &hKey)  == ERROR_SUCCESS)
	{
		if (::RegSetValueEx(hKey, strName, 0,
			REG_BINARY, (LPBYTE)pByteArray, dwSize) == ERROR_SUCCESS) 
		{
			bRet = TRUE;
		}
		if (!m_bLazyWrite) ::RegFlushKey(hKey);
		::RegCloseKey(hKey);
	}
	return bRet;
}



