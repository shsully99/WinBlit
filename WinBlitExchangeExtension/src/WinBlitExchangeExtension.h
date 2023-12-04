/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Feb 22 09:53:30 2002
 */
/* Compiler settings for C:\Documents and Settings\Sean Sullivan\My Documents\WINBLIT\WinBlitExchangeExtension\src\WinBlitExchangeExtension.idl:
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

#ifndef __WinBlitExchangeExtension_h__
#define __WinBlitExchangeExtension_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IExchangeClient_FWD_DEFINED__
#define __IExchangeClient_FWD_DEFINED__
typedef interface IExchangeClient IExchangeClient;
#endif 	/* __IExchangeClient_FWD_DEFINED__ */


#ifndef __ExchangeClient_FWD_DEFINED__
#define __ExchangeClient_FWD_DEFINED__

#ifdef __cplusplus
typedef class ExchangeClient ExchangeClient;
#else
typedef struct ExchangeClient ExchangeClient;
#endif /* __cplusplus */

#endif 	/* __ExchangeClient_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IExchangeClient_INTERFACE_DEFINED__
#define __IExchangeClient_INTERFACE_DEFINED__

/* interface IExchangeClient */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IExchangeClient;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("53D15913-7F52-11D5-8658-2CE87E000000")
    IExchangeClient : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IExchangeClientVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IExchangeClient __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IExchangeClient __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IExchangeClient __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IExchangeClient __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IExchangeClient __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IExchangeClient __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IExchangeClient __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IExchangeClientVtbl;

    interface IExchangeClient
    {
        CONST_VTBL struct IExchangeClientVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExchangeClient_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExchangeClient_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExchangeClient_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExchangeClient_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IExchangeClient_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IExchangeClient_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IExchangeClient_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IExchangeClient_INTERFACE_DEFINED__ */



#ifndef __WINBLITEXCHANGEEXTENSIONLib_LIBRARY_DEFINED__
#define __WINBLITEXCHANGEEXTENSIONLib_LIBRARY_DEFINED__

/* library WINBLITEXCHANGEEXTENSIONLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WINBLITEXCHANGEEXTENSIONLib;

EXTERN_C const CLSID CLSID_ExchangeClient;

#ifdef __cplusplus

class DECLSPEC_UUID("53D15914-7F52-11D5-8658-2CE87E000000")
ExchangeClient;
#endif
#endif /* __WINBLITEXCHANGEEXTENSIONLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
