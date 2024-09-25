using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace Invengo.Library.APP452
{
    public class Student : IDisposable
    {
        private IntPtr _nativeStudent;

        #region DllImports

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr CreateStudent(int id, string name, float score);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetStudentId(IntPtr student);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GetStudentName(IntPtr student);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetStudentScore(IntPtr student);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void DestroyStudent(IntPtr student);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr CreateStudentCollection();

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void AddStudentToCollection(IntPtr collection, IntPtr student);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GetStudentFromCollection(IntPtr collection, int index);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetStudentCollectionSize(IntPtr collection);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void DestroyStudentCollection(IntPtr collection);

        #endregion

        #region Constructor and Destructor

        public Student(int id, string name, float score)
        {
            _nativeStudent = CreateStudent(id, name, score);
        }

        public void Dispose()
        {
            if (_nativeStudent != IntPtr.Zero)
            {
                DestroyStudent(_nativeStudent);
                _nativeStudent = IntPtr.Zero;
            }
        }

        #endregion

        #region Properties

        public int Id => _nativeStudent == IntPtr.Zero ? -1 : GetStudentId(_nativeStudent);

        public string Name
        {
            get
            {
                if (_nativeStudent == IntPtr.Zero) return string.Empty;
                IntPtr namePtr = GetStudentName(_nativeStudent);
                return Marshal.PtrToStringAnsi(namePtr) ?? string.Empty;
            }
        }

        public float Score => _nativeStudent == IntPtr.Zero ? -1.0f : GetStudentScore(_nativeStudent);

        #endregion

        #region Static Methods for Student Collection

        public static IntPtr CreateCollection()
        {
            return CreateStudentCollection();
        }

        public static void AddToCollection(IntPtr collection, Student student)
        {
            if (student == null || collection == IntPtr.Zero)
                throw new ArgumentNullException();

            AddStudentToCollection(collection, student._nativeStudent);
        }

        public static List<Student> ConvertToList(IntPtr studentCollection)
        {
            int size = GetStudentCollectionSize(studentCollection);
            var students = new List<Student>(size);

            for (int i = 0; i < size; i++)
            {
                IntPtr studentPtr = GetStudentFromCollection(studentCollection, i);
                int id = GetStudentId(studentPtr);
                string name = Marshal.PtrToStringAnsi(GetStudentName(studentPtr));
                float score = GetStudentScore(studentPtr);

                // Create a managed Student object using the native pointer data
                students.Add(new Student(id, name, score));
            }

            return students;
        }

        public static void DestroyCollection(IntPtr collection)
        {
            if (collection != IntPtr.Zero)
            {
                DestroyStudentCollection(collection);
            }
        }

        #endregion
    }
}
