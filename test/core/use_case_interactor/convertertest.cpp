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

#include "convertertest.h"

ConverterTest::ConverterTest(const std::string& name)
                            :UnitTest(name){

}

InputData ConverterTest::getState() const{
    InputData state;
    InputData::Species spec1;
    InputData::Species spec2;
    InputData::Species spec3;
    InputData::Species spec4;
    InputData::Reaction reac;

    spec1.name = "C8H18";
    spec2.name = "O2";
    spec3.name = "CO2";
    spec4.name = "H2O";

    spec1.concentration = 4.0;
    spec2.concentration = 5.0;
    spec3.concentration = 8.0;
    spec4.concentration = 9.0;

    spec1.concentrationDiff = 3.0;
    spec2.concentrationDiff = 7.0;
    spec3.concentrationDiff = 13.0;
    spec4.concentrationDiff = 13.0;

    reac.name = "combustion";
    reac.mode = InputData::Reaction::const_k;
    reac.excessEnergy = 7.0;
    reac.rateConstant = 2.83583586672916e-15;
    reac.reactionRate = 7.2;
    reac.stoichiometricCoeffEducts = {InputData::SpeciesValuePair(spec1.name,1.0)
                                     ,InputData::SpeciesValuePair(spec2.name,7/2.0)
                                     ,InputData::SpeciesValuePair(spec3.name,0.0)
                                     ,InputData::SpeciesValuePair(spec4.name,0.0)};
    reac.stoichiometricCoeffProducts = {InputData::SpeciesValuePair(spec1.name,0.0)
                                       ,InputData::SpeciesValuePair(spec2.name,0.0)
                                       ,InputData::SpeciesValuePair(spec3.name,2.0)
                                       ,InputData::SpeciesValuePair(spec4.name,3.0)};
    reac.reactionPowers = {InputData::SpeciesValuePair(spec1.name,0.1)
                          ,InputData::SpeciesValuePair(spec2.name,1.65)
                          ,InputData::SpeciesValuePair(spec3.name,0.0)
                          ,InputData::SpeciesValuePair(spec4.name,0.0)};
    reac.rateConstantTable = {InputData::RateConstPair(1000.0,0.2)
                             ,InputData::RateConstPair(2000.0,0.3)
                             ,InputData::RateConstPair(3000.0,0.4)};
    reac.arrheniusCoefficients = InputData::ArrheniusCoeffPair(600.0,1235.05);

    state.integratorData.mode = InputData::IntegratorData::var_dt;
    state.integratorData.parameter = 0.1;
    state.integratorData.timeStep = 0.1;

    state.chemistryData.species.push_back(spec1);
    state.chemistryData.species.push_back(spec2);
    state.chemistryData.species.push_back(spec3);
    state.chemistryData.species.push_back(spec4);

    state.chemistryData.reactions.push_back(reac);

    state.chemistryData.temperature = 2000.0;

    return state;
}

InputData::Reaction::Mode ConverterTest::modeToMode(const Chemistry::Mode& mode) const{
    switch(mode){
    case Chemistry::const_k:
        return InputData::Reaction::const_k;
        break;
    case Chemistry::interpol_k:
        return InputData::Reaction::interpol_k;
        break;
    case Chemistry::arrhenius_k:
        return InputData::Reaction::arrhenius_k;
        break;
    case Chemistry::none:
        return InputData::Reaction::none;
        break;
    default:
        throw Exception("Mode<" + std::to_string(mode) + "> not found","ConverterTest::" + std::string(__FUNCTION__));
        break;
    }
}

void ConverterTest::setUpTest() const{
    InputData state(getState());
    Converter converter;
    std::map<size_t,std::string> speciesMap;
    std::map<size_t,std::string> reactionMap;

    converter.setUp(state.chemistryData.species,state.chemistryData.reactions);

    speciesMap = converter.getSpeciesMap();
    reactionMap = converter.getReactionMap();

    QCOMPARE(speciesMap.at(0),state.chemistryData.species.at(0).name);
    QCOMPARE(speciesMap.at(0),state.chemistryData.species.at(0).name);
    QCOMPARE(speciesMap.at(0),state.chemistryData.species.at(0).name);

    QCOMPARE(reactionMap.at(0),state.chemistryData.reactions.at(0).name);
}

void ConverterTest::chemModesTest() const{
    InputData state(getState());
    Converter converter;
    std::vector<Chemistry::Mode> chemModes;

    converter.setUp(state.chemistryData.species,state.chemistryData.reactions);

    chemModes = converter.chemModes(state.chemistryData.reactions);

    for(size_t i(0);i<chemModes.size();++i){
        QCOMPARE(modeToMode(chemModes.at(i)),state.chemistryData.reactions.at(i).mode);
    }
}

void ConverterTest::concentrationsTest() const{
    InputData state(getState());
    Converter converter;
    VectorXd concentrations;

    converter.setUp(state.chemistryData.species,state.chemistryData.reactions);

    concentrations = converter.concentrations(state.chemistryData.species);

    for(size_t i(0);i<concentrations.size();++i){
        QCOMPARE(concentrations.at(i),state.chemistryData.species.at(i).concentration);
    }
}

void ConverterTest::concentrationsDiffsTest() const{
    InputData state(getState());
    Converter converter;
    VectorXd concentrationDiffs;

    converter.setUp(state.chemistryData.species,state.chemistryData.reactions);

    concentrationDiffs = converter.concentrationsDiffs(state.chemistryData.species);

    for(size_t i(0);i<concentrationDiffs.size();++i){
        QCOMPARE(concentrationDiffs.at(i),state.chemistryData.species.at(i).concentrationDiff);
    }
}

void ConverterTest::reactionRatesTest() const{
    InputData state(getState());
    Converter converter;
    VectorXd reactionRates;

    converter.setUp(state.chemistryData.species,state.chemistryData.reactions);

    reactionRates = converter.reactionRates(state.chemistryData.reactions);

    for(size_t i(0);i<reactionRates.size();++i){
        QCOMPARE(reactionRates.at(i),state.chemistryData.reactions.at(i).reactionRate);
    }
}

void ConverterTest::rateConstantsTest() const{
    InputData state(getState());
    Converter converter;
    VectorXd rateConstants;

    converter.setUp(state.chemistryData.species,state.chemistryData.reactions);

    rateConstants = converter.rateConstants(state.chemistryData.reactions);

    for(size_t i(0);i<rateConstants.size();++i){
        QCOMPARE(rateConstants.at(i),state.chemistryData.reactions.at(i).rateConstant);
    }
}

void ConverterTest::excessEnergiesTest() const{
    InputData state(getState());
    Converter converter;
    VectorXd excessEnergies;

    converter.setUp(state.chemistryData.species,state.chemistryData.reactions);

    excessEnergies = converter.excessEnergies(state.chemistryData.reactions);

    for(size_t i(0);i<excessEnergies.size();++i){
        QCOMPARE(excessEnergies.at(i),state.chemistryData.reactions.at(i).excessEnergy);
    }
}

void ConverterTest::rateConstantsTablesTest() const{
    InputData state(getState());
    Converter converter;
    std::vector<InterpolationTable> rateConstantsTables;

    converter.setUp(state.chemistryData.species,state.chemistryData.reactions);

    rateConstantsTables = converter.rateConstantsTables(state.chemistryData.reactions);

    for(size_t i(0);i<rateConstantsTables.size();++i){
        for(size_t j(0);j<rateConstantsTables.at(i).getValueTable().size();++j){
            const double temperature = rateConstantsTables.at(i).getValueTable().at(j).first;
            const double temperatureRef = state.chemistryData.reactions.at(i).rateConstantTable.at(j).temperature;
            const double rateConst = rateConstantsTables.at(i).getValueTable().at(j).second;
            const double rateConstRef = state.chemistryData.reactions.at(i).rateConstantTable.at(j).rateConstant;

            QCOMPARE(temperature,temperatureRef);
            QCOMPARE(rateConst,rateConstRef);
        }
    }
}

void ConverterTest::stoichiometricCoeffEductsTest() const{
    InputData state(getState());
    Converter converter;
    MatrixXd stoichiometricCoeffEducts;

    converter.setUp(state.chemistryData.species,state.chemistryData.reactions);

    stoichiometricCoeffEducts = converter.stoichiometricCoeffEducts(state.chemistryData.reactions);

    for(size_t i(0);i<state.chemistryData.reactions.size();++i){
        for(size_t j(0);j<state.chemistryData.species.size();++j){
            QCOMPARE(stoichiometricCoeffEducts.at(i,j),state.chemistryData.reactions.at(i).stoichiometricCoeffEducts.at(j).value);
        }
    }
}

void ConverterTest::stoichiometricCoeffProductsTest() const{
    InputData state(getState());
    Converter converter;
    MatrixXd stoichiometricCoeffProducts;

    converter.setUp(state.chemistryData.species,state.chemistryData.reactions);

    stoichiometricCoeffProducts = converter.stoichiometricCoeffProducts(state.chemistryData.reactions);

    for(size_t i(0);i<state.chemistryData.reactions.size();++i){
        for(size_t j(0);j<state.chemistryData.species.size();++j){
            QCOMPARE(stoichiometricCoeffProducts.at(i,j),state.chemistryData.reactions.at(i).stoichiometricCoeffProducts.at(j).value);
        }
    }
}

void ConverterTest::reactionPowersTest() const{
    InputData state(getState());
    Converter converter;
    MatrixXd reactPows;

    converter.setUp(state.chemistryData.species,state.chemistryData.reactions);

    reactPows = converter.reactionPowers(state.chemistryData.reactions);

    for(size_t i(0);i<state.chemistryData.reactions.size();++i){
        for(size_t j(0);j<state.chemistryData.species.size();++j){
            QCOMPARE(reactPows.at(i,j),state.chemistryData.reactions.at(i).reactionPowers.at(j).value);
        }
    }
}

void ConverterTest::arrheniusCoefficientsTest() const{
    InputData state(getState());
    Converter converter;
    std::vector<std::pair<double,double>> coeffs;

    converter.setUp(state.chemistryData.species,state.chemistryData.reactions);

    coeffs = converter.arrheniusCoefficients(state.chemistryData.reactions);

    for(size_t i(0);i<state.chemistryData.reactions.size();++i){
        const double prefactor(coeffs.at(i).first);
        const double prefactorRef(state.chemistryData.reactions.at(i).arrheniusCoefficients.preFactor);
        const double actEnerg(coeffs.at(i).second);
        const double actEnergRef(state.chemistryData.reactions.at(i).arrheniusCoefficients.activationEnergy);

        QCOMPARE(prefactor,prefactorRef);
        QCOMPARE(actEnerg,actEnergRef);
    }
}

void ConverterTest::integratorModeTest() const{
    InputData::IntegratorData::Mode inpt1(InputData::IntegratorData::const_dt);
    InputData::IntegratorData::Mode inpt2(InputData::IntegratorData::var_dt);
    Integrator::Mode ref1(Integrator::const_dt);
    Integrator::Mode ref2(Integrator::var_dt);
    Converter converter;

    QCOMPARE(converter.integratorMode(inpt1),ref1);
    QCOMPARE(converter.integratorMode(inpt2),ref2);
;}
