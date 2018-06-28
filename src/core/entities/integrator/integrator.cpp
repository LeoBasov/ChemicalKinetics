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

#include "integrator.h"

Integrator::Integrator()
{

}

void Integrator::setMode(const Mode& mode){
    this->mode = mode;
}

void Integrator::setTimeStep(const double& timeStep){
    this->timeStep = timeStep;
}

void Integrator::setTimeStepParamter(const double& parameter){
    this->parameter = parameter;
}

double Integrator::getTimeStep() const{
    return this->timeStep;
}

VectorXd Integrator::integrate(const VectorXd& values,const VectorXd& diff){
    switch(this->mode){
    case const_dt:
        return IntegratorAlgorithms::firstOrder(values,diff,this->timeStep);
        break;
    case var_dt:
        this->timeStep = IntegratorAlgorithms::timeStep(values,diff,this->parameter);
        return IntegratorAlgorithms::firstOrder(values,diff,this->timeStep);
        break;
    default:
        throw Exception("Undefined mode<" + std::to_string(mode) + ">","Integrator::" + std::string(__FUNCTION__));
        break;
    }
}
