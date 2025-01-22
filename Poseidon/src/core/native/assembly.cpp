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
	
	assembly::assembly(r_host host, int assemblyId, int contextId) : host(host), m_assemblyId(assemblyId), m_contextId(contextId) {
		if (!isValid()) {
			switch ((assembly::assemblyLoadRes) assemblyId)
			{
			case assemblyLoadRes::failure:
				throw std::exception("[assembly] was unable to load: failure");
				break;
			case assemblyLoadRes::fileNotFound:
				throw std::filesystem::filesystem_error(
					"[assmbly] asembly not found!",
					std::error_code(static_cast<int>(std::errc::no_such_file_or_directory), std::generic_category())
				);
				break;
			case assemblyLoadRes::badPath:
				throw std::invalid_argument("[assembly] provided path was invalid");
				break;
			case assemblyLoadRes::badILformat:
				throw std::runtime_error("[assembly] The .NET assembly has a bad or corrupt IL format.");
				break;
			}
		}
		loadFunctions(); 
	}

	
	
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
		host->getUnmangedFunctionPtr(PD_STR("PoseidonSharp.native.PoseidonAssembly, PoseidonSharp"), PD_STR("GetNameNative"), (void**)&p_assemblyFunctions->assemblyGetNameNativePtr);
		host->getUnmangedFunctionPtr(PD_STR("PoseidonSharp.native.PoseidonAssembly, PoseidonSharp"), PD_STR("GetVersionStringNative"), (void**)&p_assemblyFunctions->assemblyGetVersionNativeString);
		host->getUnmangedFunctionPtr(PD_STR("PoseidonSharp.native.PoseidonAssembly, PoseidonSharp"), PD_STR("GetVersionNative"), (void**)&p_assemblyFunctions->assemblyGetVersionNative);
		host->getUnmangedFunctionPtr(PD_STR("PoseidonSharp.native.PoseidonAssembly, PoseidonSharp"), PD_STR("GetClassesNative"), (void**)&p_assemblyFunctions->assemblyGetClassesNativePtr);
		assemblyClass::loadFunctions(host);
	}
}
