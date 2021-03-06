/* =============================================================================================
 * ChemicalKinetics
 *
 * A tool to calculate chemistry kinetics
 * ---------------------------------------------------------------------------------------------
 * Copyright (C) 2018  Leo Basov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public Licens
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * =============================================================================================
 */

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
    initializeAbortCriterium(data.abortCriterion);
    initializeThermodynamics(data.thermodynamicData);
}

void UseCaseInteractor::initializeState(const InputData& data){
    this->converter.setUp(data.chemistryData.species,data.chemistryData.reactions);

    this->state.reactionMap = this->converter.getReactionMap();
    this->state.speciesMap = this->converter.getSpeciesMap();
    this->state.temperature = data.thermodynamicData.temperature;
    this->state.concentrations = this->converter.concentrations(data.chemistryData.species);
    this->state.concentrationDiffs = this->converter.concentrationsDiffs(data.chemistryData.species);
    this->state.reactionRates = this->converter.reactionRates(data.chemistryData.reactions);
    this->state.rateConstants = this->converter.rateConstants(data.chemistryData.reactions);
    this->state.time = 0.0;
}

void UseCaseInteractor::initializeIntergrator(const InputData::IntegratorData& data){
    this->integrator.setMode(this->converter.integratorMode(data.mode));
    this->integrator.setTimeStep(data.timeStep);
    this->integrator.setTimeStepParamter(data.parameter);
}

void UseCaseInteractor::initializeChemistry(const InputData::ChemistryData& data){
    this->chemistry.setModes(this->converter.chemModes(data.reactions));
    this->chemistry.setReactionPowers(this->converter.reactionPowers(data.reactions));
    this->chemistry.setStoichiometricMatrix(  this->converter.stoichiometricCoeffProducts(data.reactions)
                                            - this->converter.stoichiometricCoeffEducts(data.reactions));
    this->chemistry.setRateConstants(this->converter.rateConstants(data.reactions));
    this->chemistry.setRateConstants(this->converter.rateConstantsTables(data.reactions));
    this->chemistry.setArrheniusCoefficients(this->converter.arrheniusCoefficients(data.reactions));
    this->chemistry.setExcessEnergies(this->converter.excessEnergies(data.reactions));
}

void UseCaseInteractor::initializeAbortCriterium(const InputData::AbortCriterion& abortCriterion){
    this->abortCriterium.reset();
    this->abortCriterium.setParameter(abortCriterion.parameter);
    this->abortCriterium.setTimeStepNumber(abortCriterion.timeStepNumber);
    this->abortCriterium.setMode(this->converter.abortCriteriumMode(abortCriterion.mode));
}

void UseCaseInteractor::initializeThermodynamics(const InputData::ThermodynamicData& thermodynamicData){
    Thermodynamics::Mode mode;

    switch (thermodynamicData.mode){
    case InputData::ThermodynamicData::var_T:
        mode = Thermodynamics::Mode::var_T;
        break;
    case InputData::ThermodynamicData::const_T:
        mode = Thermodynamics::Mode::const_T;
        break;
    default:
        throw Exception("Undefined mode <" + std::to_string(thermodynamicData.mode) + ">", "UseCaseInteractor::" + std::string(__FUNCTION__));
    }

    this->thermodynamics.setMode(mode);
    this->thermodynamics.setSpecies(getThermodynamicsSpecies());
    this->thermodynamics.setTotalEnergy(getTotalEnergy());
    this->thermodynamics.setLastTemperature(thermodynamicData.temperature);
    this->thermodynamics.setTemperatureCalcAccuracy(thermodynamicData.temperatureCalcAccuracy);
}

std::vector<ThermodynamicsAlgorithms::Species> UseCaseInteractor::getThermodynamicsSpecies() const{
    std::vector<ThermodynamicsAlgorithms::Species> allSpecies;

    for(size_t st(0); st < this->state.concentrations.size(); ++st){
        ThermodynamicsAlgorithms::Species species(0.0, ThermodynamicsAlgorithms::Species::monoatomic);

        allSpecies.push_back(species);
    }

    return allSpecies;
}

double UseCaseInteractor::getTotalEnergy() const{
    VectorXd temperatures(this->state.concentrations.size());

    for(size_t st(0); st < this->state.concentrations.size(); ++st){
        temperatures.at(st) = this->state.temperature;
    }

    return this->thermodynamics.totalEnergy(this->state.concentrations, temperatures);
}

void UseCaseInteractor::execute(){
    this->state.rateConstants =  this->chemistry.getRateConstants(this->state.temperature);
    this->state.reactionRates =  this->chemistry.getReactionRates(this->state.concentrations,this->state.rateConstants);
    this->state.concentrationDiffs = this->chemistry.getConcentrationDiff(this->state.reactionRates);
    this->state.concentrations =  this->integrator.integrate(this->state.concentrations,this->state.concentrationDiffs);
    this->state.temperature = this->thermodynamics.getNewTemperature(this->state.concentrations
                                                                    ,this->chemistry.getEnergyDiff(this->state.reactionRates, this->integrator.getTimeStep()));
    this->state.time = this->state.time + this->integrator.getTimeStep();
}

void UseCaseInteractor::report(){
    this->simulationState->setState(this->state);
    this->simulationState->notify();
}
