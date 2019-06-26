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

#include "xmlreader.h"

XMLReader::XMLReader(){

}

void XMLReader::read(const std::string& fileName){
    parseXMLFile(fileName);
    convertData();
}

void XMLReader::parseXMLFile(const std::string &fileName){
    TiXmlDocument xmlDoc;

    if(!xmlDoc.LoadFile(fileName.c_str())){
        throw Exception("InputModule::" + std::string(__FUNCTION__),"File <" + fileName + "> could not be loaded");
    }

    this->xmlData = processElement(xmlDoc.FirstChildElement());
}

void XMLReader::parseXMLFile(const std::string &fileName,DataNode& node) const{
    TiXmlDocument xmlDoc;
    std::string newName(this->relativeDirectory + "./" + fileName);

    if(!xmlDoc.LoadFile(newName.c_str())){
        throw Exception("InputModule::" + std::string(__FUNCTION__),"File <" + newName + "> could not be loaded");
    }
    auto firstChildElem = xmlDoc.FirstChildElement();
    if(!firstChildElem){
         //empty files are ignored (also with comments)
    }else {
        node.addNode(processElement(firstChildElem));
    }
}

DataNode XMLReader::processElement(const TiXmlElement* element) const{
    std::string nodeName(element->Value());
    DataNode node(nodeName);

    for(const TiXmlAttribute* attribute(element->FirstAttribute());attribute!=NULL;attribute=attribute->Next()){
        node.addAttribute(std::string(attribute->Name()),std::string(attribute->Value()));
    }

    if(element->GetText()!=NULL){
        std::vector<std::string> processedText = processText(std::string(element->GetText()));
        node.addElements(processedText);
    }
    else{
        for(const TiXmlElement* child = element->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
            if(std::string(child->Value())=="load"){
                parseXMLFile(child->GetText(),node);
            }
            else{
                node.addNode(processElement(child));
            }
        }
    }

    return node;
}

std::vector<std::string> XMLReader::processText(const std::string &text) const{
    std::vector<std::string> processedText;
    std::stringstream stringStream(text);

    while(stringStream.good()){
        std::string substr;
        std::getline(stringStream,substr,',');
        processedText.push_back(substr);
    }

    return processedText;
}

void XMLReader::getRelDirectory(const std::string &fileName){
    std::stringstream outstream;
    std::string::size_type posOld = 0;
    std::string::size_type pos = fileName.find('/');

    while(pos!=std::string::npos){
        std::string substr;

        substr = fileName.substr(posOld,(pos-posOld));
        substr += "/";
        outstream << substr;

        posOld = pos+1;
        pos = fileName.find('/',pos+1);
    }

    this->relativeDirectory = outstream.str();
}

void XMLReader::convertData(){
    //DUMMY!!!

    this->xmlData.clear();
}
