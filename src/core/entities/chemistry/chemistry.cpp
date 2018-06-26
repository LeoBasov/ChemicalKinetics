#include "chemistry.h"

Chemistry::Chemistry(){

}

void Chemistry::setModes(const std::vector<Mode> &modes){
    this->modes = modes;
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

void Chemistry::setArrheniusCoefficients(const std::vector<std::pair<double,double>> &arrheniusCoefficients){
    this->arrheniusCoefficients = arrheniusCoefficients;
}

void Chemistry::setExcessEnergies(const VectorXd& excessEnergies){
    this->excessEnergies = excessEnergies;
}

VectorXd Chemistry::getRateConstants(const double& temperature) const{
    VectorXd rateConstants(this->rateConstants.size());

    for(size_t i(0);i<rateConstants.size();++i){
        rateConstants.at(i) = getRateConstant(temperature,i);
    }

    return rateConstants;
}

VectorXd Chemistry::getReactionRates(const VectorXd& concentrations,const VectorXd& rateConstants) const{
    return ChemistryAlgorithms::reactionRatePowLaw(rateConstants,concentrations,this->reactionPowers);
}

VectorXd Chemistry::getConcentrationDiff(const VectorXd& reactionRates) const{
    return ChemistryAlgorithms::concentrationDifferential(this->stoichiometricMatrix,reactionRates);
}

double Chemistry::getEnergyDiff(const VectorXd& reactionRates) const{
    return reactionRates*this->excessEnergies;
}

double Chemistry::getRateConstant(const double& temperature, const size_t &pos) const{
    switch(this->modes.at(pos)){
    case const_k:
        return this->rateConstants.at(pos);
        break;
    case interpol_k:
        return interpolateRateConstant(temperature,pos);
        break;
    case arrhenius_k:
        return calculateRateConstant(temperature,pos);
        break;
    default:
        throw Exception("Undefined mode<" + std::to_string(this->modes.at(pos)) + ">","Chemistry::" + std::string(__FUNCTION__));
        break;
    }
}

double Chemistry::interpolateRateConstant(const double& temperature,const size_t& pos) const{
    return this->rateConstantsInterpolTables.at(pos).getValue(temperature);
}

double Chemistry::calculateRateConstant(const double& temperature,const size_t& pos) const{
    const double preFactor(this->arrheniusCoefficients.at(pos).first);
    const double activationEnergy(this->arrheniusCoefficients.at(pos).second);

    return ChemistryAlgorithms::arrheniusEquation(preFactor,activationEnergy,temperature);
}
