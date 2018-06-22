#pragma once

#include <string>
#include <vector>

struct InputData{
    struct IntegratorData
    {
        std::string mode = "none";

        double timeStep = 0.0;
        double parameter = 0.0;
    };

    struct ChemistryData{
        std::string mode = "none";

        std::vector<std::string> speciesNames;
        std::vector<std::string> reactionNames;

        std::vector<std::pair<std::string,double>> concentrations;
        std::vector<std::pair<std::string,double>> reactionRates;
        std::vector<std::pair<std::string,double>> rateConstants;
        std::vector<std::vector<std::pair<double,double>>> rateConstantsTables;

        std::vector<std::pair<std::string,std::vector<std::pair<std::string,double>>>> stoichiometricCoeffEducts;
        std::vector<std::pair<std::string,std::vector<std::pair<std::string,double>>>> stoichiometricCoeffProducts;
        std::vector<std::pair<std::string,std::vector<std::pair<std::string,double>>>> reactionPowers;

        std::vector<std::pair<std::string,std::pair<double,double>>> arrheniusCoefficients;

        double temperature = 0.0;
    };

    IntegratorData integratorData;
    ChemistryData chemistryData;
};
