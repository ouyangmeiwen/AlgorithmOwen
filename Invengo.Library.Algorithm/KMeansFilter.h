// include/KMeansFilter.h

#ifndef K_MEANS_FILTER_H
#define K_MEANS_FILTER_H

#include "DataAnalyzer.h"

class KMeansFilter : public DataAnalyzer {
public:
    KMeansFilter(const std::vector<double>& inputData, int k = 2, int maxIterations = 100);

    std::vector<double> filterData() const override;

private:
    std::vector<double> data;
    int k;
    int maxIterations;

    std::vector<int> performKMeans(std::vector<double>& centroids) const;
};

#endif // K_MEANS_FILTER_H
