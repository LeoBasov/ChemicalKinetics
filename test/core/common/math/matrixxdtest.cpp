#include "matrixxdtest.h"

MatrixXdTest::MatrixXdTest(const std::string& name)
                          :UnitTest(name){

}

void MatrixXdTest::constructorTest() const{
    const std::vector<std::vector<double>> rows({{1.0,3.0},{7.0,11.0}});
    const MatrixXd mat1;
    const MatrixXd mat2(2,2,1.0);
    const MatrixXd mat3(rows);
    const MatrixXd mat4(mat3);

    QCOMPARE(mat1.sizeRow(),size_t(0));
    QCOMPARE(mat1.sizeColumn(),size_t(0));

    QCOMPARE(mat2.sizeRow(),size_t(2));
    QCOMPARE(mat2.sizeColumn(),size_t(2));

    QCOMPARE(mat2[0][0],1.0);
    QCOMPARE(mat2[1][0],1.0);
    QCOMPARE(mat2[0][1],1.0);
    QCOMPARE(mat2[1][1],1.0);

    QCOMPARE(mat3.sizeRow(),size_t(2));
    QCOMPARE(mat3.sizeColumn(),size_t(2));

    QCOMPARE(mat3[0][0],1.0);
    QCOMPARE(mat3[1][0],7.0);
    QCOMPARE(mat3[0][1],3.0);
    QCOMPARE(mat3[1][1],11.0);

    QCOMPARE(mat3.at(0,0),1.0);
    QCOMPARE(mat3.at(1,0),7.0);
    QCOMPARE(mat3.at(0,1),3.0);
    QCOMPARE(mat3.at(1,1),11.0);

    QCOMPARE(mat4.sizeRow(),size_t(2));
    QCOMPARE(mat4.sizeColumn(),size_t(2));

    QCOMPARE(mat4[0][0],1.0);
    QCOMPARE(mat4[1][0],7.0);
    QCOMPARE(mat4[0][1],3.0);
    QCOMPARE(mat4[1][1],11.0);

    QCOMPARE(mat4.at(0,0),1.0);
    QCOMPARE(mat4.at(1,0),7.0);
    QCOMPARE(mat4.at(0,1),3.0);
    QCOMPARE(mat4.at(1,1),11.0);
}

void MatrixXdTest::assignOperatorTest() const{
    const std::vector<std::vector<double>> rows({{1.0,3.0},{7.0,11.0}});
    const MatrixXd mat1(rows);
    MatrixXd mat2(2,2);

    QVERIFY(mat1.at(0,0)!=mat2.at(0,0));
    QVERIFY(mat1.at(1,0)!=mat2.at(1,0));
    QVERIFY(mat1.at(0,1)!=mat2.at(0,1));
    QVERIFY(mat1.at(1,1)!=mat2.at(1,1));

    mat2 = mat1;

    QVERIFY(mat1.at(0,0)==mat2.at(0,0));
    QVERIFY(mat1.at(1,0)==mat2.at(1,0));
    QVERIFY(mat1.at(0,1)==mat2.at(0,1));
    QVERIFY(mat1.at(1,1)==mat2.at(1,1));
}
