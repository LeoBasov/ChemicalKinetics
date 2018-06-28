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
#include <cmath>

#include "../../exceptions/exception.h"
#include "../../exceptions/logic_errors/outofrange.h"

class VectorXd
{
public:
    using size_v = std::vector<double>::size_type;

public:
    VectorXd();
    VectorXd(const size_v& size,const double& initVal = 0.0);
    VectorXd(const std::vector<double>& values);
    VectorXd(const VectorXd& other);
    ~VectorXd();

    VectorXd& operator=(const VectorXd& other);

    bool operator==(const VectorXd& other) const;
    bool operator!=(const VectorXd& other) const;
    bool operator< (const VectorXd& other) const;
    bool operator> (const VectorXd& other) const;
    bool operator<=(const VectorXd& other) const;
    bool operator>=(const VectorXd& other) const;

    VectorXd operator+(const VectorXd& other) const;
    VectorXd operator-(const VectorXd& other) const;
    VectorXd operator*(const double& value) const;
    double operator*(const VectorXd& other) const;

    double& operator[](size_v idx);
    const double& operator[](size_v idx) const;

    double& at(size_v idx);
    const double& at(size_v idx) const;

    double module() const;
    double sum() const;
    VectorXd elemWiseMult(const VectorXd& other) const;
    static VectorXd elemWiseMult(const VectorXd& lhs,const VectorXd& rhs);

    size_v size() const;
    void resize(const size_v& size,const double &values);
    void resize(const size_v& size);
    void clear();

    void validateSize(const VectorXd& other) const;
    static void validateSize(const VectorXd& lhs,const VectorXd& rhs);

    const std::vector<double>& getValues() const;

private:
    std::vector<double> values;
};
