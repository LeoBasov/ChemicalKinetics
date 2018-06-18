#include "vectorxd.h"

VectorXd::VectorXd(){

}

VectorXd::VectorXd(const std::vector<double>::size_type& size,const double& initVal)
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

double VectorXd::module() const{
    double module(0.0);

    for(std::vector<double>::size_type i;i<this->values.size();++i){
        module += this->values.at(i)*this->values.at(i);
    }

    return std::sqrt(module);
}

std::vector<double>::size_type VectorXd::size() const{
    return this->values.size();
}

void VectorXd::resize(const std::vector<double>::size_type& size,const double &values){
    this->values.resize(size,values);
}

void VectorXd::resize(const std::vector<double>::size_type& size){
    this->values.resize(size);
}

void VectorXd::clear(){
    this->values.clear();
}

const std::vector<double>& VectorXd::getValues() const{
    return this->values;
}

void VectorXd::validate(const VectorXd& other) const{
    if(size()!=other.size()){
        throw OutOfRange( "Vectors are not of compatible size. This <"
                        + std::to_string(size()) + "> other <"
                        + std::to_string(other.size()) + ">.",std::string(__FUNCTION__));
    }
}
