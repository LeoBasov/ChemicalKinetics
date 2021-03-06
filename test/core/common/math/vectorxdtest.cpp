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

#include "vectorxdtest.h"

VectorXdTest::VectorXdTest(const std::string &name):UnitTest(name){

}

void VectorXdTest::constuctorTest() const{
    const std::vector<double> vals{3.0,7.0,11.0,13.0};
    const VectorXd vec1;
    const VectorXd vec2(3,3.0);
    const VectorXd vec3(vals);
    const VectorXd vec4(vec3);

    QVERIFY(vec1.size()==0);

    QCOMPARE(3.0,vec2.at(0));
    QCOMPARE(3.0,vec2.at(1));
    QCOMPARE(3.0,vec2.at(2));

    QVERIFY(vec2.size()==3);

    QCOMPARE(3.0,vec3.at(0));
    QCOMPARE(7.0,vec3.at(1));
    QCOMPARE(11.0,vec3.at(2));
    QCOMPARE(13.0,vec3.at(3));

    QVERIFY(vec3.size()==4);

    QCOMPARE(3.0,vec4.at(0));
    QCOMPARE(7.0,vec4.at(1));
    QCOMPARE(11.0,vec4.at(2));
    QCOMPARE(13.0,vec4.at(3));

    QVERIFY(vec4.size()==4);

    QVERIFY(vec3==vec4);
}

void VectorXdTest::assignOperatorTest() const{
    const std::vector<double> vals{3.0,7.0,11.0,13.0};
    const VectorXd vec1(vals);
    VectorXd vec2(3,3.0);

    QCOMPARE(3.0,vec1.at(0));
    QCOMPARE(7.0,vec1.at(1));
    QCOMPARE(11.0,vec1.at(2));
    QCOMPARE(13.0,vec1.at(3));

    QVERIFY(vec1.size()==4);

    QCOMPARE(3.0,vec2.at(0));
    QCOMPARE(3.0,vec2.at(1));
    QCOMPARE(3.0,vec2.at(2));

    QVERIFY(vec2.size()==3);

    vec2 = vec1;

    QCOMPARE(3.0,vec2.at(0));
    QCOMPARE(7.0,vec2.at(1));
    QCOMPARE(11.0,vec2.at(2));
    QCOMPARE(13.0,vec2.at(3));

    QVERIFY(vec2.size()==4);
}

void VectorXdTest::compareOperatorTest() const{
    const std::vector<double> vals{3.0,7.0,11.0,13.0};
    const VectorXd vec1(vals);
    const VectorXd vec2(3,3.0);
    const VectorXd vec3(vec2);

    QVERIFY(vec1>vec2);
    QVERIFY(vec1>=vec2);

    QVERIFY(vec2<vec1);
    QVERIFY(vec2<=vec1);

    QVERIFY(vec2<=vec3);
    QVERIFY(vec2>=vec3);
    QVERIFY(vec2==vec3);
    QVERIFY(!(vec2>vec3));
    QVERIFY(!(vec2<vec3));
}

void VectorXdTest::arithmeticOperatorTest() const{
    const double val(3.0);
    const std::vector<double> vals1{3.0,7.0,11.0};
    const std::vector<double> vals2{13.0,17.0,23.0};
    const VectorXd vec1(vals1);
    const VectorXd vec2(vals2);
    VectorXd vec3;
    double val2(0.0);

    vec3 = vec1 + vec2;

    QCOMPARE(vec3.at(0),16.0);
    QCOMPARE(vec3.at(1),24.0);
    QCOMPARE(vec3.at(2),34.0);

    vec3 = vec1 - vec2;

    QCOMPARE(vec3.at(0),-10.0);
    QCOMPARE(vec3.at(1),-10.0);
    QCOMPARE(vec3.at(2),-12.0);

    vec3 = vec1*val;

    QCOMPARE(vec3.at(0),9.0);
    QCOMPARE(vec3.at(1),21.0);
    QCOMPARE(vec3.at(2),33.0);

    val2 = vec1*vec2;

    QCOMPARE(val2,411);
}

void VectorXdTest::moduleTest() const{
    const std::vector<double> vals1{1.0,2.0,3.0};
    const VectorXd vec1(vals1);

    QCOMPARE(vec1.module(),std::sqrt(14.0));
}

void VectorXdTest::sumTest() const{
    const std::vector<double> vals1{1.0,2.0,3.0};
    const VectorXd vec1(vals1);

    QCOMPARE(vec1.sum(),vals1.at(0) + vals1.at(1) + vals1.at(2));
}

void VectorXdTest::elemWiseMultTest() const{
    const VectorXd vec1({1.0,2.0,3.0});
    const VectorXd vec2({4.0,5.0,6.0});
    const VectorXd ref({4.0,10.0,18.0});
    const VectorXd res1(VectorXd::elemWiseMult(vec1,vec2));
    const VectorXd res2(vec1.elemWiseMult(vec2));

    QCOMPARE(res1.at(0),ref.at(0));
    QCOMPARE(res1.at(1),ref.at(1));
    QCOMPARE(res1.at(2),ref.at(2));

    QCOMPARE(res2.at(0),ref.at(0));
    QCOMPARE(res2.at(1),ref.at(1));
    QCOMPARE(res2.at(2),ref.at(2));
}
