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

#include "integratoralgorithms.h"

double IntegratorAlgorithms::timeStep(const VectorXd& values,const VectorXd& diff,const double& frac){
    double timeStep(std::numeric_limits<double>::max());

    for(size_t i(0);i<values.size();++i){
        const double timeStepNew(std::abs(frac*values.at(i)/diff.at(i)));

        if(timeStepNew==0 || diff.at(i)==0){
            continue;
        }else if(timeStepNew < timeStep){
            timeStep = timeStepNew;
        }
    }

    return timeStep;
}

VectorXd IntegratorAlgorithms::firstOrder(const VectorXd& values,const VectorXd& diff,const double& timeStep){
    return values + (diff*timeStep);
}
