#include "chemistrytest.h"

ChemistryTest::ChemistryTest(const std::string& name)
                            :UnitTest(name){

}

InputData ChemistryTest::getState() const{
    InputData state;
    InputData::Species spec1;
    InputData::Species spec2;
    InputData::Species spec3;
    InputData::Species spec4;
    InputData::Reaction reac1;
    InputData::Reaction reac2;
    InputData::Reaction reac3;

    spec1.name = "C8H18";
    spec2.name = "O2";
    spec3.name = "CO2";
    spec4.name = "H2O";

    spec1.concentration = 4.0;
    spec2.concentration = 4.0;
    spec3.concentration = 0.0;
    spec4.concentration = 0.0;

    reac1.name = "combustion1";
    reac1.mode = "const_k";
    reac1.rateConstant = 2.83583586672916e-15;
    reac1.excessEnergy = 1.0;
    reac1.stoichiometricCoeffEducts = {InputData::SpeciesValuePair(spec1.name,1.0)
                                     ,InputData::SpeciesValuePair(spec2.name,0.0)
                                     ,InputData::SpeciesValuePair(spec3.name,0.0)
                                     ,InputData::SpeciesValuePair(spec4.name,0.0)};
    reac1.stoichiometricCoeffProducts = {InputData::SpeciesValuePair(spec1.name,0.0)
                                       ,InputData::SpeciesValuePair(spec2.name,0.0)
                                       ,InputData::SpeciesValuePair(spec3.name,0.0)
                                       ,InputData::SpeciesValuePair(spec4.name,0.0)};
    reac1.reactionPowers = {InputData::SpeciesValuePair(spec1.name,1.0)
                          ,InputData::SpeciesValuePair(spec2.name,0.0)
                          ,InputData::SpeciesValuePair(spec3.name,0.0)
                          ,InputData::SpeciesValuePair(spec4.name,0.0)};

    reac2.name = "combustion2";
    reac2.mode = "interpol_k";
    reac2.rateConstant = 2.83583586672916e-15;
    reac2.excessEnergy = -3.0;
    reac2.rateConstantTable = {InputData::RateConstPair(1000.0,100.0)
                              ,InputData::RateConstPair(2000.0,200.0)};
    reac2.stoichiometricCoeffEducts = {InputData::SpeciesValuePair(spec1.name,0.0)
                                     ,InputData::SpeciesValuePair(spec2.name,2.0)
                                     ,InputData::SpeciesValuePair(spec3.name,0.0)
                                     ,InputData::SpeciesValuePair(spec4.name,0.0)};
    reac2.stoichiometricCoeffProducts = {InputData::SpeciesValuePair(spec1.name,0.0)
                                       ,InputData::SpeciesValuePair(spec2.name,0.0)
                                       ,InputData::SpeciesValuePair(spec3.name,0.0)
                                       ,InputData::SpeciesValuePair(spec4.name,0.0)};
    reac2.reactionPowers = {InputData::SpeciesValuePair(spec1.name,0.0)
                          ,InputData::SpeciesValuePair(spec2.name,2.0)
                          ,InputData::SpeciesValuePair(spec3.name,0.0)
                          ,InputData::SpeciesValuePair(spec4.name,0.0)};

    reac3.name = "combustion3";
    reac3.mode = "arrhenius_k";
    reac3.rateConstant = 2.83583586672916e-15;
    reac3.excessEnergy = 7.0;
    reac3.stoichiometricCoeffEducts = {InputData::SpeciesValuePair(spec1.name,0.0)
                                     ,InputData::SpeciesValuePair(spec2.name,0.0)
                                     ,InputData::SpeciesValuePair(spec3.name,3.0)
                                     ,InputData::SpeciesValuePair(spec4.name,0.0)};
    reac3.stoichiometricCoeffProducts = {InputData::SpeciesValuePair(spec1.name,0.0)
                                       ,InputData::SpeciesValuePair(spec2.name,0.0)
                                       ,InputData::SpeciesValuePair(spec3.name,0.0)
                                       ,InputData::SpeciesValuePair(spec4.name,0.0)};
    reac3.reactionPowers = {InputData::SpeciesValuePair(spec1.name,0.0)
                          ,InputData::SpeciesValuePair(spec2.name,0.0)
                          ,InputData::SpeciesValuePair(spec3.name,3.0)
                          ,InputData::SpeciesValuePair(spec4.name,0.0)};
    reac3.arrheniusCoefficients = InputData::ArrheniusCoeffPair(0.2,0.7);

    state.integratorData.mode = "var_dt";
    state.integratorData.parameter = 0.1;
    state.integratorData.timeStep = 0.1;

    state.chemistryData.species.push_back(spec1);
    state.chemistryData.species.push_back(spec2);
    state.chemistryData.species.push_back(spec3);
    state.chemistryData.species.push_back(spec4);

    state.chemistryData.reactions.push_back(reac1);
    state.chemistryData.reactions.push_back(reac2);
    state.chemistryData.reactions.push_back(reac3);

    state.chemistryData.temperature = 2000.0;

    return state;
}

Chemistry ChemistryTest::setUpChemisty() const{
    InputData::ChemistryData data(getState().chemistryData);
    Converter converter;
    Chemistry chemistry;

    converter.setUp(data.species,data.reactions);

    chemistry.setModes(converter.chemModes(data.reactions));
    chemistry.setReactionPowers(converter.reactionPowers(data.reactions));
    chemistry.setStoichiometricMatrix(  converter.stoichiometricCoeffProducts(data.reactions)
                                      - converter.stoichiometricCoeffEducts(data.reactions));
    chemistry.setRateConstants(converter.rateConstants(data.reactions));
    chemistry.setRateConstants(converter.rateConstantsTables(data.reactions));
    chemistry.setArrheniusCoefficients(converter.arrheniusCoefficients(data.reactions));
    chemistry.setExcessEnergies(converter.excessEnergies(data.reactions));

    return chemistry;
}

void ChemistryTest::getRateConstantsTest() const{
    const double temperature(1500.0);
    InputData::ChemistryData data(getState().chemistryData);
    Chemistry chemistry(setUpChemisty());
    VectorXd rateConstants(chemistry.getRateConstants(temperature));

    QCOMPARE(rateConstants.at(0),data.reactions.at(0).rateConstant);
    QCOMPARE(rateConstants.at(1),150.0);
    QCOMPARE(rateConstants.at(2)
            , data.reactions.at(2).arrheniusCoefficients.preFactor
             *std::exp(-data.reactions.at(2).arrheniusCoefficients.activationEnergy/(Constants::universalGasConst*temperature)));
}

void ChemistryTest::getReactionRatesTest() const{
    const double temperature(1500.0);
    InputData::ChemistryData data(getState().chemistryData);
    Chemistry chemistry(setUpChemisty());
    Converter converter;

    converter.setUp(data.species,data.reactions);

    const VectorXd rateConstants(chemistry.getRateConstants(temperature));
    const VectorXd reactionRates(chemistry.getReactionRates(converter.concentrations(data.species),rateConstants));

    QCOMPARE(reactionRates.at(0),rateConstants.at(0)*std::pow(data.species.at(0).concentration,1.0));
    QCOMPARE(reactionRates.at(1),rateConstants.at(1)*std::pow(data.species.at(1).concentration,2.0));
    QCOMPARE(reactionRates.at(2),rateConstants.at(2)*std::pow(data.species.at(2).concentration,3.0));
}

void ChemistryTest::getConcentrationDiffTest() const{
    const double temperature(1500.0);
    InputData::ChemistryData data(getState().chemistryData);
    Chemistry chemistry(setUpChemisty());
    Converter converter;

    converter.setUp(data.species,data.reactions);

    const VectorXd rateConstants(chemistry.getRateConstants(temperature));
    const VectorXd reactionRates(chemistry.getReactionRates(converter.concentrations(data.species),rateConstants));
    const VectorXd concentrationDiffs(chemistry.getConcentrationDiff(reactionRates));

    QCOMPARE(concentrationDiffs.at(0),reactionRates.at(0)*(-1.0));
    QCOMPARE(concentrationDiffs.at(1),reactionRates.at(1)*(-2.0));
    QCOMPARE(concentrationDiffs.at(2),reactionRates.at(2)*(3.0));
    QCOMPARE(concentrationDiffs.at(3),reactionRates.at(2)*(0.0));
}

void ChemistryTest::setExcessEnergiesTest() const{
    InputData::ChemistryData data(getState().chemistryData);
    Chemistry chemistry(setUpChemisty());
    VectorXd concentrationDiffs({1.0,2.0,3.0});
    VectorXd ecxessEnergiesRef({data.reactions.at(0).excessEnergy
                               ,data.reactions.at(1).excessEnergy
                               ,data.reactions.at(2).excessEnergy});

    QCOMPARE(chemistry.getEnergyDiff(concentrationDiffs),ecxessEnergiesRef*concentrationDiffs);
}
