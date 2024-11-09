#pragma once
#ifndef _ASSEMBLY_
#define _ASSEMBLY_
#include <string>
#include <memory>
#include <core/native/interop/interop.h>
#include "assemblyClass.h"
#include <core/host.h>
namespace poseidon::core::native
{
	class assembly
	{
	public:
		enum assemblyLoadRes : int
		{
			failure = -1,
			badILformat = -2,
			badPath = -3,
			fileNotFound = -4
		};
		assembly() = default;
		assembly(r_host host,int assemblyId,int contextId);
		assembly(const assembly& other);
		operator bool() const { return isValid(); }
		bool isValid() const { return m_assemblyId > 0; }
		const assemblyLoadRes getResult();
		const std::string getErrorString();
		
		const std::string getName();

		const std::string getVersionString();
		const nativeVersion getVersion();
		const std::vector<assemblyClass> getClasses();
		~assembly()
		{
		}
	private:
		void loadFunctions();
	private:
		r_host host;
		int m_assemblyId;
		int m_contextId;
	};

}
#endif // !_ASSEMBLY_
