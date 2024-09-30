#pragma once
#include <core/native/interop/nativeString.h>
#include <core/utils/platform.h>
namespace poseidon::core
{
	using f_createContext = int (PD_CALLTYPE*)(nativeString string);
	using f_loadAssembly = int (PD_CALLTYPE*)(int contextId, nativeString path);
}