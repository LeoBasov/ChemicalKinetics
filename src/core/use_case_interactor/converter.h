#pragma once

#include <map>
#include <vector>

#include "../common/math/matrixxd.h"

class Converter
{
public:
    enum Type{species=1,reaction=2};

    using Vector = std::vector<std::pair<std::string,double>>;
    using Matrix = std::vector<std::pair<std::string,std::vector<std::pair<std::string,double>>>>;

public:
    Converter();

    void setUp(const std::vector<std::string>& species,const std::vector<std::string>& reactions);

    VectorXd vector(const Vector& vec,const Type& type) const;
    MatrixXd matrix(const Matrix& mat) const;

    const std::map<std::size_t,std::string>& getSpeciesMap() const;
    const std::map<std::size_t,std::string>& getReactionMap() const;

private:
    std::map<std::string,std::size_t> speciesMapIn;
    std::map<std::size_t,std::string> speciesMapOut;
    std::map<std::string,std::size_t> reactionMapIn;
    std::map<std::size_t,std::string> reactionMapOut;

    size_t index(const Type& type,const std::string& name) const;
};
