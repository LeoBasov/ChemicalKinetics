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
                       ,0.0
                       ,2.0 + 2.0*((vibrTemperatures.at(2)/temperatures.at(2))/(std::exp(vibrTemperatures.at(2)/temperatures.at(2)) - 1.0))});
    std::vector<ThermodynamicsAlgorithms::Species>
    species{ThermodynamicsAlgorithms::Species(vibrTemperatures.at(0),ThermodynamicsAlgorithms::Species::diatomic)
           ,ThermodynamicsAlgorithms::Species(vibrTemperatures.at(1),ThermodynamicsAlgorithms::Species::monoatomic)
           ,ThermodynamicsAlgorithms::Species(vibrTemperatures.at(2),ThermodynamicsAlgorithms::Species::diatomic)};
    const VectorXd res(ThermodynamicsAlgorithms::internalDOF(temperatures,species));

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

void ThermodynamicsAlgorithmsTest::temperatureTest() const{
    const double temperature(500.0);
    const VectorXd concentrations(std::vector<double>{0.1,0.9});
    const VectorXd temperatures(std::vector<double>{temperature,temperature});
    const std::vector<ThermodynamicsAlgorithms::Species>
    species{ThermodynamicsAlgorithms::Species(500.0,ThermodynamicsAlgorithms::Species::diatomic)
           ,ThermodynamicsAlgorithms::Species(100.0,ThermodynamicsAlgorithms::Species::monoatomic)};
    const double energy(ThermodynamicsAlgorithms::totalEnergy(concentrations,temperatures,species));
    const double epsilon(0.01);


    const double temperatureNew1 = ThermodynamicsAlgorithms::temperature(concentrations,species,temperature + 400.0,energy,epsilon);
    const double temperatureNew2 = ThermodynamicsAlgorithms::temperature(concentrations,species,temperature - 400.0,energy,epsilon);
    const VectorXd newTemperatures1(std::vector<double>{temperatureNew1,temperatureNew1});
    const VectorXd newTemperatures2(std::vector<double>{temperatureNew2,temperatureNew2});
    const double newEnergy1(ThermodynamicsAlgorithms::totalEnergy(concentrations,newTemperatures1,species));
    const double newEnergy2(ThermodynamicsAlgorithms::totalEnergy(concentrations,newTemperatures2,species));

    QVERIFY((std::abs(energy - newEnergy1)/energy) < epsilon);
    QVERIFY((std::abs(energy - newEnergy2)/energy) < epsilon);
}
