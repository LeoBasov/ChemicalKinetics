#include "thermodynamics.h"

Thermodynamics::Thermodynamics(){

}

void Thermodynamics::setSpecies(std::vector<ThermodynamicsAlgorithms::Species> species){
    this->species = species;
}

void Thermodynamics::setTotalEnergy(const double& energy){
    this->energy = energy;
}

void Thermodynamics::addEnergy(const double& energyDelta){
    this->energy += energyDelta;
}

void Thermodynamics::setLastTemperature(const double& temperature){
    this->lastTemperature = temperature;
}

void Thermodynamics::setTemperatureCalcAccuracy(const double& epsilon){
    this->epsilon = epsilon;
}

void Thermodynamics::setMode(const Mode& mode){
    this->mode = mode;
}

double Thermodynamics::getNewTemperature(const VectorXd& concentrations, const double& energyDiff){
    addEnergy(energyDiff);

    switch (this->mode){
    case var_T:
        this->lastTemperature = temperature(concentrations);
        break;
    case const_T:
        break;
    default:
        throw Exception("Undefined mode <" + std::to_string(this->mode) + ">", "Thermodynamics::" + std::string(__FUNCTION__));
    }

    return this->lastTemperature;
}

double Thermodynamics::totalEnergy(const VectorXd& concentrations,const VectorXd& temperatures) const{
    return ThermodynamicsAlgorithms::totalEnergy(concentrations,temperatures,this->species);
}

double Thermodynamics::temperature(const VectorXd& concentrations) const{
    return ThermodynamicsAlgorithms::temperature(concentrations,this->species,this->lastTemperature,this->energy,this->epsilon);
}
