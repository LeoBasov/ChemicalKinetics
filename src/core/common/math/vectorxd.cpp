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

const std::vector<double>& VectorXd::getValues() const{
    return this->values;
}
