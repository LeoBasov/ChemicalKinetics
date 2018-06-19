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

MatrixXd::Proxy MatrixXd::operator[](const size_r& row){
    return Proxy(this->values.at(row));
}

double& MatrixXd::at(const size_r& row,const size_c& column){
    try{
        return this->values.at(row).at(column);
    }catch(std::out_of_range& e){
        throw OutOfRange(e.what(),std::string(__FUNCTION__));
    }catch(std::exception& e){
        throw Exception(e.what(),std::string(__FUNCTION__));
    }
}

const double& MatrixXd::at(const size_r& row,const size_c& column) const{
    try{
        return this->values.at(row).at(column);
    }catch(std::out_of_range& e){
        throw OutOfRange(e.what(),std::string(__FUNCTION__));
    }catch(std::exception& e){
        throw Exception(e.what(),std::string(__FUNCTION__));
    }
}

const std::vector<std::vector<double>>& MatrixXd::getValues() const{
    return this->values;
}
