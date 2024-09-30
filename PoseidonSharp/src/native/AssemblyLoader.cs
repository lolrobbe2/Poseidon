using PoseidonSharp.native.interop;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Runtime.Loader;
using System.Threading;
namespace PoseidonSharp.native
{
    public static class AssemblyLoader
    {
        public enum AssemblyLoadRes : int
        {
            failure = -1,
            badILformat = -2,
            badPath = -3
        }
        private static readonly Dictionary<int, Assembly> s_AssemblyCache = new();

        static private Dictionary<int, Assembly> s_loadedAssembliesCache = new();
        static private Dictionary<int,AssemblyLoadContext> assemblyLoadContexts = new();

        private static Timer _cacheClearTimer;  // Timer to clear the cache

        static AssemblyLoader()
        {
            _cacheClearTimer = new Timer(ClearCache, null, TimeSpan.Zero, TimeSpan.FromMinutes(1));
        }

        [UnmanagedCallersOnly]
        internal static int CreateContext(NativeString name)
        {
            AssemblyLoadContext context = new AssemblyLoadContext(name, true);
            if(assemblyLoadContexts.ContainsKey(context.GetHashCode())) return context.GetHashCode();
            assemblyLoadContexts.Add(context.GetHashCode(), context);
            
            return context.GetHashCode();
        }

        [UnmanagedCallersOnly]
        internal static AssemblyLoadRes LoadAssembly(int loadAssemblyContextId, NativeString path)
        {
            Console.WriteLine(path);
            try
            {
                Assembly asm = assemblyLoadContexts[loadAssemblyContextId].LoadFromAssemblyPath(path);
                s_AssemblyCache.Add(loadAssemblyContextId, asm);
                return (AssemblyLoadRes)asm.GetHashCode();
            }
            catch (BadImageFormatException e) { return AssemblyLoadRes.badILformat; }
            catch (ArgumentException e) { Console.WriteLine(e.ToString()); }
            return AssemblyLoadRes.failure;
        }

        internal static Assembly GetAssembly(int loadAssemblyContextId,int assemblyId)
        {
            if(s_AssemblyCache.TryGetValue(loadAssemblyContextId, out Assembly asm)) return asm;
            return assemblyLoadContexts[loadAssemblyContextId].Assemblies.FirstOrDefault(a => a.GetHashCode() == assemblyId); ;
        }
        private static void ClearCache(object state)
        {
            s_AssemblyCache.Clear();
        }
    }
}
