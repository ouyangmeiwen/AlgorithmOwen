using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Invengo.Library.APP452
{
    /// <summary>
    /// 标签源信息
    /// </summary>
    public class TagDto 
    {
        public string Epc { get; set; }

        public string Tid { get; set; }

        /// <summary>
        /// 标签RSSI值
        /// </summary>
        public double RSSI { get; set; }

        /// <summary>
        /// 天线号（集线器）
        /// 【层号】
        /// </summary>
        public int Antenna { get; set; }

        public string afi { get; set; }
        /// <summary>
        /// 书架第N列
        /// </summary>
        public byte addr { get; set; }

        public string barcode { get; set; }
        public int ReadCount { get; set; }
        public DateTime? Time { get; set; }
    }
}
