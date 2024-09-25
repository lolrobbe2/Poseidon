#pragma once
#ifndef _PLATFORM_
#define _PLATFORM_
#if defined(_WIN32) || defined(_WIN64)
#define PD_PLATFORM_WINDOWS
#define PD_PLATFORM_NAME "windows"
#elif defined (macintosh) || defined(Macintosh) || defined(__APPLE__) ||defined(__MACH__)
#define PD_PLATFORM_MAC
#define PD_PLATFORM_NAME "macintosh"
#elif defined(__linux__ )|| defined(linux) ||defined( __linux)
#define PD_PLATFORM_LINUX
#define PD_PLATFORM_NAME "linux"
#endif // defined(_WIN32 || _WIN64)
#endif // !_PLATFORM_

#ifdef PD_PLATFORM_WINDOWS
#include <Windows.h>
#ifdef _WCHAR_T_DEFINED
typedef wchar_t char_t;
#else
typedef unsigned short char_t;
#endif
#endif

