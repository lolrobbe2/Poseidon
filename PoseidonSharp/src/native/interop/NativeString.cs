using System;
using System.Runtime.InteropServices;

#nullable enable
namespace PoseidonSharp.native.interop
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct NativeString
    {
        internal IntPtr m_NativeString;      
        private Bool32 m_IsDisposed;

        
        public void Dispose()
        {
            if (!m_IsDisposed || m_NativeString != IntPtr.Zero) return;

            Marshal.FreeCoTaskMem(m_NativeString);
            m_NativeString = IntPtr.Zero;

            m_IsDisposed = true;

            GC.SuppressFinalize(this);
        }
        public IntPtr ToIntptr()
        {
            unsafe
            {
                IntPtr ptr = Marshal.AllocHGlobal(sizeof(IntPtr) + sizeof(Bool32));
                Marshal.WriteIntPtr(ptr, m_NativeString);
                Marshal.WriteByte(ptr + sizeof(IntPtr),(byte) m_IsDisposed.Value);
                return ptr;
            }
            
        }
        public override string? ToString() => this;

        public static NativeString Null() => new NativeString() { m_NativeString = IntPtr.Zero };

        public static implicit operator NativeString(string? InString) => new() { m_IsDisposed = false,m_NativeString = Marshal.StringToCoTaskMemUTF8(InString) };
        public static implicit operator string?(NativeString InString) => Marshal.PtrToStringUTF8(InString.m_NativeString);
        public static implicit operator IntPtr(NativeString InString) => InString.ToIntptr();
    }
}
