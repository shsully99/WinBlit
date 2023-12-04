/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Mar 19 09:48:07 2002
 */
/* Compiler settings for C:\Documents and Settings\Sean Sullivan\My Documents\WINBLIT\PatLic\src\PatLic.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __PatLic_h__
#define __PatLic_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ILicenseProvider_FWD_DEFINED__
#define __ILicenseProvider_FWD_DEFINED__
typedef interface ILicenseProvider ILicenseProvider;
#endif 	/* __ILicenseProvider_FWD_DEFINED__ */


#ifndef __LicenseProvider_FWD_DEFINED__
#define __LicenseProvider_FWD_DEFINED__

#ifdef __cplusplus
typedef class LicenseProvider LicenseProvider;
#else
typedef struct LicenseProvider LicenseProvider;
#endif /* __cplusplus */

#endif 	/* __LicenseProvider_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ILicenseProvider_INTERFACE_DEFINED__
#define __ILicenseProvider_INTERFACE_DEFINED__

/* interface ILicenseProvider */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILicenseProvider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BBF085F3-B413-11D5-8689-7C9ECC000000")
    ILicenseProvider : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GeneratePAK( 
            /* [in] */ BSTR bstrKey,
            /* [in] */ long lCode,
            /* [out][in] */ BSTR __RPC_FAR *bstrPAK) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ValidatePAK( 
            /* [in] */ BSTR bstrKey,
            /* [in] */ long lCode,
            /* [in] */ BSTR bstrPAK,
            /* [retval][out] */ BOOL __RPC_FAR *bPAKValid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILicenseProviderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILicenseProvider __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILicenseProvider __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILicenseProvider __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILicenseProvider __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILicenseProvider __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILicenseProvider __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILicenseProvider __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GeneratePAK )( 
            ILicenseProvider __RPC_FAR * This,
            /* [in] */ BSTR bstrKey,
            /* [in] */ long lCode,
            /* [out][in] */ BSTR __RPC_FAR *bstrPAK);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ValidatePAK )( 
            ILicenseProvider __RPC_FAR * This,
            /* [in] */ BSTR bstrKey,
            /* [in] */ long lCode,
            /* [in] */ BSTR bstrPAK,
            /* [retval][out] */ BOOL __RPC_FAR *bPAKValid);
        
        END_INTERFACE
    } ILicenseProviderVtbl;

    interface ILicenseProvider
    {
        CONST_VTBL struct ILicenseProviderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILicenseProvider_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILicenseProvider_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILicenseProvider_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILicenseProvider_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILicenseProvider_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILicenseProvider_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILicenseProvider_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILicenseProvider_GeneratePAK(This,bstrKey,lCode,bstrPAK)	\
    (This)->lpVtbl -> GeneratePAK(This,bstrKey,lCode,bstrPAK)

#define ILicenseProvider_ValidatePAK(This,bstrKey,lCode,bstrPAK,bPAKValid)	\
    (This)->lpVtbl -> ValidatePAK(This,bstrKey,lCode,bstrPAK,bPAKValid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILicenseProvider_GeneratePAK_Proxy( 
    ILicenseProvider __RPC_FAR * This,
    /* [in] */ BSTR bstrKey,
    /* [in] */ long lCode,
    /* [out][in] */ BSTR __RPC_FAR *bstrPAK);


void __RPC_STUB ILicenseProvider_GeneratePAK_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILicenseProvider_ValidatePAK_Proxy( 
    ILicenseProvider __RPC_FAR * This,
    /* [in] */ BSTR bstrKey,
    /* [in] */ long lCode,
    /* [in] */ BSTR bstrPAK,
    /* [retval][out] */ BOOL __RPC_FAR *bPAKValid);


void __RPC_STUB ILicenseProvider_ValidatePAK_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILicenseProvider_INTERFACE_DEFINED__ */



#ifndef __PATLICLib_LIBRARY_DEFINED__
#define __PATLICLib_LIBRARY_DEFINED__

/* library PATLICLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PATLICLib;

EXTERN_C const CLSID CLSID_LicenseProvider;

#ifdef __cplusplus

class DECLSPEC_UUID("BBF085F4-B413-11D5-8689-7C9ECC000000")
LicenseProvider;
#endif
#endif /* __PATLICLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
