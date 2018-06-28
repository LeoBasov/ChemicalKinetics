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

#include <map>
#include <vector>

#include "../common/math/matrixxd.h"
#include "../common/data_types/interpolationtable.h"
#include "../common/data_types/inputdata.h"
#include "../entities/chemistry/chemistry.h"
#include "../entities/integrator/integrator.h"

class Converter
{
public:
    Converter();

    void setUp(const std::vector<InputData::Species>& species,const std::vector<InputData::Reaction>& reactions);

    std::vector<Chemistry::Mode> chemModes(const std::vector<InputData::Reaction>& reactions) const;
    VectorXd concentrations(const std::vector<InputData::Species>& species) const;
    VectorXd concentrationsDiffs(const std::vector<InputData::Species>& species) const;
    VectorXd reactionRates(const std::vector<InputData::Reaction>& reactions) const;
    VectorXd rateConstants(const std::vector<InputData::Reaction>& reactions) const;
    VectorXd excessEnergies(const std::vector<InputData::Reaction>& reactions) const;
    std::vector<InterpolationTable> rateConstantsTables(const std::vector<InputData::Reaction>& reactions) const;
    MatrixXd stoichiometricCoeffEducts(const std::vector<InputData::Reaction>& reactions) const;
    MatrixXd stoichiometricCoeffProducts(const std::vector<InputData::Reaction>& reactions) const;
    MatrixXd reactionPowers(const std::vector<InputData::Reaction>& reactions) const;
    std::vector<std::pair<double,double>> arrheniusCoefficients(const std::vector<InputData::Reaction>& reactions) const;

    Integrator::Mode integratorMode(const InputData::IntegratorData::Mode &mode) const;

    const std::map<std::size_t,std::string>& getSpeciesMap() const;
    const std::map<std::size_t,std::string>& getReactionMap() const;

private:
    std::map<std::string,std::size_t> speciesMapIn;
    std::map<std::size_t,std::string> speciesMapOut;
    std::map<std::string,std::size_t> reactionMapIn;
    std::map<std::size_t,std::string> reactionMapOut;

    void registerSpecies(const std::vector<InputData::Species>& species);
    void registerReactions(const std::vector<InputData::Reaction>& reactions);
    Chemistry::Mode chemMode(const InputData::Reaction::Mode &mode) const;
};
