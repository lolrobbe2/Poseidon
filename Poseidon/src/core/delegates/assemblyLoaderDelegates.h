#pragma once
#include <core/native/interop/nativeString.h>
#include <core/utils/platform.h>
namespace poseidon::core
{
	using createContextFunc = int (PD_CALLTYPE*)(nativeString string);
	typedef int (PD_CALLTYPE* loadAssemblyFunc)(int contextId, nativeString path);
}