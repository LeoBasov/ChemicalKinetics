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

#include "thermodynamicsalgorithms.h"

double ThermodynamicsAlgorithms::internalDOF(const double& temperature, const Species &species){
    switch (species.type) {
    case Species::monoatomic:
        return 0.0;
        break;
    case Species::diatomic:
        return diatomicInternalDOF(temperature,species.characteresticVibrationalsTemp);
        break;
    default:
        throw Exception("Type <" +std::to_string(species.type) + "> not defines."
                       ,"ThermodynamicsAlgorithms::" + std::string(__FUNCTION__));
        break;
    }
}

double ThermodynamicsAlgorithms::diatomicInternalDOF(const double& temperature,const double& characteresticVibrationalsTemp){
    const double fraction(characteresticVibrationalsTemp/temperature);
    const double denum(std::exp(fraction) - 1.0);

    return 2.0 + 2.0*fraction/denum;
}

VectorXd ThermodynamicsAlgorithms::internalDOF(const VectorXd& temperatures,const std::vector<Species> &species){
    VectorXd vec(temperatures.size());

    if(temperatures.size()!=species.size()){
        throw Exception("Length of temperatures <" + std::to_string(temperatures.size())
                       +"> != length species <" + std::to_string(species.size()) + ">."
                       ,"ThermodynamicsAlgorithms::" + std::string(__FUNCTION__));
    }

    for(size_t i(0);i<vec.size();++i){
        vec.at(i) = internalDOF(temperatures.at(i),species.at(i));
    }

    return vec;
}

double ThermodynamicsAlgorithms::totalEnergy(const VectorXd& concentrations,const VectorXd& temperatures,const VectorXd& internalDOF){
    const double factor(0.5*Constants::boltzmannConst);
    const double concentrSum(concentrations.sum());

    return concentrSum>0.0 ? concentrations*(temperatures*3.0*factor + VectorXd::elemWiseMult(internalDOF,temperatures)*factor)*(1.0/concentrSum) : 0.0;
}

double ThermodynamicsAlgorithms::totalEnergy(const VectorXd& concentrations,const VectorXd& temperatures,const std::vector<Species>& species){
    VectorXd dof(ThermodynamicsAlgorithms::internalDOF(temperatures,species));

    return ThermodynamicsAlgorithms::totalEnergy(concentrations,temperatures,dof);
}
