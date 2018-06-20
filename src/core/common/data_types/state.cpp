#include "state.h"

State::State(){

}

State::~State(){

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

void State::clear(){
    this->speciesMap.clear();
    this->reactionMap.clear();
    this->concentrations.clear();
    this->reactionRates.clear();
    this->stoichiometricCoeffEducts.clear();
    this->stoichiometricCoeffProducts.clear();
    this->reactionPowers.clear();
    this->time = 0.0;
    this->temperature = 0.0;
    this->cv = 0.0;
}

void State::resize(const size_t& row,const size_t& column){
    this->concentrations = VectorXd(column);
    this->reactionRates = VectorXd(column);
    this->stoichiometricCoeffEducts = MatrixXd(row,column);
    this->stoichiometricCoeffProducts = MatrixXd(row,column);
    this->reactionPowers = MatrixXd(row,column);
}
