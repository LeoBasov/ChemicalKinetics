#pragma once

#include "../../common/math/matrixxd.h"

namespace ChemistryAlgorithms{

VectorXd reactionRatePowLaw(const VectorXd& rateConstants,const VectorXd& concentrations,const MatrixXd& reactionPows);

}
