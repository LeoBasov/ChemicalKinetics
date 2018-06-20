#pragma once

#include <vector>
#include <algorithm>

#include "../../exceptions/exception.h"

class InterpolationTable
{
public:
    InterpolationTable();
    InterpolationTable(const std::vector<std::pair<double,double>>& valueTable);

    void clear();
    double getValue(const double &valueFirst) const;
    void addValuePair(const double &valueFirst,const double &valueSecond);

    const std::vector<std::pair<double,double>> &getValueTable() const;

    bool operator==(const InterpolationTable& other) const;
    bool operator!=(const InterpolationTable& other) const;

private:
    std::vector<std::pair<double,double>> valueTable;

    double interpolate(const double &x_0,const double &x_1,const double &y_0,const double &y_1,const double &x) const;
};
