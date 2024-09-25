#include <core/CoreCLR.h>
#include <iostream>


int main(int argc, char** argv) {
	poseidon::core::CoreCLR::init();
	std::cout << poseidon::core::CoreCLR::getDotnetRoot() << std::endl;
	std::shared_ptr<poseidon::core::host> host = poseidon::core::HostFxr::getHost();
	host->isValid();
}