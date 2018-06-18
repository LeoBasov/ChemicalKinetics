#include "vectorxdtest.h"

VectorXdTest::VectorXdTest(const std::string &name):UnitTest(name){

}

void VectorXdTest::constuctorTest() const{
    std::vector<double> vals{3.0,7.0,11.0,13.0};
    VectorXd vec1;
    VectorXd vec2(3,3.0);
    VectorXd vec3(vals);
    VectorXd vec4(vec3);

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
