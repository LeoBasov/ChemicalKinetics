#include "chemistryalgorithms.h"

double ChemistryAlgorithms::arrheniusEquation(const double& preFact,const double& activationEnergy,const double& temperature){
    return preFact*std::exp((-1.0)*activationEnergy/(Constants::universalGasConst*temperature));
}

VectorXd ChemistryAlgorithms::reactionRatePowLaw(const VectorXd& rateConstants,const VectorXd& concentrations,const MatrixXd& reactionPows){
    VectorXd reactionRates(rateConstants);

    for(size_t i(0);i<rateConstants.size();++i){
        for(size_t j(0);j<concentrations.size();++j){
            reactionRates.at(i) *= std::pow(concentrations.at(j),reactionPows.at(i,j));
        }
    }

    return reactionRates;
}

VectorXd ChemistryAlgorithms::concentrationDifferential(const MatrixXd& stochiometricMatrix,const VectorXd& reactionRates){
    return stochiometricMatrix*reactionRates;
}
