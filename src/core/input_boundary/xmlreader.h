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

#include <memory>
#include <sstream>

#include "filereader.h"
#include "../../third_party/tinyxml/tinyxml.h"
#include "../exceptions/exception.h"
#include "../common/data_types/datanode.h"
#include "../common/utility.hpp"

class XMLReader : public FileReader
{
public:
    XMLReader();

    virtual void read(const std::string& fileName) override;

private:
    std::string relativeDirectory;
    DataNode xmlData;

    void parseXMLFile(const std::string &fileName);
    void parseXMLFile(const std::string &fileName, DataNode& node) const;
    DataNode processElement(const TiXmlElement* element) const;
    std::vector<std::string> processText(const std::string &text) const;
    void getRelDirectory(const std::string &fileName);

    void convertData();
};
