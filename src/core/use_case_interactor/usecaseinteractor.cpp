#include "usecaseinteractor.h"

UseCaseInteractor::UseCaseInteractor()
{

}

void UseCaseInteractor::start(){
    initialize();

    while(this->abortCriterium.valid()){
        execute();
        report();
    }
}

void UseCaseInteractor::stop(){
    this->abortCriterium.abort();
}

void UseCaseInteractor::initialize(){
    //DUMMY
}

void UseCaseInteractor::execute(){
    VectorXd concentrationDiffs;

    this->state.setRateConstants(this->chemistry.getRateConstants(this->state.getTemperature()));
    this->state.setReactionRates(this->chemistry.getReactionRates(this->state.getConcentrations(),this->state.getRateConstants()));

    concentrationDiffs = this->chemistry.getConcentrationDiff(this->state.getReactionRates());

    this->state.setConcentrations(this->integrator.integrate(this->state.getConcentrations(),concentrationDiffs));
}

void UseCaseInteractor::report(){
    //DUMMY
}
