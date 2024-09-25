// include/DataAnalyzer.h

#ifndef DATA_ANALYZER_H
#define DATA_ANALYZER_H

#include <vector>

// 定义一个纯虚类 DataAnalyzer，所有过滤方法将继承该类
class DataAnalyzer {
public:
    virtual ~DataAnalyzer() = default;

    // 纯虚方法，返回过滤后的数据
    virtual std::vector<double> filterData() const = 0;
};

#endif // DATA_ANALYZER_H
