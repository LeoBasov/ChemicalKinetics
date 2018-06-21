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
