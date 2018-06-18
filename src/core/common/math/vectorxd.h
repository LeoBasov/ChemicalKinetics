#pragma once

#include <vector>

class VectorXd
{
public:
    VectorXd();
    VectorXd(const std::vector<double>::size_type& size,const double& initVal = 0.0);
    VectorXd(const std::vector<double>& values);
    VectorXd(const VectorXd& other);
    ~VectorXd();

    const std::vector<double>& getValues() const;

private:
    std::vector<double> values;
};
