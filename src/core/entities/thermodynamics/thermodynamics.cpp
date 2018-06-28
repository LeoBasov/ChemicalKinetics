#include "thermodynamics.h"

Thermodynamics::Thermodynamics(){

}

void Thermodynamics::setSpecies(std::vector<ThermodynamicsAlgorithms::Species> species){
    this->species = species;
}

void Thermodynamics::setTotalEnergy(const double& energy){
    this->totalEnerg = energy;
}

void Thermodynamics::addEnergy(const double& energyDelta){
    this->totalEnerg += energyDelta;
}

double Thermodynamics::totalEnergy(const VectorXd& concentrations,const VectorXd& temperatures) const{
    VectorXd dof(ThermodynamicsAlgorithms::internalDOF(temperatures,this->species));

    return ThermodynamicsAlgorithms::totalEnergy(concentrations,temperatures,dof);
}
