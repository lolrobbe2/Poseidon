#pragma once
#ifndef _HOST_
#define _HOST_
#include "delegates/hdtDelegates.h"
#include <core/native/AssemblyLoader.h>
#include <filesystem>
typedef void* hostHandle;
typedef int (PD_CALLTYPE* UnmanagedFunctionPtr)();
namespace poseidon::core
{
	struct hostFunctions
	{
	protected:
		friend class host;
		load_assembly_fn load_assembly_ptr = nullptr;
		get_function_pointer_fn get_function_pointer_ptr = nullptr;
		operator bool()const { return load_assembly_ptr && get_function_pointer_ptr; }
	};
	class host : public std::enable_shared_from_this<host>
	{
	public:
		enum hostres : int
		{
			success = 0,
			failure = 1,
			functions_not_initialized = 2,
			load_assembly_filenotfound = -2146233079,
			invalid_assembly_format = -2146234297,
			type_load = -2146233054
		};
		enum delegateType
		{
			com_activation,
			load_in_memory_assembly,
			winrt_activation,
			com_register,
			com_unregister,
			load_assembly_and_get_function_pointer,
			get_function_pointer,
			load_assembly,
			load_assembly_bytes,
		};
		host() = default;
		host(hostHandle handle) : m_handle(handle)
		{
			loadDelegates();
			loadAssembly("./PoseidonSharp.dll");
		}

		~host();
		const hostHandle native() const { return m_handle; }
		void release();
		/**
		 * @brief Finds a specified type in the default load context, locates the required method, and returns a native function pointer to that method.
		 *        The method's signature can be specified via a delegate type.
		 *
		 * @param typeName The assembly-qualified type name to find.
		 * @param methodName The name of the method on the specified type. The method must be static and must match the expected delegate signature.
		 *
		 * @return void* Returns a native function pointer to the requested managed method. The returned function pointer has the lifetime of the process
		 *         and can be used to call the method multiple times.
		 *
		 * @details
		 * This function looks up the specified type in the default load context (`AssemblyLoadContext.Default`) and returns the method specified by
		 * `methodName`. The method must match the delegate signature and be a static method. If the type and method require assemblies that haven't
		 * been loaded yet, the helper will resolve and load them from the default load context (typically from the Trusted Platform Assembly).
		 *
		 * If `typeName` or `methodName` refers to assemblies or types that are not present in the default load context, they must be resolvable from
		 * there. This function works best when the application is initialized via `hostfxr_initialize_for_dotnet_command_line`, as this ensures the
		 * application's assemblies are loaded in the default context.
		 *
		 * Currently, there's no way to release the function pointer after calling it, but this might be supported in the future.
		 */
		int getUnmangedFunctionPtr(const char_t* typeName, const char_t* methodName, void** function);
		bool isValid() const { return m_handle; }
		void getRuntimeDelegate(enum host::delegateType type, void** delegate);
		std::shared_ptr<native::assemblyLoader> getAssemblyLoader(const std::string& name = "root");
		hostres loadAssembly(std::filesystem::path path);
		operator bool() const { return m_handle; }
	private:

		hostFunctions functions;
		void loadDelegates();
		hostHandle m_handle;
	};

}
#endif // !_HOST_



