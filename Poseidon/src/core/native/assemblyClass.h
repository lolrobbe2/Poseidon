#pragma once
#ifndef _ASSEMBLY_CLASS_
#define _ASSEMBLY_CLASS_
#include <core/native/interop/interop.h>
#include <core/native/refTypes.h>
#pragma pack(push,1)
namespace poseidon::core
{
	class host;
	class assemblyClass
	{
	public:
		static void loadFunctions(r_host host);
	private:
		const nativeString name;
		const nativeString nameSpace;
		const nativeString assemblyName;
		const int m_contextId;
		const int m_assemblyId;
	};
}
#endif // !_ASSEMBLY_CLASS_
#pragma pack(pop)