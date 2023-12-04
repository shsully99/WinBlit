

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 03:14:07 2038
 */
/* Compiler settings for ATLLogApp.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ATLLogApp_h__
#define __ATLLogApp_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICoLogger_FWD_DEFINED__
#define __ICoLogger_FWD_DEFINED__
typedef interface ICoLogger ICoLogger;

#endif 	/* __ICoLogger_FWD_DEFINED__ */


#ifndef __CoLogger_FWD_DEFINED__
#define __CoLogger_FWD_DEFINED__

#ifdef __cplusplus
typedef class CoLogger CoLogger;
#else
typedef struct CoLogger CoLogger;
#endif /* __cplusplus */

#endif 	/* __CoLogger_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICoLogger_INTERFACE_DEFINED__
#define __ICoLogger_INTERFACE_DEFINED__

/* interface ICoLogger */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICoLogger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("28B8F4C4-46C4-4F12-A104-302628610CFA")
    ICoLogger : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DisplayText( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Log( 
            long lSeverity,
            long lThreadID,
            BSTR bstrText) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnInitialize( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Level( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Level( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Path( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICoLoggerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICoLogger * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICoLogger * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICoLogger * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            ICoLogger * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DisplayText )( 
            ICoLogger * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Log )( 
            ICoLogger * This,
            long lSeverity,
            long lThreadID,
            BSTR bstrText);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UnInitialize )( 
            ICoLogger * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Level )( 
            ICoLogger * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Level )( 
            ICoLogger * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Path )( 
            ICoLogger * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Path )( 
            ICoLogger * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ICoLoggerVtbl;

    interface ICoLogger
    {
        CONST_VTBL struct ICoLoggerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICoLogger_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICoLogger_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICoLogger_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICoLogger_Initialize(This)	\
    ( (This)->lpVtbl -> Initialize(This) ) 

#define ICoLogger_DisplayText(This)	\
    ( (This)->lpVtbl -> DisplayText(This) ) 

#define ICoLogger_Log(This,lSeverity,lThreadID,bstrText)	\
    ( (This)->lpVtbl -> Log(This,lSeverity,lThreadID,bstrText) ) 

#define ICoLogger_UnInitialize(This)	\
    ( (This)->lpVtbl -> UnInitialize(This) ) 

#define ICoLogger_get_Level(This,pVal)	\
    ( (This)->lpVtbl -> get_Level(This,pVal) ) 

#define ICoLogger_put_Level(This,newVal)	\
    ( (This)->lpVtbl -> put_Level(This,newVal) ) 

#define ICoLogger_get_Path(This,pVal)	\
    ( (This)->lpVtbl -> get_Path(This,pVal) ) 

#define ICoLogger_put_Path(This,newVal)	\
    ( (This)->lpVtbl -> put_Path(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICoLogger_INTERFACE_DEFINED__ */



#ifndef __ATLLOGAPPLib_LIBRARY_DEFINED__
#define __ATLLOGAPPLib_LIBRARY_DEFINED__

/* library ATLLOGAPPLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ATLLOGAPPLib;

EXTERN_C const CLSID CLSID_CoLogger;

#ifdef __cplusplus

class DECLSPEC_UUID("AE01A429-E4C6-4803-8B09-08BA375ECBB9")
CoLogger;
#endif
#endif /* __ATLLOGAPPLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


