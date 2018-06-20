#include "integrator.h"

Integrator::Integrator()
{

}

void Integrator::setMode(const Mode& mode){
    this->mode = mode;
}

void Integrator::setTimeStep(const double& timeStep){
    this->timeStep = timeStep;
}

void Integrator::setTimeStepParamter(const double& parameter){
    this->parameter = parameter;
}

VectorXd Integrator::integrate(const VectorXd& values,const VectorXd& diff){
    switch(this->mode){
    case const_dt:
        return IntegratorAlgorithms::firstOrder(values,diff,this->timeStep);
        break;
    case var_dt:
        this->timeStep = IntegratorAlgorithms::timeStep(values,diff,this->parameter);
        return IntegratorAlgorithms::firstOrder(values,diff,this->timeStep);
        break;
    default:
        throw Exception("Undefined mode<" + std::to_string(mode) + ">","Integrator::" + std::string(__FUNCTION__));
        break;
    }
}
