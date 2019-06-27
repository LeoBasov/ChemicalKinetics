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

#include "utility.hpp"

InputData Utility::converDataNodeToInputData(const DataNode& dataNode){
    InputData inputData;

    inputData.chemistryData = getChemistryData(dataNode.getNode("chemistry_data"));
    inputData.thermodynamicData = getThermodynamicData(dataNode.getNode("thermodynamic_data"));
    inputData.integratorData = getIntegratorData(dataNode.getNode("integrator_data"));
    inputData.abortCriterion = getAbortCriterion(dataNode.getNode("abort_criterion"));

    return inputData;
}

InputData::ChemistryData Utility::getChemistryData(const DataNode& ){
    InputData::ChemistryData data;

    return data;
}

InputData::ThermodynamicData Utility::getThermodynamicData(const DataNode& ){
    InputData::ThermodynamicData data;

    return data;
}

InputData::IntegratorData Utility::getIntegratorData(const DataNode& ){
    InputData::IntegratorData data;

    return data;
}

InputData::AbortCriterion Utility::getAbortCriterion(const DataNode& ){
    InputData::AbortCriterion data;

    return data;
}
