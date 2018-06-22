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

MatrixXd MatrixXd::operator+(const MatrixXd& other) const{
    MatrixXd returnVals(this->values);

    validateMat(other);

    for(size_r i(0);i<this->values.size();++i){
        for(size_c j(0);j<this->values.front().size();++j){
            returnVals.at(i,j) += other.at(i,j);
        }
    }

    return returnVals;
}

MatrixXd MatrixXd::operator-(const MatrixXd& other) const{
    MatrixXd returnVals(this->values);

    validateMat(other);

    for(size_r i(0);i<this->values.size();++i){
        for(size_c j(0);j<this->values.front().size();++j){
            returnVals.at(i,j) -= other.at(i,j);
        }
    }

    return returnVals;
}

MatrixXd MatrixXd::operator*(const double& value) const{
    MatrixXd returnVals(this->values);

    for(size_r i(0);i<this->values.size();++i){
        for(size_c j(0);j<this->values.front().size();++j){
            returnVals.at(i,j) *= value;
        }
    }

    return returnVals;
}

VectorXd MatrixXd::operator*(const VectorXd& vec) const{
    VectorXd returnValues(sizeRow());

    validateVec(vec);

    for(size_r i(0);i<sizeRow();++i){
        for(size_c j(0);j<sizeColumn();++j){
            returnValues.at(i) += at(i,j)*vec.at(j);
        }
    }

    return returnValues;
}

MatrixXd::Proxy MatrixXd::operator[](const size_r& row){
    return Proxy(this->values.at(row));
}

MatrixXd::ConstProxy MatrixXd::operator[](const size_r& row) const{
    return ConstProxy(this->values.at(row));
}

MatrixXd MatrixXd::transpose(const MatrixXd& mat){
    MatrixXd retMat(mat.sizeColumn(),mat.sizeRow());

    for(size_t i(0);i<mat.sizeRow();++i){
        for(size_t j(0);j<mat.sizeColumn();++j){
            retMat.at(j,i) = mat.at(i,j);
        }
    }

    return retMat;
}

MatrixXd MatrixXd::transpose() const{
    return transpose(*this);
}

double& MatrixXd::at(const size_r& row,const size_c& column){
    try{
        return this->values.at(row).at(column);
    }catch(std::out_of_range& e){
        throw OutOfRange(e.what(),"MatrixXd::" + std::string(__FUNCTION__));
    }catch(std::exception& e){
        throw Exception(e.what(),"MatrixXd::" + std::string(__FUNCTION__));
    }
}

const double& MatrixXd::at(const size_r& row,const size_c& column) const{
    try{
        return this->values.at(row).at(column);
    }catch(std::out_of_range& e){
        throw OutOfRange(e.what(),"MatrixXd::" + std::string(__FUNCTION__));
    }catch(std::exception& e){
        throw Exception(e.what(),"MatrixXd::" + std::string(__FUNCTION__));
    }
}

MatrixXd::size_r MatrixXd::sizeRow() const{
    return this->values.size();
}

MatrixXd::size_c MatrixXd::sizeColumn() const{
    if(!this->values.size()){
        return 0;
    }else{
        return this->values.front().size();
    }
}

void MatrixXd::clear(){
    this->values.clear();
}

const std::vector<std::vector<double>>& MatrixXd::getValues() const{
    return this->values;
}

void MatrixXd::validateMat(const MatrixXd& other) const{
    if((sizeRow()!=other.sizeRow()) || (sizeColumn()!=other.sizeColumn())){
        throw OutOfRange( "Matrizes are not of compatible size. This row size<"
                        + std::to_string(sizeRow()) + "> other <"
                        + std::to_string(other.sizeRow()) + ">. This column size<"
                        + std::to_string(sizeColumn()) + "> other <"
                        + std::to_string(other.sizeColumn()) + ">."
                        , "MatrixXd::" + std::string(__FUNCTION__));
    }
}

void MatrixXd::validateVec(const VectorXd& vec) const{
    if(sizeColumn()!=vec.size()){
        throw OutOfRange( "Matrix and vector are not of compatible size. Matrix <"
                        + std::to_string(sizeColumn()) + "> vector <"
                        + std::to_string(vec.size()) + ">."
                        , "MatrixXd::" + std::string(__FUNCTION__));
    }
}
