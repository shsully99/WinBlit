/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jul 09 13:09:54 2002
 */
/* Compiler settings for C:\Documents and Settings\Sean Sullivan\My Documents\WINBLIT\WinBlitWebBand\src\WinBlitWebBand.idl:
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

#ifndef __WinBlitWebBand_h__
#define __WinBlitWebBand_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IExplorerBand_FWD_DEFINED__
#define __IExplorerBand_FWD_DEFINED__
typedef interface IExplorerBand IExplorerBand;
#endif 	/* __IExplorerBand_FWD_DEFINED__ */


#ifndef __ICommBand_FWD_DEFINED__
#define __ICommBand_FWD_DEFINED__
typedef interface ICommBand ICommBand;
#endif 	/* __ICommBand_FWD_DEFINED__ */


#ifndef __ExplorerBand_FWD_DEFINED__
#define __ExplorerBand_FWD_DEFINED__

#ifdef __cplusplus
typedef class ExplorerBand ExplorerBand;
#else
typedef struct ExplorerBand ExplorerBand;
#endif /* __cplusplus */

#endif 	/* __ExplorerBand_FWD_DEFINED__ */


#ifndef __CommBand_FWD_DEFINED__
#define __CommBand_FWD_DEFINED__

#ifdef __cplusplus
typedef class CommBand CommBand;
#else
typedef struct CommBand CommBand;
#endif /* __cplusplus */

#endif 	/* __CommBand_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IExplorerBand_INTERFACE_DEFINED__
#define __IExplorerBand_INTERFACE_DEFINED__

/* interface IExplorerBand */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IExplorerBand;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("326215A3-58C1-11D5-8601-508750000000")
    IExplorerBand : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IExplorerBandVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IExplorerBand __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IExplorerBand __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IExplorerBand __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IExplorerBand __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IExplorerBand __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IExplorerBand __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IExplorerBand __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IExplorerBandVtbl;

    interface IExplorerBand
    {
        CONST_VTBL struct IExplorerBandVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExplorerBand_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExplorerBand_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExplorerBand_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExplorerBand_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IExplorerBand_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IExplorerBand_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IExplorerBand_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IExplorerBand_INTERFACE_DEFINED__ */


#ifndef __ICommBand_INTERFACE_DEFINED__
#define __ICommBand_INTERFACE_DEFINED__

/* interface ICommBand */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICommBand;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("326215A5-58C1-11D5-8601-508750000000")
    ICommBand : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDocument( 
            IDispatch __RPC_FAR *pDisp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommBandVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICommBand __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICommBand __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICommBand __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICommBand __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICommBand __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICommBand __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICommBand __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDocument )( 
            ICommBand __RPC_FAR * This,
            IDispatch __RPC_FAR *pDisp);
        
        END_INTERFACE
    } ICommBandVtbl;

    interface ICommBand
    {
        CONST_VTBL struct ICommBandVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommBand_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICommBand_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICommBand_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICommBand_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICommBand_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICommBand_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICommBand_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICommBand_SetDocument(This,pDisp)	\
    (This)->lpVtbl -> SetDocument(This,pDisp)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommBand_SetDocument_Proxy( 
    ICommBand __RPC_FAR * This,
    IDispatch __RPC_FAR *pDisp);


void __RPC_STUB ICommBand_SetDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommBand_INTERFACE_DEFINED__ */



#ifndef __WINBLITWEBBANDLib_LIBRARY_DEFINED__
#define __WINBLITWEBBANDLib_LIBRARY_DEFINED__

/* library WINBLITWEBBANDLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WINBLITWEBBANDLib;

EXTERN_C const CLSID CLSID_ExplorerBand;

#ifdef __cplusplus

class DECLSPEC_UUID("326215A4-58C1-11D5-8601-508750000000")
ExplorerBand;
#endif

EXTERN_C const CLSID CLSID_CommBand;

#ifdef __cplusplus

class DECLSPEC_UUID("326215A6-58C1-11D5-8601-508750000000")
CommBand;
#endif
#endif /* __WINBLITWEBBANDLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
