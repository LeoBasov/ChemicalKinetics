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

#include "thermodynamicsalgorithms.h"

class Thermodynamics
{
public:
    enum Mode{var_T=1, const_T=2, none=0};

    Thermodynamics();

    void setSpecies(std::vector<ThermodynamicsAlgorithms::Species> species);
    void setTotalEnergy(const double& energy);
    void addEnergy(const double& energyDelta);
    void setLastTemperature(const double& temperature);
    void setTemperatureCalcAccuracy(const double& epsilon);
    void setMode(const Mode& mode);

    double getNewTemperature(const VectorXd& concentrations, const double &energyDiff);

    double totalEnergy(const VectorXd &concentrations,const VectorXd& temperatures) const;
    double temperature(const VectorXd& concentrations) const;

private:
    std::vector<ThermodynamicsAlgorithms::Species> species;
    double energy = 0.0;
    double lastTemperature = 0.0;
    double epsilon = 0.0;
    Mode mode = none;
};
