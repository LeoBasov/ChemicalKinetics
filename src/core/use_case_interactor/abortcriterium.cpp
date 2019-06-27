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

#include "abortcriterium.h"

AbortCriterium::AbortCriterium()
{

}

bool AbortCriterium::valid(const State& state){
    if(this->firstRun){
        this->firstRun = false;
        this->lastState = state;
    }else{
        this->validVal = checkCriterium(state);
        this->lastState = state;
    }

    return this->validVal;
}

void AbortCriterium::abort(){
    this->validVal = false;
}

void AbortCriterium::reset(){
    this->validVal = true;
    this->firstRun = true;
    this->lastState = State();
}

bool AbortCriterium::checkCriterium(const State &state){
    double locMax(std::numeric_limits<double>::min());

    for(size_t st = 0; st < state.concentrationDiffs.size(); ++st){
        if(state.concentrationDiffs.at(st) > locMax){
            locMax = state.concentrationDiffs.at(st);

            if(locMax > this->biggesDiff){
                this->biggesDiff = locMax;
            }
        }
    }

    if((locMax/this->biggesDiff) < 0.001){
        return false;
    }else{
        return true;
    }
}
