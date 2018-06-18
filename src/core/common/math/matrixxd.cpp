#include "matrixxd.h"

MatrixXd::MatrixXd(){

}

MatrixXd::MatrixXd(std::vector<std::vector<double>>::size_type& rowSize,std::vector<double>::size_type& columnSize,const double& initVal)
                  :values(rowSize,std::vector<double>(columnSize,initVal)){

}

MatrixXd::MatrixXd(const std::vector<std::vector<double>>& values)
                  :values(values){

}

MatrixXd::MatrixXd(const MatrixXd& other)
                  :values(other.getValues()){

}

MatrixXd::~MatrixXd(){

}

const std::vector<std::vector<double>>& MatrixXd::getValues() const{
    return this->values;
}
