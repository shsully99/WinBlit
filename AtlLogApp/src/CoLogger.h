// CoLogger.h : Declaration of the CCoLogger

#ifndef __COLOGGER_H_
#define __COLOGGER_H_
#include <comutil.h>

#include "resource.h"       // main symbols
#include "CEventDlg.h"
#include <iostream>
#include <fstream>
using namespace std; 
class CCEventDlg;

/////////////////////////////////////////////////////////////////////////////
// CCoLogger
class ATL_NO_VTABLE CCoLogger : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCoLogger, &CLSID_CoLogger>,
	public ICoLogger
{
public:
	CCoLogger()
	{
	m_bDialogAlive =FALSE;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COLOGGER)
DECLARE_NOT_AGGREGATABLE(CCoLogger)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCoLogger)
	COM_INTERFACE_ENTRY(ICoLogger)
END_COM_MAP()

// ICoLogger
public:
	STDMETHOD(get_Path)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Path)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Level)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Level)(/*[in]*/ long newVal);
	CCEventDlg *m_Dlg;
	BOOL m_bDialogAlive ; 
	STDMETHOD(UnInitialize)();
	STDMETHOD(Log)(long lSeverity, long lThreadID, BSTR bstrText);
	STDMETHOD(DisplayText)();
	STDMETHOD(Initialize)();
	long m_iLogLevel; 
	bool m_bLogFile;
	CComBSTR m_bstrLogPath;
	ofstream  m_ofstream;
	HRESULT FinalConstruct();
};

#endif //__COLOGGER_H_
