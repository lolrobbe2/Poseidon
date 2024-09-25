#pragma once
#include <catch2/catch_all.hpp>
#include <poseidon.h>
TEST_CASE("CoreCLR_getHostfxrPath must return a valid path when hostfxr is installed") {
	REQUIRE(std::filesystem::exists(poseidon::core::CoreCLR::getHostfxrPath()));
}

TEST_CASE("CoreCLR_init init returns true when not initialized") {
	REQUIRE(poseidon::core::CoreCLR::init());
	poseidon::core::CoreCLR::shutdown();
}
TEST_CASE("CoreCLR_init init returns false when initialized") {
	poseidon::core::CoreCLR::init();
	REQUIRE_FALSE(poseidon::core::CoreCLR::init());
	poseidon::core::CoreCLR::shutdown();
}
TEST_CASE("Hostfxr_loadfunctions Hostfxr loadfunctions fails when _lib is not valid") {
	REQUIRE_FALSE(poseidon::core::HostFxr::loadFunctions());
}