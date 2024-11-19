using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using PoseidonSharp.native.interop;

namespace PoseidonSharp.native
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    internal struct Field
    {
        public NativeString name;
        public FieldAttributes attributes;
        
        public Field(FieldInfo info)
        {
            name = info.Name;
            name.setManaged(true);
            attributes = info.Attributes;
        }
        public static implicit operator Field(FieldInfo info)
        {
            return new Field(info);
        }
    }

}
