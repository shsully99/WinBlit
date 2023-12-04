/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Feb 27 13:38:00 2002
 */
/* Compiler settings for C:\Documents and Settings\Sean Sullivan\My Documents\WINBLIT\WinBlitReaderManager\src\WinBlitReaderManager.idl:
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

#ifndef __WinBlitReaderManager_h__
#define __WinBlitReaderManager_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IWinBlitData_FWD_DEFINED__
#define __IWinBlitData_FWD_DEFINED__
typedef interface IWinBlitData IWinBlitData;
#endif 	/* __IWinBlitData_FWD_DEFINED__ */


#ifndef __IWinBlitReader_FWD_DEFINED__
#define __IWinBlitReader_FWD_DEFINED__
typedef interface IWinBlitReader IWinBlitReader;
#endif 	/* __IWinBlitReader_FWD_DEFINED__ */


#ifndef __ISetting_FWD_DEFINED__
#define __ISetting_FWD_DEFINED__
typedef interface ISetting ISetting;
#endif 	/* __ISetting_FWD_DEFINED__ */


#ifndef __ISettings_FWD_DEFINED__
#define __ISettings_FWD_DEFINED__
typedef interface ISettings ISettings;
#endif 	/* __ISettings_FWD_DEFINED__ */


#ifndef __IStatistic_FWD_DEFINED__
#define __IStatistic_FWD_DEFINED__
typedef interface IStatistic IStatistic;
#endif 	/* __IStatistic_FWD_DEFINED__ */


#ifndef __IStatistics_FWD_DEFINED__
#define __IStatistics_FWD_DEFINED__
typedef interface IStatistics IStatistics;
#endif 	/* __IStatistics_FWD_DEFINED__ */


#ifndef __IBrowserWrapper_FWD_DEFINED__
#define __IBrowserWrapper_FWD_DEFINED__
typedef interface IBrowserWrapper IBrowserWrapper;
#endif 	/* __IBrowserWrapper_FWD_DEFINED__ */


#ifndef __WinBlitData_FWD_DEFINED__
#define __WinBlitData_FWD_DEFINED__

#ifdef __cplusplus
typedef class WinBlitData WinBlitData;
#else
typedef struct WinBlitData WinBlitData;
#endif /* __cplusplus */

#endif 	/* __WinBlitData_FWD_DEFINED__ */


#ifndef __WinBlitReader_FWD_DEFINED__
#define __WinBlitReader_FWD_DEFINED__

#ifdef __cplusplus
typedef class WinBlitReader WinBlitReader;
#else
typedef struct WinBlitReader WinBlitReader;
#endif /* __cplusplus */

#endif 	/* __WinBlitReader_FWD_DEFINED__ */


#ifndef __Setting_FWD_DEFINED__
#define __Setting_FWD_DEFINED__

#ifdef __cplusplus
typedef class Setting Setting;
#else
typedef struct Setting Setting;
#endif /* __cplusplus */

#endif 	/* __Setting_FWD_DEFINED__ */


#ifndef __Settings_FWD_DEFINED__
#define __Settings_FWD_DEFINED__

#ifdef __cplusplus
typedef class Settings Settings;
#else
typedef struct Settings Settings;
#endif /* __cplusplus */

#endif 	/* __Settings_FWD_DEFINED__ */


#ifndef __Statistic_FWD_DEFINED__
#define __Statistic_FWD_DEFINED__

#ifdef __cplusplus
typedef class Statistic Statistic;
#else
typedef struct Statistic Statistic;
#endif /* __cplusplus */

#endif 	/* __Statistic_FWD_DEFINED__ */


#ifndef __Statistics_FWD_DEFINED__
#define __Statistics_FWD_DEFINED__

#ifdef __cplusplus
typedef class Statistics Statistics;
#else
typedef struct Statistics Statistics;
#endif /* __cplusplus */

#endif 	/* __Statistics_FWD_DEFINED__ */


#ifndef __BrowserWrapper_FWD_DEFINED__
#define __BrowserWrapper_FWD_DEFINED__

#ifdef __cplusplus
typedef class BrowserWrapper BrowserWrapper;
#else
typedef struct BrowserWrapper BrowserWrapper;
#endif /* __cplusplus */

#endif 	/* __BrowserWrapper_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IWinBlitData_INTERFACE_DEFINED__
#define __IWinBlitData_INTERFACE_DEFINED__

/* interface IWinBlitData */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWinBlitData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0E9E0E5F-190E-11D5-859E-6CA415000000")
    IWinBlitData : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialise( 
            /* [in] */ long lDataSourceType,
            /* [in] */ VARIANT varDataSourceURL,
            /* [in] */ VARIANT varConfig) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetData( 
            /* [in] */ long lDataOffset,
            /* [out][in] */ BSTR __RPC_FAR *pbstrData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindString( 
            /* [in] */ BSTR bstrSearchString,
            /* [in] */ long lSearchOffset,
            /* [in] */ long lSearchDirection,
            /* [retval][out] */ long __RPC_FAR *lStringOffset) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Uninitialise( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetParaAtPercent( 
            /* [in] */ long lPercent,
            /* [out][in] */ long __RPC_FAR *lPara,
            BOOL bRound) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPercentAtPara( 
            /* [out][in] */ long __RPC_FAR *lPercent,
            /* [in] */ long lPara) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWinBlitDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWinBlitData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWinBlitData __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWinBlitData __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWinBlitData __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWinBlitData __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWinBlitData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWinBlitData __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialise )( 
            IWinBlitData __RPC_FAR * This,
            /* [in] */ long lDataSourceType,
            /* [in] */ VARIANT varDataSourceURL,
            /* [in] */ VARIANT varConfig);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetData )( 
            IWinBlitData __RPC_FAR * This,
            /* [in] */ long lDataOffset,
            /* [out][in] */ BSTR __RPC_FAR *pbstrData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindString )( 
            IWinBlitData __RPC_FAR * This,
            /* [in] */ BSTR bstrSearchString,
            /* [in] */ long lSearchOffset,
            /* [in] */ long lSearchDirection,
            /* [retval][out] */ long __RPC_FAR *lStringOffset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Uninitialise )( 
            IWinBlitData __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParaAtPercent )( 
            IWinBlitData __RPC_FAR * This,
            /* [in] */ long lPercent,
            /* [out][in] */ long __RPC_FAR *lPara,
            BOOL bRound);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPercentAtPara )( 
            IWinBlitData __RPC_FAR * This,
            /* [out][in] */ long __RPC_FAR *lPercent,
            /* [in] */ long lPara);
        
        END_INTERFACE
    } IWinBlitDataVtbl;

    interface IWinBlitData
    {
        CONST_VTBL struct IWinBlitDataVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWinBlitData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWinBlitData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWinBlitData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWinBlitData_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWinBlitData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWinBlitData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWinBlitData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWinBlitData_Initialise(This,lDataSourceType,varDataSourceURL,varConfig)	\
    (This)->lpVtbl -> Initialise(This,lDataSourceType,varDataSourceURL,varConfig)

#define IWinBlitData_GetData(This,lDataOffset,pbstrData)	\
    (This)->lpVtbl -> GetData(This,lDataOffset,pbstrData)

#define IWinBlitData_FindString(This,bstrSearchString,lSearchOffset,lSearchDirection,lStringOffset)	\
    (This)->lpVtbl -> FindString(This,bstrSearchString,lSearchOffset,lSearchDirection,lStringOffset)

#define IWinBlitData_Uninitialise(This)	\
    (This)->lpVtbl -> Uninitialise(This)

#define IWinBlitData_GetParaAtPercent(This,lPercent,lPara,bRound)	\
    (This)->lpVtbl -> GetParaAtPercent(This,lPercent,lPara,bRound)

#define IWinBlitData_GetPercentAtPara(This,lPercent,lPara)	\
    (This)->lpVtbl -> GetPercentAtPara(This,lPercent,lPara)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinBlitData_Initialise_Proxy( 
    IWinBlitData __RPC_FAR * This,
    /* [in] */ long lDataSourceType,
    /* [in] */ VARIANT varDataSourceURL,
    /* [in] */ VARIANT varConfig);


void __RPC_STUB IWinBlitData_Initialise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinBlitData_GetData_Proxy( 
    IWinBlitData __RPC_FAR * This,
    /* [in] */ long lDataOffset,
    /* [out][in] */ BSTR __RPC_FAR *pbstrData);


void __RPC_STUB IWinBlitData_GetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinBlitData_FindString_Proxy( 
    IWinBlitData __RPC_FAR * This,
    /* [in] */ BSTR bstrSearchString,
    /* [in] */ long lSearchOffset,
    /* [in] */ long lSearchDirection,
    /* [retval][out] */ long __RPC_FAR *lStringOffset);


void __RPC_STUB IWinBlitData_FindString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinBlitData_Uninitialise_Proxy( 
    IWinBlitData __RPC_FAR * This);


void __RPC_STUB IWinBlitData_Uninitialise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinBlitData_GetParaAtPercent_Proxy( 
    IWinBlitData __RPC_FAR * This,
    /* [in] */ long lPercent,
    /* [out][in] */ long __RPC_FAR *lPara,
    BOOL bRound);


void __RPC_STUB IWinBlitData_GetParaAtPercent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinBlitData_GetPercentAtPara_Proxy( 
    IWinBlitData __RPC_FAR * This,
    /* [out][in] */ long __RPC_FAR *lPercent,
    /* [in] */ long lPara);


void __RPC_STUB IWinBlitData_GetPercentAtPara_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWinBlitData_INTERFACE_DEFINED__ */


#ifndef __IWinBlitReader_INTERFACE_DEFINED__
#define __IWinBlitReader_INTERFACE_DEFINED__

/* interface IWinBlitReader */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWinBlitReader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A1777A90-27A6-11d5-85B6-269F99000000")
    IWinBlitReader : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadData( 
            /* [in] */ long lDataSourceType,
            /* [in] */ VARIANT varDataSource) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnloadData( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Display( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Start( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowHelp( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Register( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowAbout( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWinBlitReaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWinBlitReader __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWinBlitReader __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWinBlitReader __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWinBlitReader __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWinBlitReader __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWinBlitReader __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWinBlitReader __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadData )( 
            IWinBlitReader __RPC_FAR * This,
            /* [in] */ long lDataSourceType,
            /* [in] */ VARIANT varDataSource);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnloadData )( 
            IWinBlitReader __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Display )( 
            IWinBlitReader __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Start )( 
            IWinBlitReader __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IWinBlitReader __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowHelp )( 
            IWinBlitReader __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Register )( 
            IWinBlitReader __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowAbout )( 
            IWinBlitReader __RPC_FAR * This);
        
        END_INTERFACE
    } IWinBlitReaderVtbl;

    interface IWinBlitReader
    {
        CONST_VTBL struct IWinBlitReaderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWinBlitReader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWinBlitReader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWinBlitReader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWinBlitReader_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWinBlitReader_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWinBlitReader_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWinBlitReader_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWinBlitReader_LoadData(This,lDataSourceType,varDataSource)	\
    (This)->lpVtbl -> LoadData(This,lDataSourceType,varDataSource)

#define IWinBlitReader_UnloadData(This)	\
    (This)->lpVtbl -> UnloadData(This)

#define IWinBlitReader_Display(This)	\
    (This)->lpVtbl -> Display(This)

#define IWinBlitReader_Start(This)	\
    (This)->lpVtbl -> Start(This)

#define IWinBlitReader_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IWinBlitReader_ShowHelp(This)	\
    (This)->lpVtbl -> ShowHelp(This)

#define IWinBlitReader_Register(This)	\
    (This)->lpVtbl -> Register(This)

#define IWinBlitReader_ShowAbout(This)	\
    (This)->lpVtbl -> ShowAbout(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinBlitReader_LoadData_Proxy( 
    IWinBlitReader __RPC_FAR * This,
    /* [in] */ long lDataSourceType,
    /* [in] */ VARIANT varDataSource);


void __RPC_STUB IWinBlitReader_LoadData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinBlitReader_UnloadData_Proxy( 
    IWinBlitReader __RPC_FAR * This);


void __RPC_STUB IWinBlitReader_UnloadData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinBlitReader_Display_Proxy( 
    IWinBlitReader __RPC_FAR * This);


void __RPC_STUB IWinBlitReader_Display_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinBlitReader_Start_Proxy( 
    IWinBlitReader __RPC_FAR * This);


void __RPC_STUB IWinBlitReader_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinBlitReader_Stop_Proxy( 
    IWinBlitReader __RPC_FAR * This);


void __RPC_STUB IWinBlitReader_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinBlitReader_ShowHelp_Proxy( 
    IWinBlitReader __RPC_FAR * This);


void __RPC_STUB IWinBlitReader_ShowHelp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinBlitReader_Register_Proxy( 
    IWinBlitReader __RPC_FAR * This);


void __RPC_STUB IWinBlitReader_Register_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinBlitReader_ShowAbout_Proxy( 
    IWinBlitReader __RPC_FAR * This);


void __RPC_STUB IWinBlitReader_ShowAbout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWinBlitReader_INTERFACE_DEFINED__ */


#ifndef __ISetting_INTERFACE_DEFINED__
#define __ISetting_INTERFACE_DEFINED__

/* interface ISetting */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISetting;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A1777A91-27A6-11d5-85B6-269F99000000")
    ISetting : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Rule( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Rule( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Period( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Period( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISettingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISetting __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISetting __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISetting __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISetting __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISetting __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISetting __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISetting __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Rule )( 
            ISetting __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Rule )( 
            ISetting __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Period )( 
            ISetting __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Period )( 
            ISetting __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            ISetting __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            ISetting __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ISetting __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            ISetting __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ISettingVtbl;

    interface ISetting
    {
        CONST_VTBL struct ISettingVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISetting_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISetting_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISetting_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISetting_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISetting_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISetting_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISetting_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISetting_get_Rule(This,pVal)	\
    (This)->lpVtbl -> get_Rule(This,pVal)

#define ISetting_put_Rule(This,newVal)	\
    (This)->lpVtbl -> put_Rule(This,newVal)

#define ISetting_get_Period(This,pVal)	\
    (This)->lpVtbl -> get_Period(This,pVal)

#define ISetting_put_Period(This,newVal)	\
    (This)->lpVtbl -> put_Period(This,newVal)

#define ISetting_get_Value(This,pVal)	\
    (This)->lpVtbl -> get_Value(This,pVal)

#define ISetting_put_Value(This,newVal)	\
    (This)->lpVtbl -> put_Value(This,newVal)

#define ISetting_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define ISetting_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISetting_get_Rule_Proxy( 
    ISetting __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISetting_get_Rule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISetting_put_Rule_Proxy( 
    ISetting __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ISetting_put_Rule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISetting_get_Period_Proxy( 
    ISetting __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISetting_get_Period_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISetting_put_Period_Proxy( 
    ISetting __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ISetting_put_Period_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISetting_get_Value_Proxy( 
    ISetting __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISetting_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISetting_put_Value_Proxy( 
    ISetting __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISetting_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISetting_get_Name_Proxy( 
    ISetting __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISetting_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISetting_put_Name_Proxy( 
    ISetting __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISetting_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISetting_INTERFACE_DEFINED__ */


#ifndef __ISettings_INTERFACE_DEFINED__
#define __ISettings_INTERFACE_DEFINED__

/* interface ISettings */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A1777A92-27A6-11d5-85B6-269F99000000")
    ISettings : public IDispatch
    {
    public:
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR bstrKey,
            /* [in] */ long lIndex,
            /* [in] */ long lRule,
            /* [in] */ BSTR bstrValue,
            /* [in] */ long lPeriod) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Index) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE get_ItemCustom( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ISetting __RPC_FAR *__RPC_FAR *ppSetting) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISettings __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISettings __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISettings __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISettings __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISettings __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ISettings __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ISettings __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ISettings __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ISettings __RPC_FAR * This,
            /* [in] */ BSTR bstrKey,
            /* [in] */ long lIndex,
            /* [in] */ long lRule,
            /* [in] */ BSTR bstrValue,
            /* [in] */ long lPeriod);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ISettings __RPC_FAR * This,
            /* [in] */ VARIANT Index);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            ISettings __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ItemCustom )( 
            ISettings __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ISetting __RPC_FAR *__RPC_FAR *ppSetting);
        
        END_INTERFACE
    } ISettingsVtbl;

    interface ISettings
    {
        CONST_VTBL struct ISettingsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISettings_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISettings_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISettings_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISettings_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISettings_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define ISettings_get_Item(This,Index,pVal)	\
    (This)->lpVtbl -> get_Item(This,Index,pVal)

#define ISettings_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ISettings_Add(This,bstrKey,lIndex,lRule,bstrValue,lPeriod)	\
    (This)->lpVtbl -> Add(This,bstrKey,lIndex,lRule,bstrValue,lPeriod)

#define ISettings_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#define ISettings_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define ISettings_get_ItemCustom(This,Index,ppSetting)	\
    (This)->lpVtbl -> get_ItemCustom(This,Index,ppSetting)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE ISettings_get__NewEnum_Proxy( 
    ISettings __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);


void __RPC_STUB ISettings_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ISettings_get_Item_Proxy( 
    ISettings __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB ISettings_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ISettings_get_Count_Proxy( 
    ISettings __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISettings_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ISettings_Add_Proxy( 
    ISettings __RPC_FAR * This,
    /* [in] */ BSTR bstrKey,
    /* [in] */ long lIndex,
    /* [in] */ long lRule,
    /* [in] */ BSTR bstrValue,
    /* [in] */ long lPeriod);


void __RPC_STUB ISettings_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ISettings_Remove_Proxy( 
    ISettings __RPC_FAR * This,
    /* [in] */ VARIANT Index);


void __RPC_STUB ISettings_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ISettings_Clear_Proxy( 
    ISettings __RPC_FAR * This);


void __RPC_STUB ISettings_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISettings_get_ItemCustom_Proxy( 
    ISettings __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ ISetting __RPC_FAR *__RPC_FAR *ppSetting);


void __RPC_STUB ISettings_get_ItemCustom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISettings_INTERFACE_DEFINED__ */


#ifndef __IStatistic_INTERFACE_DEFINED__
#define __IStatistic_INTERFACE_DEFINED__

/* interface IStatistic */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IStatistic;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8DE52EB1-28C9-11D5-85B9-A46552000000")
    IStatistic : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Quantity( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Quantity( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStatisticVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStatistic __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStatistic __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStatistic __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IStatistic __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IStatistic __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IStatistic __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IStatistic __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IStatistic __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Type )( 
            IStatistic __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Quantity )( 
            IStatistic __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Quantity )( 
            IStatistic __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IStatistic __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IStatistic __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IStatisticVtbl;

    interface IStatistic
    {
        CONST_VTBL struct IStatisticVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStatistic_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStatistic_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStatistic_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStatistic_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IStatistic_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IStatistic_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IStatistic_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IStatistic_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IStatistic_put_Type(This,newVal)	\
    (This)->lpVtbl -> put_Type(This,newVal)

#define IStatistic_get_Quantity(This,pVal)	\
    (This)->lpVtbl -> get_Quantity(This,pVal)

#define IStatistic_put_Quantity(This,newVal)	\
    (This)->lpVtbl -> put_Quantity(This,newVal)

#define IStatistic_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IStatistic_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IStatistic_get_Type_Proxy( 
    IStatistic __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IStatistic_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IStatistic_put_Type_Proxy( 
    IStatistic __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IStatistic_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IStatistic_get_Quantity_Proxy( 
    IStatistic __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IStatistic_get_Quantity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IStatistic_put_Quantity_Proxy( 
    IStatistic __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IStatistic_put_Quantity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IStatistic_get_Name_Proxy( 
    IStatistic __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IStatistic_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IStatistic_put_Name_Proxy( 
    IStatistic __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IStatistic_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStatistic_INTERFACE_DEFINED__ */


#ifndef __IStatistics_INTERFACE_DEFINED__
#define __IStatistics_INTERFACE_DEFINED__

/* interface IStatistics */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IStatistics;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8DE52EB5-28C9-11D5-85B9-A46552000000")
    IStatistics : public IDispatch
    {
    public:
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE get_ItemCustom( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IStatistic __RPC_FAR *__RPC_FAR *ppStatistic) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStatisticsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStatistics __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStatistics __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStatistics __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IStatistics __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IStatistics __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IStatistics __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IStatistics __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IStatistics __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IStatistics __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IStatistics __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IStatistics __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ItemCustom )( 
            IStatistics __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IStatistic __RPC_FAR *__RPC_FAR *ppStatistic);
        
        END_INTERFACE
    } IStatisticsVtbl;

    interface IStatistics
    {
        CONST_VTBL struct IStatisticsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStatistics_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStatistics_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStatistics_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStatistics_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IStatistics_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IStatistics_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IStatistics_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IStatistics_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IStatistics_get_Item(This,Index,pVal)	\
    (This)->lpVtbl -> get_Item(This,Index,pVal)

#define IStatistics_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IStatistics_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IStatistics_get_ItemCustom(This,Index,ppStatistic)	\
    (This)->lpVtbl -> get_ItemCustom(This,Index,ppStatistic)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IStatistics_get__NewEnum_Proxy( 
    IStatistics __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);


void __RPC_STUB IStatistics_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStatistics_get_Item_Proxy( 
    IStatistics __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IStatistics_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IStatistics_get_Count_Proxy( 
    IStatistics __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IStatistics_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IStatistics_Reset_Proxy( 
    IStatistics __RPC_FAR * This);


void __RPC_STUB IStatistics_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStatistics_get_ItemCustom_Proxy( 
    IStatistics __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ IStatistic __RPC_FAR *__RPC_FAR *ppStatistic);


void __RPC_STUB IStatistics_get_ItemCustom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStatistics_INTERFACE_DEFINED__ */


#ifndef __IBrowserWrapper_INTERFACE_DEFINED__
#define __IBrowserWrapper_INTERFACE_DEFINED__

/* interface IBrowserWrapper */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IBrowserWrapper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("27506A61-712F-11D5-862D-C05E6D000000")
    IBrowserWrapper : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Run( 
            /* [in] */ BSTR bstrDataSource) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDoc( 
            /* [out] */ VARIANT_BOOL __RPC_FAR *bLoaded,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pDispatch) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBrowserWrapperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBrowserWrapper __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBrowserWrapper __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBrowserWrapper __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IBrowserWrapper __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IBrowserWrapper __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IBrowserWrapper __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IBrowserWrapper __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            IBrowserWrapper __RPC_FAR * This,
            /* [in] */ BSTR bstrDataSource);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDoc )( 
            IBrowserWrapper __RPC_FAR * This,
            /* [out] */ VARIANT_BOOL __RPC_FAR *bLoaded,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pDispatch);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IBrowserWrapper __RPC_FAR * This);
        
        END_INTERFACE
    } IBrowserWrapperVtbl;

    interface IBrowserWrapper
    {
        CONST_VTBL struct IBrowserWrapperVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBrowserWrapper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBrowserWrapper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBrowserWrapper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBrowserWrapper_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBrowserWrapper_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBrowserWrapper_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBrowserWrapper_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IBrowserWrapper_Run(This,bstrDataSource)	\
    (This)->lpVtbl -> Run(This,bstrDataSource)

#define IBrowserWrapper_GetDoc(This,bLoaded,pDispatch)	\
    (This)->lpVtbl -> GetDoc(This,bLoaded,pDispatch)

#define IBrowserWrapper_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBrowserWrapper_Run_Proxy( 
    IBrowserWrapper __RPC_FAR * This,
    /* [in] */ BSTR bstrDataSource);


void __RPC_STUB IBrowserWrapper_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBrowserWrapper_GetDoc_Proxy( 
    IBrowserWrapper __RPC_FAR * This,
    /* [out] */ VARIANT_BOOL __RPC_FAR *bLoaded,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pDispatch);


void __RPC_STUB IBrowserWrapper_GetDoc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBrowserWrapper_Stop_Proxy( 
    IBrowserWrapper __RPC_FAR * This);


void __RPC_STUB IBrowserWrapper_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBrowserWrapper_INTERFACE_DEFINED__ */



#ifndef __WINBLITREADERMANAGERLib_LIBRARY_DEFINED__
#define __WINBLITREADERMANAGERLib_LIBRARY_DEFINED__

/* library WINBLITREADERMANAGERLib */
/* [helpstring][version][uuid] */ 

typedef 
enum CursorConfiguration
    {	cDisplayScreenText	= 1,
	cDisplayCursorText	= 2,
	cStaticCursor	= 4,
	cSequentialCursor	= 8,
	cRandomCursor	= 16,
	cSlowHandCursor	= 32,
	cUnused1	= 64,
	cLineDivisions	= 128,
	cWordDivisions	= 256,
	cCharDivisions	= 512,
	cEqualiseWordDivisions	= 1024,
	cEqualiseLineDivisions	= 2048,
	cFillCursorArea	= 4096,
	cLeaveCursorHighlighted	= 8192,
	cUnused2	= 16384
    }	cCursorConfigurations;

typedef 
enum StatisticType
    {	cWordCount	= 1,
	cElapsedTime	= 2,
	cReadTime	= 3
    }	cStatisticTypes;

typedef 
enum SettingType
    {	cPauseAt	= 1,
	cDelayAt	= 2,
	cHTMLTags	= 3
    }	cSettingTypes;


EXTERN_C const IID LIBID_WINBLITREADERMANAGERLib;

EXTERN_C const CLSID CLSID_WinBlitData;

#ifdef __cplusplus

class DECLSPEC_UUID("0E9E0E60-190E-11D5-859E-6CA415000000")
WinBlitData;
#endif

EXTERN_C const CLSID CLSID_WinBlitReader;

#ifdef __cplusplus

class DECLSPEC_UUID("70AA5212-27A9-11d5-85B6-269F99000000")
WinBlitReader;
#endif

EXTERN_C const CLSID CLSID_Setting;

#ifdef __cplusplus

class DECLSPEC_UUID("A1777A97-27A6-11d5-85B6-269F99000000")
Setting;
#endif

EXTERN_C const CLSID CLSID_Settings;

#ifdef __cplusplus

class DECLSPEC_UUID("A1777A98-27A6-11d5-85B6-269F99000000")
Settings;
#endif

EXTERN_C const CLSID CLSID_Statistic;

#ifdef __cplusplus

class DECLSPEC_UUID("8DE52EB2-28C9-11D5-85B9-A46552000000")
Statistic;
#endif

EXTERN_C const CLSID CLSID_Statistics;

#ifdef __cplusplus

class DECLSPEC_UUID("8DE52EB6-28C9-11D5-85B9-A46552000000")
Statistics;
#endif

EXTERN_C const CLSID CLSID_BrowserWrapper;

#ifdef __cplusplus

class DECLSPEC_UUID("27506A62-712F-11D5-862D-C05E6D000000")
BrowserWrapper;
#endif
#endif /* __WINBLITREADERMANAGERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
