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
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    internal struct AssemblyClass
    {
        
        public interop.NativeString Name;
        public interop.NativeString NameSpace;
        public interop.NativeString AssemblyName;
        int ContextId;
        int AssemblyId;
        public AssemblyClass(string typeName, int contextId,int assemblyId) : this(Type.GetType(typeName, false, false), contextId, assemblyId)
        {
        }
        public AssemblyClass(Type type, int contextId, int assemblyId)
        {
            ContextId = contextId;
            AssemblyId = assemblyId;
            Name = type.Name;
            Name.setManaged(true);
            NameSpace = type.Namespace;
            NameSpace.setManaged(true);
            AssemblyName = type.Assembly.GetName().Name;
            AssemblyName.setManaged(true);
        }
        public Type? GetType()
        {
            return Type.GetType(Name,false,false);
        }
        public FieldInfo[] GetFields()
        {
            return GetType()?.GetFields();
        }
        [UnmanagedCallersOnly]
        unsafe static public IntPtr GetFieldsNative(int contextId, int assemblyId, NativeString name)
        {
            AssemblyClass assemblyClass = new AssemblyClass(name, contextId, assemblyId);
            Field[] fields = (Field[])assemblyClass.GetFields().Select(field => new Field(field));
            return new NativeArray<Field>().ToIntptr();
        }
    }
}
