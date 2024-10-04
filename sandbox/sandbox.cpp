#include <core/CoreCLR.h>
#include <iostream>
#include <core/native/assemblyClass.h>

int main(int argc, char** argv) {
	poseidon::core::CoreCLR::init();
	//std::cout << poseidon::core::CoreCLR::getDotnetRoot() << std::endl;
	std::shared_ptr<poseidon::core::host> host = poseidon::core::HostFxr::getHost();
	std::shared_ptr<poseidon::core::native::assemblyLoader> loader = host->getAssemblyLoader();
	auto assm = loader->loadAssembly("PoseidonSharp.dll");
	if (!assm->isValid())
		std::cout << assm->getErrorString() << std::endl;
	const std::vector<poseidon::core::assemblyClass>classes = assm->getClasses();
}