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
    this->state.setUp(data.chemistryData.speciesNames,data.chemistryData.reactionNames);
    this->state.setTemperature(data.chemistryData.temperature);

    for(auto pair : data.chemistryData.concentrations){
        this->state.setConcentration(pair.first,pair.second);
    }

    for(size_t i(0);i<data.chemistryData.reactionRates.size();++i){
        this->state.setReactionRate(data.chemistryData.reactionRates.at(i).first,data.chemistryData.reactionRates.at(i).second);
        this->state.setRateConstant(data.chemistryData.rateConstants.at(i).first,data.chemistryData.rateConstants.at(i).second);
    }

    for(size_t i(0);i<data.chemistryData.stoichiometricCoeffEducts.size();++i){
        const std::string reaction(data.chemistryData.stoichiometricCoeffEducts.at(i).first);

        for(size_t j(0);j<data.chemistryData.stoichiometricCoeffEducts.at(i).second.size();++j){
            const std::string species(data.chemistryData.stoichiometricCoeffEducts.at(i).second.at(j).first);
            const double stoichiometricCoeffEduct((data.chemistryData.stoichiometricCoeffEducts.at(i).second.at(j).second));
            const double stoichiometricCoeffProduct((data.chemistryData.stoichiometricCoeffProducts.at(i).second.at(j).second));
            const double reactionPower((data.chemistryData.reactionPowers.at(i).second.at(j).second));

            this->state.setStoichiometricCoeffEduct(species,reaction,stoichiometricCoeffEduct);
            this->state.setStoichiometricCoeffProduct(species,reaction,stoichiometricCoeffProduct);
            this->state.setReactionPower(species,reaction,reactionPower);
        }
    }
}

void UseCaseInteractor::initializeIntergrator(const InputData::IntegratorData& data){
    if(data.mode=="const_dt"){
        this->integrator.setMode(Integrator::const_dt);
    }else if(data.mode=="var_dt"){
        this->integrator.setMode(Integrator::var_dt);
    }else if(data.mode=="none"){
        throw Exception("No mode set","UseCaseInteractor::" + std::string(__FUNCTION__));
    }

    this->integrator.setTimeStep(data.timeStep);
    this->integrator.setTimeStepParamter(data.parameter);
}

void UseCaseInteractor::initializeChemistry(const InputData::ChemistryData& data){
    if(data.mode=="const_k"){
        this->chemistry.setMode(Chemistry::const_k);
    }else if(data.mode=="interpol_k"){
        this->chemistry.setMode(Chemistry::interpol_k);
    }else if(data.mode=="arrhenius_k"){
        this->chemistry.setMode(Chemistry::arrhenius_k);
    }else{
        throw Exception("No mode set","UseCaseInteractor::" + std::string(__FUNCTION__));
    }

    this->chemistry.setReactionPowers(this->state.getReactionPowers());
    this->chemistry.setStoichiometricMatrix(this->state.getStoichiometricMatrix());
    this->chemistry.setRateConstants(this->state.getRateConstants());
    this->chemistry.setRateConstants(data.rateConstantsTables);
    this->chemistry.setArrheniusCoefficients(data.arrheniusCoefficients);
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
