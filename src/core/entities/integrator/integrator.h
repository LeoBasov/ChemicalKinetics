#pragma once

#include "integratoralgorithms.h"

class Integrator
{
public:
    enum Mode{const_dt=1,var_dt=2,none=0};

public:
    Integrator();

    void setMode(const Mode& mode);
    void setTimeStep(const double& timeStep);
    void setTimeStepParamter(const double& parameter);

    double getTimeStep() const;

    VectorXd integrate(const VectorXd& values,const VectorXd& diff);

private:
    double timeStep = 0.0;
    double parameter = 0.0;
    Mode mode = none;
};
