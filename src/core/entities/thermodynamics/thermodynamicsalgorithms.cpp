#include "thermodynamicsalgorithms.h"

double ThermodynamicsAlgorithms::internalDOF(const double& temperature,const double& characteresticVibrationalsTemp,const Species& species){
    switch (species) {
    case monoatomic:
        return 0.0;
        break;
    case diatomic:
        return diatomicInternalDOF(temperature,characteresticVibrationalsTemp);
        break;
    default:
        throw Exception();
        break;
    }
}

double ThermodynamicsAlgorithms::diatomicInternalDOF(const double& temperature,const double& characteresticVibrationalsTemp){
    const double fraction(characteresticVibrationalsTemp/temperature);
    const double denum(std::exp(fraction) - 1.0);

    return 2.0 + 2.0*fraction/denum;
}

VectorXd ThermodynamicsAlgorithms::internalDOF(const VectorXd& temperatures,const VectorXd& characteresticVibrationalsTemps,const std::vector<Species>& species){
    VectorXd vec(temperatures.size());

    temperatures.validateSize(characteresticVibrationalsTemps);

    for(size_t i(0);i<vec.size();++i){
        vec.at(i) = internalDOF(temperatures.at(i),characteresticVibrationalsTemps.at(i),species.at(i));
    }

    return vec;
}

double ThermodynamicsAlgorithms::totalEnergy(const VectorXd& concentrations,const VectorXd& temperatures,const VectorXd& internalDOF){
    const double factor(0.5*Constants::boltzmannConst);
    const double concentrSum(concentrations.sum());

    return concentrSum>0.0 ? concentrations*(temperatures*3.0*factor + VectorXd::elemWiseMult(internalDOF,temperatures)*factor)*(1.0/concentrSum) : 0.0;
}
