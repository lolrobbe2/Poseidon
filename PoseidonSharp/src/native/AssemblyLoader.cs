using PoseidonSharp.native.interop;
using System;
using System.Collections.Generic;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Runtime.Loader;
namespace PoseidonSharp.native
{
    public static class AssemblyLoader
    {
        static private Dictionary<int, Assembly> loadedAssemblies = new();
        static private Dictionary<int,AssemblyLoadContext> assemblyLoadContexts = new();

        [UnmanagedCallersOnly]
        internal static int CreateContext(NativeString name)
        {
            AssemblyLoadContext context = new AssemblyLoadContext(name, true);
            if(assemblyLoadContexts.ContainsKey(context.GetHashCode())) return context.GetHashCode();
            assemblyLoadContexts.Add(context.GetHashCode(), context);
            return context.GetHashCode();
        }

        [UnmanagedCallersOnly]
        internal static int LoadAssembly(int loadAssemblyContextId, NativeString path)
        {
            Assembly asm = assemblyLoadContexts[loadAssemblyContextId].LoadFromAssemblyPath(path);
            if (loadedAssemblies.ContainsKey(asm.GetHashCode())) return asm.GetHashCode();
            loadedAssemblies.Add(asm.GetHashCode(), asm);
            return asm.GetHashCode();
        }

        internal static Assembly GetAssembly(int assemblyId)
        {
            return loadedAssemblies[assemblyId];
        }
    }
}
