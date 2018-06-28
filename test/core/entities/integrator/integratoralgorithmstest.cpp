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

#include "integratoralgorithmstest.h"

IntegratorAlgorithmsTest::IntegratorAlgorithmsTest(const std::string& name)
                                                  :UnitTest(name){

}

void IntegratorAlgorithmsTest::timeStepTest() const{
    const VectorXd values(std::vector<double>{1.0,3.0,7.0});
    const VectorXd diffs(std::vector<double>{10.0,3.0,7.0});
    const double frac(0.1);
    const double refVal(0.01);

    QCOMPARE(IntegratorAlgorithms::timeStep(values,diffs,frac),refVal);
}

void IntegratorAlgorithmsTest::firstOrderTest() const{
    const VectorXd values(std::vector<double>{1.0,3.0,7.0});
    const VectorXd diffs(std::vector<double>{10.0,3.0,7.0});
    const VectorXd ref(std::vector<double>{1.1,3.03,7.07});
    VectorXd results;
    const double timeStep(0.01);

    results = IntegratorAlgorithms::firstOrder(values,diffs,timeStep);

    QCOMPARE(results.at(0),ref.at(0));
    QCOMPARE(results.at(1),ref.at(1));
    QCOMPARE(results.at(2),ref.at(2));
}
