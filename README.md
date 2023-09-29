# RegFreeCpp
Sample Reg-Free C++ COM Component with Isolated COM C++ and C# Test Apps

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
