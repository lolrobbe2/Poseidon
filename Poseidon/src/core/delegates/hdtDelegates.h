#pragma once
#ifndef _HDT_DELEGATES_
#define _HDT_DELEGATES_
#include <core/utils/platform.h>
namespace poseidon 
{
    /**
     * @brief Loads a managed assembly by its path into the default load context using the runtime delegate type `hdt_load_assembly`.
     *
     * @param assembly_path The path to the assembly to load. The path must meet the same requirements as the `assemblyPath`
     *        parameter of `AssemblyLoadContext.LoadFromAssemblyPath`. This path will also be used for dependency resolution
     *        via any `.deps.json` corresponding to the assembly.
     * @param load_context The load context in which the assembly will be loaded. For .NET 8, this parameter must be `nullptr`,
     *        and the assembly will be loaded only in the default load context.
     * @param reserved A reserved parameter for future extensibility. Currently, this must be `nullptr`.
     *
     * @return int Returns a status code indicating success or failure of the assembly loading operation.
     *
     * @details
     * Calling `hostfxr_get_runtime_delegate(handle, hdt_load_assembly, &helper)` returns a function pointer to this runtime helper.
     * The function will load the specified assembly into the default load context using `AssemblyDependencyResolver`
     * to register additional dependency resolution for that context.
     *
     * This function works by resolving the assembly path and loading it into the default load context. The function also supports
     * dependency resolution via any `.deps.json` file that corresponds to the specified assembly. It leverages the
     * `AssemblyDependencyResolver` class for this purpose.
     *
     * Like the other helpers, this function must be called with valid parameters, where `assembly_path` specifies a valid path
     * to the managed assembly, `load_context` is `nullptr` (for .NET 8), and `reserved` is `nullptr`.
     */
    typedef int(PD_CALLTYPE* load_assembly_fn)(
        const char_t* assembly_path,
        void* load_context,
        void* reserved);
    /**
     * @brief Finds a specified type in the default load context, locates the required method on it,
     * and returns a native function pointer to that method. The method's signature can be specified via the delegate type name.
     *
     * @param type_name Assembly qualified type name to find.
     * @param method_name Name of the method on the specified type. The method must be static and match the signature of the delegate_type_name.
     * @param delegate_type_name Assembly qualified delegate type name representing the method signature.
     *        If this is `nullptr`, the method signature is assumed to be:
     *        - `public delegate int ComponentEntryPoint(IntPtr args, int sizeBytes);`
     *        which maps to the native signature:
     *        - `int component_entry_point_fn(void *arg, int32_t arg_size_in_bytes);`
     *        Alternatively, it can be specified as `UNMANAGEDCALLERSONLY_METHOD` (defined as `(const char_t*)-1`),
     *        meaning the managed method is marked with the `UnmanagedCallersOnlyAttribute`.
     * @param load_context Reserved for specifying the load context used to locate the type and method.
     *        For .NET 5, this must be `nullptr`, and the API will locate the type/method in the default load context.
     * @param reserved Reserved for future use. Must currently be `nullptr`.
     * @param delegate Output parameter that will receive the native function pointer to the requested managed method.
     *
     * @details
     * The helper function looks up the `type_name` in the default load context (`AssemblyLoadContext.Default`)
     * and returns the specified method. If the type and method require assemblies that haven't been loaded in the
     * default ALC yet, they will be resolved and loaded there (likely from the Trusted Platform Assembly).
     *
     * This function only works in the default load context. No additional assembly resolution logic is registered.
     * It is allowed to call the helper in any valid host context but is typically used in contexts initialized
     * via `hostfxr_initialize_for_dotnet_command_line`, as in that case the application code is available in the default load context.
     *
     * Contexts initialized via `hostfxr_initialize_for_runtime_config` only load framework assemblies in the default load context,
     * meaning `type_name` must resolve to a type in one of those framework assemblies.
     *
     * The returned native function pointer has the lifetime of the process and can be called multiple times.
     * Currently, there is no way to release the native function pointer, but this functionality may be added in future versions.
     */
    typedef int (PD_CALLTYPE* get_function_pointer_fn)(
        const char_t* type_name,
        const char_t* method_name,
        const char_t* delegate_type_name,
        void* load_context,
        void* reserved,
        /*out*/ void** delegate);
}
#endif // !_HDT_DELEGATES_
