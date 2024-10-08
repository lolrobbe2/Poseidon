using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace PoseidonSharp.managed
{
    public static class GarbageCollector
    {
        [UnmanagedCallersOnly]
        internal static void Collect()
        {
            GC.Collect();
            GC.WaitForPendingFinalizers();
        }
        [UnmanagedCallersOnly]
        static void GCHandleFree(IntPtr ptr)
        {
            GCHandle.FromIntPtr(ptr).Free();
        }
     
    }
}
