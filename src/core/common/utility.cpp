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

InputData::ChemistryData Utility::getChemistryData(const DataNode& node){
    InputData::ChemistryData data;

    data.species = getSpeciesData(node.getNode("participating_species"));
    data.reactions = getReactionsData(node.getNode("reactions"));

    return data;
}

InputData::ThermodynamicData Utility::getThermodynamicData(const DataNode& node){
    InputData::ThermodynamicData data;

    data.temperature = std::stod(node.getAttribute("temperature"));

    return data;
}

InputData::IntegratorData Utility::getIntegratorData(const DataNode& node){
    const std::string modeStr(node.getAttribute("mode"));
    InputData::IntegratorData data;

    if(modeStr == "var_dt"){
        data.mode = InputData::IntegratorData::var_dt;
        data.parameter = std::stod(node.getAttribute("parameter"));
    }else if(modeStr == "const_dt"){
        data.mode = InputData::IntegratorData::const_dt;
        data.timeStep = std::stod(node.getAttribute("time_step"));
    }else{
        throw Exception("Undefined mode <" + modeStr + ">", "Utility::" + std::string(__FUNCTION__));
    }

    return data;
}

InputData::AbortCriterion Utility::getAbortCriterion(const DataNode& node){
    const std::string modeStr(node.getAttribute("mode"));
    InputData::AbortCriterion data;

    if(modeStr == "var_steps"){
        data.mode = InputData::AbortCriterion::var_steps;
        data.parameter = std::stod(node.getAttribute("parameter"));
    }else{
        throw Exception("Undefined mode <" + modeStr + ">", "Utility::" + std::string(__FUNCTION__));
    }

    return data;
}

std::vector<InputData::Species> Utility::getSpeciesData(const DataNode& node){
    std::vector<InputData::Species> species;

    for(auto locNode : node.getNodes("species")){
        InputData::Species locSpecies;

        locSpecies.name = locNode.getAttribute("name");
        locSpecies.concentration = std::stod(locNode.getAttribute("concentration"));

        species.push_back(locSpecies);
    }

    return species;
}

std::vector<InputData::Reaction> Utility::getReactionsData(const DataNode& node){
    std::vector<InputData::Reaction> reactions;

    for(auto locNode : node.getNodes("reaction")){
        reactions.push_back(getReactionData(locNode));
    }

    return reactions;
}

InputData::Reaction Utility::getReactionData(const DataNode& node){
    InputData::Reaction reaction;

    reaction.name = node.getAttribute("name");

    reaction.stoichiometricCoeffEducts = getSpeciesValuePairs(node.getNode("educts").getNodes());
    reaction.stoichiometricCoeffProducts = getSpeciesValuePairs(node.getNode("products").getNodes());
    reaction.reactionPowers = getSpeciesValuePairs(node.getNode("reaction_powers").getNodes());

    return reaction;
}

std::vector<InputData::SpeciesValuePair> Utility::getSpeciesValuePairs(const std::vector<DataNode>& nodes){
    std::vector<InputData::SpeciesValuePair> pairs;

    for(const auto& node : nodes){
        InputData::SpeciesValuePair pair;

        pair.species = node.getAttribute("species");
        pair.value = std::stod(node.getAttribute("value"));

        pairs.push_back(pair);
    }

    return pairs;
}
