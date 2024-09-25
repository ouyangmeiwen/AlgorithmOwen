// include/ZScoreFilter.h

#ifndef Z_SCORE_FILTER_H
#define Z_SCORE_FILTER_H

#include "DataAnalyzer.h"

class ZScoreFilter : public DataAnalyzer {
public:
    ZScoreFilter(const std::vector<double>& inputData, double threshold = 2.0);

    std::vector<double> filterData() const override;

private:
    std::vector<double> data;
    double threshold;
};

#endif // Z_SCORE_FILTER_H
