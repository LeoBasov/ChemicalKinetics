#include "converter.h"

Converter::Converter(){

}

void Converter::setUp(const std::vector<std::string>& species,const std::vector<std::string>& reactions){
    this->speciesMapIn.clear();
    this->speciesMapOut.clear();
    this->reactionMapIn.clear();
    this->reactionMapOut.clear();

    for(size_t i(0);i<species.size();++i){
        this->speciesMapIn[species.at(i)] = i;
        this->speciesMapOut[i] = species.at(i);
    }
    for(size_t i(0);i<reactions.size();++i){
        this->reactionMapIn[reactions.at(i)] = i;
        this->reactionMapOut[i] = reactions.at(i);
    }
}

VectorXd Converter::vector(const Vector& vec,const Type& type) const{
    VectorXd retVec;

    for(auto elem : vec){
        retVec.at(index(type,elem.first)) = elem.second;
    }

    return retVec;
}

MatrixXd Converter::matrix(const Matrix& mat) const{
    MatrixXd retMat(mat.size(),mat.front().second.size());

    for(auto row : mat){
        const std::string reaction(row.first);

        for(auto column : row.second){
            const std::string species(column.first);
            const size_t idxRow(this->reactionMapIn.at(reaction));
            const size_t idxColumn(this->speciesMapIn.at(species));

            retMat.at(idxRow,idxColumn) = column.second;
        }
    }

    return retMat;
}

size_t Converter::index(const Type& type,const std::string& name) const{
    switch(type){
    case species:
        return this->speciesMapIn.at(name);
        break;
    case reaction:
        return this->reactionMapIn.at(name);
        break;
    default:
        throw Exception("Undefined type <" + std::to_string(type) + ">","Converter::" + std::string(__FUNCTION__));
        break;
    }
}