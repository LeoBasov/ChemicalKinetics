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

#include "csvwriterviewtest.h"

CSVWriterViewTest::CSVWriterViewTest(){
    this->stream.open("concentrations.csv");
}

void CSVWriterViewTest::update(){
    const State& locSt(this->viewModel->getState());

    if(this->first){
        this->stream << "#time" << ",";
        this->stream << "#temperature" << ",";

        for(size_t i(0);i<locSt.concentrations.size();i++){
            this->stream << "#" << locSt.speciesMap.at(i) << ",";
        }

        this->stream << std::endl;
        this->first = false;
    }

    this->stream << locSt.time << ",";
    this->stream << locSt.temperature << ",";

    for(size_t i(0);i<locSt.concentrations.size();i++){
        this->stream << locSt.concentrations.at(i) << ",";
    }

    this->stream << std::endl;
}
