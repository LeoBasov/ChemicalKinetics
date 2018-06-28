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

#include "chemistryalgorithms.h"
#include "../../common/data_types/interpolationtable.h"

class Chemistry
{
public:
    enum Mode{none=0,const_k=1,interpol_k=2,arrhenius_k=3};

public:
    Chemistry();

    void setModes(const std::vector<Mode>& modes);
    void setReactionPowers(const MatrixXd& reactionPowers);
    void setStoichiometricMatrix(const MatrixXd& stoichiometricMatrix);
    void setRateConstants(const VectorXd& rateConstants);
    void setRateConstants(const std::vector<InterpolationTable>& rateConstantsInterpolTables);
    void setArrheniusCoefficients(const std::vector<std::pair<double,double>>& arrheniusCoefficients);
    void setExcessEnergies(const VectorXd& excessEnergies);

    VectorXd getRateConstants(const double& temperature) const;
    VectorXd getReactionRates(const VectorXd& concentrations,const VectorXd& rateConstants) const;
    VectorXd getConcentrationDiff(const VectorXd& reactionRates) const;
    double getEnergyDiff(const VectorXd& reactionRates) const;

private:
    std::vector<Mode> modes;
    VectorXd rateConstants;
    VectorXd excessEnergies;
    MatrixXd stoichiometricMatrix;
    MatrixXd reactionPowers;
    std::vector<InterpolationTable> rateConstantsInterpolTables;
    std::vector<std::pair<double,double>> arrheniusCoefficients; //first = pre factor, second = activation energy

    double getRateConstant(const double& temperature,const size_t& pos) const;
    double interpolateRateConstant(const double& temperature,const size_t& pos) const;
    double calculateRateConstant(const double& temperature,const size_t& pos) const;
};
