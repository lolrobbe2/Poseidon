#pragma once
#ifndef _ASSEMBLY_DELEGATES_
#define _ASSEMBLY_DELEGATES_
#pragma once
#include <core/native/interop/interop.h>
#include <core/utils/platform.h>
#include <core/native/assemblyClass.h>
namespace poseidon::core 
{
	using f_assemblyGetNameNative = nativeString(PD_CALLTYPE*)(int contextId, int assemblyId);
	using f_assemblyGetVersionStringNative = nativeString(PD_CALLTYPE*)(int contextId, int assemblyId);
	using f_assemblyGetVersionNative = nativeVersion(PD_CALLTYPE*)(int contextId, int assemblyId);
	using f_assemblyGetClassesNative = nativeArray<assemblyClass>*(PD_CALLTYPE*)(int contextId, int assemblyId);

}
#endif // !_ASSEMBLY_DELEGATES_
