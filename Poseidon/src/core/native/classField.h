#pragma once
#ifndef _CLASS_FIELD_
#define _CLASS_FIELD_
#include <core/native/interop/interop.h>
#include <core/native/refTypes.h>
#pragma pack(push,1)
namespace poseidon::core 
{
    enum fieldAttributes
    {
        //
        // Summary:
        //     Specifies that the field cannot be referenced.
        PrivateScope = 0,
        //
        // Summary:
        //     Specifies that the field is accessible only by the parent type.
        Private = 1,
        //
        // Summary:
        //     Specifies that the field is accessible only by subtypes in this assembly.
        FamANDAssem = 2,
        //
        // Summary:
        //     Specifies that the field is accessible throughout the assembly.
        Assembly = 3,
        //
        // Summary:
        //     Specifies that the field is accessible only by type and subtypes.
        Family = 4,
        //
        // Summary:
        //     Specifies that the field is accessible by subtypes anywhere, as well as throughout
        //     this assembly.
        FamORAssem = 5,
        //
        // Summary:
        //     Specifies that the field is accessible by any member for whom this scope is visible.
        Public = 6,
        //
        // Summary:
        //     Specifies the access level of a given field.
        FieldAccessMask = 7,
        //
        // Summary:
        //     Specifies that the field represents the defined type, or else it is per-instance.
        Static = 16,
        //
        // Summary:
        //     Specifies that the field is initialized only, and can be set only in the body
        //     of a constructor.
        InitOnly = 32,
        //
        // Summary:
        //     Specifies that the field's value is a compile-time (static or early bound) constant.
        //     Any attempt to set it throws a System.FieldAccessException.
        Literal = 64,
        //
        // Summary:
        //     Specifies that the field does not have to be serialized when the type is remoted.
        NotSerialized = 128,
        //
        // Summary:
        //     Specifies that the field has a relative virtual address (RVA). The RVA is the
        //     location of the method body in the current image, as an address relative to the
        //     start of the image file in which it is located.
        HasFieldRVA = 256,
        //
        // Summary:
        //     Specifies a special method, with the name describing how the method is special.
        SpecialName = 512,
        //
        // Summary:
        //     Specifies that the common language runtime (metadata internal APIs) should check
        //     the name encoding.
        RTSpecialName = 1024,
        //
        // Summary:
        //     Specifies that the field has marshaling information.
        HasFieldMarshal = 4096,
        //
        // Summary:
        //     Reserved for future use.
        PinvokeImpl = 8192,
        //
        // Summary:
        //     Specifies that the field has a default value.
        HasDefault = 32768,
        //
        // Summary:
        //     Reserved.
        ReservedMask = 38144
    };

    using runtimeFieldHandle = void*;

	class field 
	{
    public:
        static void loadFunctions(r_host host);
    private:
        const nativeString name;
        const runtimeFieldHandle fieldHandle;
	};
}
#pragma pack(pop)
#endif // !_CLASS_FIELD_
