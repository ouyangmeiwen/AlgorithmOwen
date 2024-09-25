#pragma once
#ifdef MYLIBRARY_EXPORTS
#define MYLIBRARY_API __declspec(dllexport)
#else
#define MYLIBRARY_API __declspec(dllimport)
#endif

extern "C" {
    MYLIBRARY_API void freeDoubleArray(double* array);
    MYLIBRARY_API double* ZScoreFilterCal(double factor,double* inputArray, int length, int* outputLength);
    MYLIBRARY_API double* IQRFilterCal(double* inputArray, int length, int* outputLength);
    MYLIBRARY_API double* KMeansFilterCal(int k, int maxIterations, double* inputArray, int length, int* outputLength);
    MYLIBRARY_API double* DBSCANFilterCal(double epsilon, int minPoints,double* inputArray, int length, int* outputLength);
    MYLIBRARY_API double* VarianceFilterCal(double varianceThreshold,double* inputArray, int length, int* outputLength);
}
