#pragma once
#ifndef _NATIVE_VERSION_
#define _NATIVE_VERSION_
#include <cstdint>
#pragma pack(push, 1)
struct nativeVersion
{
    uint32_t Major;
    uint32_t Minor;
    uint32_t Build;
    uint32_t Revision;
};
#pragma pack(pop)

#endif // !_NATIVE_VERSION_
