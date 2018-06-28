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

#include "chemistryalgorithmstest.h"

ChemistryAlgorithmsTest::ChemistryAlgorithmsTest(const std::string& name)
                                                :UnitTest(name){

}

void ChemistryAlgorithmsTest::arrheniusEquationTest() const{
    const double preFactor(13.0);
    const double activationEnergy(0.0);
    const double temperature(1.0);

    QCOMPARE(ChemistryAlgorithms::arrheniusEquation(preFactor,activationEnergy,temperature),preFactor);
}

void ChemistryAlgorithmsTest::reactionRatePowLawTest() const{
    const VectorXd rateConstants(std::vector<double>{1.0,3.0});
    const VectorXd concentrations(std::vector<double>{3.0,7.0});
    const VectorXd refVals1(std::vector<double>{21.0,63.0});
    const VectorXd refVals2(std::vector<double>{147.0,194481.0});
    VectorXd results;
    const MatrixXd pows1(2,2,0.0);
    const MatrixXd pows2(2,2,1.0);
    MatrixXd pows3(2,2,1.0);

    pows3.at(0,0) = 1.0;
    pows3.at(0,1) = 2.0;
    pows3.at(1,0) = 3.0;
    pows3.at(1,1) = 4.0;

    results = ChemistryAlgorithms::reactionRatePowLaw(rateConstants,concentrations,pows1);

    QCOMPARE(results.at(0),rateConstants.at(0));
    QCOMPARE(results.at(1),rateConstants.at(1));

    results = ChemistryAlgorithms::reactionRatePowLaw(rateConstants,concentrations,pows2);

    QCOMPARE(results.at(0),refVals1.at(0));
    QCOMPARE(results.at(1),refVals1.at(1));

    results = ChemistryAlgorithms::reactionRatePowLaw(rateConstants,concentrations,pows3);

    QCOMPARE(results.at(0),refVals2.at(0));
    QCOMPARE(results.at(1),refVals2.at(1));
}
