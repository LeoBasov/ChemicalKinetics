#include "converter.h"

Converter::Converter(){

}

void Converter::setUp(const std::vector<InputData::Species>& species,const std::vector<InputData::Reaction>& reactions){
    this->speciesMapIn.clear();
    this->speciesMapOut.clear();
    this->reactionMapIn.clear();
    this->reactionMapOut.clear();

    for(size_t i(0);i<species.size();++i){
        this->speciesMapIn[species.at(i).name] = i;
        this->speciesMapOut[i] = species.at(i).name;
    }
    for(size_t i(0);i<reactions.size();++i){
        this->reactionMapIn[reactions.at(i).name] = i;
        this->reactionMapOut[i] = reactions.at(i).name;
    }
}

const std::map<std::size_t,std::string>& Converter::getSpeciesMap() const{
    return this->speciesMapOut;
}

const std::map<std::size_t,std::string>& Converter::getReactionMap() const{
    return this->reactionMapOut;
}

VectorXd Converter::concentrations(const std::vector<InputData::Species>& species) const{
    VectorXd retVec(species.size());

    for(auto elem : species){
        retVec.at(this->speciesMapIn.at(elem.name)) = elem.concentration;
    }

    return retVec;
}

VectorXd Converter::concentrationsDiffs(const std::vector<InputData::Species>& species) const{
    VectorXd retVec(species.size());

    for(auto elem : species){
        retVec.at(this->speciesMapIn.at(elem.name)) = elem.concentrationDiff;
    }

    return retVec;
}

VectorXd Converter::reactionRates(const std::vector<InputData::Reaction>& reactions) const{
    VectorXd retVec(reactions.size());

    for(auto reaction : reactions){
        retVec.at(this->reactionMapIn.at(reaction.name)) = reaction.reactionRate;
    }

    return retVec;
}

VectorXd Converter::rateConstatns(const std::vector<InputData::Reaction>& reactions) const{
    VectorXd retVec(reactions.size());

    for(auto reaction : reactions){
        retVec.at(this->reactionMapIn.at(reaction.name)) = reaction.rateConstant;
    }

    return retVec;
}

std::vector<InterpolationTable> Converter::rateConstantsTables(const std::vector<InputData::Reaction>& reactions) const{
    std::vector<InterpolationTable> tables(reactions.size());

    for(auto reaction : reactions){
        InterpolationTable table;

        for(auto tab : reaction.rateConstantTable){
            table.addValuePair(tab.temperature,tab.rateConstant);
        }

        tables.push_back(table);
    }

    return tables;
}

MatrixXd Converter::stoichiometricCoeffEducts(const std::vector<InputData::Reaction>& reactions) const{
    MatrixXd mat(reactions.size(),reactions.front().stoichiometricCoeffEducts.size());

    for(auto reaction : reactions){
        for(auto elem : reaction.stoichiometricCoeffEducts){
            const size_t idxRow(this->reactionMapIn.at(reaction.name));
            const size_t idxColumn(this->speciesMapIn.at(elem.species));

            mat.at(idxRow,idxColumn) = elem.value;
        }
    }


    return mat;
}

MatrixXd Converter::stoichiometricCoeffProducts(const std::vector<InputData::Reaction>& reactions) const{
    MatrixXd mat(reactions.size(),reactions.front().stoichiometricCoeffEducts.size());

    for(auto reaction : reactions){
        for(auto elem : reaction.stoichiometricCoeffProducts){
            const size_t idxRow(this->reactionMapIn.at(reaction.name));
            const size_t idxColumn(this->speciesMapIn.at(elem.species));

            mat.at(idxRow,idxColumn) = elem.value;
        }
    }


    return mat;
}

MatrixXd Converter::reactionPowers(const std::vector<InputData::Reaction>& reactions) const{
    MatrixXd mat(reactions.size(),reactions.front().stoichiometricCoeffEducts.size());

    for(auto reaction : reactions){
        for(auto elem : reaction.reactionPowers){
            const size_t idxRow(this->reactionMapIn.at(reaction.name));
            const size_t idxColumn(this->speciesMapIn.at(elem.species));

            mat.at(idxRow,idxColumn) = elem.value;
        }
    }


    return mat;
}

std::vector<std::pair<double,double>> Converter::arrheniusCoefficients(const std::vector<InputData::Reaction>& reactions) const{
    std::vector<std::pair<double,double>> coeffs(reactions.size());

    for(auto reaction : reactions){
        coeffs.at(this->reactionMapIn.at(reaction.name)) = {reaction.arrheniusCoefficients.preFactor,reaction.arrheniusCoefficients.activationEnergy};
    }

    return coeffs;
}

VectorXd Converter::vector(const Vector& vec,const Type& type) const{
    VectorXd retVec(vec.size());

    for(auto elem : vec){
        retVec.at(index(type,elem.first)) = elem.second;
    }

    return retVec;
}

std::vector<std::pair<double,double>> Converter::vectorPair(const VectorPair vec,const Type& type) const{
    std::vector<std::pair<double,double>> retVec(vec.size());

    for(auto elem : vec){
        retVec.at(index(type,elem.first)) = elem.second;
    }

    return retVec;
}

std::vector<InterpolationTable> Converter::vectorTable(const VectorTable vec,const Type& type) const{
    std::vector<InterpolationTable> retVec(vec.size());

    for(auto elem : vec){
        retVec.at(index(type,elem.first)) = InterpolationTable(elem.second);
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
