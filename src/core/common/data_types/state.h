#pragma once

#include <map>

#include "../math/matrixxd.h"

struct State{
    std::map<std::size_t,std::string> speciesMap;
    std::map<std::size_t,std::string> reactionMap;
    VectorXd concentrations;
    VectorXd reactionRates;
    VectorXd rateConstants;
    double time = 0.0;
    double temperature = 0.0;
    double cv = 0.0;
};
