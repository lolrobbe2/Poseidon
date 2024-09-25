#pragma once
#ifndef _CORE_CLR_
#define _CORE_CLR_
#include <filesystem>
#include "host.h"
namespace poseidon
{
	namespace core
	{
		class CoreCLR
		{
		public:
			static bool init();
			static bool shutdown();
			static std::filesystem::path getDotnetRoot();
			static std::filesystem::path getHostfxrPath();
			static std::filesystem::path getLatestHostfxrVersionDir(std::filesystem::path hostfxrPath);
		private:

		};
		class HostFxr
		{
		public:
			static bool loadFunctions();
			static std::shared_ptr<host> getHost(std::filesystem::path& hostConfigJson);
			static std::shared_ptr<host> getHost();
		protected:
			friend class host;
			//internall
			static int32_t main(const int argc, const unsigned short** argv);
			static int32_t mainStartupinfo(const int argc,
				const unsigned short** argv,
				const unsigned short* host_path,
				const unsigned short* dotnet_root,
				const unsigned short* app_path);
			static int32_t mainbundleStartupinfo(const int argc,
				const unsigned short** argv,
				const unsigned short* host_path,
				const unsigned short* dotnet_root,
				const unsigned short* app_path,
				int64_t bundle_header_offset);
			static int32_t initializeForRuntimeConfig(const unsigned short* runtime_config_path, hostHandle* handle);
			static int32_t close(hostHandle handle);
		};
	}
}
#endif // !_CORE_CLR_