// MyDebugOutput.h : Declaration of the CMyDebugOutput

#pragma once
#include "resource.h"       // main symbols



#include "RegFreeCpp_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CMyDebugOutput

class ATL_NO_VTABLE CMyDebugOutput :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMyDebugOutput, &CLSID_MyDebugOutput>,
	public ISupportErrorInfo,
	public IDispatchImpl<IMyDebugOutput, &IID_IMyDebugOutput, &LIBID_RegFreeCppLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CMyDebugOutput()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CMyDebugOutput)
	COM_INTERFACE_ENTRY(IMyDebugOutput)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(WriteLine)(BSTR Message);
};

OBJECT_ENTRY_AUTO(__uuidof(MyDebugOutput), CMyDebugOutput)
