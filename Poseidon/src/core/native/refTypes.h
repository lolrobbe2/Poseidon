#pragma once
#ifndef _REF_TYPES_
#define _REF_TYPES
#include <memory>
/**
* these are the reference types for all the native classes
*/

namespace poseidon::core {
	class host;
	class garbageCollector;
}
namespace poseidon::core::native {
	class assembly;
	class assemblyLoader;
}
namespace poseidon {
	typedef std::shared_ptr<core::host> r_host;
	typedef std::shared_ptr<core::native::assembly> r_assembly;
	typedef std::shared_ptr<core::native::assemblyLoader> r_assemblyLoader;

	typedef std::shared_ptr<core::garbageCollector> r_garbageCollector;
}
#endif // !_REF_TYPES_
