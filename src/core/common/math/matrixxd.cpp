#include "matrixxd.h"

MatrixXd::MatrixXd(){

}

MatrixXd::MatrixXd(const size_r& rowSize,const size_r& columnSize,const double& initVal)
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

MatrixXd& MatrixXd::operator=(const MatrixXd& other){
    if(this!=&other){
        this->values = other.getValues();
    }

    return *this;
}

const std::vector<std::vector<double>>& MatrixXd::getValues() const{
    return this->values;
}
