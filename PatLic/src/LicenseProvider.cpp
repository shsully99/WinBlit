// LicenseProvider.cpp : Implementation of CLicenseProvider
#include "stdafx.h"
#include "PatLic.h"
#include "LicenseProvider.h"
/////////////////////////////////////////////////////////////////////////////
// CLicenseProvider


STDMETHODIMP CLicenseProvider::GeneratePAK(BSTR bstrKey, long lCode, BSTR *pbstrPAK)
{
	USES_CONVERSION; 
	const char* pchKey = (const char *)  OLE2T(bstrKey); 

	m_MD5.setPlainText(pchKey);		

	*pbstrPAK = ::SysAllocString(T2OLE(m_MD5.getMD5Digest())); 

	return S_OK;
}

STDMETHODIMP CLicenseProvider::ValidatePAK(BSTR bstrKey, long lCode, BSTR bstrPAK, BOOL *bPAKValid)
{
	if (lLogLevel == -1)
	{
		IUnknown *pUnk;
		CLSID clsLogApp;
		CLSIDFromProgID(L"ATLLogApp.BlitLog.1", &clsLogApp);
		if (SUCCEEDED(GetActiveObject(clsLogApp,  NULL,  (IUnknown**)&pUnk)))
		{
			m_Log = pUnk;
			if (m_Log) m_Log->get_Level(&lLogLevel);
			ATL_TRACE0(1," Started logging in WinBlitReader"); 
		}
	}

	USES_CONVERSION; 
	*bPAKValid = FALSE; 
	unsigned char* pchKey = (unsigned char *)  OLE2T(bstrKey); 

	char* pchPAK = OLE2T(bstrPAK); 

	if (m_MD5.ValidatePAK((const char *)pchKey, pchPAK))
	{
		*bPAKValid = TRUE; 
	}
	return S_OK; 
}
