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

double Thermodynamics::totalEnergy(const VectorXd& concentrations,const VectorXd& temperatures) const{
    return ThermodynamicsAlgorithms::totalEnergy(concentrations,temperatures,this->species);
}

double Thermodynamics::temperature(const VectorXd& concentrations) const{
    return ThermodynamicsAlgorithms::temperature(concentrations,this->species,this->lastTemperature,this->energy,this->epsilon);
}
