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

		host->getUnmangedFunctionPtr(PD_STR("PoseidonSharp.native.Field, PoseidonSharp"), PD_STR("GetFieldsNative"), (void**)p_assemblyClassFunctionsPtr->assemblyClassGetFieldsNative);
	}

	const std::vector<field> assemblyClass::getFields() const
	{
		return p_assemblyClassFunctionsPtr->assemblyClassGetFieldsNative(m_contextId,m_assemblyId,name)->toVector();
	}
}