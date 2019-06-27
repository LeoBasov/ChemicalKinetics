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

#include "data_types/datanode.h"
#include "data_types/inputdata.h"

namespace  Utility{

InputData converDataNodeToInputData(const DataNode& dataNode);
InputData::ChemistryData getChemistryData(const DataNode& dataNode);
InputData::ThermodynamicData getThermodynamicData(const DataNode& dataNode);
InputData::IntegratorData getIntegratorData(const DataNode& dataNode);
InputData::AbortCriterion getAbortCriterion(const DataNode& dataNode);

std::vector<InputData::Species> getSpeciesData(const DataNode& dataNode);
std::vector<InputData::Reaction> getReactionsData(const DataNode& dataNode);
InputData::Reaction getReactionData(const DataNode& dataNode);

};

