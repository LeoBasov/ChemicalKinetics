#pragma once

#include "../../exceptions/exception.h"
#include "../../exceptions/logic_errors/outofrange.h"
#include "vectorxd.h"

#include <vector>

class MatrixXd
{
public:
    using size_r = std::vector<std::vector<double>>::size_type;
    using size_c = std::vector<double>::size_type;

private:
    class Proxy
    {
    public:
        explicit Proxy(std::vector<double>& column):values(column){

        }

        double& operator[](const size_c& column){
            return this->values[column];
        }

        double operator[](const size_c& column) const{
            return this->values[column];
        }

    private:
        std::vector<double>& values;
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

    double& at(const size_r& row,const size_c& column);
    const double& at(const size_r& row,const size_c& column) const;

    size_r sizeRow() const;
    size_c sizeColumn() const;

    const std::vector<std::vector<double>>& getValues() const;

private:
    std::vector<std::vector<double>> values;

    void validateMat(const MatrixXd& other) const;
    void validateVec(const VectorXd& vec) const;
};
