#include "chemistry.h"

Chemistry::Chemistry(){

}

void Chemistry::setMode(const Mode& mode){
    this->mode = mode;
}

void Chemistry::setReactionPowers(const MatrixXd& reactionPowers){
    this->reactionPowers = reactionPowers;
}

void Chemistry::setReactionStoichiometricMatrix(const MatrixXd& stoichiometricMatrix){
    this->stoichiometricMatrix = stoichiometricMatrix;
}

void Chemistry::setRateConstants(const VectorXd& rateConstants){
    this->rateConstants = rateConstants;
}

void Chemistry::setRateConstants(const std::vector<InterpolationTable>& rateConstantsInterpolTables){
    this->rateConstantsInterpolTables = rateConstantsInterpolTables;
}

void Chemistry::setArrheniusCoefficients(const double& preFact,const double& activationEnergy){
    this->arrheniusPreFact = preFact;
    this->arrheniusActivationEnergy = activationEnergy;
}

VectorXd Chemistry::calculateConcentrationDiff(const VectorXd& concentrations) const{
    const VectorXd reactionrates(ChemistryAlgorithms::reactionRatePowLaw(this->rateConstants,concentrations,this->reactionPowers));

    return ChemistryAlgorithms::concentrationDifferential(this->stoichiometricMatrix,reactionrates);
}

VectorXd Chemistry::calculateConcentrationDiff(const VectorXd& concentrations,const VectorXd& rateConstants){
    setRateConstants(rateConstants);

    return calculateConcentrationDiff(concentrations);
}
