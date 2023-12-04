/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Feb 28 09:34:46 2002
 */
/* Compiler settings for C:\Documents and Settings\Sean Sullivan\My Documents\WINBLIT\WinBlitScript\WinBlitScript.idl:
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

#ifndef __WinBlitScript_h__
#define __WinBlitScript_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IBlitScript_FWD_DEFINED__
#define __IBlitScript_FWD_DEFINED__
typedef interface IBlitScript IBlitScript;
#endif 	/* __IBlitScript_FWD_DEFINED__ */


#ifndef __BlitScript_FWD_DEFINED__
#define __BlitScript_FWD_DEFINED__

#ifdef __cplusplus
typedef class BlitScript BlitScript;
#else
typedef struct BlitScript BlitScript;
#endif /* __cplusplus */

#endif 	/* __BlitScript_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IBlitScript_INTERFACE_DEFINED__
#define __IBlitScript_INTERFACE_DEFINED__

/* interface IBlitScript */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IBlitScript;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B43CBC08-742A-4596-9C5F-C6B412F0E52C")
    IBlitScript : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadData( 
            /* [in] */ long lDataSourceType,
            /* [in] */ VARIANT varDataSource) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnloadData( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Display( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBlitScriptVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBlitScript __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBlitScript __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBlitScript __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IBlitScript __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IBlitScript __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IBlitScript __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IBlitScript __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadData )( 
            IBlitScript __RPC_FAR * This,
            /* [in] */ long lDataSourceType,
            /* [in] */ VARIANT varDataSource);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnloadData )( 
            IBlitScript __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Display )( 
            IBlitScript __RPC_FAR * This);
        
        END_INTERFACE
    } IBlitScriptVtbl;

    interface IBlitScript
    {
        CONST_VTBL struct IBlitScriptVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBlitScript_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBlitScript_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBlitScript_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBlitScript_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBlitScript_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBlitScript_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBlitScript_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IBlitScript_LoadData(This,lDataSourceType,varDataSource)	\
    (This)->lpVtbl -> LoadData(This,lDataSourceType,varDataSource)

#define IBlitScript_UnloadData(This)	\
    (This)->lpVtbl -> UnloadData(This)

#define IBlitScript_Display(This)	\
    (This)->lpVtbl -> Display(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBlitScript_LoadData_Proxy( 
    IBlitScript __RPC_FAR * This,
    /* [in] */ long lDataSourceType,
    /* [in] */ VARIANT varDataSource);


void __RPC_STUB IBlitScript_LoadData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBlitScript_UnloadData_Proxy( 
    IBlitScript __RPC_FAR * This);


void __RPC_STUB IBlitScript_UnloadData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBlitScript_Display_Proxy( 
    IBlitScript __RPC_FAR * This);


void __RPC_STUB IBlitScript_Display_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBlitScript_INTERFACE_DEFINED__ */



#ifndef __WINBLITSCRIPTLib_LIBRARY_DEFINED__
#define __WINBLITSCRIPTLib_LIBRARY_DEFINED__

/* library WINBLITSCRIPTLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WINBLITSCRIPTLib;

EXTERN_C const CLSID CLSID_BlitScript;

#ifdef __cplusplus

class DECLSPEC_UUID("D8B3C8E3-F2F4-44D0-A4B4-C8E098813569")
BlitScript;
#endif
#endif /* __WINBLITSCRIPTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
