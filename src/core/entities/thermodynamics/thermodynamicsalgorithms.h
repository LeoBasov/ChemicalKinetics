#pragma once

#include "../../common/math/vectorxd.h"

namespace ThermodynamicsAlgorithms{

double totalEnergy(const VectorXd& concentrations,const VectorXd& temperatures,const VectorXd& internalDOF);

}
