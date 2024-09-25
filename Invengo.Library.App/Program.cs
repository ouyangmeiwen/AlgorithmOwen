using System.Runtime.InteropServices;

namespace Invengo.Library.App
{
    internal class Program
    {
        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void freeDoubleArray(IntPtr array);

        /// <summary>
        /// Z-Score 是一种标准化的方法，用于衡量一个数据点与均值之间的标准差距离。
        /// 通过设定一个阈值（通常为2或3），
        /// 我们可以识别异常数据点。
        /// </summary>
        /// <param name="factor">2.0</param>
        /// <param name="inputArray"></param>
        /// <param name="length"></param>
        /// <param name="outputLength"></param>
        /// <returns></returns>
        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ZScoreFilterCal(double factor, double[] inputArray, int length, out int outputLength);
        /// <summary>
        /// IQR Filter 四分位距（Interquartile Range, IQR）
        /// 是指数据的上四分位数（Q3）和下四分位数（Q1）之间的范围。
        /// 异常值通常被定义为低于Q1-1.5IQR或高于Q3+1.5IQR的数据点。
        /// </summary>
        /// <param name="inputArray"></param>
        /// <param name="length"></param>
        /// <param name="outputLength"></param>
        /// <returns></returns>
        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr IQRFilterCal(double[] inputArray, int length, out int outputLength);
        /// <summary>
        /// K-Means Filter 除了统计方法外，
        /// 还可以使用机器学习中的聚类算法来识别和过滤异常数据。
        /// 常见的算法包括K-Means和DBSCAN。
        /// </summary>
        /// <param name="k">2</param>
        /// <param name="maxIterations">100</param>
        /// <param name="inputArray"></param>
        /// <param name="length"></param>
        /// <param name="outputLength"></param>
        /// <returns></returns>
        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr KMeansFilterCal(int k, int maxIterations, double[] inputArray, int length, out int outputLength);
        /// <summary>
        /// DBSCAN Filter DBSCAN 是一种基于密度的聚类算法，可以识别和过滤异常点，这些点通常位于低密度区域。
        /// epsilon = 0.5：这个值通常是通过实验或数据的具体特征来确定的。
        /// 如果数据点之间的距离普遍较小，那么较小的 epsilon 可能会更合适。
        /// 选择适当的 epsilon 是关键，因为它决定了点的邻域大小，影响簇的形成。
        /// minPoints = 3：通常来说，minPoints 值应大于数据的维度。
        /// 对于二维数据，常见的选择是 4 或 5，这可以确保簇的稳定性和可靠性。
        /// 在实际应用中，可能需要根据数据的密度来调整这个值。
        /// </summary>
        /// <param name="epsilon">0.5</param>
        /// <param name="minPoints">3</param>
        /// <param name="inputArray"></param>
        /// <param name="length"></param>
        /// <param name="outputLength"></param>
        /// <returns></returns>
        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr DBSCANFilterCal(double epsilon, int minPoints, double[] inputArray, int length, out int outputLength);

        /// <summary>
        /// Variance Filter 四分法
        /// </summary>
        /// <param name="varianceThreshold"></param>
        /// <param name="inputArray"></param>
        /// <param name="length"></param>
        /// <param name="outputLength"></param>
        /// <returns></returns>
        [DllImport("Invengo.Library.Algorithm.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr VarianceFilterCal(double varianceThreshold, double[] inputArray, int length, out int outputLength);
       
        
        
        static void Main(string[] args)
        {
            // Define the input array
            double[] inputArray = {
                -10.0, -12.5, -11.0, -13.0, -9.5, -50.0,
                -10.2, -12.8, -11.2, -13.1, -9.9, -10.5,
                -11.5, -12.0, -10.8, -12.3, -13.5, -9.7,
                -10.1, -10.9, -11.6, -12.7, -12.9, -9.6,
                -20
                };
            string result1 = string.Join(", ", inputArray);
            Console.WriteLine("原始数据:" + result1);
            // Call the DLL function
            int outputLength;

            if (true)
            {
                IntPtr outputPtr = ZScoreFilterCal(2.0,inputArray, inputArray.Length, out outputLength);
                double[] outputArray = new double[outputLength];
                Marshal.Copy(outputPtr, outputArray, 0, outputLength);
                // Free the unmanaged array
                freeDoubleArray(outputPtr);
                Console.WriteLine("===============================");
                string result = string.Join(", ", outputArray);
                Console.WriteLine("ZScore:" + result);
            }


            if (true)
            {
                IntPtr outputPtr = IQRFilterCal(inputArray, inputArray.Length, out outputLength);
                double[] outputArray = new double[outputLength];
                Marshal.Copy(outputPtr, outputArray, 0, outputLength);
                // Free the unmanaged array
                freeDoubleArray(outputPtr);
                Console.WriteLine("===============================");
                string result = string.Join(", ", outputArray);
                Console.WriteLine("IQR:" + result);
            }

            if (true)
            {
                IntPtr outputPtr = KMeansFilterCal(2, 100, inputArray, inputArray.Length, out outputLength);
                double[] outputArray = new double[outputLength];
                Marshal.Copy(outputPtr, outputArray, 0, outputLength);
                // Free the unmanaged array
                freeDoubleArray(outputPtr);
                Console.WriteLine("===============================");
                string result = string.Join(", ", outputArray);
                Console.WriteLine("KMeans:" + result);

            }


            if (true)
            {
                IntPtr outputPtr = DBSCANFilterCal(0.5, 3, inputArray, inputArray.Length, out outputLength);
                double[] outputArray = new double[outputLength];
                Marshal.Copy(outputPtr, outputArray, 0, outputLength);
                // Free the unmanaged array
                freeDoubleArray(outputPtr);
                Console.WriteLine("===============================");
                string result = string.Join(", ", outputArray);
                Console.WriteLine("DBSCAN:" + result);

            }

            if (true)
            {
                IntPtr outputPtr = VarianceFilterCal(1.5, inputArray, inputArray.Length, out outputLength);
                double[] outputArray = new double[outputLength];
                Marshal.Copy(outputPtr, outputArray, 0, outputLength);
                // Free the unmanaged array
                freeDoubleArray(outputPtr);
                Console.WriteLine("===============================");
                string result = string.Join(", ", outputArray);
                Console.WriteLine("Variance:" + result);

            }
            Console.ReadLine();
        }
    }
}
