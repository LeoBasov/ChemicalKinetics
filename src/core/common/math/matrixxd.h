#pragma once

#include <vector>

class MatrixXd
{
public:
    MatrixXd();
    MatrixXd(std::vector<std::vector<double>>::size_type& rowSize,std::vector<double>::size_type& columnSize,const double& initVal = 0.0);
    MatrixXd(const std::vector<std::vector<double>>& values);
    MatrixXd(const MatrixXd& other);
    ~MatrixXd();

    MatrixXd& operator=(const MatrixXd& other);

    const std::vector<std::vector<double>>& getValues() const;

private:
    std::vector<std::vector<double>> values;
};
