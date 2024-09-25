// src/ZScoreFilter.cpp
#include "pch.h"

#include "ZScoreFilter.h"
#include <cmath>
#include <numeric>

ZScoreFilter::ZScoreFilter(const std::vector<double>& inputData, double threshold)
    : data(inputData), threshold(threshold) {}

std::vector<double> ZScoreFilter::filterData() const {
    double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    double variance = 0.0;

    for (const auto& value : data) {
        variance += (value - mean) * (value - mean);
    }
    variance /= data.size();
    double stddev = std::sqrt(variance);

    std::vector<double> filteredData;
    for (const auto& value : data) {
        double zScore = stddev != 0 ? (value - mean) / stddev : 0;
        if (std::abs(zScore) <= threshold) {
            filteredData.push_back(value);
        }
    }

    return filteredData;
}
