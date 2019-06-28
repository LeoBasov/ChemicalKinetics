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

#include "../common/data_types/state.h"
#include "../common/data_types/inputdata.h"
#include "abortcriterium.h"
#include "../entities/chemistry/chemistry.h"
#include "../entities/integrator/integrator.h"
#include "../entities/thermodynamics/thermodynamics.h"
#include "converter.h"
#include "simulationstate.h"

class UseCaseInteractor
{
public:
    explicit UseCaseInteractor(const std::shared_ptr<SimulationState>& simState);

    void start(const InputData& data);
    void stop();

private:
    Converter converter;
    State state;
    AbortCriterium abortCriterium;
    Chemistry chemistry;
    Integrator integrator;
    Thermodynamics thermodynamics;
    std::shared_ptr<SimulationState> simulationState;

    void initialize(const InputData& data);
    void initializeState(const InputData& data);
    void initializeIntergrator(const InputData::IntegratorData& data);
    void initializeChemistry(const InputData::ChemistryData& data);
    void initializeAbortCriterium(const InputData::AbortCriterion &abortCriterion);
    void initializeThermodynamics(const InputData::ThermodynamicData& thermodynamicData);

    std::vector<ThermodynamicsAlgorithms::Species> getThermodynamicsSpecies() const;
    double getTotalEnergy() const;

    void execute();
    void report();
};
