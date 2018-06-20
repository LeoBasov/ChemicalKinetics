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
