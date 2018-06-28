/* =============================================================================================
 * ChemicalKinetics
 *
 * A tool to calculate chemistry kinetics
 * ---------------------------------------------------------------------------------------------
 * Copyright (C) 2018  Leo Basov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public Licens
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * =============================================================================================
 */

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

    InterpolationTable& operator=(const InterpolationTable& other);

    bool operator==(const InterpolationTable& other) const;
    bool operator!=(const InterpolationTable& other) const;

private:
    std::vector<std::pair<double,double>> valueTable;

    double interpolate(const double &x_0,const double &x_1,const double &y_0,const double &y_1,const double &x) const;
};
