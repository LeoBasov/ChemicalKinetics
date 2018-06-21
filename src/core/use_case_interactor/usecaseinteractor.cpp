#include "usecaseinteractor.h"

UseCaseInteractor::UseCaseInteractor()
{

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
    this->state.reactionRates = converter.vector(data.chemistryData.reactionRates,Converter::reaction);
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
    this->chemistry.setRateConstants(this->state.rateConstants);
    this->chemistry.setRateConstants(data.rateConstantsTables);
    this->chemistry.setArrheniusCoefficients(data.arrheniusCoefficients);
}

void UseCaseInteractor::execute(){
    VectorXd concentrationDiffs;

    this->state.rateConstants =  this->chemistry.getRateConstants(this->state.temperature);
    this->state.reactionRates =  this->chemistry.getReactionRates(this->state.concentrations,this->state.rateConstants);

    concentrationDiffs = this->chemistry.getConcentrationDiff(this->state.reactionRates);

    this->state.concentrations =  this->integrator.integrate(this->state.concentrations,concentrationDiffs);
}

void UseCaseInteractor::report(){
    //DUMMY
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
