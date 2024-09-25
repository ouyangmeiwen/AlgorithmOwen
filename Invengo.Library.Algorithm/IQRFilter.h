// include/IQRFilter.h

#ifndef IQR_FILTER_H
#define IQR_FILTER_H

#include "DataAnalyzer.h"

class IQRFilter : public DataAnalyzer {
public:
    IQRFilter(const std::vector<double>& inputData);

    std::vector<double> filterData() const override;

private:
    std::vector<double> data;

    std::pair<double, double> calculateIQR() const;
};

#endif // IQR_FILTER_H
