#pragma once
#ifndef _ASSEMBLY_DELEGATES_
#define _ASSEMBLY_DELEGATES_
#pragma once
#include <core/native/interop/nativeString.h>
#include <core/utils/platform.h>
namespace poseidon::core 
{
	using f_assemblyGetNameNative = nativeString(PD_CALLTYPE*)(int contextId, int assemblyId);
}
#endif // !_ASSEMBLY_DELEGATES_
