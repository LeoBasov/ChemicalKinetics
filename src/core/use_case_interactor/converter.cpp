#include "converter.h"

Converter::Converter(){

}

void Converter::setUp(const std::vector<InputData::Species>& species,const std::vector<InputData::Reaction>& reactions){
    registerSpecies(species);
    registerReactions(reactions);
}

void Converter::registerSpecies(const std::vector<InputData::Species>& species){
    this->speciesMapIn.clear();
    this->speciesMapOut.clear();

    for(size_t i(0);i<species.size();++i){
        auto returnVal1 = this->speciesMapIn.insert({species.at(i).name,i});
        auto returnVal2 = this->speciesMapOut.insert({i,species.at(i).name});

        if(!returnVal1.second){
            throw Exception("Value pair <" + species.at(i).name + "," + std::to_string(i) + "> could not be registered in speciesMap."
                           ,"Converter::" + std::string(__FUNCTION__));
        }else if(!returnVal2.second){
            throw Exception("Value pair <" + std::to_string(i) + "," + species.at(i).name + "> could not be registered in speciesMap."
                           ,"Converter::" + std::string(__FUNCTION__));
        }
    }
}

void Converter::registerReactions(const std::vector<InputData::Reaction>& reactions){
    this->reactionMapIn.clear();
    this->reactionMapOut.clear();

    for(size_t i(0);i<reactions.size();++i){
        auto returnVal1 = this->reactionMapIn.insert({reactions.at(i).name,i});
        auto returnVal2 = this->reactionMapOut.insert({i,reactions.at(i).name});

        if(!returnVal1.second){
            throw Exception("Value pair <" + reactions.at(i).name + "," + std::to_string(i) + "> could not be registered in reactionMap."
                           ,"Converter::" + std::string(__FUNCTION__));
        }else if(!returnVal2.second){
            throw Exception("Value pair <" + std::to_string(i) + "," + reactions.at(i).name + "> could not be registered in reactionMap."
                           ,"Converter::" + std::string(__FUNCTION__));
        }
    }
}

const std::map<std::size_t,std::string>& Converter::getSpeciesMap() const{
    return this->speciesMapOut;
}

const std::map<std::size_t,std::string>& Converter::getReactionMap() const{
    return this->reactionMapOut;
}

std::vector<Chemistry::Mode> Converter::chemModes(const std::vector<InputData::Reaction>& reactions) const{
    std::vector<Chemistry::Mode> modesRet(reactions.size());

    for(auto reaction : reactions){
        modesRet.at(this->reactionMapIn.at(reaction.name)) = chemMode(reaction.mode);
    }

    return modesRet;
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

VectorXd Converter::excessEnergies(const std::vector<InputData::Reaction>& reactions) const{
    VectorXd retVec(reactions.size());

    for(auto reaction : reactions){
        retVec.at(this->reactionMapIn.at(reaction.name)) = reaction.excessEnergy;
    }

    return retVec;
}

std::vector<InterpolationTable> Converter::rateConstantsTables(const std::vector<InputData::Reaction>& reactions) const{
    std::vector<InterpolationTable> tables(reactions.size());

    for(size_t i(0);i<reactions.size();++i){
        InterpolationTable table;

        for(auto tab : reactions.at(i).rateConstantTable){
            table.addValuePair(tab.temperature,tab.rateConstant);
        }

        tables.at(i) = table;
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

Chemistry::Mode Converter::chemMode(const::std::string& str) const{
    if(str=="const_k"){
        return Chemistry::const_k;
    }else if(str=="interpol_k"){
        return Chemistry::interpol_k;
    }else if(str=="arrhenius_k"){
        return Chemistry::arrhenius_k;
    }else{
        throw Exception("No mode set","UseCaseInteractor::" + std::string(__FUNCTION__));
    }
}
