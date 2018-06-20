#include "chemistry.h"

Chemistry::Chemistry(){

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

VectorXd Chemistry::calculateConcentrationDiff(const VectorXd& concentrations) const{
    const VectorXd reactionrates(ChemistryAlgorithms::reactionRatePowLaw(this->rateConstants,concentrations,this->reactionPowers));

    return ChemistryAlgorithms::concentrationDifferential(this->stoichiometricMatrix,reactionrates);
}

VectorXd Chemistry::calculateConcentrationDiff(const VectorXd& concentrations,const VectorXd& rateConstants){
    setRateConstants(rateConstants);

    return calculateConcentrationDiff(concentrations);
}
