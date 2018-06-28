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

#include "chemistryalgorithms.h"

double ChemistryAlgorithms::arrheniusEquation(const double& preFact,const double& activationEnergy,const double& temperature){
    return preFact*std::exp((-1.0)*activationEnergy/(Constants::universalGasConst*temperature));
}

VectorXd ChemistryAlgorithms::reactionRatePowLaw(const VectorXd& rateConstants,const VectorXd& concentrations,const MatrixXd& reactionPows){
    VectorXd reactionRates(rateConstants);

    for(size_t i(0);i<rateConstants.size();++i){
        for(size_t j(0);j<concentrations.size();++j){
            reactionRates.at(i) *= std::pow(concentrations.at(j),reactionPows.at(i,j));
        }
    }

    return reactionRates;
}

VectorXd ChemistryAlgorithms::concentrationDifferential(const MatrixXd& stochiometricMatrix,const VectorXd& reactionRates){
    return stochiometricMatrix.transpose()*reactionRates;
}
