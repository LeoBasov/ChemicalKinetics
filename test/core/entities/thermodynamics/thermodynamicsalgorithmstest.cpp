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

#include "thermodynamicsalgorithmstest.h"

ThermodynamicsAlgorithmsTest::ThermodynamicsAlgorithmsTest(const std::string& name)
                                                          :UnitTest(name){

}

void ThermodynamicsAlgorithmsTest::internamDOF() const{
    const VectorXd temperatures({1.0,2.0,3.0});
    const VectorXd vibrTemperatures({4.0,5.0,6.0});
    const VectorXd ref({2.0 + 2.0*((vibrTemperatures.at(0)/temperatures.at(0))/(std::exp(vibrTemperatures.at(0)/temperatures.at(0)) - 1.0))
                       ,2.0 + 2.0*((vibrTemperatures.at(1)/temperatures.at(1))/(std::exp(vibrTemperatures.at(1)/temperatures.at(1)) - 1.0))
                       ,2.0 + 2.0*((vibrTemperatures.at(2)/temperatures.at(2))/(std::exp(vibrTemperatures.at(2)/temperatures.at(2)) - 1.0))});
    const VectorXd res(ThermodynamicsAlgorithms::internamDOF(temperatures,vibrTemperatures));

    QCOMPARE(res.at(0),ref.at(0));
    QCOMPARE(res.at(1),ref.at(1));
    QCOMPARE(res.at(2),ref.at(2));
}

void ThermodynamicsAlgorithmsTest::totalEnergyTest() const{
    const double factor(0.5*Constants::boltzmannConst);
    const double bysum(1.0/6.0);
    const VectorXd concentrations({1.0,2.0,3.0});
    const VectorXd temperatures({4.0,5.0,6.0});
    const VectorXd dofs({7.0,8.0,9.0});
    const double res(ThermodynamicsAlgorithms::totalEnergy(concentrations,temperatures,dofs));
    const VectorXd ref({concentrations.at(0)*bysum*(3.0*factor*temperatures.at(0) + dofs.at(0)*factor*temperatures.at(0))
                       ,concentrations.at(1)*bysum*(3.0*factor*temperatures.at(1) + dofs.at(1)*factor*temperatures.at(1))
                       ,concentrations.at(2)*bysum*(3.0*factor*temperatures.at(2) + dofs.at(2)*factor*temperatures.at(2))});

    QCOMPARE(res,ref.sum());
}
