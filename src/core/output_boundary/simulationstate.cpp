#include "simulationstate.h"

SimulationState::SimulationState(){

}

SimulationState::~SimulationState(){

}

const State& SimulationState::getState() const{
    return this->state;
}

void SimulationState::setState(const State& state){
    this->state = state;
}
