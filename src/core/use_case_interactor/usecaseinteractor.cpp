#include "usecaseinteractor.h"

UseCaseInteractor::UseCaseInteractor(const std::shared_ptr<SimulationState> &simState)
                                    :simulationState(simState){

}

void UseCaseInteractor::start(const InputData& data){
    initialize(data);

    while(this->abortCriterium.valid()){
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
}

void UseCaseInteractor::initializeState(const InputData& data){
    this->converter.setUp(data.chemistryData.speciesNames,data.chemistryData.reactionNames);

    this->state.reactionMap = this->converter.getReactionMap();
    this->state.speciesMap = this->converter.getSpeciesMap();
    this->state.temperature = data.chemistryData.temperature;
    this->state.concentrations = converter.vector(data.chemistryData.concentrations,Converter::species);
    this->state.concentrationDiffs = converter.vector(data.chemistryData.concentrationDiffs,Converter::species);
    this->state.reactionRates = converter.vector(data.chemistryData.reactionRates,Converter::reaction);
    this->state.rateConstants = converter.vector(data.chemistryData.rateConstants,Converter::reaction);
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
    this->chemistry.setRateConstants(converter.vector(data.rateConstants,Converter::reaction));
    this->chemistry.setRateConstants(this->converter.vectorTable(data.rateConstantsTables,Converter::reaction));
    this->chemistry.setArrheniusCoefficients(this->converter.vectorPair(data.arrheniusCoefficients,Converter::reaction));
}

void UseCaseInteractor::execute(){
    this->state.rateConstants =  this->chemistry.getRateConstants(this->state.temperature);
    this->state.reactionRates =  this->chemistry.getReactionRates(this->state.concentrations,this->state.rateConstants);
    this->state.concentrationDiffs = this->chemistry.getConcentrationDiff(this->state.reactionRates);
    this->state.concentrations =  this->integrator.integrate(this->state.concentrations,this->state.concentrationDiffs);
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
