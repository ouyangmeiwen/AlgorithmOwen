// src/IQRFilter.cpp
#include "pch.h"

#include "IQRFilter.h"
#include <algorithm>

IQRFilter::IQRFilter(const std::vector<double>& inputData)
    : data(inputData) {}

std::pair<double, double> IQRFilter::calculateIQR() const {
    std::vector<double> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end());

    size_t q1Idx = sortedData.size() / 4;
    size_t q3Idx = 3 * sortedData.size() / 4;

    double q1 = sortedData[q1Idx];
    double q3 = sortedData[q3Idx];
    double iqr = q3 - q1;

    return { q1, q3 };
}

std::vector<double> IQRFilter::filterData() const {
    // 获取返回值
    std::pair<double, double> result = calculateIQR();
    // 解构
    double q1 = result.first;
    double q3 = result.second;
    double iqr = q3 - q1;
    double lowerBound = q1 - 1.5 * iqr;
    double upperBound = q3 + 1.5 * iqr;

    std::vector<double> filteredData;
    for (const auto& value : data) {
        if (value >= lowerBound && value <= upperBound) {
            filteredData.push_back(value);
        }
    }

    return filteredData;
}
