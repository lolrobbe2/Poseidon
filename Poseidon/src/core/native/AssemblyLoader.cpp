#include "AssemblyLoader.h"
#include <core/host.h>
#include <core/delegates/assemblyLoaderDelegates.h>
#include <core/native/interop/interop.h>
namespace poseidon::core::native
{
	typedef struct assemblyLoaderFunctions
	{
		createContextFunc p_createContext = nullptr;
	};
	assemblyLoader::assemblyLoader(std::shared_ptr<host> p_host, const std::string& name) :p_host(p_host){
		loadFunctions();
		m_loadContextId = createContext(name);
	}
	void assemblyLoader::loadFunctions()
	{
		if (p_assemblyLoaderFunctions) return;
		p_assemblyLoaderFunctions = new assemblyLoaderFunctions();
		p_host->getUnmangedFunctionPtr(PD_STR("PoseidonSharp.native.AssemblyLoader, PoseidonSharp"), PD_STR("CreateContext"), (void**)&p_assemblyLoaderFunctions->p_createContext);
	}
	std::shared_ptr<assembly> assemblyLoader::loadAssembly(std::filesystem::path path)
	{
		nativeString n_path{ (const char*)path.c_str() };
		//return std::make_shared<assembly>(p_assemblyLoaderFunctions->(n_path));
		return nullptr;
	}
	int assemblyLoader::createContext(const std::string& name)
	{
		nativeString n_string{ name.c_str() };
		return p_assemblyLoaderFunctions->p_createContext(n_string);
	}
	assemblyLoader::~assemblyLoader()
	{
	}
}
