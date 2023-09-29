

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Mon Jan 18 19:14:07 2038
 */
/* Compiler settings for RegFreeCpp.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
    protocol : all , ms_ext, c_ext, robust
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

#ifndef __RegFreeCpp_i_h__
#define __RegFreeCpp_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IMyDebugOutput_FWD_DEFINED__
#define __IMyDebugOutput_FWD_DEFINED__
typedef interface IMyDebugOutput IMyDebugOutput;

#endif 	/* __IMyDebugOutput_FWD_DEFINED__ */


#ifndef __MyDebugOutput_FWD_DEFINED__
#define __MyDebugOutput_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyDebugOutput MyDebugOutput;
#else
typedef struct MyDebugOutput MyDebugOutput;
#endif /* __cplusplus */

#endif 	/* __MyDebugOutput_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IMyDebugOutput_INTERFACE_DEFINED__
#define __IMyDebugOutput_INTERFACE_DEFINED__

/* interface IMyDebugOutput */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyDebugOutput;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("26f75a2a-d3f8-4e54-a12c-899316eb3116")
    IMyDebugOutput : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteLine( 
            /* [in] */ BSTR Message) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMyDebugOutputVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyDebugOutput * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyDebugOutput * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyDebugOutput * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMyDebugOutput * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMyDebugOutput * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMyDebugOutput * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMyDebugOutput * This,
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
        
        DECLSPEC_XFGVIRT(IMyDebugOutput, WriteLine)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WriteLine )( 
            IMyDebugOutput * This,
            /* [in] */ BSTR Message);
        
        END_INTERFACE
    } IMyDebugOutputVtbl;

    interface IMyDebugOutput
    {
        CONST_VTBL struct IMyDebugOutputVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyDebugOutput_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyDebugOutput_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyDebugOutput_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyDebugOutput_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMyDebugOutput_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMyDebugOutput_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMyDebugOutput_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMyDebugOutput_WriteLine(This,Message)	\
    ( (This)->lpVtbl -> WriteLine(This,Message) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMyDebugOutput_INTERFACE_DEFINED__ */



#ifndef __RegFreeCppLib_LIBRARY_DEFINED__
#define __RegFreeCppLib_LIBRARY_DEFINED__

/* library RegFreeCppLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_RegFreeCppLib;

EXTERN_C const CLSID CLSID_MyDebugOutput;

#ifdef __cplusplus

class DECLSPEC_UUID("04f2a6ef-f2ee-4c33-a65e-7c02a1c9bdb5")
MyDebugOutput;
#endif
#endif /* __RegFreeCppLib_LIBRARY_DEFINED__ */

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


