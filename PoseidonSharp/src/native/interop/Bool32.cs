using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace PoseidonSharp.native.interop
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct Bool32
    {
        public uint Value { get; set; }

        public static implicit operator Bool32(bool InValue) => new() { Value = InValue ? 1u : 0u };
        public static implicit operator bool(Bool32 InBool32) => InBool32.Value > 0;
    }
}
