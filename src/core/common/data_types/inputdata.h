#pragma once

#include <string>
#include <vector>

struct InputData{
    struct RateConstPair{
        RateConstPair(const double& temperature,const double& rateConstant)
                     :temperature(temperature),rateConstant(rateConstant){}

        double temperature = 0.0;
        double rateConstant = 0.0;
    };

    struct ArrheniusCoeffPair{
        double preFactor = 0.0;
        double activationEnergy = 0.0;
    };

    struct SpeciesValuePair{
        SpeciesValuePair(const std::string& species,const double& value)
                        :species(species),value(value){}

        std::string species;
        double value = 0.0;
    };

    struct Reaction{
        std::string name;
        std::string mode = "none";

        double reactionRate = 0.0;
        double rateConstant = 0.0;
        std::vector<RateConstPair> rateConstantTables;
        ArrheniusCoeffPair arrheniusCoefficients;

        std::vector<SpeciesValuePair> stoichiometricCoeffEducts;
        std::vector<SpeciesValuePair> stoichiometricCoeffProducts;
        std::vector<SpeciesValuePair> reactionPowers;
    };

    struct Species{
        std::string name;

        double concentration = 0.0;
        double concentrationDiff = 0.0;
        double temperature = 0.0;
    };

    struct ChemistryData{
        std::string mode = "none";

        std::vector<Species> species;
        std::vector<Reaction> reactions;

        std::vector<std::pair<std::string,double>> concentrationDiffs;
        std::vector<std::pair<std::string,double>> reactionRates;
        std::vector<std::pair<std::string,double>> rateConstants;
        std::vector<std::pair<std::string,std::vector<std::pair<double,double>>>> rateConstantsTables;

        std::vector<std::pair<std::string,std::vector<std::pair<std::string,double>>>> stoichiometricCoeffEducts;
        std::vector<std::pair<std::string,std::vector<std::pair<std::string,double>>>> stoichiometricCoeffProducts;
        std::vector<std::pair<std::string,std::vector<std::pair<std::string,double>>>> reactionPowers;

        std::vector<std::pair<std::string,std::pair<double,double>>> arrheniusCoefficients;

        double temperature = 0.0;
    };

    struct IntegratorData{
        std::string mode = "none";

        double timeStep = 0.0;
        double parameter = 0.0;
    };

    ChemistryData chemistryData;
    IntegratorData integratorData;
};
