using System;
using System.Runtime.InteropServices;

namespace PoseidonSharp.native.interop
{
    [StructLayout(LayoutKind.Sequential)]
    internal struct NativeArray<T> where T : struct
    {
        public int Size;
        public IntPtr UnmanagedArray; // Pointer to unmanaged memory

        public NativeArray(T[] values)
        {
            Size = values.Length;

            // Allocate unmanaged memory for the array
            UnmanagedArray = Marshal.AllocHGlobal(Size * Marshal.SizeOf(typeof(T)));

            // Copy the values from the managed array to the unmanaged array
            for (int i = 0; i < values.Length; i++)
            {
                IntPtr elementPtr = IntPtr.Add(UnmanagedArray, i * Marshal.SizeOf(typeof(T)));
                Marshal.StructureToPtr(values[i], elementPtr, false);
            }
        }

        // Method to retrieve the value from unmanaged memory
        public T GetValue(int index)
        {
            if (index < 0 || index >= Size)
                throw new IndexOutOfRangeException();

            IntPtr elementPtr = IntPtr.Add(UnmanagedArray, index * Marshal.SizeOf(typeof(T)));
            return Marshal.PtrToStructure<T>(elementPtr);
        }

        // Convert the structure to an IntPtr for use in C++
        public IntPtr ToIntptr()
        {
            IntPtr ptr = IntPtr.Zero;
            unsafe
            {
                // Allocate unmanaged memory for the metadata (Size and pointer to UnmanagedArray)
                ptr = Marshal.AllocHGlobal(sizeof(int) + IntPtr.Size);
                Marshal.WriteInt32(ptr, Size);  // Write the size of the array
                Marshal.WriteIntPtr(ptr + sizeof(int), UnmanagedArray);  // Write the pointer to the unmanaged array
            }
            return ptr;
        }

        // Method to free the unmanaged memory from C++ side
        public static void FreeUnmanagedArray(IntPtr arrayPtr)
        {
            if (arrayPtr == IntPtr.Zero)
                return;

            // Retrieve the pointer to the unmanaged array
            IntPtr unmanagedArray = Marshal.ReadIntPtr(arrayPtr + sizeof(int));

            // Free the unmanaged memory
            Marshal.FreeHGlobal(unmanagedArray);

            // Free the structure itself
            Marshal.FreeHGlobal(arrayPtr);
        }

        // Dispose method to free the unmanaged memory from the C# side
        public void Dispose()
        {
            if (UnmanagedArray != IntPtr.Zero)
            {
                Marshal.FreeHGlobal(UnmanagedArray);
                UnmanagedArray = IntPtr.Zero;
            }
        }
    }
}
