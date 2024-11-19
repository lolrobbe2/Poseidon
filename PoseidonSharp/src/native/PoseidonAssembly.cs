using PoseidonSharp.native.interop;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Threading.Tasks;

#nullable enable
namespace PoseidonSharp.native
{
   
    [StructLayout(LayoutKind.Sequential)]
    internal class PoseidonAssembly
    {
        static ConcurrentDictionary<UInt64, AssemblyClass> s_assemblyClassCache = new();
        static ConcurrentDictionary<UInt64, DateTime> s_accessTimeCache = new();
        private static Task? s_cleanupTask;
        private static readonly object s_cleanupLock = new object();
        private static bool s_cleanupRunning = false;
        public PoseidonAssembly(int contextId, int assemblyId)
        {
            m_ContextId = contextId;
            m_AssemblyId = assemblyId;
            StartCleanupTask();
        }
        private static UInt64 GenerateCacheKey(int assemblyId, string className)
        {
            return ((UInt64)(UInt32)assemblyId << 32) | (UInt64)(UInt32)className.GetHashCode();
        }

        public string? GetName()
        {
            return GetNative().GetName().Name;
        }
        public string GetVersionString()
        {
            return GetNative().GetName().Version!.ToString();
        }
        public interop.Version GetVersion()
        {
            return interop.Version.FromVersionNative(GetNative().GetName().Version);
        }
        public int GetClassCount() { return GetNative().GetTypes().Length; }
        public NativeArray<AssemblyClass> GetClasses()
        {
                return new NativeArray<AssemblyClass>(GetNative()
                    .GetTypes()
                    .Where(type => type.IsClass && !(type.Name.StartsWith('<') || type.Name.EndsWith('>')))
                    .Select(ClassType => new AssemblyClass(ClassType, m_ContextId, m_AssemblyId))
                    .ToArray());
        }
        public AssemblyClass? GetClassRaw(string name)
        {
            Type? type = GetNative().GetTypes().FirstOrDefault(type => type.IsClass && type.Name.Equals(name));
            if (type == null) return null;
            return new(type,m_ContextId,m_AssemblyId);
        }
        public AssemblyClass? GetClass(string name)
        {
            if (s_assemblyClassCache.TryGetValue(GenerateCacheKey(m_AssemblyId, name), out var assemblyClassCached)) { s_accessTimeCache[GenerateCacheKey(m_AssemblyId,name)] = DateTime.Now; return assemblyClassCached; }
            AssemblyClass? AssemblyClass = GetClassRaw(name);
            if(AssemblyClass == null) return null;
            s_assemblyClassCache[GenerateCacheKey(m_AssemblyId, name)] = (AssemblyClass)AssemblyClass;
            s_accessTimeCache[GenerateCacheKey(m_AssemblyId, name)] = DateTime.Now;
            return AssemblyClass;
        }

        // Timer callback for cleaning up old cache entries
        private static async Task CleanupTask()
        {
            while (true)
            {
                await Task.Delay(200); // Delay for 200 milliseconds before running cleanup

                DateTime now = DateTime.Now;
                List<UInt64> keysToRemove = new List<UInt64>();

                // Identify stale entries to remove
                foreach (var pair in s_accessTimeCache)
                {
                    if ((now - pair.Value).TotalSeconds > 10) // Remove entries not accessed in the last 10 seconds
                    {
                        keysToRemove.Add(pair.Key);
                    }
                }

                // Remove stale cache entries
                foreach (var key in keysToRemove)
                {
                    s_assemblyClassCache.TryRemove(key, out _);
                    s_accessTimeCache.TryRemove(key, out _);
                }
            }
        }

        private void StartCleanupTask()
        {
            if (!s_cleanupRunning)
            {
                lock (s_cleanupLock)
                {
                    // Check again in case another thread started it
                    if (!s_cleanupRunning)
                    {
                        s_cleanupRunning = true;
                        s_cleanupTask = Task.Run(async () => await CleanupTask());
                    }
                }
            }
        }

        [UnmanagedCallersOnly]
        internal static NativeString GetNameNative(int contextId, int assemblyId) { return new PoseidonAssembly(contextId, assemblyId).GetName(); }
        [UnmanagedCallersOnly]
        internal static NativeString GetVersionStringNative(int contextId, int assemblyId) { return new PoseidonAssembly(contextId, assemblyId).GetVersionString(); }
        [UnmanagedCallersOnly]
        internal static interop.Version GetVersionNative(int contextId, int assemblyId) { return new PoseidonAssembly(contextId, assemblyId).GetVersion(); }
        [UnmanagedCallersOnly]
        internal unsafe static IntPtr GetClassesNative(int contextId, int assemblyId) {
            NativeArray<AssemblyClass> array = new PoseidonAssembly(contextId, assemblyId).GetClasses();
            Console.WriteLine(array.Size);
            
           return array.ToIntptr();
        }
        private Assembly GetNative()
        {
            return AssemblyLoader.GetAssembly(m_ContextId, m_AssemblyId);
        }
        int m_AssemblyId;
        int m_ContextId;
    }
}
