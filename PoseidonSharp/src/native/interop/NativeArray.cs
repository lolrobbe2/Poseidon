using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace PoseidonSharp.native.interop
{
    [StructLayout(LayoutKind.Sequential)]
    internal struct NativeArray<T> where T : struct
    {
        public Int32 Size;
        public GCHandle handle;
        T[] array;

        public T GetValue(int index) => array[index];
        public NativeArray(T[] values)
        {
            Size = values.Length;
            array = values;
            handle = GCHandle.Alloc(array, GCHandleType.Pinned);
        }
        public IntPtr ToIntptr()
        {
            IntPtr ptr = IntPtr.Zero;
            unsafe
            {
                ptr = Marshal.AllocHGlobal(sizeof(UInt32) + sizeof(GCHandle) + sizeof(IntPtr));
                Marshal.WriteInt32(ptr, Size);
                Marshal.WriteIntPtr(ptr + sizeof(Int32), (IntPtr)handle);
                Marshal.WriteIntPtr(ptr + sizeof(Int32) + sizeof(IntPtr), handle.AddrOfPinnedObject());
            }
          
            return ptr;
        }
        // Dispose method for freeing unmanaged memory
        public void Dispose()
        {
            handle.Free();  
            Dispose(true);
            GC.SuppressFinalize(this); // Prevent finalizer from running
        }

        // Protected Dispose method to handle resource cleanup
        void Dispose(bool disposing)
        {
            // If disposing is true, dispose managed resources here (if any)
            if (array != null)
            {
                array = null; // Clear the reference
            }
        }

        public IntPtr GetAddress()
        {
            if (!handle.IsAllocated)
                throw new InvalidOperationException("Array is not pinned.");

            return handle.AddrOfPinnedObject();
        }
         
        // Finalizer for cleanup (if Dispose is not called)

    }
}
