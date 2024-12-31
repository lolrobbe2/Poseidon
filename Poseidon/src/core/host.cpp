#include "host.h"
#include "CoreCLR.h"
#include <core/delegates/hdtDelegates.h> 
#include <codecvt>
#include <iostream>
#include <thirdParty/coreclr/coreclr_delegates.h>
#include <core/native/AssemblyLoader.h>
namespace poseidon::core
{
	
	host::host(hostHandle handle) : m_handle(handle)
	{
		loadDelegates();
		if (success != loadAssembly("./PoseidonSharp.dll"))
			throw new std::exception("unable to load PoseidonSharp.dll");
	}
	
	host::~host()
	{
		if (m_handle)
			release();

	}
	void host::release()
	{
		if (!isValid()) return;
		int32_t res = HostFxr::close(m_handle);
		if (res) throw new std::exception("[HostFxr] could not release host" + res);
		m_handle = nullptr;
	}
	int host::getUnmangedFunctionPtr(const char_t* typeName, const char_t* methodName, void** function)
	{
		
		if (!functions && !isValid()) return hostres::failure;
		return functions.get_function_pointer_ptr(typeName, methodName,UNMANAGEDCALLERSONLY_METHOD,nullptr ,nullptr, function);
	}
	const r_garbageCollector host::getGarbageCollector()
	{
		if (!isValid()) return nullptr;
		if(!r_garbageCollector) r_garbageCollector = std::make_shared<garbageCollector>(shared_from_this());
		return r_garbageCollector;
	}
	r_assemblyLoader host::getAssemblyLoader(const std::string& name)
	{
		return std::make_shared<native::assemblyLoader>(shared_from_this(), name);
	}
	host::hostres host::loadAssembly(std::filesystem::path path)
	{
		if (!functions) return functions_not_initialized;
		else if (!isValid()) return host_invalid;
		return (hostres)functions.load_assembly_ptr(std::filesystem::absolute(path).wstring().c_str(), nullptr, nullptr);
	}
	host::hostres host::loadDelegates()
	{
		if (functions) return functions_not_initialized;
		else if (!isValid()) return host_invalid;

		getRuntimeDelegate(load_assembly, (void**)&functions.load_assembly_ptr);
		getRuntimeDelegate(get_function_pointer, (void**)&functions.get_function_pointer_ptr);
	}
	void host::getRuntimeDelegate(host::delegateType type, void** delegate)
	{
		if (!isValid()) return;
		HostFxr::getRuntimeDelegate(m_handle, type, delegate);
	}
}
