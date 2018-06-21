#pragma once

#include <map>
#include <vector>

class Converter
{
public:
    Converter();

    void setUp(const std::vector<std::string>& species,const std::vector<std::string>& reactions);

private:
    std::map<std::string,std::size_t> speciesMapIn;
    std::map<std::size_t,std::string> speciesMapOut;
    std::map<std::string,std::size_t> reactionMapIn;
    std::map<std::size_t,std::string> reactionMapOut;
};
