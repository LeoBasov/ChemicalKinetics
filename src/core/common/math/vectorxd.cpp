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

#include "vectorxd.h"

VectorXd::VectorXd(){

}

VectorXd::VectorXd(const size_v& size,const double& initVal)
                  :values(size,initVal){

}

VectorXd::VectorXd(const std::vector<double>& values)
                  :values(values){

}

VectorXd::VectorXd(const VectorXd& other)
                  :VectorXd(other.getValues()){

}

VectorXd::~VectorXd(){

}

VectorXd& VectorXd::operator=(const VectorXd& other){
    if(this!=&other){
        this->values = other.getValues();
    }

    return *this;
}

bool VectorXd::operator==(const VectorXd& other) const{
    return getValues() == other.getValues();
}

bool VectorXd::operator!=(const VectorXd& other) const{
    return !(*this==other);
}

bool VectorXd::operator< (const VectorXd& other) const{
    return module()<other.module();
}

bool VectorXd::operator> (const VectorXd& other) const{
    return module()>other.module();
}

bool VectorXd::operator<=(const VectorXd& other) const{
    return !(*this>other);
}

bool VectorXd::operator>=(const VectorXd& other) const{
    return !(*this<other);
}

VectorXd VectorXd::operator+(const VectorXd& other) const{
    VectorXd returnVals(this->values);

    validateSize(other);

    for(size_v i(0);i<this->values.size();++i){
        returnVals.at(i) += other.at(i);
    }

    return returnVals;
}

VectorXd VectorXd::operator-(const VectorXd& other) const{
    VectorXd returnVals(this->values);

    validateSize(other);

    for(size_v i(0);i<this->values.size();++i){
        returnVals.at(i) -= other.at(i);
    }

    return returnVals;
}

VectorXd VectorXd::operator*(const double& value) const{
    VectorXd returnVals(this->values);

    for(size_v i(0);i<this->values.size();++i){
        returnVals.at(i) *= value;
    }

    return returnVals;
}

double VectorXd::operator*(const VectorXd& other) const{
    double returnVal(0.0);

    validateSize(other);

    for(size_v i(0);i<this->values.size();++i){
        returnVal += at(i)*other.at(i);
    }

    return returnVal;
}

double& VectorXd::operator[](size_v idx){
    return this->values[idx];
}

const double& VectorXd::operator[](size_v idx) const{
    return this->values[idx];
}

double& VectorXd::at(size_v idx){
    try{
        return this->values.at(idx);
    }catch(std::out_of_range& e){
        throw OutOfRange(e.what(),"VectorXd::" + std::string(__FUNCTION__));
    }catch(std::exception& e){
        throw Exception(e.what(),"VectorXd::" + std::string(__FUNCTION__));
    }
}

const double& VectorXd::at(size_v idx) const{
    try{
        return this->values.at(idx);
    }catch(std::out_of_range& e){
        throw OutOfRange(e.what(),"VectorXd::" + std::string(__FUNCTION__));
    }catch(std::exception& e){
        throw Exception(e.what(),"VectorXd::" + std::string(__FUNCTION__));
    }
}

double VectorXd::module() const{
    double module(0.0);

    for(size_v i(0);i<this->values.size();++i){
        module += this->values.at(i)*this->values.at(i);
    }

    return std::sqrt(module);
}

double VectorXd::sum() const{
    double sum(0.0);

    for(size_v i(0);i<this->values.size();++i){
        sum += this->values.at(i);
    }

    return sum;
}

VectorXd VectorXd::elemWiseMult(const VectorXd& other) const{
    return elemWiseMult(*this,other);
}

VectorXd VectorXd::elemWiseMult(const VectorXd& lhs,const VectorXd& rhs){
    VectorXd vec(lhs.size());

    validateSize(lhs,rhs);

    for(size_t i(0);i<lhs.size();++i){
        vec.at(i) = lhs.at(i)*rhs.at(i);
    }

    return vec;
}

VectorXd::size_v VectorXd::size() const{
    return this->values.size();
}

void VectorXd::resize(const size_v& size,const double &values){
    this->values.resize(size,values);
}

void VectorXd::resize(const size_v& size){
    this->values.resize(size);
}

void VectorXd::clear(){
    this->values.clear();
}

void VectorXd::validateSize(const VectorXd& other) const{
    validateSize(*this,other);
}

void VectorXd::validateSize(const VectorXd& lhs,const VectorXd& rhs){
    if(lhs.size()!=rhs.size()){
        throw OutOfRange( "Vectors are not of compatible size. Lhs <"
                        + std::to_string(lhs.size()) + "> rhs <"
                        + std::to_string(rhs.size()) + ">."
                        ,"VectorXd::" + std::string(__FUNCTION__));
    }
}

const std::vector<double>& VectorXd::getValues() const{
    return this->values;
}
