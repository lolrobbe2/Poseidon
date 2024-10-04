#pragma once
#include "platform.h"
#include <optional>
#include <string>
#include <string>
#include <cassert>
#include <memory>

#ifdef _CODECVT_  /// deprected in c++ 17
_STL_DISABLE_DEPRECATED_WARNING
_NODISCARD std::optional<std::wstring> StrA2W(const std::string& Data)
{
    assert(Data.length() > 0);
    if (Data.length() == 0) {
        return std::nullopt;
    }
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    return converterX.from_bytes(Data);
}

_NODISCARD std::optional<std::string>  StrW2A(const std::wstring& Data)
{
    assert(Data.length() > 0);
    if (Data.length() == 0) {
        return std::nullopt;
    }
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    return converterX.to_bytes(Data);
}
_STL_RESTORE_DEPRECATED_WARNING
#else
std::optional<std::string> StrW2A(const std::wstring & Data) { // convert from LPWSTR to LPSTR
    assert(Data.length() > 0);
    if (Data.length() == 0) {
        return std::nullopt;
    }
    UINT acp = GetACP();
    int buflen = WideCharToMultiByte(acp, 0, Data.c_str(), -1, nullptr, 0, nullptr, nullptr) + 8;
    auto dest = std::make_unique<char[]>(buflen);
    int buflen2 = WideCharToMultiByte(acp, 0, Data.c_str(), -1, dest.get(), buflen, NULL, NULL) + 8;
    assert(buflen == buflen2);
    if (buflen == buflen2)
        return dest.get();
    return std::nullopt;
}

_NODISCARD std::optional<std::wstring> StrA2W(const std::string& Data) { // convert from LPSTR to LPWSTR
    assert(Data.length() > 0);
    if (Data.length() == 0) {
        return std::nullopt;
    }
    UINT acp = GetACP();
    auto buflen = MultiByteToWideChar(acp, 0, Data.c_str(), -1, nullptr, 0) + 8;
    auto dest = std::make_unique<wchar_t[]>(buflen);
    auto buflen2 = (MultiByteToWideChar(acp, 0, Data.c_str(), -1, dest.get(), buflen) + 8);
    assert(buflen == buflen2);
    if (buflen == buflen2)
        return dest.get();
    return std::nullopt;
}
#endif