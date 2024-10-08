#pragma once
#ifndef _GARBAGE_COLLECTOR_
#define _GARBAGE_COLLECTOR_
#include <memory>

#include <core/utils/platform.h>
namespace poseidon::core 
{
	class host;
	class garbageCollector
	{
	public:
		/**
		* @brief forces an immediate garbage collection of all generations
		* @
		*/
		void collect();
		void unpinHandle(void* handle);
	protected:
		friend class host;
		garbageCollector(std::shared_ptr<host> p_host);

	

	private:
		std::shared_ptr<host> p_host;
	};

}
#endif // !_GARBAGE_COLLECTOR_
