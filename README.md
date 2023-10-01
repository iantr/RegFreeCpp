# RegFreeCpp
## Sample Reg-Free C++ COM Component with Isolated COM C++ and C# Test Apps

The purpose of the RegFreeCpp project is to show how to create a COM component in C++ and then use it without registration or "reg-free" in both a C++ Isolated COM app and a C# app. I found the documentation to be lacking so I'm putting this sample out there along with detailed instructions so other folks might have an easier time.

There are three projects in the solution:
- RegFreeCpp - this is a simple C++ ATL-based COM object that just prints a message to the sytem debug output.
- CppTest - this is a simple Isolated COM C++ app that instantiates the RegFreeCpp component can calls its single method
- DotNetFrameworkTest - this is a C# .NET Framework console app that also instantiates the RegFreeCpp component can calls its single method

This project uses Visual Studio 2022.

Start by creating a new C++ ATL Project named RegFreeCpp.

![Create C++ ATL Project](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture1.png "Create C++ ATL Project")

![ATL Project Properties](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture2.png "Set the ATL project properties")

That makes the DLL that will host the component(s).

By default the ATL Wizard creates a DLL that supports registration for COM usage the traditional way. Let’s disable that before proceeding, since the build process automatically registers the DLL and any components it implements. Open the RegFreeCpp.def source file and comment-out DllRegisterServer, DllUnregisterServer and DllInstall, as shown here with semi-colons on those lines:

```c
; RegFreeCpp.def : Declares the module parameters.

LIBRARY

EXPORTS
	DllCanUnloadNow        PRIVATE
	DllGetClassObject      PRIVATE
	;DllRegisterServer     PRIVATE
	;DllUnregisterServer   PRIVATE
	;DllInstall            PRIVATE

```

Let’s now make some updates to the project:

Set C++ 20 and Warning Level 4. Start off with a good foundation. Be sure to select All Configurations and All Platforms first, then adjust the C++ Language Standard to be ISO C++ 20. This gives you access to newer handy STL classes such as std::string_view, std::format and std::filesystem.

![Project language settings](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture3.png "Set the project to use C++ 20")

Let’s set the warning level to 4 to keep the code safe as its developed:

![Project compiler warning settings](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture4.png "Set the project to use warning level 4")

Since we don’t want to have the COM components registered from this DLL, let’s turn off link-time registration. The Register Output option is found on the General tab of the Linker settings:

![Project settings to not register the COM object](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture5.png "Turn off COM object registration")

The other important Linker setting to change is generating a manifest for the executable. Having this present will prevent the DLL from being loaded in a .NET project via reg-free COM. We will add a COM-related manifest later.

![Project settings to not create a manifest for the DLL](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture6.png "Turn off executable manifest creation")

Try building the project – it should build now.

Let’s create a COM component to live in the DLL. For this sample we’ll just create a simple object that outputs a string to the system debug output. 

To the RegFreeCpp project, add a new item:

![Create a COM component](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture7.png "Create a COM component")

Using the ATL Simple Object wizard is highly recommended:

![ATL Simple Object wizard](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture8.png "Create a COM component")

The defaults suggested for the Names are fine for this sample. Don’t press Finish yet – there’s important options on the Other tab.

![ATL Simple Object other settings](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture9.png "Create a COM component with threading model 'Both'")

Selecting Both for the threading model supports easy usage and especially debugging. Select that unless you have a specific need otherwise.

For elegant integration into .NET environments, select ISupportErrorInfo. This allows for errors with descriptive messages to be surfaced as exceptions in C# applications.

![ATL Simple Object other settings](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture10.png "Create a COM component with threading model 'Both'")

Now press Finish to add this component to the DLL.

Let’s add a method to the MyDebugOutput component’s interface. This is best and most easily done using the Visual Studio Class View. Select the IMyDebugOutput interface in the RegFreeCpp project within Class View, right-click to Add a new Method, as shown here:

![Add a method to the object](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture11.png "Create the WriteLine method")

You may need to build the project to get all the nodes as displayed here. When adding the method it’s important to select the correct IMyDebugOutput node. Two identical nodes are displayed. The one you don’t want is the one with the tooltip for the icon that says ‘_interface IMyDebugNode’.  

![Add a method to the object](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture12.png "Create the WriteLine method")

The project should build. If not, revisit the Class View node that you added the method to.

For the implementation of WriteLine in MyDebugOutput.cpp, lets use some STL. You might as well include the needed STL headers in the pre-compiled headers, so add #include <string> to pch.h.

Let’s start with the essential message code, like this:

```cpp
STDMETHODIMP CMyDebugOutput::WriteLine(BSTR Message)
{
	if (nullptr == Message)
		return E_INVALIDARG;

	std::wstring message(OLE2CW(Message)); // Cast the BSTR to a wchar_t string

	// Help the caller in case they didn't add a carriage return
	if (L'\n' != message.back()) 
		message.append(L"\n");

	OutputDebugString(message.c_str());

	return S_OK;
}
```

Now let’s make the error case nicer for .NET environments by added an IErrorInfo message. ATL’s helper function, AtlReportError, does this quite nicely and forces you to do it right by requiring the error message to be in the DLL’s string resources. Let’s add the error message there. 

Open the Resource View and then open the String Table that’s already been created, as shown here:

![Add a string resource](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture13.png "Create the WriteLine method error message string")

Add a string as shown here:

![Add a string resource](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture14.png "Create the WriteLine method error message string")

To reference the message, you’ll need to add #include “resource.h” to MyDebugOutput.cpp.

The implementation of WriteMessage can be updated as follows, adding the call to AtlReportError. Note the message ID passed: IDS_MESSAGE_NULL, from resource.h.

```cpp
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
```

Next up is to create the COM manifest so clients can instantiate the component as an Isolated COM aka registry-free component usage style application.

Create RegFreeCpp.manifest in the settings for the project by adding a post-build event that runs the Windows SDK Manifest Tool (mt.exe), as shown here:

![Create a COM manifest](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture15.png "Create the manifest file so the COM object can be instantiated")

The Command Line is set to:

```
mt.exe -out:$(OutDir)RegFreeCpp.manifest -tlb:$(IntDirFullPath)RegFreeCpp.tlb -dll:RegFreeCpp.dll -rgs:$(ProjectDir)RegFreeCpp.rgs
```

Do a build and notice RegFreeCpp.manifest in the output folder. It should look like this:

```xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0">
	<file name="RegFreeCpp.dll" hashalg="SHA1">
		<comClass 
            clsid="{04F2A6EF-F2EE-4C33-A65E-7C02A1C9BDB5}" 
            tlbid="{EB8D811E-FD0F-448A-A908-864EAAE142C3}">
        </comClass>
		<typelib 
            tlbid="{EB8D811E-FD0F-448A-A908-864EAAE142C3}" 
            version="1.0" 
            helpdir="" 
            flags="HASDISKIMAGE">
        </typelib>
	</file>
	<comInterfaceExternalProxyStub 
        name="IMyDebugOutput" 
        iid="{26F75A2A-D3F8-4E54-A12C-899316EB3116}" 
        tlbid="{EB8D811E-FD0F-448A-A908-864EAAE142C3}" proxyStubClsid32="{00020424-0000-0000-C000-000000000046}">
    </comInterfaceExternalProxyStub>
</assembly>
```

## C++ Test Application
It’s time to test it! Let’s start with a C++ console app. To the solution, add a new C++ console app. Let’s call it CppTest. 

![Create a C++ Console app](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture16.png)

To the CppTest project, add a reference to the RegFreeCpp project. Also add the RegFreeCpp_i.c to the project so the CLSID can be used in the component instantiation. The project should look like this:

![Create a C++ Console app](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture17.png)

The CppTest.cpp file needs a few includes so that the Windows SDK and ATL libraries can be used. It also needs the RegFreeCpp interface header file. Add these lines to the top of CppTest.cpp:

```cpp
#define _WIN32_DCOM
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <atlbase.h>
#include <atlcom.h>


#include <iostream>
#include <iomanip>

#include "..\RegFreeCpp\RegFreeCpp_i.h"
```

The main function initializes COM then attempts to instantiate the RegFreeCpp component and call it’s WriteLine method:

```cpp
int main()
{
    std::cout << "CppTest!\n";

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
```

The last thing we need to do is incorporate the RegFreeCpp.manifest file into the project. 

This is done in the project settings Manifest area’s Input and Output section, adding the following to the Additional Manifest Files entry:

```
$(OutDir)RegFreeCpp.manifest
```

![Configure the manifest to be included](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture18.png)

Give it a try. It should work. If you step through the code and stop just after the call to WriteLine, you should see the debug message in the Visual Studio Output window:

![Configure the manifest to be included](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture19.png)

If you want to see the output while not running in a debugger, you could use the Debug View app from SysInternals.

## C# Test Application

Let’s make a C# .NET Framework test application. Add a C# Console App (.NET Framework) project to the solution and let’s name it DotNetFrameworkTest.

A .NET app needs a manifest so it can be augmented to reference the COM object’s manifest: RegFreeCpp.manifest in this case. To the DotNetFrameworkTest app, add a manifest:

![Add a manifest](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture20.png)

You might as well uncomment the block that indicates this app is compatible with Windows 10, which also indicates Windows 11.

```xml
      <!-- Windows 10 -->
      <supportedOS Id="{8e0f7a12-bfb3-4fe8-b9a5-48fd50a15a9a}" />
```

Now add a dependency section at the top just under the main assembly node. The start of the app.manifest file will look like this:

```xml
<?xml version="1.0" encoding="utf-8"?>
<assembly manifestVersion="1.0" xmlns="urn:schemas-microsoft-com:asm.v1">
	<dependency>
		<dependentAssembly>
			<assemblyIdentity
                type="win32"
                name="RegFreeCpp"
                version="1.0.0.0"
                processorArchitecture="*"
            />
		</dependentAssembly>
	</dependency>
```

Next you need to change the Platform target to be either x86 or x64, since a native-code DLL will be loaded into the process. Assuming x64, go to the Build tab of the project settings and change All Configurations to target the x64 platform, like this:

![Set the Platform to x64](https://github.com/iantr/RegFreeCpp/blob/main/doc/Picture21.png)

Since we are using a native-code COM component, an Interop assembly needs to be generated for it. This can be accomplished in the Pre-build step of the settings with the following command:

```
"$(TargetFrameworkSDKToolsDirectory)tlbimp.exe" "$(SolutionDir)RegFreeCpp\x64\$(ConfigurationName)\RegFreeCpp.tlb" /out:"$(ProjectDir)Interop.RegFreeCpp.dll"
```

In the same pre-build settings, add these commands to copy the RegFreeCpp.dll and RegFreeCpp.manifest to the current folder. This ensures those files are located where the debugger expects them to be so you can test your app in the debugger.

```
copy "$(SolutionDir)x64\$(ConfigurationName)\RegFreeCpp.dll".
copy "$(SolutionDir)x64\$(ConfigurationName)\RegFreeCpp.manifest".
```

Build the C# project so the Interop DLL gets generated.


Now add a reference to the generated Interop.RegFreeCpp.dll in the project directory. 


We can finally add some code. Change Program.cs to the following:

```C#
using System;
using Interop.RegFreeCpp;

namespace DotNetFrameworkTest
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var debugOutput = new MyDebugOutput();

            try
            {
                debugOutput.WriteLine("Debug message from MyDebugOuput");

                Console.WriteLine("MyDebugOutput succeeded");
            }
            catch(Exception ex) 
            { 
                Console.WriteLine("MyDebugOutput failed: " + ex.ToString());
            }
        }
    }
}
```

Run the program. It should succeed. In my testing, the debug output did not go to the Debug window in Visual Studio. I ran Debug View from SysInternals and saw the output that way. 

You can test the error handling by passing null to the WriteLine method and see the exception be thrown and the error message from the RegFreeCpp’s resources be displayed.
