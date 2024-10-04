#pragma once
#ifndef _NATIVE_ARRAY_
#define _NATIVE_ARRAY_
#include <exception>
#include <vector>
#pragma pack(push, 1)
/*
* @brief this class allows you to change the values of a C# array (you cannot resize the array
*/
template<typename TYPE>
struct nativeArray
{
private:
	int32_t size;
	void* handle;
	TYPE* p_array;

public:
	TYPE& get(int index) const { if (index >= size) { throw new std::exception("[NativeArray] index out of bounds"); } return p_array[index]; }
	TYPE& operator[](int index) const { return get(index); }
	const size_t getSize() const { return size; }
	operator const size_t() const { return size; }
	const std::vector<TYPE> toVector() const { return std::vector<TYPE>(p_array, p_array + size); }
	operator const std::vector<TYPE>() const { return toVector(); }

};
#pragma pack(pop)

#endif // !_NATIVE_ARRAY_
