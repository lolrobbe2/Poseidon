using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace PoseidonSharp.native
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    internal struct AssemblyClass
    {
        
        public interop.NativeString Name;
        public interop.NativeString NameSpace;
        public interop.NativeString AssemblyName;
        int ContextId;
        int AssemblyId;
        public AssemblyClass(Type type, int contextId,int assemblyId)
        {
            ContextId = contextId;
            AssemblyId = assemblyId;
            Name = type.Name;
            NameSpace = type.Namespace;
            AssemblyName = type.Assembly.GetName().Name;
        }
    }
}
