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

TEST_CASE("Host hosts are invalidated after CoreCLR shutdown"){
	poseidon::core::CoreCLR::init();
	std::shared_ptr<poseidon::core::host> host = poseidon::core::HostFxr::getHost();
	poseidon::core::CoreCLR::shutdown();
	REQUIRE_FALSE(host->isValid());
}

TEST_CASE("Host host can be release manually") {
	REQUIRE_NOTHROW([&]() {
		poseidon::core::CoreCLR::init();
		std::shared_ptr<poseidon::core::host> host = poseidon::core::HostFxr::getHost();
		host->release();
		REQUIRE_FALSE(host->isValid());
		poseidon::core::CoreCLR::shutdown();
		}());
}