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
