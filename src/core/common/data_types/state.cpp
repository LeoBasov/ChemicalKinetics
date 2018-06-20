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
    this->stoichiometricCoeffEducts.clear();
    this->stoichiometricCoeffProducts.clear();
    this->reactionPowers.clear();
    this->time = 0.0;
    this->temperature = 0.0;
    this->cv = 0.0;
}
