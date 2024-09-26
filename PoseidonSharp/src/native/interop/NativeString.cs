using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace PoseidonSharp.native.interop
{
    [StructLayout(LayoutKind.Sequential)]
    public struct NativeString
    {
        internal IntPtr m_NativeString;
        [MarshalAs(UnmanagedType.Bool)] 
        private bool m_IsDisposed;

        public void Dispose()
        {
            if (!m_IsDisposed)
            {
                if (m_NativeString != IntPtr.Zero)
                {
                    Marshal.FreeCoTaskMem(m_NativeString);
                    m_NativeString = IntPtr.Zero;
                }

                m_IsDisposed = true;
            }

            GC.SuppressFinalize(this);
        }

        public override string? ToString() => this;

        public static NativeString Null() => new NativeString() { m_NativeString = IntPtr.Zero };

        public static implicit operator NativeString(string? InString) => new() { m_NativeString = Marshal.StringToCoTaskMemAuto(InString) };
        public static implicit operator string?(NativeString InString) => Marshal.PtrToStringAuto(InString.m_NativeString);
    }
}
