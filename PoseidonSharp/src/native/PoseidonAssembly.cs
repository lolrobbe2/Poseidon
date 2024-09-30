using PoseidonSharp.native.interop;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace PoseidonSharp.native
{
    internal class PoseidonAssembly
    {
        public PoseidonAssembly(int assemblyId,int contextId)
        {
            m_AssemblyId = assemblyId;
            m_ContextId = contextId;
        }

        public string GetName()
        {
            string? fullName = GetNative().FullName;
            return string.IsNullOrEmpty(fullName) ? "" : fullName;
        }
        [UnmanagedCallersOnly]
        internal static NativeString GetNameNative(int assemblyId, int contextId) { return new PoseidonAssembly(assemblyId, contextId).GetName(); }
        private Assembly GetNative()
        {
            return AssemblyLoader.GetAssembly(m_ContextId, m_AssemblyId);
        }
        int m_AssemblyId;
        int m_ContextId;
    }
}
