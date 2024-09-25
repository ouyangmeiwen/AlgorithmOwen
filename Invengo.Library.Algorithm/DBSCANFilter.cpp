// src/DBSCANFilter.cpp
#include "pch.h"

#include "DBSCANFilter.h"
#include <algorithm>
#include <cmath>

DBSCANFilter::DBSCANFilter(const std::vector<double>& inputData, double epsilon, int minPoints)
    : data(inputData), epsilon(epsilon), minPoints(minPoints) {}

std::vector<int> DBSCANFilter::performDBSCAN() const {
    std::vector<int> labels(data.size(), -1);
    int clusterId = 0;

    for (size_t i = 0; i < data.size(); ++i) {
        if (labels[i] != -1) continue;

        std::vector<int> neighbors;
        for (size_t j = 0; j < data.size(); ++j) {
            if (std::abs(data[i] - data[j]) <= epsilon) {
                neighbors.push_back(j);
            }
        }

        if (neighbors.size() < minPoints) {
            labels[i] = -2;  // Mark as noise
            continue;
        }

        labels[i] = clusterId;
        for (size_t j = 0; j < neighbors.size(); ++j) {
            if (labels[neighbors[j]] == -2) {
                labels[neighbors[j]] = clusterId;
            }
            if (labels[neighbors[j]] != -1) continue;

            labels[neighbors[j]] = clusterId;

            std::vector<int> additionalNeighbors;
            for (size_t k = 0; k < data.size(); ++k) {
                if (std::abs(data[neighbors[j]] - data[k]) <= epsilon) {
                    additionalNeighbors.push_back(k);
                }
            }

            if (additionalNeighbors.size() >= minPoints) {
                neighbors.insert(neighbors.end(), additionalNeighbors.begin(), additionalNeighbors.end());
            }
        }

        ++clusterId;
    }

    return labels;
}

std::vector<double> DBSCANFilter::filterData() const {
    std::vector<int> labels = performDBSCAN();

    std::vector<double> filteredData;
    for (size_t i = 0; i < data.size(); ++i) {
        if (labels[i] >= 0) {
            filteredData.push_back(data[i]);
        }
    }

    return filteredData;
}
