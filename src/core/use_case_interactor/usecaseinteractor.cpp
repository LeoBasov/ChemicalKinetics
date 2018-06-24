#include "usecaseinteractor.h"

UseCaseInteractor::UseCaseInteractor(const std::shared_ptr<SimulationState> &simState)
                                    :simulationState(simState){

}

void UseCaseInteractor::start(const InputData& data){
    initialize(data);
    report();

    while(this->abortCriterium.valid(this->state)){
        execute();
        report();
    }
}

void UseCaseInteractor::stop(){
    this->abortCriterium.abort();
}

void UseCaseInteractor::initialize(const InputData& data){
    initializeState(data);
    initializeIntergrator(data.integratorData);
    initializeChemistry(data.chemistryData);
    initializeAbortCriterium();
}

void UseCaseInteractor::initializeState(const InputData& data){
    this->converter.setUp(data.chemistryData.species,data.chemistryData.reactions);

    this->state.reactionMap = this->converter.getReactionMap();
    this->state.speciesMap = this->converter.getSpeciesMap();
    this->state.temperature = data.chemistryData.temperature;
    this->state.concentrations = this->converter.concentrations(data.chemistryData.species);
    this->state.concentrationDiffs = this->converter.concentrationsDiffs(data.chemistryData.species);
    this->state.reactionRates = this->converter.reactionRates(data.chemistryData.reactions);
    this->state.rateConstants = this->converter.rateConstatns(data.chemistryData.reactions);
    this->state.time = 0.0;
}

void UseCaseInteractor::initializeIntergrator(const InputData::IntegratorData& data){
    this->integrator.setMode(integratorMode(data.mode));
    this->integrator.setTimeStep(data.timeStep);
    this->integrator.setTimeStepParamter(data.parameter);
}

void UseCaseInteractor::initializeChemistry(const InputData::ChemistryData& data){
    this->chemistry.setMode(chemistryMode(data.mode));
    this->chemistry.setReactionPowers(this->converter.matrix(data.reactionPowers));
    this->chemistry.setStoichiometricMatrix(this->converter.matrix(data.stoichiometricCoeffProducts) - this->converter.matrix(data.stoichiometricCoeffEducts));
    this->chemistry.setRateConstants(converter.rateConstatns(data.reactions));
    this->chemistry.setRateConstants(this->converter.vectorTable(data.rateConstantsTables,Converter::reaction));
    this->chemistry.setArrheniusCoefficients(this->converter.vectorPair(data.arrheniusCoefficients,Converter::reaction));
}

void UseCaseInteractor::initializeAbortCriterium(){
    this->abortCriterium.reset();
}

void UseCaseInteractor::execute(){
    this->state.rateConstants =  this->chemistry.getRateConstants(this->state.temperature);
    this->state.reactionRates =  this->chemistry.getReactionRates(this->state.concentrations,this->state.rateConstants);
    this->state.concentrationDiffs = this->chemistry.getConcentrationDiff(this->state.reactionRates);
    this->state.concentrations =  this->integrator.integrate(this->state.concentrations,this->state.concentrationDiffs);
    this->state.time = this->state.time + this->integrator.getTimeStep();
}

void UseCaseInteractor::report(){
    this->simulationState->setState(this->state);
    this->simulationState->notify();
}

Chemistry::Mode UseCaseInteractor::chemistryMode(const std::string& str) const{
    if(str=="const_k"){
        return Chemistry::const_k;
    }else if(str=="interpol_k"){
        return Chemistry::interpol_k;
    }else if(str=="arrhenius_k"){
        return Chemistry::arrhenius_k;
    }else{
        throw Exception("No mode set","UseCaseInteractor::" + std::string(__FUNCTION__));
    }
}

Integrator::Mode UseCaseInteractor::integratorMode(const std::string& str) const{
    if(str=="const_dt"){
        return Integrator::const_dt;
    }else if(str=="var_dt"){
        return Integrator::var_dt;
    }else{
        throw Exception("No mode set","UseCaseInteractor::" + std::string(__FUNCTION__));
    }
}
