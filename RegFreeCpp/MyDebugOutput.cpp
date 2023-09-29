// MyDebugOutput.cpp : Implementation of CMyDebugOutput

#include "pch.h"
#include "MyDebugOutput.h"
#include "resource.h"



// CMyDebugOutput

STDMETHODIMP CMyDebugOutput::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] = 
	{
		&IID_IMyDebugOutput
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CMyDebugOutput::WriteLine(BSTR Message)
{
	if (nullptr == Message)
	{
		AtlReportError(CLSID_MyDebugOutput, IDS_MESSAGE_NULL, IID_IMyDebugOutput, E_INVALIDARG);
	
		return E_INVALIDARG;
	}

	std::wstring message(OLE2CW(Message)); // Cast the BSTR to a wchar_t string

	// Help the caller in case they didn't add a carriage return
	if (L'\n' != message.back()) 
		message.append(L"\n");

	OutputDebugString(message.c_str());

	return S_OK;
}
