#pragma once

#include <map>
#include <vector>

#include "../common/math/matrixxd.h"
#include "../common/data_types/interpolationtable.h"
#include "../common/data_types/inputdata.h"

class Converter
{
public:
    enum Type{species=1,reaction=2};

    using Vector = std::vector<std::pair<std::string,double>>;
    using VectorPair = std::vector<std::pair<std::string,std::pair<double,double>>>;
    using VectorTable = std::vector<std::pair<std::string,std::vector<std::pair<double,double>>>>;
    using Matrix = std::vector<std::pair<std::string,std::vector<std::pair<std::string,double>>>>;

public:
    Converter();

    void setUp(const std::vector<InputData::Species>& species,const std::vector<InputData::Reaction>& reactions);

    VectorXd concentrations(const std::vector<InputData::Species>& species) const;
    VectorXd concentrationsDiffs(const std::vector<InputData::Species>& species) const;
    VectorXd reactionRates(const std::vector<InputData::Reaction>& reactions) const;
    VectorXd rateConstatns(const std::vector<InputData::Reaction>& reactions) const;

    VectorXd vector(const Vector& vec,const Type& type) const;
    std::vector<std::pair<double,double>> vectorPair(const VectorPair vec,const Type& type) const;
    std::vector<InterpolationTable> vectorTable(const VectorTable vec,const Type& type) const;
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
