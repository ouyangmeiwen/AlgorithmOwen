// include/VarianceFilter.h

#ifndef VARIANCE_FILTER_H
#define VARIANCE_FILTER_H

#include "DataAnalyzer.h"

class VarianceFilter : public DataAnalyzer {
public:
    VarianceFilter(const std::vector<double>& inputData, double varianceThreshold = 1.5);

    std::vector<double> filterData() const override;

private:
    std::vector<double> data;
    double varianceThreshold;

    double calculateVariance(const std::vector<double>& data, double mean) const;
};

#endif // VARIANCE_FILTER_H
