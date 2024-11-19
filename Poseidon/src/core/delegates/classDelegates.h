#pragma once
#ifndef _CLASS_DELEGATES_
#define _CLASS_DELEGATES_
#include <core/utils/platform.h>
#include <core/native/interop/nativeString.h>
#include <core/native/classField.h>

namespace poseidon::core 
{
	using f_getFieldsNative = nativeArray<field>*(PD_CALLTYPE*)(int contextId, int assemblyId, nativeString name);
}
#endif // !_CLASS_DELEGATES_
