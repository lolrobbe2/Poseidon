#pragma once
#ifndef _GARBAGE_COLLECTOR_
#define _GARBAGE_COLLECTOR_
#include <memory>
#include <core/utils/platform.h>
#include <core/native/refTypes.h>
namespace poseidon::core 
{
	struct garbageCollectorFunctions;
	class garbageCollector
	{
	public:
		/**
		* @brief forces an immediate garbage collection of all generations
		* @
		*/
		void collect() const;
		void unpinHandle(void* handle) const;

		garbageCollector(r_host host);
	private:
		r_host p_host;
		garbageCollectorFunctions* p_garbageCollectorFunctions = nullptr;
	};

}
#endif // !_GARBAGE_COLLECTOR_
