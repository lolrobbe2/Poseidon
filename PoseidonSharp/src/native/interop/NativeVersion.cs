using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace PoseidonSharp.native.interop
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    internal struct Version
    {
        UInt32 Major;
        UInt32 Minor;
        UInt32 Build;
        UInt32 Revision;
        static public Version FromVersionNative(System.Version version)
        {
            Version native = new();
            native.Major = (UInt32)version.Major;
            native.Minor = (UInt32)version.Minor;
            native.Build = (UInt32)version.Build;
            native.Revision = (UInt32)version.Revision;

            return native;
        }
    }
}
