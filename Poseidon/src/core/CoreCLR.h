#pragma once
#ifndef _CORE_CLR_
#define _CORE_CLR_
#include <filesystem>
#include "host.h"
#include <core/native/refTypes.h>
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
			static std::filesystem::path getCoreCLRPath();
			static std::filesystem::path getHostfxrPath();
			static std::filesystem::path getLatestVersionDir(std::filesystem::path hostfxrPath);
			static bool loadFunctions();
		private:
			static inline bool m_init = false;
		};
		class HostFxr
		{
		public:
			static bool loadFunctions();
			static r_host getHost(std::filesystem::path& hostConfigJson);
			static r_host getHost();
		protected:
			friend class host;
			//internall
			static int32_t _main(const int argc, const unsigned short** argv);
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
			static void getRuntimeDelegate(const hostHandle handle,enum host::delegateType type,void** delegate);
			
		protected:
			friend class CoreCLR;
			static void invalidateHosts();
		};
	}
}
#endif // !_CORE_CLR_