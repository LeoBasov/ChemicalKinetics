#pragma once

#include "../../common/math/matrixxd.h"
#include "../../common/constants.h"

namespace ChemistryAlgorithms{

double arrheniusEquation(const double& preFact,const double& activationEnergy,const double& temperature);
VectorXd reactionRatePowLaw(const VectorXd& rateConstants,const VectorXd& concentrations,const MatrixXd& reactionPows);
VectorXd concentrationDifferential(const MatrixXd& stochiometricMatrix, const VectorXd& reactionRates);

}
