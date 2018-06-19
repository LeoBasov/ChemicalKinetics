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

    size_v size() const;
    void resize(const size_v& size,const double &values);
    void resize(const size_v& size);
    void clear();

    const std::vector<double>& getValues() const;

private:
    std::vector<double> values;

    void validate(const VectorXd& other) const;
};
