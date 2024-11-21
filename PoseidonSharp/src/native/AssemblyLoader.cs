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
            badPath = -3,
            fileNotFound = -4,
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
        internal static void ReleaseContext(int loadAssemblyContextId)
        {
            if (assemblyLoadContexts.ContainsKey(loadAssemblyContextId))
                assemblyLoadContexts.Remove(loadAssemblyContextId);
        }
        [UnmanagedCallersOnly]
        internal static AssemblyLoadRes LoadAssembly(int loadAssemblyContextId, NativeString path)
        {
            try
            {
                Assembly asm = assemblyLoadContexts[loadAssemblyContextId].LoadFromAssemblyPath(path);
                s_AssemblyCache.Add(loadAssemblyContextId, asm);
                return (AssemblyLoadRes)asm.GetHashCode();
            }
            catch (BadImageFormatException) { return AssemblyLoadRes.badILformat; }
            catch (ArgumentException) { return AssemblyLoadRes.badPath; }
            catch (System.IO.FileNotFoundException) { return AssemblyLoadRes.fileNotFound; }
            catch (Exception) { return AssemblyLoadRes.failure; }
        }

        [UnmanagedCallersOnly]
        internal static NativeString GetName(int loadAssemblyContextId)
        {
            try
            {
                NativeString assemblyLoadContext = assemblyLoadContexts[loadAssemblyContextId].Name;
                assemblyLoadContext.setManaged(true);
                return assemblyLoadContext;
            }
            catch (Exception)
            {
                NativeString res = "";
                res.setManaged(true);
                return res;
            }
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
