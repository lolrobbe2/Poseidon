#include "assembly.h"
#include <core/delegates/assemblyDelegates.h>
#include <core/host.h>
namespace poseidon::core::native
{
	struct assemblyFunctions
	{
		f_assemblyGetNameNative assemblyGetNameNativePtr = nullptr;
		f_assemblyGetVersionStringNative assemblyGetVersionNativeString = nullptr;
		f_assemblyGetVersionNative assemblyGetVersionNative = nullptr;
		f_assemblyGetClassesNative assemblyGetClassesNativePtr = nullptr;

	};
	static assemblyFunctions* p_assemblyFunctions = nullptr;
	
	assembly::assembly(std::shared_ptr<host> p_host, int assemblyId, int contextId) : p_host(p_host), m_assemblyId(assemblyId), m_contextId(contextId) { loadFunctions(); }

	
	
	const assembly::assemblyLoadRes assembly::getResult()
	{
		return (assemblyLoadRes) m_assemblyId;
	}
	const std::string assembly::getErrorString()
	{
		switch (getResult())
		{
		case failure:
			return "[Assembly] failure";
		case badPath:
			return "[Assembly] badPath";
		case badILformat:
			return "[Assembly] badILformat";
		case  fileNotFound:
			return "[Assembly] fileNotFound";
		default:
			return "Unkown";
		}
		return "Success";
	}
	const std::string assembly::getName()
	{
		return p_assemblyFunctions->assemblyGetNameNativePtr(m_contextId,m_assemblyId);
	}
	const std::string assembly::getVersionString() 
	{
		return p_assemblyFunctions->assemblyGetVersionNativeString(m_contextId,m_assemblyId);
	}
	const nativeVersion assembly::getVersion()
	{
		return p_assemblyFunctions->assemblyGetVersionNative(m_contextId, m_assemblyId);
	}
	const std::vector<assemblyClass> assembly::getClasses()
	{
		return *p_assemblyFunctions->assemblyGetClassesNativePtr(m_contextId,m_assemblyId);
	}
	void assembly::loadFunctions()
	{
		if (p_assemblyFunctions) return;
		p_assemblyFunctions = new assemblyFunctions();
		std::cout << "abc: " << sizeof(nativeArray<assemblyClass>) << std::endl;
		p_host->getUnmangedFunctionPtr(PD_STR("PoseidonSharp.native.PoseidonAssembly, PoseidonSharp"), PD_STR("GetNameNative"), (void**)&p_assemblyFunctions->assemblyGetNameNativePtr);
		p_host->getUnmangedFunctionPtr(PD_STR("PoseidonSharp.native.PoseidonAssembly, PoseidonSharp"), PD_STR("GetVersionStringNative"), (void**)&p_assemblyFunctions->assemblyGetVersionNativeString);
		p_host->getUnmangedFunctionPtr(PD_STR("PoseidonSharp.native.PoseidonAssembly, PoseidonSharp"), PD_STR("GetVersionNative"), (void**)&p_assemblyFunctions->assemblyGetVersionNative);
		p_host->getUnmangedFunctionPtr(PD_STR("PoseidonSharp.native.PoseidonAssembly, PoseidonSharp"), PD_STR("GetClassesNative"), (void**)&p_assemblyFunctions->assemblyGetClassesNativePtr);

	}
}
