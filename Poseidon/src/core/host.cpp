#include "host.h"
#include "CoreCLR.h"
#include <core/delegates/hdtDelegates.h> 
#include <codecvt>
#include <iostream>
#include <thirdParty/coreclr/coreclr_delegates.h>
namespace poseidon::core
{
	host::~host()
	{
		release();
	}
	void host::release()
	{
		if (!isValid()) return;
		HostFxr::close(m_handle);

		m_handle = nullptr;
	}
	int host::getUnmangedFunctionPtr(const char_t* typeName, const char_t* methodName, void** function)
	{
		
		if (!functions) return hostres::failure;
		return functions.get_function_pointer_ptr(typeName, methodName,UNMANAGEDCALLERSONLY_METHOD,nullptr ,nullptr, function);
	}
	std::shared_ptr<native::assemblyLoader> host::getAssemblyLoader(const std::string& name)
	{
		return std::make_shared<native::assemblyLoader>(shared_from_this(),name);
	}
	host::hostres host::loadAssembly(std::filesystem::path path)
	{
		if (!functions) return functions_not_initialized;
		std::cout << std::filesystem::absolute(path) << std::endl;
		return (hostres)functions.load_assembly_ptr(std::filesystem::absolute(path).wstring().c_str(), nullptr, nullptr);
	}
	void host::loadDelegates()
	{
		if (functions) return;
		getRuntimeDelegate(load_assembly, (void**)&functions.load_assembly_ptr);
		getRuntimeDelegate(get_function_pointer, (void**)&functions.get_function_pointer_ptr);
	}
	void host::getRuntimeDelegate(host::delegateType type, void** delegate)
	{
		HostFxr::getRuntimeDelegate(m_handle, type, delegate);
	}
}
