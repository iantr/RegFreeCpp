// CppTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _WIN32_DCOM
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <atlbase.h>
#include <atlcom.h>

#include "..\RegFreeCpp\RegFreeCpp_i.h"

#include <iostream>
#include <iomanip>

int main()
{
    std::cout << "RegFreeCpp C++ Test!\n";

    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr))
        return -3;

    CComPtr<IMyDebugOutput> debugOutput;

    hr = debugOutput.CoCreateInstance(CLSID_MyDebugOutput);

    if (FAILED(hr))
    {
        std::wcout << L"Could not create an instance of MyDebugOutput. hr = 0x" << std::hex << std::setw(8) << std::setfill(L'0') << hr << L" ";
        if (REGDB_E_CLASSNOTREG == hr)
            std::wcout << L"Class not registered (RegFreeCpp.dll not loaded)\n";

        std::wcout << std::endl;
        return -2;
    }

    hr = debugOutput->WriteLine(CComBSTR(L"Debug message from MyDebugOuput"));

    if (FAILED(hr))
    {
        std::wcout << L"MyDebugOutput returned failure: 0x" << std::hex << std::setw(8) << std::setfill(L'0') << hr << std::endl;
    }
    else
    {
        std::wcout << L"MyDebugOutput succeeded\n";
    }

    // Clean-up
    debugOutput.Release();

    CoUninitialize();
}

