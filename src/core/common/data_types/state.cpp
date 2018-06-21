#include "state.h"

State::State(){

}

State::~State(){

}

void State::clear(){
    this->speciesMap.clear();
    this->reactionMap.clear();
    this->concentrations.clear();
    this->reactionRates.clear();
    this->rateConstants.clear();
    this->stoichiometricCoeffEducts.clear();
    this->stoichiometricCoeffProducts.clear();
    this->reactionPowers.clear();
    this->time = 0.0;
    this->temperature = 0.0;
    this->cv = 0.0;
}

void State::setUp(const std::vector<std::string>& species,const std::vector<std::string>& reactions){
    clear();
    resize(reactions.size(),species.size());

    for(size_t i(0);i<species.size();++i){
        this->speciesMap[species.at(i)] = i;
    }
    for(size_t i(0);i<reactions.size();++i){
        this->reactionMap[reactions.at(i)] = i;
    }
}

void State::setConcentration(const std::string& species,const double& concentration){
    this->concentrations.at(this->speciesMap.at(species)) = concentration;
}

void State::setConcentrations(const VectorXd& concentrations){
    this->concentrations = concentrations;
}

void State::setReactionRate(const std::string& reaction,const double& reactionRate){
    this->reactionRates.at(this->reactionMap.at(reaction)) = reactionRate;
}

void State::setReactionRates(const VectorXd& reactionRates){
    this->reactionRates = reactionRates;
}

void State::setRateConstant(const std::string& reaction,const double& rateConstant){
    this->rateConstants.at(this->reactionMap.at(reaction)) = rateConstant;
}

void State::setRateConstants(const VectorXd& rateConstants){
    this->rateConstants = rateConstants;
}

void State::setStoichiometricCoeffEduct(const std::string& species,const std::string& reaction,const double& coeff){
    this->stoichiometricCoeffEducts.at(this->reactionMap.at(reaction),this->speciesMap.at(species)) = coeff;
}

void State::setStoichiometricCoeffProduct(const std::string& species,const std::string& reaction,const double& coeff){
    this->stoichiometricCoeffProducts.at(this->reactionMap.at(reaction),this->speciesMap.at(species)) = coeff;
}

void State::setReactionPower(const std::string& species,const std::string& reaction,const double& pow){
    this->reactionPowers.at(this->reactionMap.at(reaction),this->speciesMap.at(species)) = pow;
}

void State::setTime(const double& time){
    this->time = time;
}

void State::setTemperature(const double& temperature){
    this->temperature = temperature;
}

void State::setCv(const double& cv){
    this->cv = cv;
}

const std::map<std::string,std::size_t>& State::getSpeciesMap() const{
    return this->speciesMap;
}

const std::map<std::string,std::size_t>& State::getReactionMap() const{
    return this->speciesMap;
}

const VectorXd& State::getConcentrations() const{
    return this->concentrations;
}

const VectorXd& State::getReactionRates() const{
    return this->reactionRates;
}

const VectorXd& State::getRateConstants() const{
    return this->rateConstants;
}

const MatrixXd& State::getStoichiometricCoeffEducts() const{
    return this->stoichiometricCoeffEducts;
}

const MatrixXd& State::getStoichiometricCoeffProducts() const{
    return this->stoichiometricCoeffProducts;
}

MatrixXd State::getStoichiometricMatrix() const{
    return this->stoichiometricCoeffProducts - this->stoichiometricCoeffEducts;
}

const MatrixXd& State::getReactionPowers() const{
    return this->reactionPowers;
}

double State::getTime() const{
    return this->time;
}

double State::getTemperature() const{
    return this->temperature;
}

double State::getCv() const{
    return this->cv;
}

void State::resize(const size_t& row,const size_t& column){
    this->concentrations = VectorXd(column);
    this->reactionRates = VectorXd(row);
    this->rateConstants = VectorXd(row);
    this->stoichiometricCoeffEducts = MatrixXd(row,column);
    this->stoichiometricCoeffProducts = MatrixXd(row,column);
    this->reactionPowers = MatrixXd(row,column);
}
