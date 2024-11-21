#include <catch2/catch_all.hpp>
#include <poseidon.h>
TEST_CASE("when no assemblyLoader name is given the root assembly is generated ","[AssemblyLoader]") {
	poseidon::core::CoreCLR::init();
	poseidon::r_host host = poseidon::core::HostFxr::getHost();
	poseidon::r_assemblyLoader assemblyLoader = host->getAssemblyLoader();
	REQUIRE(assemblyLoader->getName() == "root");
	poseidon::core::CoreCLR::shutdown();
}