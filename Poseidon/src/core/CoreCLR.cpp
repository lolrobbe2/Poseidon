
#include "CoreCLR.h"
#include <thirdParty/coreclr/hostfxr.h>
#include <thirdParty/coreclr/coreclr_delegates.h>
#include <core/utils/dynamicLibrary.h>
#include <regex>
#include <iostream>
#include <codecvt>
#include <fstream>
#pragma warning(disable : 4966)

namespace poseidon::core
{
	static bool _init = false;
	static std::shared_ptr<platform::dynamicLibrary> _lib;
	static std::vector<std::shared_ptr<host>> registeredHosts;
	struct HostFxrFunctions
	{
		hostfxr_main_fn main = nullptr;
		hostfxr_main_startupinfo_fn mainStartupInfo = nullptr;
		hostfxr_main_bundle_startupinfo_fn mainBundleStartupinfo = nullptr;
		hostfxr_initialize_for_runtime_config_fn initializeForRuntimeConfig = nullptr;
		hostfxr_close_fn close = nullptr;
		hostfxr_get_runtime_delegate_fn getRuntimeDelegate = nullptr;
		operator bool() const { return main && mainStartupInfo && mainBundleStartupinfo && initializeForRuntimeConfig && getRuntimeDelegate; }
	};
	struct CoreCLRFunctions
	{

		load_assembly_and_get_function_pointer_fn loadAssemblyAndGetFunctionPointer = nullptr;
		
		operator bool() const { return loadAssemblyAndGetFunctionPointer; }
	};
	static HostFxrFunctions hostFxrFunc;
	static CoreCLRFunctions coreClrFunc;
	bool CoreCLR::init()
	{
		if (_init) return false;
		_init = true;
		_lib = std::make_shared<platform::dynamicLibrary>(getHostfxrPath().string() + "/hostfxr.dll");
		if (!_lib->isValid()) return false;
		HostFxr::loadFunctions();
		return true;
	}
	bool CoreCLR::shutdown()
	{
		if (!_init) return false;
		HostFxr::invalidateHosts();
		_lib.reset();
		_init = false;
		return true;
	}
	std::filesystem::path CoreCLR::getDotnetRoot()
	{
		const char* envPath = getenv("DOTNET_ROOT_X64");
		if (!envPath)
		{
			std::filesystem::path path = std::filesystem::path(std::getenv("ProgramFiles"));
			return path.string() + "/dotnet/";
		}
		return envPath;
	}
	std::filesystem::path CoreCLR::getCoreCLRPath()
	{
		return getLatestVersionDir((getDotnetRoot().string() + "shared/Microsoft.NETCore.App/"));
	}
	std::filesystem::path CoreCLR::getHostfxrPath()
	{
		return getLatestVersionDir((getDotnetRoot().string() + "host/fxr/"));
	}

	std::tuple<int, int, int> parseVersion(const std::string& versionStr)
	{
		std::regex versionRegex(R"((\d+)\.(\d+)\.(\d+))");
		std::smatch match;

		if (std::regex_match(versionStr, match, versionRegex))
		{
			int major = std::stoi(match[1]);
			int minor = std::stoi(match[2]);
			int patch = std::stoi(match[3]);
			return { major, minor, patch };
		}
		return { 0, 0, 0 };
	}

	std::filesystem::path CoreCLR::getLatestVersionDir(std::filesystem::path hostfxrPath)
	{
		std::vector<std::filesystem::path> versionDirs;
		for (const auto& entry : std::filesystem::directory_iterator(hostfxrPath))
		{
			if (entry.is_directory()) {
				std::string dirName = entry.path().filename().string();
				// Ensure the directory name is a valid version string before adding it
				if (std::regex_match(dirName, std::regex(R"(\d+\.\d+\.\d+)")))
					versionDirs.push_back(entry.path());

			}
		}


		// Sort directories by version number
		std::sort(versionDirs.begin(), versionDirs.end(), [](const std::filesystem::path& a, const std::filesystem::path& b) {
			return parseVersion(a.filename().string()) > parseVersion(b.filename().string());
			});
		return *versionDirs.begin();
	}

	bool CoreCLR::loadFunctions()
	{
		if (!hostFxrFunc || !_lib) return false;

	}

#pragma region hostfxr
	bool HostFxr::loadFunctions()
	{
		if (hostFxrFunc || !_lib) return false;
		hostFxrFunc.main = (hostfxr_main_fn)_lib->getProcAddress("hostfxr_main");
		hostFxrFunc.mainBundleStartupinfo = (hostfxr_main_bundle_startupinfo_fn)_lib->getProcAddress("hostfxr_main_bundle_startupinfo");
		hostFxrFunc.mainStartupInfo = (hostfxr_main_startupinfo_fn)_lib->getProcAddress("hostfxr_main_startupinfo");
		hostFxrFunc.initializeForRuntimeConfig = (hostfxr_initialize_for_runtime_config_fn)_lib->getProcAddress("hostfxr_initialize_for_runtime_config");
		hostFxrFunc.close = (hostfxr_close_fn)_lib->getProcAddress("hostfxr_close");
		hostFxrFunc.getRuntimeDelegate = (hostfxr_get_runtime_delegate_fn)_lib->getProcAddress("hostfxr_get_runtime_delegate");
		return true;
	}
	std::shared_ptr<host> HostFxr::getHost(std::filesystem::path& hostConfigJson)
	{
		hostHandle handle;
		initializeForRuntimeConfig((unsigned short*)std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(hostConfigJson.string()).c_str(), &handle);
		registeredHosts.push_back(std::make_shared<host>(handle));
		return registeredHosts.back();
	}
	std::shared_ptr<host> HostFxr::getHost()
	{
		std::ofstream file("poseidonRuntimeConfig.json");

		if (file.is_open())
		{
			file << R"({
				"runtimeOptions": {
				  "tfm": "net8.0",
				  "rollForward": "LatestMinor",
				  "framework": {
					"name": "Microsoft.NETCore.App",
					"version": "8.0.1"
				  }
				}
			  })";
			file.close();
		}
		std::filesystem::path configPath = "poseidonRuntimeConfig.json";
		return getHost(configPath);
	}
	int32_t HostFxr::main(const int argc, const unsigned short** argv)
	{
		return hostFxrFunc.main(argc,(const char_t**)argv);
	}
	int32_t HostFxr::mainStartupinfo(const int argc, const unsigned short** argv, const unsigned short* host_path, const unsigned short* dotnet_root, const unsigned short* app_path)
	{
		return hostFxrFunc.mainStartupInfo(argc, (const char_t**)argv, (const char_t*)host_path, (const char_t*)dotnet_root, (const char_t*)app_path);
	}
	int32_t HostFxr::mainbundleStartupinfo(const int argc, const unsigned short** argv, const unsigned short* host_path, const unsigned short* dotnet_root, const unsigned short* app_path, int64_t bundle_header_offset)
	{
		return hostFxrFunc.mainBundleStartupinfo(argc,(const char_t**)argv,(const char_t*)host_path,(const char_t*)dotnet_root,(const char_t*)app_path,bundle_header_offset);
	}
	int32_t HostFxr::initializeForRuntimeConfig(const unsigned short* runtime_config_path,hostHandle* handle)
	{
		hostfxr_initialize_parameters params = { sizeof(hostfxr_initialize_parameters), CoreCLR::getHostfxrPath().wstring().c_str(), CoreCLR::getDotnetRoot().wstring().c_str()};
		return hostFxrFunc.initializeForRuntimeConfig((char_t*)runtime_config_path, nullptr, handle);
	}
	int32_t HostFxr::close(const hostHandle handle)
	{
		if (!handle) throw new std::exception("[HostFxr] atempting to close invalid host!");
		return hostFxrFunc.close((const hostfxr_handle) handle);
	}
	void HostFxr::getRuntimeDelegate(const hostHandle handle, host::delegateType type, void** delegate)
	{
		hostFxrFunc.getRuntimeDelegate(handle,(hostfxr_delegate_type)type, delegate);
	}

	void HostFxr::invalidateHosts()
	{
		registeredHosts.clear();
	}
#pragma endregion
}
#pragma warning(pop)