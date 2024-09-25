#pragma once
#ifndef _POSEIDON_TEST_
#define _POSEIDON_TEST_
#include <catch2/catch_all.hpp>
#include <core/test_coreCLR.h>
#include <iostream>

int main(int argc, char** argv) {
	Catch::Session session; // There must be exactly one instance

	// writing to session.configData() here sets defaults
	// this is the preferred way to set them
	bool verbose = true;

	const char* args[] = { "--success", NULL }; // NULL-terminated array

	int returnCode = session.applyCommandLine(1, args);
	if (returnCode != 0) // Indicates a command line error
		return returnCode;

	// writing to session.configData() or session.Config() here
	// overrides command line args
	// only do this if you know you need to

	int numFailed = session.run();
	std::cout << "Press Enter to exit...";
	std::cin.ignore();  // Ignore the newline character left in the buffer
	std::cin.get();     // Wait for user to press Enter
	// numFailed is clamped to 255 as some unices only use the lower 8 bits.
	// This clamping has already been applied, so just return it here
	// You can also do any post run clean-up here
	return numFailed;
}
#endif // !_POSEIDON_TEST_
