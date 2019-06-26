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

#include <vector>
#include <string>
#include <map>

#include "../../exceptions/exception.h"

class DataNode
{
public:
    DataNode();
    DataNode(const DataNode &node);
    DataNode(const std::string &name);
    ~DataNode() = default;

    void clear();

    void addAttribute(const std::string& attribute
                     ,const std::string& value);
    void addNode(DataNode node);
    void addElements(const std::vector<std::string>& elements);

    std::string getName() const;

    const std::map<std::string,std::string>& getAttributes() const;
    std::vector<DataNode> getNodes() const;
    const std::vector<std::string>& getElements() const;

    std::string getAttribute(const std::string& attribute) const;
    std::vector<DataNode> getNodes(const std::string& nodeStr) const;
    DataNode getNode(const std::string& nodeStr) const;
    DataNode getNode(const std::string& nodeStr, const std::string& attributStr, const std::string& value) const;
    std::pair<bool,std::vector<DataNode>> findNodes(const std::string& nodeStr) const;
    std::pair<bool,DataNode> findNode(const std::string& nodeStr) const;
    std::pair<bool,DataNode> findNode(const std::string& nodeStr, const std::string& attributStr, const std::string& value) const;

private:
    std::string name;
    std::map<std::string,std::string> attributes;
    std::vector<DataNode> nodes;
    std::vector<std::string> elements;
};
