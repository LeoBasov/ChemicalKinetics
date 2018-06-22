#include "integratoralgorithms.h"

double IntegratorAlgorithms::timeStep(const VectorXd& values,const VectorXd& diff,const double& frac){
    double timeStep(std::numeric_limits<double>::max());

    for(size_t i(0);i<values.size();++i){
        const double timeStepNew(std::abs(frac*values.at(i)/diff.at(i)));

        if(timeStepNew==0 || diff.at(i)==0){
            continue;
        }else if(timeStepNew < timeStep){
            timeStep = timeStepNew;
        }
    }

    return timeStep;
}

VectorXd IntegratorAlgorithms::firstOrder(const VectorXd& values,const VectorXd& diff,const double& timeStep){
    return values + (diff*timeStep);
}
