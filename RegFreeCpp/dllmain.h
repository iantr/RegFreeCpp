// dllmain.h : Declaration of module class.

class CRegFreeCppModule : public ATL::CAtlDllModuleT< CRegFreeCppModule >
{
public :
	DECLARE_LIBID(LIBID_RegFreeCppLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_REGFREECPP, "{eb8d811e-fd0f-448a-a908-864eaae142c3}")
};

extern class CRegFreeCppModule _AtlModule;
