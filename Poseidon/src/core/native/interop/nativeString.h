#pragma once
#ifndef _NATIVE_STRING_
#define _NATIVE_STRING_


#include <iostream>
#include <cstring>  // For string operations
#include <cstdlib>  // For malloc and free

#pragma pack(push, 1)
struct nativeString
{
private:
    char* m_NativeString; // Pointer to dynamically allocated string
    uint32_t m_IsDisposed = true;    // Disposal flag

public: 
    // Constructor - Initializes with a C-style string (nullptr if not provided)
    nativeString(const char* str = nullptr) : m_NativeString(nullptr), m_IsDisposed(false)
    {
        if (!str) return;
        
        // Allocate memory and copy the input string
        m_NativeString = (char*)malloc(strlen(str) + 1);
        
        if (!m_NativeString) return;

        strcpy_s(m_NativeString, strlen(str) + 1, str);

    }
    nativeString(const std::string& str) : nativeString(str.c_str()){

    }

    // Destructor - Calls Dispose to clean up the allocated memory
    ~nativeString()
    {
        Dispose(); // Ensure memory is freed when object is destroyed
    }

    // Dispose method - Frees the allocated memory
    void Dispose()
    {
        if (m_IsDisposed || !m_NativeString) return;
        free(m_NativeString);       // Free the memory allocated for the string
        m_NativeString = nullptr;   // Set the pointer to nullptr
        m_IsDisposed = true;            // Mark as disposed
    }

    // Implicit conversion to std::string for easy use in C++
    operator std::string() const
    {
        return m_NativeString ? std::string(m_NativeString) : std::string();
    }

    // Implicit conversion from std::string to nativeString
    static nativeString FromString(const std::string& str)
    {
        return nativeString(str.c_str());
    }

    // Implicit conversion from nativeString to std::string
    static std::string ToString(const nativeString& nativeStr)
    {
        return nativeStr.m_NativeString ? std::string(nativeStr.m_NativeString) : std::string();
    }
};
#pragma pack(pop)
#endif // !_NATIVE_STRING_
