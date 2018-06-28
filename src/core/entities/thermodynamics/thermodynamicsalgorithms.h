#pragma once

#include "../../common/math/vectorxd.h"
#include "../../common/constants.h"

namespace ThermodynamicsAlgorithms{

double totalEnergy(const VectorXd& concentrations,const VectorXd& temperatures,const VectorXd& internalDOF);

}
