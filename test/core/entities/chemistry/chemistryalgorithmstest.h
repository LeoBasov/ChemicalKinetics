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

#include "../../../unittest.h"
#include "../../../../src/core/entities/chemistry/chemistryalgorithms.h"

class ChemistryAlgorithmsTest : public UnitTest
{
    Q_OBJECT
public:
    ChemistryAlgorithmsTest(const std::string& name);

private slots:
    void arrheniusEquationTest() const;
    void reactionRatePowLawTest() const;
};
