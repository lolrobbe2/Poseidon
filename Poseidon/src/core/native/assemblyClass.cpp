#include "assemblyClass.h"
#include <core/delegates/classDelegates.h>
#include <core/host.h>
namespace poseidon::core
{
	struct assemblyClassFunctions
	{
	};
	static assemblyClassFunctions* p_assemblyClassFunctionsPtr = nullptr;
	void assemblyClass::loadFunctions(r_host host)
	{
		if (p_assemblyClassFunctionsPtr) return;
		p_assemblyClassFunctionsPtr = new assemblyClassFunctions();
	}
}