#pragma once

#include <vector>

class MatrixXd
{
public:
    using size_r = std::vector<std::vector<double>>::size_type;
    using size_c = std::vector<double>::size_type;

public:
    MatrixXd();
    MatrixXd(const size_r& rowSize,const size_c& columnSize,const double& initVal = 0.0);
    MatrixXd(const std::vector<std::vector<double>>& values);
    MatrixXd(const MatrixXd& other);
    ~MatrixXd();

    MatrixXd& operator=(const MatrixXd& other);

    const std::vector<std::vector<double>>& getValues() const;

private:
    std::vector<std::vector<double>> values;
};
