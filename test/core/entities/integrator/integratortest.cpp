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

#include "integratortest.h"

IntegratorTest::IntegratorTest(const std::string& name):UnitTest(name)
{

}

void IntegratorTest::integratorTest() const{
    const double dt = 0.1;
    const double dtParam = 0.1;
    const double refParamDt(0.1*(1.0/7.0));
    const VectorXd values(std::vector<double>{1.0,3.0,7.0});
    const VectorXd diff(std::vector<double>{7.0,3.0,1.0});
    const VectorXd refConstDt(std::vector<double>{1.7,3.3,7.1});
    const VectorXd refVarDt(std::vector<double>{1.0 + refParamDt*7.0,3.0 + refParamDt*3.0,7.0 + refParamDt*1.0});
    VectorXd results;
    Integrator integrator;
    bool control(false);

    integrator.setTimeStep(dt);
    integrator.setTimeStepParamter(dtParam);

    integrator.setMode(Integrator::const_dt);

    results = integrator.integrate(values,diff);

    QCOMPARE(results.at(0),refConstDt.at(0));
    QCOMPARE(results.at(1),refConstDt.at(1));
    QCOMPARE(results.at(2),refConstDt.at(2));

    integrator.setMode(Integrator::var_dt);

    results = integrator.integrate(values,diff);

    QCOMPARE(results.at(0),refVarDt.at(0));
    QCOMPARE(results.at(1),refVarDt.at(1));
    QCOMPARE(results.at(2),refVarDt.at(2));

    integrator.setMode(Integrator::none);

    try{
        results = integrator.integrate(values,diff);
    }catch(Exception){
        control = true;
    }

    QVERIFY(control);
}
