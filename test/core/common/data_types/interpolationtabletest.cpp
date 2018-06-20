#include "interpolationtabletest.h"

InterpolationTableTest::InterpolationTableTest(const std::string& name):UnitTest(name)
{

}

void InterpolationTableTest::getSetTest() const{
    InterpolationTable table;

    double x_0(0.0);
    double x_1(1.0);
    double x_2(2.0);
    double y_0(0.0);
    double y_1(1.0);
    double y_2(4.0);

    table.addValuePair(x_1,y_1);
    table.addValuePair(x_0,y_0);
    table.addValuePair(x_2,y_2);

    QCOMPARE(table.getValue(0.0),0.0);
    QCOMPARE(table.getValue(1.0),1.0);
    QCOMPARE(table.getValue(2.0),4.0);

    QCOMPARE(table.getValue(0.5),0.5);
    QCOMPARE(table.getValue(1.5),2.5);
}

void InterpolationTableTest::compareOperatorTest() const{
    InterpolationTable table1;
    InterpolationTable table2;
    InterpolationTable table3;

    double x_0(0.0);
    double x_1(1.0);
    double x_2(2.0);
    double x_3(3.0);
    double y_0(0.0);
    double y_1(1.0);
    double y_2(4.0);
    double y_3(7.0);

    table1.addValuePair(x_0,y_0);
    table1.addValuePair(x_1,y_1);
    table1.addValuePair(x_2,y_2);

    table2.addValuePair(x_0,y_0);
    table2.addValuePair(x_1,y_1);
    table2.addValuePair(x_2,y_2);

    table3.addValuePair(x_0,y_0);
    table3.addValuePair(x_1,y_1);
    table3.addValuePair(x_3,y_3);

    QVERIFY(table1==table2);
    QVERIFY(table1!=table3);
}
