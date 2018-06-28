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

#include "../../exceptions/exception.h"
#include "../../exceptions/logic_errors/outofrange.h"
#include "vectorxd.h"

#include <vector>
#include <memory>

class MatrixXd
{
public:
    using size_r = std::vector<std::vector<double>>::size_type;
    using size_c = std::vector<double>::size_type;

private:
    class Proxy
    {
    public:
        explicit Proxy(std::vector<double>& row):values(row){

        }

        double& operator[](const size_c& column){
            return this->values[column];
        }

    private:
        std::vector<double>& values;
    };

    class ConstProxy
    {
    public:
        explicit ConstProxy(const std::vector<double>& row):values(row){

        }

        double operator[](const size_c& column) const{
            return this->values[column];
        }

    private:
        const std::vector<double>& values;
    };


public:
    MatrixXd();
    MatrixXd(const size_r& rowSize,const size_c& columnSize,const double& initVal = 0.0);
    MatrixXd(const std::vector<std::vector<double>>& values);
    MatrixXd(const MatrixXd& other);
    ~MatrixXd();

    MatrixXd& operator=(const MatrixXd& other);

    MatrixXd operator+(const MatrixXd& other) const;
    MatrixXd operator-(const MatrixXd& other) const;
    MatrixXd operator*(const double& value) const;
    VectorXd operator*(const VectorXd& vec) const;

    Proxy operator[](const size_r& row);
    ConstProxy operator[](const size_r& row) const;

    static MatrixXd transpose(const MatrixXd& mat);
    MatrixXd transpose() const;

    double& at(const size_r& row,const size_c& column);
    const double& at(const size_r& row,const size_c& column) const;

    size_r sizeRow() const;
    size_c sizeColumn() const;
    void clear();

    const std::vector<std::vector<double>>& getValues() const;

private:
    std::vector<std::vector<double>> values;

    void validateMat(const MatrixXd& other) const;
    void validateVec(const VectorXd& vec) const;
};
