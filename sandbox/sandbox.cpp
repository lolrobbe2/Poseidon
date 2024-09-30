#include <core/CoreCLR.h>
#include <iostream>


int main(int argc, char** argv) {
	poseidon::core::CoreCLR::init();
	//std::cout << poseidon::core::CoreCLR::getDotnetRoot() << std::endl;
	std::shared_ptr<poseidon::core::host> host = poseidon::core::HostFxr::getHost();
	std::cout << std::filesystem::current_path() << std::endl;
	std::cout << host->loadAssembly("./PoseidonSharp.dll") << std::endl;
	/*
	UnmanagedFunctionPtr function;
	 std::cout << host->getUnmangedFunctionPtr(PD_STR("PoseidonSharp.native.AssemblyLoader, PoseidonSharp"), PD_STR("MyUnmanagedMethod"),(void**) & function) << std::endl;
	std::cout << function() << std::endl;
	*/
	auto loader = host->getAssemblyLoader();
	auto assm = loader->loadAssembly("PoseidonSharp.dll");
}