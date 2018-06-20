#pragma once

#include "chemistryalgorithms.h"
#include "../../common/data_types/interpolationtable.h"

class Chemistry
{
public:
    enum Mode{none=0,const_k=1,interpol_k=2,arrhenius_k=3};

public:
    Chemistry();

    void setMode(const Mode& mode);
    void setReactionPowers(const MatrixXd& reactionPowers);
    void setReactionStoichiometricMatrix(const MatrixXd& stoichiometricMatrix);
    void setRateConstants(const VectorXd& rateConstants);
    void setRateConstants(const std::vector<InterpolationTable>& rateConstantsInterpolTables);
    void setArrheniusCoefficients(std::vector<std::pair<double,double>> arrheniusCoefficients);

    VectorXd calculateConcentrationDiff(const VectorXd& concentrations,const double& temperature) const;

    VectorXd getRateConstants(const double& temperature) const;
    VectorXd getReactionRates(const VectorXd& concentrations,const double& temperature) const;

private:
    Mode mode = none;
    VectorXd rateConstants;
    MatrixXd stoichiometricMatrix;
    MatrixXd reactionPowers;
    std::vector<InterpolationTable> rateConstantsInterpolTables;
    std::vector<std::pair<double,double>> arrheniusCoefficients; //first = pre factor, second = activation energy

    VectorXd interpolateRateConstants(const double& temperature) const;
    VectorXd calculateRateConstants(const double& temperature) const;
};
