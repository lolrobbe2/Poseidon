#pragma once
#ifndef _GARBAGE_COLLECTOR_DELEGATES_
#define _GARBAGE_COLLECTOR_DELEGATES_
#include <core/utils/platform.h>
namespace poseidon::core 
{
	using f_collectGarbage = void(PD_CALLTYPE*)();
	using GChandle = void*;
	using f_unpinHandle = void(PD_CALLTYPE*)(GChandle);
}
#endif // !_GARBAGE_COLLECTOR_
