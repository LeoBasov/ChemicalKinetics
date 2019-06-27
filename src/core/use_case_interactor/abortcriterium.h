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

#include <limits>

#include  "../common/data_types/state.h"

class AbortCriterium
{
public:
    enum Mode{const_steps = 1, var_steps = 2, none = 0};

    AbortCriterium();

    void reset();
    void abort();

    bool valid(const State &state);

    void setParameter(const double& parametr);
    void setTimeStepNumber(const unsigned int& maxTimeStepNumber);
    void setMode(const Mode& mode);

private:
    bool validVal = true;
    bool firstRun = true;
    State lastState;
    double biggesDiff = std::numeric_limits<double>::min();
    double parameter = 0.1;
    unsigned int maxTimeStepNumber = 0;
    unsigned int currentTimeStepNumber = 0;
    Mode mode = none;

    bool checkCriterium(const State &state);

    bool varSteps(const State &state);
};
