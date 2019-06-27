/* =============================================================================================
 * ChemicalKinetics
 *
 * A tool to calculate chemistry kinetics
 * ---------------------------------------------------------------------------------------------
 * Copyright (C) 2018  Leo Basov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public Licens
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * =============================================================================================
 */

#pragma once

#include <string>
#include <vector>

struct InputData{
    struct RateConstPair{
        RateConstPair(){}
        RateConstPair(const double& temperature,const double& rateConstant)
                     :temperature(temperature),rateConstant(rateConstant){}

        double temperature = 0.0;
        double rateConstant = 0.0;
    };

    struct ArrheniusCoeffPair{
        ArrheniusCoeffPair(){}
        ArrheniusCoeffPair(const double& preFactor,const double& activationEnergy)
                          :preFactor(preFactor),activationEnergy(activationEnergy){}

        double preFactor = 0.0;
        double activationEnergy = 0.0;
    };

    struct SpeciesValuePair{
        SpeciesValuePair(){}
        SpeciesValuePair(const std::string& species,const double& value)
                        :species(species),value(value){}

        std::string species;
        double value = 0.0;
    };

    struct Reaction{        
        enum Mode{const_k=1,interpol_k=2,arrhenius_k=3,none=0};

        std::string name;
        Mode mode = none;

        double excessEnergy = 0.0;
        double reactionRate = 0.0;
        double rateConstant = 0.0;
        std::vector<RateConstPair> rateConstantTable;
        ArrheniusCoeffPair arrheniusCoefficients;
        std::vector<SpeciesValuePair> stoichiometricCoeffEducts;
        std::vector<SpeciesValuePair> stoichiometricCoeffProducts;
        std::vector<SpeciesValuePair> reactionPowers;
    };

    struct Species{
        enum Type{monoatomic,diatomic,none};

        std::string name;
        Type type = none;

        double concentration = 0.0;
        double concentrationDiff = 0.0;
        double temperature = 0.0;
        double charVibrationTemp = 0.0;
    };

    struct ChemistryData{
        double temperature = 0.0;

        std::vector<Species> species;
        std::vector<Reaction> reactions;
    };

    struct IntegratorData{
        enum Mode{const_dt=1,var_dt=2,none=0};

        Mode mode = none;

        double timeStep = 0.0;
        double parameter = 0.0;
    };

    struct AbortCriterion{
        enum Mode{const_steps = 1, var_steps = 2, none = 0};

        Mode mode = none;

        unsigned int timeStepNumber = 0;
        double parameter = 0.2;
    };

    ChemistryData chemistryData;
    IntegratorData integratorData;
    AbortCriterion abortCriterion;
};
