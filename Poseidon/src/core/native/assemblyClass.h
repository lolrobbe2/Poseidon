#pragma once
#ifndef _ASSEMBLY_CLASS_
#define _ASSEMBLY_CLASS_
#include <core/native/interop/interop.h>
#include <core/native/refTypes.h>
#include <core/native/classField.h>
#pragma pack(push,1)
namespace poseidon::core
{
	class assemblyClass
	{
	public:
		static void loadFunctions(r_host host);
		const std::vector<field> getFields() const;
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