#pragma once

#include <limits>

#include "../../common/math/vectorxd.h"

namespace IntegratorAlgorithms{

double timeStep(const VectorXd& values,const VectorXd& diff,const double& frac);
VectorXd firstOrder(const VectorXd& values,const VectorXd& diff,const double& timeStep);

}
