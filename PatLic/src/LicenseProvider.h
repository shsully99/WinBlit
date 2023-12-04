// LicenseProvider.h : Declaration of the CLicenseProvider

#ifndef __LICENSEPROVIDER_H_
#define __LICENSEPROVIDER_H_

#include "resource.h"       // main symbols
#include "MD5.h"			// 

/////////////////////////////////////////////////////////////////////////////
// CLicenseProvider
class ATL_NO_VTABLE CLicenseProvider : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLicenseProvider, &CLSID_LicenseProvider>,
	public IDispatchImpl<ILicenseProvider, &IID_ILicenseProvider, &LIBID_PATLICLib>
{
public:
	CLicenseProvider()
	{
	}
	CMD5 m_MD5; 
DECLARE_REGISTRY_RESOURCEID(IDR_LICENSEPROVIDER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLicenseProvider)
	COM_INTERFACE_ENTRY(ILicenseProvider)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ILicenseProvider
public:
	STDMETHOD(ValidatePAK)(/*[in]*/ BSTR bstrKey, /*[in]*/ long lCode, /*[in]*/ BSTR bstrPAK, /*[out.retval]*/ BOOL* bPAKValid);
	STDMETHOD(GeneratePAK)(/*[in]*/ BSTR bstrKey, /*[in]*/ long lCode, /*[in.out]*/ BSTR* bstrPAK);
};

#endif //__LICENSEPROVIDER_H_
