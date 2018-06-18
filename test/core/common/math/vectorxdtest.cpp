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
