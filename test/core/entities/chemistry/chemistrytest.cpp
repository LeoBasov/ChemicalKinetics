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
    reac1.stoichiometricCoeffEducts = {InputData::SpeciesValuePair(spec1.name,1.0)
                                     ,InputData::SpeciesValuePair(spec2.name,7/2.0)
                                     ,InputData::SpeciesValuePair(spec3.name,0.0)
                                     ,InputData::SpeciesValuePair(spec4.name,0.0)};
    reac1.stoichiometricCoeffProducts = {InputData::SpeciesValuePair(spec1.name,0.0)
                                       ,InputData::SpeciesValuePair(spec2.name,0.0)
                                       ,InputData::SpeciesValuePair(spec3.name,2.0)
                                       ,InputData::SpeciesValuePair(spec4.name,3.0)};
    reac1.reactionPowers = {InputData::SpeciesValuePair(spec1.name,0.1)
                          ,InputData::SpeciesValuePair(spec2.name,1.65)
                          ,InputData::SpeciesValuePair(spec3.name,0.0)
                          ,InputData::SpeciesValuePair(spec4.name,0.0)};

    reac2.name = "combustion2";
    reac2.mode = "interpol_k";
    reac2.rateConstant = 2.83583586672916e-15;
    reac2.rateConstantTable = {InputData::RateConstPair(1000.0,100.0)
                              ,InputData::RateConstPair(2000.0,200.0)};
    reac2.stoichiometricCoeffEducts = {InputData::SpeciesValuePair(spec1.name,1.0)
                                     ,InputData::SpeciesValuePair(spec2.name,7/2.0)
                                     ,InputData::SpeciesValuePair(spec3.name,0.0)
                                     ,InputData::SpeciesValuePair(spec4.name,0.0)};
    reac2.stoichiometricCoeffProducts = {InputData::SpeciesValuePair(spec1.name,0.0)
                                       ,InputData::SpeciesValuePair(spec2.name,0.0)
                                       ,InputData::SpeciesValuePair(spec3.name,2.0)
                                       ,InputData::SpeciesValuePair(spec4.name,3.0)};
    reac2.reactionPowers = {InputData::SpeciesValuePair(spec1.name,0.1)
                          ,InputData::SpeciesValuePair(spec2.name,1.65)
                          ,InputData::SpeciesValuePair(spec3.name,0.0)
                          ,InputData::SpeciesValuePair(spec4.name,0.0)};

    reac3.name = "combustion3";
    reac3.mode = "arrhenius_k";
    reac3.rateConstant = 2.83583586672916e-15;
    reac3.stoichiometricCoeffEducts = {InputData::SpeciesValuePair(spec1.name,1.0)
                                     ,InputData::SpeciesValuePair(spec2.name,7/2.0)
                                     ,InputData::SpeciesValuePair(spec3.name,0.0)
                                     ,InputData::SpeciesValuePair(spec4.name,0.0)};
    reac3.stoichiometricCoeffProducts = {InputData::SpeciesValuePair(spec1.name,0.0)
                                       ,InputData::SpeciesValuePair(spec2.name,0.0)
                                       ,InputData::SpeciesValuePair(spec3.name,2.0)
                                       ,InputData::SpeciesValuePair(spec4.name,3.0)};
    reac3.reactionPowers = {InputData::SpeciesValuePair(spec1.name,0.1)
                          ,InputData::SpeciesValuePair(spec2.name,1.65)
                          ,InputData::SpeciesValuePair(spec3.name,0.0)
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
    chemistry.setRateConstants(converter.rateConstatns(data.reactions));
    chemistry.setRateConstants(converter.rateConstantsTables(data.reactions));
    chemistry.setArrheniusCoefficients(converter.arrheniusCoefficients(data.reactions));

    return chemistry;
}
