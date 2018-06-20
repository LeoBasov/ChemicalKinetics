#pragma once

#include "chemistryalgorithms.h"

class Chemistry
{
public:
    Chemistry();

    void setReactionPowers(const MatrixXd& reactionPowers);
    void setReactionStoichiometricMatrix(const MatrixXd& stoichiometricMatrix);
    void setRateConstants(const VectorXd& rateConstants);

    VectorXd calculateConcentrationDiff(const VectorXd& concentrations) const;
    VectorXd calculateConcentrationDiff(const VectorXd& concentrations,const VectorXd& rateConstants);

private:
    VectorXd rateConstants;
    MatrixXd stoichiometricMatrix;
    MatrixXd reactionPowers;
};
