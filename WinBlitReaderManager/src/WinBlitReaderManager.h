

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 03:14:07 2038
 */
/* Compiler settings for WinBlitReaderManager.idl:
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

#ifndef __WinBlitReaderManager_h__
#define __WinBlitReaderManager_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
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

#ifdef __cplusplus
extern "C"{
#endif 


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
            /* [out][in] */ BSTR *pbstrData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindString( 
            /* [in] */ BSTR bstrSearchString,
            /* [in] */ long lSearchOffset,
            /* [in] */ long lSearchDirection,
            /* [retval][out] */ long *lStringOffset) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Uninitialise( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetParaAtPercent( 
            /* [in] */ long lPercent,
            /* [out][in] */ long *lPara,
            BOOL bRound) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPercentAtPara( 
            /* [out][in] */ long *lPercent,
            /* [in] */ long lPara) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWinBlitDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWinBlitData * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWinBlitData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWinBlitData * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWinBlitData * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWinBlitData * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWinBlitData * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWinBlitData * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Initialise )( 
            IWinBlitData * This,
            /* [in] */ long lDataSourceType,
            /* [in] */ VARIANT varDataSourceURL,
            /* [in] */ VARIANT varConfig);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetData )( 
            IWinBlitData * This,
            /* [in] */ long lDataOffset,
            /* [out][in] */ BSTR *pbstrData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindString )( 
            IWinBlitData * This,
            /* [in] */ BSTR bstrSearchString,
            /* [in] */ long lSearchOffset,
            /* [in] */ long lSearchDirection,
            /* [retval][out] */ long *lStringOffset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Uninitialise )( 
            IWinBlitData * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetParaAtPercent )( 
            IWinBlitData * This,
            /* [in] */ long lPercent,
            /* [out][in] */ long *lPara,
            BOOL bRound);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPercentAtPara )( 
            IWinBlitData * This,
            /* [out][in] */ long *lPercent,
            /* [in] */ long lPara);
        
        END_INTERFACE
    } IWinBlitDataVtbl;

    interface IWinBlitData
    {
        CONST_VTBL struct IWinBlitDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWinBlitData_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWinBlitData_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWinBlitData_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWinBlitData_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWinBlitData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWinBlitData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWinBlitData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWinBlitData_Initialise(This,lDataSourceType,varDataSourceURL,varConfig)	\
    ( (This)->lpVtbl -> Initialise(This,lDataSourceType,varDataSourceURL,varConfig) ) 

#define IWinBlitData_GetData(This,lDataOffset,pbstrData)	\
    ( (This)->lpVtbl -> GetData(This,lDataOffset,pbstrData) ) 

#define IWinBlitData_FindString(This,bstrSearchString,lSearchOffset,lSearchDirection,lStringOffset)	\
    ( (This)->lpVtbl -> FindString(This,bstrSearchString,lSearchOffset,lSearchDirection,lStringOffset) ) 

#define IWinBlitData_Uninitialise(This)	\
    ( (This)->lpVtbl -> Uninitialise(This) ) 

#define IWinBlitData_GetParaAtPercent(This,lPercent,lPara,bRound)	\
    ( (This)->lpVtbl -> GetParaAtPercent(This,lPercent,lPara,bRound) ) 

#define IWinBlitData_GetPercentAtPara(This,lPercent,lPara)	\
    ( (This)->lpVtbl -> GetPercentAtPara(This,lPercent,lPara) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




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
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowHelp( 
            /* [in] */ long lHelpType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Register( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowAbout( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DemoMode( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DemoMode( 
            /* [retval][out] */ long *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWinBlitReaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWinBlitReader * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWinBlitReader * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWinBlitReader * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWinBlitReader * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWinBlitReader * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWinBlitReader * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWinBlitReader * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadData )( 
            IWinBlitReader * This,
            /* [in] */ long lDataSourceType,
            /* [in] */ VARIANT varDataSource);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnloadData )( 
            IWinBlitReader * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Display )( 
            IWinBlitReader * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            IWinBlitReader * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IWinBlitReader * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowHelp )( 
            IWinBlitReader * This,
            /* [in] */ long lHelpType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Register )( 
            IWinBlitReader * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowAbout )( 
            IWinBlitReader * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_State )( 
            IWinBlitReader * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DemoMode )( 
            IWinBlitReader * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DemoMode )( 
            IWinBlitReader * This,
            /* [retval][out] */ long *pVal);
        
        END_INTERFACE
    } IWinBlitReaderVtbl;

    interface IWinBlitReader
    {
        CONST_VTBL struct IWinBlitReaderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWinBlitReader_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWinBlitReader_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWinBlitReader_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWinBlitReader_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWinBlitReader_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWinBlitReader_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWinBlitReader_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWinBlitReader_LoadData(This,lDataSourceType,varDataSource)	\
    ( (This)->lpVtbl -> LoadData(This,lDataSourceType,varDataSource) ) 

#define IWinBlitReader_UnloadData(This)	\
    ( (This)->lpVtbl -> UnloadData(This) ) 

#define IWinBlitReader_Display(This)	\
    ( (This)->lpVtbl -> Display(This) ) 

#define IWinBlitReader_Start(This)	\
    ( (This)->lpVtbl -> Start(This) ) 

#define IWinBlitReader_Stop(This)	\
    ( (This)->lpVtbl -> Stop(This) ) 

#define IWinBlitReader_ShowHelp(This,lHelpType)	\
    ( (This)->lpVtbl -> ShowHelp(This,lHelpType) ) 

#define IWinBlitReader_Register(This)	\
    ( (This)->lpVtbl -> Register(This) ) 

#define IWinBlitReader_ShowAbout(This)	\
    ( (This)->lpVtbl -> ShowAbout(This) ) 

#define IWinBlitReader_get_State(This,pVal)	\
    ( (This)->lpVtbl -> get_State(This,pVal) ) 

#define IWinBlitReader_put_DemoMode(This,newVal)	\
    ( (This)->lpVtbl -> put_DemoMode(This,newVal) ) 

#define IWinBlitReader_get_DemoMode(This,pVal)	\
    ( (This)->lpVtbl -> get_DemoMode(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




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
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Rule( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Period( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Period( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISettingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISetting * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISetting * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISetting * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISetting * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISetting * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISetting * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISetting * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rule )( 
            ISetting * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Rule )( 
            ISetting * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Period )( 
            ISetting * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Period )( 
            ISetting * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            ISetting * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            ISetting * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ISetting * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ISetting * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ISettingVtbl;

    interface ISetting
    {
        CONST_VTBL struct ISettingVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISetting_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISetting_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISetting_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISetting_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISetting_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISetting_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISetting_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISetting_get_Rule(This,pVal)	\
    ( (This)->lpVtbl -> get_Rule(This,pVal) ) 

#define ISetting_put_Rule(This,newVal)	\
    ( (This)->lpVtbl -> put_Rule(This,newVal) ) 

#define ISetting_get_Period(This,pVal)	\
    ( (This)->lpVtbl -> get_Period(This,pVal) ) 

#define ISetting_put_Period(This,newVal)	\
    ( (This)->lpVtbl -> put_Period(This,newVal) ) 

#define ISetting_get_Value(This,pVal)	\
    ( (This)->lpVtbl -> get_Value(This,pVal) ) 

#define ISetting_put_Value(This,newVal)	\
    ( (This)->lpVtbl -> put_Value(This,newVal) ) 

#define ISetting_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define ISetting_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




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
            /* [retval][out] */ LPUNKNOWN *pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
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
            /* [retval][out] */ ISetting **ppSetting) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISettings * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISettings * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISettings * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISettings * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISettings * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISettings * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISettings * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ISettings * This,
            /* [retval][out] */ LPUNKNOWN *pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ISettings * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ISettings * This,
            /* [retval][out] */ long *pVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ISettings * This,
            /* [in] */ BSTR bstrKey,
            /* [in] */ long lIndex,
            /* [in] */ long lRule,
            /* [in] */ BSTR bstrValue,
            /* [in] */ long lPeriod);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ISettings * This,
            /* [in] */ VARIANT Index);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ISettings * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *get_ItemCustom )( 
            ISettings * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ISetting **ppSetting);
        
        END_INTERFACE
    } ISettingsVtbl;

    interface ISettings
    {
        CONST_VTBL struct ISettingsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISettings_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISettings_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISettings_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISettings_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISettings_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISettings_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISettings_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISettings_get__NewEnum(This,pVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,pVal) ) 

#define ISettings_get_Item(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,Index,pVal) ) 

#define ISettings_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ISettings_Add(This,bstrKey,lIndex,lRule,bstrValue,lPeriod)	\
    ( (This)->lpVtbl -> Add(This,bstrKey,lIndex,lRule,bstrValue,lPeriod) ) 

#define ISettings_Remove(This,Index)	\
    ( (This)->lpVtbl -> Remove(This,Index) ) 

#define ISettings_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ISettings_get_ItemCustom(This,Index,ppSetting)	\
    ( (This)->lpVtbl -> get_ItemCustom(This,Index,ppSetting) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




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
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Quantity( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Quantity( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStatisticVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStatistic * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStatistic * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStatistic * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IStatistic * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IStatistic * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IStatistic * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IStatistic * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IStatistic * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            IStatistic * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Quantity )( 
            IStatistic * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Quantity )( 
            IStatistic * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IStatistic * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IStatistic * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IStatisticVtbl;

    interface IStatistic
    {
        CONST_VTBL struct IStatisticVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStatistic_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStatistic_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStatistic_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStatistic_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IStatistic_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IStatistic_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IStatistic_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IStatistic_get_Type(This,pVal)	\
    ( (This)->lpVtbl -> get_Type(This,pVal) ) 

#define IStatistic_put_Type(This,newVal)	\
    ( (This)->lpVtbl -> put_Type(This,newVal) ) 

#define IStatistic_get_Quantity(This,pVal)	\
    ( (This)->lpVtbl -> get_Quantity(This,pVal) ) 

#define IStatistic_put_Quantity(This,newVal)	\
    ( (This)->lpVtbl -> put_Quantity(This,newVal) ) 

#define IStatistic_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define IStatistic_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




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
            /* [retval][out] */ LPUNKNOWN *pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE get_ItemCustom( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IStatistic **ppStatistic) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStatisticsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStatistics * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStatistics * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStatistics * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IStatistics * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IStatistics * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IStatistics * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IStatistics * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IStatistics * This,
            /* [retval][out] */ LPUNKNOWN *pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IStatistics * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IStatistics * This,
            /* [retval][out] */ long *pVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IStatistics * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *get_ItemCustom )( 
            IStatistics * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IStatistic **ppStatistic);
        
        END_INTERFACE
    } IStatisticsVtbl;

    interface IStatistics
    {
        CONST_VTBL struct IStatisticsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStatistics_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStatistics_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStatistics_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStatistics_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IStatistics_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IStatistics_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IStatistics_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IStatistics_get__NewEnum(This,pVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,pVal) ) 

#define IStatistics_get_Item(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,Index,pVal) ) 

#define IStatistics_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IStatistics_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IStatistics_get_ItemCustom(This,Index,ppStatistic)	\
    ( (This)->lpVtbl -> get_ItemCustom(This,Index,ppStatistic) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




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
            /* [out] */ VARIANT_BOOL *bLoaded,
            /* [retval][out] */ IDispatch **pDispatch) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBrowserWrapperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBrowserWrapper * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBrowserWrapper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBrowserWrapper * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBrowserWrapper * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBrowserWrapper * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBrowserWrapper * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBrowserWrapper * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Run )( 
            IBrowserWrapper * This,
            /* [in] */ BSTR bstrDataSource);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDoc )( 
            IBrowserWrapper * This,
            /* [out] */ VARIANT_BOOL *bLoaded,
            /* [retval][out] */ IDispatch **pDispatch);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IBrowserWrapper * This);
        
        END_INTERFACE
    } IBrowserWrapperVtbl;

    interface IBrowserWrapper
    {
        CONST_VTBL struct IBrowserWrapperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBrowserWrapper_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBrowserWrapper_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBrowserWrapper_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBrowserWrapper_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IBrowserWrapper_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IBrowserWrapper_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IBrowserWrapper_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IBrowserWrapper_Run(This,bstrDataSource)	\
    ( (This)->lpVtbl -> Run(This,bstrDataSource) ) 

#define IBrowserWrapper_GetDoc(This,bLoaded,pDispatch)	\
    ( (This)->lpVtbl -> GetDoc(This,bLoaded,pDispatch) ) 

#define IBrowserWrapper_Stop(This)	\
    ( (This)->lpVtbl -> Stop(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBrowserWrapper_INTERFACE_DEFINED__ */



#ifndef __WINBLITREADERMANAGERLib_LIBRARY_DEFINED__
#define __WINBLITREADERMANAGERLib_LIBRARY_DEFINED__

/* library WINBLITREADERMANAGERLib */
/* [helpstring][version][uuid] */ 

typedef 
enum CursorConfiguration
    {
        cDisplayScreenText	= 1,
        cDisplayCursorText	= 2,
        cRSVPCursor	= 4,
        cTachistoscopicCursor	= 8,
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
        cCursorSound	= 16384,
        cAutoStartBlitPad	= 32768,
        cAutoStartIE	= 65536,
        cAutoStartOutlook	= 131072,
        cAutoStartWord	= 262144
    } 	cCursorConfigurations;

typedef 
enum StatisticType
    {
        cWordCount	= 1,
        cElapsedTime	= 2,
        cReadTime	= 3
    } 	cStatisticTypes;

typedef 
enum SettingType
    {
        cPauseAt	= 1,
        cDelayAt	= 2,
        cHTMLTags	= 3
    } 	cSettingTypes;

typedef 
enum eSTATE
    {
        e_NONE	= 0,
        e_LOADINGDATA	= 1,
        e_DATALOADED	= 2,
        e_DISPLAYING	= 3,
        e_MOVINGSCROLLBAR	= 4,
        e_RUNNING	= 5,
        e_PAUSED	= 6,
        e_SETTINGS	= 7
    } 	eSTATE;


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

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize64(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal64(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal64(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree64(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


