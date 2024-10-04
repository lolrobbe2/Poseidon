#pragma once
#ifndef _ASSEMBLY_LOADER_
#define _ASSEMBLY_LOADER_
#include <memory>
#include <core/native/interop/interop.h>
#include <filesystem>
#include <core/native/assembly.h>
namespace poseidon::core::native 
{
	struct assemblyLoaderFunctions;
	class assemblyLoader 
	{
	public:
		assemblyLoader(std::shared_ptr<host> p_host,const std::string& path);
		std::shared_ptr<assembly> loadAssembly(std::filesystem::path path);
		void loadFunctions();
		~assemblyLoader();

	private:
		int createContext(const std::string& name);
		std::shared_ptr<host> p_host;
		assemblyLoaderFunctions* p_assemblyLoaderFunctions = nullptr;
		int m_loadContextId = 0;
	};

}
#endif // !_ASSEMBLY_LOADER_