// include/DBSCANFilter.h

#ifndef DBSCAN_FILTER_H
#define DBSCAN_FILTER_H

#include "DataAnalyzer.h"

class DBSCANFilter : public DataAnalyzer {
public:
    /***
    epsilon = 0.5：这个值通常是通过实验或数据的具体特征来确定的。如果数据点之间的距离普遍较小，那么较小的 epsilon 可能会更合适。选择适当的 epsilon 是关键，因为它决定了点的邻域大小，影响簇的形成。
    minPoints = 3：通常来说，minPoints 值应大于数据的维度。对于二维数据，常见的选择是 4 或 5，这可以确保簇的稳定性和可靠性。在实际应用中，可能需要根据数据的密度来调整这个值。
    ****/
    DBSCANFilter(const std::vector<double>& inputData, double epsilon = 0.5, int minPoints = 3);

    std::vector<double> filterData() const override;

private:
    std::vector<double> data;
    double epsilon;
    int minPoints;

    std::vector<int> performDBSCAN() const;
};

#endif // DBSCAN_FILTER_H
