// src/KMeansFilter.cpp
#include "pch.h"

#include "KMeansFilter.h"
#include <limits>
#include <cmath>
#include <algorithm>


KMeansFilter::KMeansFilter(const std::vector<double>& inputData, int k, int maxIterations)
    : data(inputData), k(k), maxIterations(maxIterations) {}

std::vector<int> KMeansFilter::performKMeans(std::vector<double>& centroids) const {
    std::vector<int> labels(data.size(), -1);
    centroids.resize(k);

    std::copy(data.begin(), data.begin() + k, centroids.begin());

    bool changed = true;
    while (changed) {
        changed = false;

        // Assign labels based on centroids
        for (size_t i = 0; i < data.size(); ++i) {
            const double LARGE_VALUE = 1e300; // 一个非常大的值，用于初始化
            double minDistance = LARGE_VALUE;
            int bestCluster = 0;

            for (int j = 0; j < k; ++j) {
                double distance = std::abs(data[i] - centroids[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    bestCluster = j;
                }
            }

            if (labels[i] != bestCluster) {
                labels[i] = bestCluster;
                changed = true;
            }
        }

        // Update centroids
        std::vector<double> newCentroids(k, 0.0);
        std::vector<int> counts(k, 0);

        for (size_t i = 0; i < data.size(); ++i) {
            newCentroids[labels[i]] += data[i];
            ++counts[labels[i]];
        }

        for (int j = 0; j < k; ++j) {
            if (counts[j] > 0) {
                centroids[j] = newCentroids[j] / counts[j];
            }
        }
    }

    return labels;
}

std::vector<double> KMeansFilter::filterData() const {
    std::vector<double> centroids;
    std::vector<int> labels = performKMeans(centroids);

    std::vector<int> clusterSizes(k, 0);
    for (const auto& label : labels) {
        if (label >= 0) {
            ++clusterSizes[label];
        }
    }

    int outlierCluster = std::distance(clusterSizes.begin(), std::min_element(clusterSizes.begin(), clusterSizes.end()));

    std::vector<double> filteredData;
    for (size_t i = 0; i < data.size(); ++i) {
        if (labels[i] != outlierCluster) {
            filteredData.push_back(data[i]);
        }
    }

    return filteredData;
}
