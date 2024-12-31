#include <catch2/catch_all.hpp>
#include <poseidon.h>
TEST_CASE("when no assemblyLoader name is given the root assemblyGenerator is generated ","[AssemblyLoader]") {
	poseidon::core::CoreCLR::init();
	poseidon::r_host host = poseidon::core::HostFxr::getHost();
	poseidon::r_assemblyLoader assemblyLoader = host->getAssemblyLoader();
	REQUIRE(assemblyLoader->getName() == "root");
	poseidon::core::CoreCLR::shutdown();
}

TEST_CASE("when and assemblyLoader name is given the assemblyLoader name is correct", "[AssemblyLoader]") {
	poseidon::core::CoreCLR::init();
	poseidon::r_host host = poseidon::core::HostFxr::getHost();
	poseidon::r_assemblyLoader assemblyLoader = host->getAssemblyLoader("test name");
	REQUIRE(assemblyLoader->getName() == "test name");
	poseidon::core::CoreCLR::shutdown();
}