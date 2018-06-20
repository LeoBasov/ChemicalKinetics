#pragma once

#include <map>

#include "../math/matrixxd.h"

class State
{
public:
    State();
    ~State();

    void setUp(const std::vector<std::string>& species,const std::vector<std::string>& reactions);
    void clear();

private:
    std::map<std::string,std::size_t> speciesMap;
    std::map<std::string,std::size_t> reactionMap;
    VectorXd concentrations;
    VectorXd reactionRates;
    MatrixXd stoichiometricCoeffEducts;
    MatrixXd stoichiometricCoeffProducts;
    MatrixXd reactionPowers;
    double time = 0.0;
    double temperature = 0.0;
    double cv = 0.0;

    void resize(const size_t& row,const size_t& column);
};
