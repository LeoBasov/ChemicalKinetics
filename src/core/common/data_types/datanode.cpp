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

#include "datanode.h"

DataNode::DataNode(){

}

DataNode::DataNode(const std::string &name):name(name){

}

DataNode::DataNode(const DataNode &node)
                  :name(node.name)
                  ,attributes(node.attributes)
                  ,nodes(node.nodes)
                  ,elements(node.elements){

}


void DataNode::clear(){
    this->name.clear();
    this->attributes.clear();
    this->nodes.clear();
    this->elements.clear();
}

void DataNode::addAttribute(const std::string& attribute, const std::string &value){
    auto returnPair = this->attributes.insert({attribute,value});

    if(!returnPair.second){
        throw Exception("Erro when trying to add attribute <" + attribute + ">"
                       ,"DataNode::" + std::string(__FUNCTION__));
    }
}

void DataNode::addNode(DataNode node){
    this->nodes.push_back(node);
}

void DataNode::addElements(const std::vector<std::string>& elements){
    for(auto element : elements){
        this->elements.push_back(element);
    }
}

std::string DataNode::getName() const{
    return this->name;
}

const std::map<std::string,std::string>& DataNode::getAttributes() const{
    return this->attributes;
}

std::vector<DataNode> DataNode::getNodes() const{
    return this->nodes;
}

const std::vector<std::string>& DataNode::getElements() const{
    return this->elements;
}

std::string DataNode::getAttribute(const std::string& attribute) const{
    std::string value;

    try{
        value = this->attributes.at(attribute);
    }
    catch(std::out_of_range &){
        throw Exception("Requested attribute <" + attribute + "> not in list.", "DataNode::"+std::string(__FUNCTION__));
    }
    catch(std::exception &e){
        throw Exception(e.what(), "DataNode::" + std::string(__FUNCTION__));
    }

    return value;
}

std::vector<DataNode> DataNode::getNodes(const std::string& nodeStr) const{
    std::vector<DataNode> returnNodes;

    for(const DataNode &node:this->nodes){
        if(node.getName()==nodeStr){
            returnNodes.push_back(node);
        }
    }

    if(returnNodes.size()==0){
        throw Exception("Requested node <" + nodeStr + "> not in list.", "DataNode::" + std::string(__FUNCTION__));
    }

    return returnNodes;
}

DataNode DataNode::getNode(const std::string& nodeStr) const{
    std::vector<DataNode> returnNodes;

    for(const DataNode &node:this->nodes){
        if(node.getName()==nodeStr){
            returnNodes.push_back(node);
        }
    }

    if(returnNodes.size()==0){
        throw Exception("Requested node <" + nodeStr + "> not in list.", "DataNode::" + std::string(__FUNCTION__));
    }
    else if(returnNodes.size()>1){
        throw Exception("Requested node <" + nodeStr + "> defined multiple times.", "DataNode::" + std::string(__FUNCTION__));
    }

    return returnNodes.at(0);
}

DataNode DataNode::getNode(const std::string& nodeStr,const std::string& attributStr,const std::string& value) const{
    std::vector<DataNode> returnNodes;

    for(const DataNode &node:this->nodes){
        try{
            if(node.getName()==nodeStr && node.getAttribute(attributStr)==value){
                returnNodes.push_back(node);
            }
        }catch(Exception){
            continue;
        }catch(std::exception &e){
            throw Exception(std::string(e.what()), "DataNode::"+std::string(__FUNCTION__));
        }
    }

    if(returnNodes.size()==0){
        throw Exception("Requested node <" + nodeStr + "> with attribute <" + attributStr + "> = <" + value + "> not in list."
                       ,"DataNode::" + std::string(__FUNCTION__));
    }
    else if(returnNodes.size()>1){
        throw Exception("Requested node <" + nodeStr + "> with attribute <" + attributStr + "> = <" + value + "> defined multiple times."
                       ,"DataNode::" + std::string(__FUNCTION__));
    }

    return returnNodes.at(0);
}

std::pair<bool,std::vector<DataNode>> DataNode::findNodes(const std::string& nodeStr) const{
    std::pair<bool,std::vector<DataNode>> returnPair{false,std::vector<DataNode>()};

    for(const DataNode &node:this->nodes){
        if(node.getName()==nodeStr){
            returnPair.first = true;
            returnPair.second.push_back(node);
        }
    }

    return returnPair;
}

std::pair<bool,DataNode> DataNode::findNode(const std::string& nodeStr) const{
    std::pair<bool,DataNode> returnPair{false,DataNode()};

    for(const DataNode &node : this->nodes){
        if(node.getName() == nodeStr){
            if(returnPair.first){
                throw Exception("Requested node <" + nodeStr + "> defined multiple times."
                               ,"DataNode::" + std::string(__FUNCTION__));
            }else{
                returnPair.first = true;
                returnPair.second = node;
            }
        }
    }

    return returnPair;
}

std::pair<bool,DataNode> DataNode::findNode(const std::string& nodeStr, const std::string& attributStr, const std::string& value) const{
    std::pair<bool,DataNode> returnPair{false,DataNode()};

    for(const DataNode &node:this->nodes){
        try{
            if(node.getName()==nodeStr && node.getAttribute(attributStr)==value){
                if(returnPair.first){
                    throw Exception("Requested node <" + nodeStr + "> with attribute <" + attributStr + "> = <" + value + "> defined multiple times."
                                   ,"DataNode::" + std::string(__FUNCTION__));
                }else{
                    returnPair.first = true;
                    returnPair.second = node;
                }
            }
        }catch(Exception){
            continue;
        }catch(std::exception &e){
            throw Exception(std::string(e.what())
                           ,"DataNode::" + std::string(__FUNCTION__));
        }
    }

    return returnPair;
}
