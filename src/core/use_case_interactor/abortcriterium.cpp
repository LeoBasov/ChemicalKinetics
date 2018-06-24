#include "abortcriterium.h"

AbortCriterium::AbortCriterium()
{

}

bool AbortCriterium::valid(const State& state){
    if(this->firstRun){
        this->firstRun = false;
        this->lastState = state;
    }else{
        this->validVal = checkCriterium(state);
        this->lastState = state;
    }

    return this->validVal;
}

void AbortCriterium::abort(){
    this->validVal = false;
}

void AbortCriterium::reset(){
    this->validVal = true;
    this->firstRun = true;
    this->lastState = State();
}

bool AbortCriterium::checkCriterium(const State &state) const{
    //DUMMY

    const double timeStep(state.time - this->lastState.time);

    if(timeStep>50.0e+12){
        return false;
    }else{
        return true;
    }
}
