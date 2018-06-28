#pragma once

#include "../../common/math/vectorxd.h"
#include "../../common/constants.h"

namespace ThermodynamicsAlgorithms{

VectorXd internamDOF(const VectorXd& temperatures,const VectorXd& characteresticVibrationalsTemps);
double totalEnergy(const VectorXd& concentrations,const VectorXd& temperatures,const VectorXd& internalDOF);

}
