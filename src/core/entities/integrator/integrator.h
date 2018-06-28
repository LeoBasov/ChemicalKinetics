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

#include "integratoralgorithms.h"

class Integrator
{
public:
    enum Mode{const_dt=1,var_dt=2,none=0};

public:
    Integrator();

    void setMode(const Mode& mode);
    void setTimeStep(const double& timeStep);
    void setTimeStepParamter(const double& parameter);

    double getTimeStep() const;

    VectorXd integrate(const VectorXd& values,const VectorXd& diff);

private:
    double timeStep = 0.0;
    double parameter = 0.0;
    Mode mode = none;
};
