/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Feb 01 12:56:02 2002
 */
/* Compiler settings for C:\Documents and Settings\Sean Sullivan\My Documents\WinBlit\BlitLog\src\BlitLog.idl:
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

#ifndef __BlitLog_h__
#define __BlitLog_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ILogger_FWD_DEFINED__
#define __ILogger_FWD_DEFINED__
typedef interface ILogger ILogger;
#endif 	/* __ILogger_FWD_DEFINED__ */


#ifndef __Logger_FWD_DEFINED__
#define __Logger_FWD_DEFINED__

#ifdef __cplusplus
typedef class Logger Logger;
#else
typedef struct Logger Logger;
#endif /* __cplusplus */

#endif 	/* __Logger_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ILogger_INTERFACE_DEFINED__
#define __ILogger_INTERFACE_DEFINED__

/* interface ILogger */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILogger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("28B8F4C4-46C4-4F12-A104-302628610CFA")
    ILogger : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Initialise( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnInitialise( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DisplayText( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Log( 
            long lSeverity,
            long lThreadID,
            BSTR bstrText) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Level( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Level( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Path( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILoggerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILogger __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILogger __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILogger __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialise )( 
            ILogger __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnInitialise )( 
            ILogger __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisplayText )( 
            ILogger __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Log )( 
            ILogger __RPC_FAR * This,
            long lSeverity,
            long lThreadID,
            BSTR bstrText);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Level )( 
            ILogger __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Level )( 
            ILogger __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Path )( 
            ILogger __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Path )( 
            ILogger __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ILoggerVtbl;

    interface ILogger
    {
        CONST_VTBL struct ILoggerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILogger_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILogger_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILogger_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILogger_Initialise(This)	\
    (This)->lpVtbl -> Initialise(This)

#define ILogger_UnInitialise(This)	\
    (This)->lpVtbl -> UnInitialise(This)

#define ILogger_DisplayText(This)	\
    (This)->lpVtbl -> DisplayText(This)

#define ILogger_Log(This,lSeverity,lThreadID,bstrText)	\
    (This)->lpVtbl -> Log(This,lSeverity,lThreadID,bstrText)

#define ILogger_get_Level(This,pVal)	\
    (This)->lpVtbl -> get_Level(This,pVal)

#define ILogger_put_Level(This,newVal)	\
    (This)->lpVtbl -> put_Level(This,newVal)

#define ILogger_get_Path(This,pVal)	\
    (This)->lpVtbl -> get_Path(This,pVal)

#define ILogger_put_Path(This,newVal)	\
    (This)->lpVtbl -> put_Path(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILogger_Initialise_Proxy( 
    ILogger __RPC_FAR * This);


void __RPC_STUB ILogger_Initialise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILogger_UnInitialise_Proxy( 
    ILogger __RPC_FAR * This);


void __RPC_STUB ILogger_UnInitialise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILogger_DisplayText_Proxy( 
    ILogger __RPC_FAR * This);


void __RPC_STUB ILogger_DisplayText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILogger_Log_Proxy( 
    ILogger __RPC_FAR * This,
    long lSeverity,
    long lThreadID,
    BSTR bstrText);


void __RPC_STUB ILogger_Log_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILogger_get_Level_Proxy( 
    ILogger __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILogger_get_Level_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ILogger_put_Level_Proxy( 
    ILogger __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ILogger_put_Level_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ILogger_get_Path_Proxy( 
    ILogger __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ILogger_get_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ILogger_put_Path_Proxy( 
    ILogger __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ILogger_put_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILogger_INTERFACE_DEFINED__ */



#ifndef __BLITLOGLib_LIBRARY_DEFINED__
#define __BLITLOGLib_LIBRARY_DEFINED__

/* library BLITLOGLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_BLITLOGLib;

EXTERN_C const CLSID CLSID_Logger;

#ifdef __cplusplus

class DECLSPEC_UUID("AE01A429-E4C6-4803-8B09-08BA375ECBB9")
Logger;
#endif
#endif /* __BLITLOGLib_LIBRARY_DEFINED__ */

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
