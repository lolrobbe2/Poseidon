﻿using PoseidonSharp.native.interop;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
#nullable enable
namespace PoseidonSharp.native
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct AssemblyClass
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
            Console.WriteLine($"{NameSpace}.{Name}, {AssemblyName}");
            return Type.GetType($"{NameSpace}.{Name}, {AssemblyName}", true,false);
        }
        public FieldInfo[] GetFields()
        {
            return GetType()!.GetFields();
        }
        [UnmanagedCallersOnly]
        internal unsafe static IntPtr GetFieldsNative(int contextId, int assemblyId, NativeString name)
        {
            try
            {
                Console.WriteLine(name.ToString());
                Console.WriteLine(Type.GetType(name, true, false));
                AssemblyClass? assemblyClass = new AssemblyClass(Type.GetType(name, true, false),contextId,assemblyId) ;
                Field[] fields = assemblyClass?.GetFields().Select(field => new Field(field)).ToArray();
                Console.WriteLine(fields.Length);
                return new NativeArray<Field>().ToIntptr();
            }
            catch(Exception e) {
                Console.WriteLine(e.ToString());
                return IntPtr.Zero;
            }
        }
    }
}
