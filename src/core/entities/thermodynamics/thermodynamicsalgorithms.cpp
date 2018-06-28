#include "thermodynamicsalgorithms.h"

double ThermodynamicsAlgorithms::totalEnergy(const VectorXd& concentrations,const VectorXd& temperatures,const VectorXd& internalDOF){
    const double factor(0.5*Constants::boltzmannConst);
    const double concentrSum(concentrations.sum());

    return concentrSum>0.0 ? concentrations*(temperatures*3.0*factor + VectorXd::elemWiseMult(internalDOF,temperatures)*factor)*(1.0/concentrSum) : 0.0;
}
