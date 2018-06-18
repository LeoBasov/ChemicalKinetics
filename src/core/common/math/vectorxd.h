#pragma once

#include <vector>
#include <cmath>

#include "../../exceptions/logic_errors/outofrange.h"

class VectorXd
{
public:
    VectorXd();
    VectorXd(const std::vector<double>::size_type& size,const double& initVal = 0.0);
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

    double module() const;

    std::vector<double>::size_type size() const;
    void resize(const std::vector<double>::size_type& size,const double &values);
    void resize(const std::vector<double>::size_type& size);
    void clear();

    const std::vector<double>& getValues() const;

private:
    std::vector<double> values;

    void validate(const VectorXd& other) const;
};
