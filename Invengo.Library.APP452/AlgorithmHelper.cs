using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Invengo.Library.APP452
{
    public class AlgorithmHelper : IDisposable
    {
        private IntPtr _native;

        #region DllImports

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr CreateTag(int antenna, string epc, double rssi, int readcount,string name);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetTagAnt(IntPtr tag);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GetTagEpc(IntPtr tag);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern double GetTagRssi(IntPtr tag);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetTagReadCount(IntPtr tag);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GetTagName(IntPtr tag);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void DestroyTag(IntPtr tag);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr CreateTags();

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void AddTag(IntPtr collection, IntPtr tag);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GetTag(IntPtr collection, int index);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetTagsSize(IntPtr collection);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void DestroyTags(IntPtr collection);

        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr AnalyzeTags(IntPtr collection, double min, double max);


        #endregion

        #region Constructor and Destructor

        private AlgorithmHelper(int antenna, string epc, double rssi,int readcount,string name)
        {
            _native = CreateTag(antenna, epc, rssi, readcount, name);
        }

        public void Dispose()
        {
            if (_native != IntPtr.Zero)
            {
                DestroyTag(_native);
                _native = IntPtr.Zero;
            }
        }

        #endregion

        #region Properties

        private int Antenna => _native == IntPtr.Zero ? -1 : GetTagAnt(_native);

        private string Epc
        {
            get
            {
                if (_native == IntPtr.Zero) return string.Empty;
                IntPtr epcPtr = GetTagEpc(_native);
                return Marshal.PtrToStringAnsi(epcPtr) ?? string.Empty;
            }
        }

        private double Rssi => _native == IntPtr.Zero ? -1.0f : GetTagRssi(_native);


        private int ReadCount => _native == IntPtr.Zero ? -1 : GetTagReadCount(_native);

        private string Name
        {
            get
            {
                if (_native == IntPtr.Zero) return string.Empty;
                IntPtr namePtr = GetTagName(_native);
                return Marshal.PtrToStringAnsi(namePtr) ?? string.Empty;
            }
        }
        #endregion

        #region Static Methods for TagHelper Collection

        private static IntPtr CreateCollection()
        {
            return CreateTags();
        }

        private static void AddToCollection(IntPtr collection, AlgorithmHelper tag)
        {
            if (tag == null || collection == IntPtr.Zero)
                throw new ArgumentNullException();

            AddTag(collection, tag._native);
        }

        private static List<AlgorithmHelper> ConvertToList(IntPtr tagCollection)
        {
            int size = GetTagsSize(tagCollection);
            var taghelper = new List<AlgorithmHelper>(size);

            for (int i = 0; i < size; i++)
            {
                IntPtr tagPtr = GetTag(tagCollection, i);
                int ant = GetTagAnt(tagPtr);
                string epc = Marshal.PtrToStringAnsi(GetTagEpc(tagPtr));
                double rssi = GetTagRssi(tagPtr);
                int readcount = GetTagReadCount(tagPtr);
                string name = Marshal.PtrToStringAnsi(GetTagName(tagPtr));
                taghelper.Add(new AlgorithmHelper(ant, epc, rssi, readcount, name));
            }
            return taghelper;
        }

        private static void DestroyCollection(IntPtr collection)
        {
            if (collection != IntPtr.Zero)
            {
                DestroyTags(collection);
            }
        }
        public static List<TagDto> AnalyzeTags(List<TagDto> input, double? min, double? max)
        {
            IntPtr tags_old = CreateCollection();
            foreach (var item in input)
            {
                var tag = new AlgorithmHelper(item.Antenna, item.Epc, item.RSSI, item.ReadCount, item.Name);
                AddToCollection(tags_old, tag);
            }
            IntPtr tags_analyze = AnalyzeTags(tags_old, min ?? double.MinValue, max ?? double.MaxValue);
            var lst = ConvertToList(tags_analyze);
            DestroyCollection(tags_old);
            DestroyCollection(tags_analyze);
            var result = lst.Select(x => new TagDto()
            {
                Antenna = x.Antenna,
                Epc = x.Epc,
                RSSI = Math.Round(x.Rssi, 2),
                ReadCount = x.ReadCount,
                Name = x.Name
            }).ToList();
            return result;
        }
        #endregion
    }
}
