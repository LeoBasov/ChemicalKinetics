#pragma once

#include <map>

#include "../math/matrixxd.h"

class State
{
public:
    State();
    ~State();

    void clear();

    void setUp(const std::vector<std::string>& species,const std::vector<std::string>& reactions);

    void setConcentration(const std::string& species,const double& concentration);
    void setConcentrations(const VectorXd& concentrations);
    void setReactionRate(const std::string& reaction,const double& reactionRate);
    void setReactionRates(const VectorXd& reactionRates);
    void setRateConstant(const std::string& reaction,const double& rateConstant);
    void setRateConstants(const VectorXd& rateConstants);
    void setStoichiometricCoeffEduct(const std::string& species,const std::string& reaction,const double& coeff);
    void setStoichiometricCoeffProduct(const std::string& species,const std::string& reaction,const double& coeff);
    void setReactionPower(const std::string& species,const std::string& reaction,const double& pow);
    void setTime(const double& time);
    void setTemperature(const double& temperature);
    void setCv(const double& cv);

    const std::map<std::string,std::size_t>& getSpeciesMap() const;
    const std::map<std::string,std::size_t>& getReactionMap() const;

    const VectorXd& getConcentrations() const;
    const VectorXd& getReactionRates() const;
    const VectorXd& getRateConstants() const;
    const MatrixXd& getStoichiometricCoeffEducts() const;
    const MatrixXd& getStoichiometricCoeffProducts() const;
    MatrixXd getStoichiometricMatrix() const;
    const MatrixXd& getReactionPowers() const;
    double getTime() const;
    double getTemperature() const;
    double getCv() const;

private:
    std::map<std::string,std::size_t> speciesMap;
    std::map<std::string,std::size_t> reactionMap;
    VectorXd concentrations;
    VectorXd reactionRates;
    VectorXd rateConstants;
    MatrixXd stoichiometricCoeffEducts;
    MatrixXd stoichiometricCoeffProducts;
    MatrixXd reactionPowers;
    double time = 0.0;
    double temperature = 0.0;
    double cv = 0.0;

    void resize(const size_t& row,const size_t& column);
};
