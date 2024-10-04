#include "AssemblyLoader.h"
#include <core/host.h>
#include <core/delegates/assemblyLoaderDelegates.h>
#include <core/native/interop/interop.h>
#include <core/native/assemblyClass.h>
namespace poseidon::core::native
{
	struct assemblyLoaderFunctions
	{
		f_createContext p_createContext = nullptr;
		f_loadAssembly p_loadAssembly = nullptr;
	};
	assemblyLoader::assemblyLoader(std::shared_ptr<host> p_host, const std::string& name) :p_host(p_host){
		loadFunctions();
		m_loadContextId = createContext(name);
		assemblyClass::loadFunctions(p_host);

	}
	void assemblyLoader::loadFunctions()
	{
		if (p_assemblyLoaderFunctions) return;
		p_assemblyLoaderFunctions = new assemblyLoaderFunctions();
		p_host->getUnmangedFunctionPtr(PD_STR("PoseidonSharp.native.AssemblyLoader, PoseidonSharp"), PD_STR("CreateContext"), (void**)&p_assemblyLoaderFunctions->p_createContext);
		p_host->getUnmangedFunctionPtr(PD_STR("PoseidonSharp.native.AssemblyLoader, PoseidonSharp"), PD_STR("LoadAssembly"), (void**)&p_assemblyLoaderFunctions->p_loadAssembly);
	}
	std::shared_ptr<assembly> assemblyLoader::loadAssembly(std::filesystem::path path)
	{
		nativeString n_path{ (char*)std::filesystem::absolute(path).string().c_str()};
		return std::make_shared<assembly>(p_host,p_assemblyLoaderFunctions->p_loadAssembly(m_loadContextId,n_path),m_loadContextId);
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
