#include "assemblyClass.h"
#include <core/delegates/classDelegates.h>
#include <core/host.h>
namespace poseidon::core
{
	struct assemblyClassFunctions
	{
		f_getFieldsNative assemblyClassGetFieldsNative = nullptr;
	};
	static assemblyClassFunctions* p_assemblyClassFunctionsPtr = nullptr;
	void assemblyClass::loadFunctions(r_host host)
	{
		if (p_assemblyClassFunctionsPtr) return;
		p_assemblyClassFunctionsPtr = new assemblyClassFunctions();

		host->getUnmangedFunctionPtr(PD_STR("PoseidonSharp.native.AssemblyClass, PoseidonSharp"), PD_STR("GetFieldsNative"), (void**)&p_assemblyClassFunctionsPtr->assemblyClassGetFieldsNative);
	}

	const std::vector<field> assemblyClass::getFields() const
	{
		std::string _nameSpace = nameSpace;
		std::string _name = name;
		std::string _assemblyName = assemblyName;
		std::string typeName = _nameSpace + "." + _name + ", " + _assemblyName;
		nativeString nativeTypeName{ typeName };
		return p_assemblyClassFunctionsPtr->assemblyClassGetFieldsNative(m_contextId,m_assemblyId,nativeTypeName)->toVector();
	}
}