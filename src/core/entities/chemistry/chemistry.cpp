#include "chemistry.h"

Chemistry::Chemistry(){

}

void Chemistry::setMode(const Mode& mode){
    this->mode = mode;
}

void Chemistry::setReactionPowers(const MatrixXd& reactionPowers){
    this->reactionPowers = reactionPowers;
}

void Chemistry::setStoichiometricMatrix(const MatrixXd& stoichiometricMatrix){
    this->stoichiometricMatrix = stoichiometricMatrix;
}

void Chemistry::setRateConstants(const VectorXd& rateConstants){
    this->rateConstants = rateConstants;
}

void Chemistry::setRateConstants(const std::vector<InterpolationTable>& rateConstantsInterpolTables){
    this->rateConstantsInterpolTables = rateConstantsInterpolTables;
}

void Chemistry::setRateConstants(const std::vector<std::vector<std::pair<double,double>>>& rateConstantsInterpolTables){
    this->rateConstantsInterpolTables.clear();

    for(auto table : rateConstantsInterpolTables){
        this->rateConstantsInterpolTables.push_back(InterpolationTable(table));
    }
}

void Chemistry::setArrheniusCoefficients(const std::vector<std::pair<double,double>> &arrheniusCoefficients){
    this->arrheniusCoefficients = arrheniusCoefficients;
}

VectorXd Chemistry::getRateConstants(const double& temperature) const{
    switch(this->mode){
    case const_k:
        return this->rateConstants;
        break;
    case interpol_k:
        return interpolateRateConstants(temperature);
        break;
    case arrhenius_k:
        return calculateRateConstants(temperature);
        break;
    default:
        throw Exception("Undefined mode<" + std::to_string(mode) + ">","Chemistry::" + std::string(__FUNCTION__));
        break;
    }
}

VectorXd Chemistry::getReactionRates(const VectorXd& concentrations,const VectorXd& rateConstants) const{
    return ChemistryAlgorithms::reactionRatePowLaw(rateConstants,concentrations,this->reactionPowers);
}

VectorXd Chemistry::getConcentrationDiff(const VectorXd& reactionRates) const{
    return ChemistryAlgorithms::concentrationDifferential(this->stoichiometricMatrix,reactionRates);
}

VectorXd Chemistry::interpolateRateConstants(const double& temperature) const{
    VectorXd rateConstants(this->rateConstantsInterpolTables.size());

    for(size_t i(0);i<this->rateConstantsInterpolTables.size();++i){
        rateConstants.at(i) = this->rateConstantsInterpolTables.at(i).getValue(temperature);
    }

    return rateConstants;
}

VectorXd Chemistry::calculateRateConstants(const double& temperature) const{
    VectorXd rateConstants(this->arrheniusCoefficients.size());

    for(size_t i(0);i<this->arrheniusCoefficients.size();++i){
        const double preFactor(this->arrheniusCoefficients.at(i).first);
        const double activationEnergy(this->arrheniusCoefficients.at(i).second);

        rateConstants.at(i) = ChemistryAlgorithms::arrheniusEquation(preFactor,activationEnergy,temperature);
    }

    return rateConstants;
}
