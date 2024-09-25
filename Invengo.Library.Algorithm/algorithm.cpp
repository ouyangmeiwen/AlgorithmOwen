#include "pch.h"
#include "algorithm.h"

#include <vector>
#include <algorithm>
#include "ZScoreFilter.h"
#include "IQRFilter.h"
#include "KMeansFilter.h"
#include "DBSCANFilter.h"
#include "VarianceFilter.h"

extern "C" {
    __declspec(dllexport) void freeDoubleArray(double* array) {
        delete[] array;
    }
    double* ZScoreFilterCal(double factor, double* inputArray, int length, int* outputLength)
    {
        // Convert input array to std::vector
        std::vector<double> inputVector(inputArray, inputArray + length);

        // Process the input vector: Only keep even-indexed elements and increment them

        ZScoreFilter zScoreFilter(inputVector, 2.0);
        std::vector<double> zScoreFiltered = zScoreFilter.filterData();


        // Set the output length to the size of the processed vector
        *outputLength = static_cast<int>(zScoreFiltered.size());

        // Allocate memory for the output array
        double* outputArray = new double[*outputLength];
        std::copy(zScoreFiltered.begin(), zScoreFiltered.end(), outputArray);

        return outputArray;
    }
    double* IQRFilterCal(double* inputArray, int length, int* outputLength)
    {
        // Convert input array to std::vector
        std::vector<double> inputVector(inputArray, inputArray + length);

        // Process the input vector: Only keep even-indexed elements and increment them

        IQRFilter iqrFilter(inputVector);
        std::vector<double> iqrFiltered = iqrFilter.filterData();


        // Set the output length to the size of the processed vector
        *outputLength = static_cast<int>(iqrFiltered.size());

        // Allocate memory for the output array
        double* outputArray = new double[*outputLength];
        std::copy(iqrFiltered.begin(), iqrFiltered.end(), outputArray);

        return outputArray;
    }
    double* KMeansFilterCal(int k, int maxIterations, double* inputArray, int length, int* outputLength)
    {
        // Convert input array to std::vector
        std::vector<double> inputVector(inputArray, inputArray + length);

        // Process the input vector: Only keep even-indexed elements and increment them

        KMeansFilter kMeansFilter(inputVector, k, maxIterations);
        std::vector<double> kMeansFiltered = kMeansFilter.filterData();


        // Set the output length to the size of the processed vector
        *outputLength = static_cast<int>(kMeansFiltered.size());

        // Allocate memory for the output array
        double* outputArray = new double[*outputLength];
        std::copy(kMeansFiltered.begin(), kMeansFiltered.end(), outputArray);

        return outputArray;
    }
    double* DBSCANFilterCal(double epsilon, int minPoints, double* inputArray, int length, int* outputLength)
    {
        // Convert input array to std::vector
        std::vector<double> inputVector(inputArray, inputArray + length);

        // Process the input vector: Only keep even-indexed elements and increment them

       // DBSCAN Filter DBSCAN 是一种基于密度的聚类算法，可以识别和过滤异常点，这些点通常位于低密度区域。
        DBSCANFilter dbscanFilter(inputVector, epsilon, minPoints);
        std::vector<double> dbscanFiltered = dbscanFilter.filterData();


        // Set the output length to the size of the processed vector
        *outputLength = static_cast<int>(dbscanFiltered.size());

        // Allocate memory for the output array
        double* outputArray = new double[*outputLength];
        std::copy(dbscanFiltered.begin(), dbscanFiltered.end(), outputArray);

        return outputArray;
    }
    double* VarianceFilterCal(double varianceThreshold,double* inputArray, int length, int* outputLength)
    {
        // Convert input array to std::vector
        std::vector<double> inputVector(inputArray, inputArray + length);

        // Process the input vector: Only keep even-indexed elements and increment them

        VarianceFilter varianceFilter(inputVector, varianceThreshold);
        std::vector<double> varianceFiltered = varianceFilter.filterData();


        // Set the output length to the size of the processed vector
        *outputLength = static_cast<int>(varianceFiltered.size());

        // Allocate memory for the output array
        double* outputArray = new double[*outputLength];
        std::copy(varianceFiltered.begin(), varianceFiltered.end(), outputArray);

        return outputArray;
    }
}
