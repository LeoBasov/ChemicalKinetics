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
    void setArrheniusCoefficients(const double& preFact,const double& activationEnergy);

    VectorXd calculateConcentrationDiff(const VectorXd& concentrations) const;
    VectorXd calculateConcentrationDiff(const VectorXd& concentrations,const VectorXd& rateConstants);

private:
    Mode mode = none;
    VectorXd rateConstants;
    MatrixXd stoichiometricMatrix;
    MatrixXd reactionPowers;
    double arrheniusPreFact = 0.0;
    double arrheniusActivationEnergy = 0.0;
};
