/* =============================================================================================
 * ChemicalKinetics
 *
 * A tool to calculate chemistry kinetics
 * ---------------------------------------------------------------------------------------------
 * Copyright (C) 2018  Leo Basov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public Licens
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * =============================================================================================
 */

#pragma once

#include "../../common/math/vectorxd.h"
#include "../../common/constants.h"

namespace ThermodynamicsAlgorithms{

enum Species{monoatomic=1,diatomic=2,none=0};

double internalDOF(const double& temperature,const double& characteresticVibrationalsTemp,const Species& species);
double diatomicInternalDOF(const double& temperature,const double& characteresticVibrationalsTemp);
VectorXd internalDOF(const VectorXd& temperatures,const VectorXd& characteresticVibrationalsTemps,const std::vector<Species>& species);
double totalEnergy(const VectorXd& concentrations,const VectorXd& temperatures,const VectorXd& internalDOF);

}
