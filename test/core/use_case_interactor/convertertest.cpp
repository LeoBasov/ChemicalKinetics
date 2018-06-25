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
    spec2.concentration = 4.0;
    spec3.concentration = 0.0;
    spec4.concentration = 0.0;

    reac.name = "combustion";
    reac.mode = "const_k";
    reac.rateConstant = 2.83583586672916e-15;
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

    state.integratorData.mode = "var_dt";
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
