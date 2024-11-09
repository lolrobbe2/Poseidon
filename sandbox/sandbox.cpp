#include <core/CoreCLR.h>
#include <iostream>
#include <core/native/assemblyClass.h>
#include <core/native/AssemblyLoader.h>

	int main(int argc, char** argv) {
		poseidon::core::CoreCLR::init();
		std::cout << poseidon::core::CoreCLR::getDotnetRoot() << std::endl;
		poseidon::r_host host = poseidon::core::HostFxr::getHost();
		
		poseidon::r_assemblyLoader loader = host->getAssemblyLoader();
		auto assm = loader->loadAssembly("PoseidonSharp.dll");

		const std::vector<poseidon::core::assemblyClass>classes = assm->getClasses();
		//host->getGarbageCollector()->collect();

		poseidon::core::CoreCLR::shutdown();
		return 0;
	}
