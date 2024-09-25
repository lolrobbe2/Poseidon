#include "dynamicLibrary.h"
#include <iostream>
namespace poseidon
{
	namespace platform
	{
		dynamicLibrary::dynamicLibrary(std::filesystem::path path) : m_handle(LOAD_DYLIB(path.c_str()))
		{
		}
		dynamicLibrary::dynamicLibrary(dyLibHandle handle) : m_handle(handle)
		{
			
		}
		dynamicLibrary::~dynamicLibrary()
		{
			CLOSE_DYLIB(m_handle);
		}
		procAddress dynamicLibrary::getProcAddress(const std::string& functionName)
		{
			procAddress proc = GET_PROC_ADDRESS(functionName.c_str());
			std::cout << "[dynamicLibrary] unable to load procedure!" << std::endl;
			return proc;
		}
	}
}
