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

void MatrixXdTest::arithmeticOperatorsTest() const{
    const std::vector<std::vector<double>> rows({{1.0,3.0},{7.0,11.0}});
    const double val(10);
    const VectorXd vec(std::vector<double>{3.0,7.0});
    const MatrixXd mat1(2,2,1.0);
    const MatrixXd mat2(rows);
    MatrixXd result;
    VectorXd resultVec;

    result = mat1 + mat2;

    QCOMPARE(result.sizeRow(),size_t(2));
    QCOMPARE(result.sizeColumn(),size_t(2));

    QCOMPARE(result[0][0],2.0);
    QCOMPARE(result[1][0],8.0);
    QCOMPARE(result[0][1],4.0);
    QCOMPARE(result[1][1],12.0);

    result = mat1 - mat2;

    QCOMPARE(result.sizeRow(),size_t(2));
    QCOMPARE(result.sizeColumn(),size_t(2));

    QCOMPARE(result[0][0],0.0);
    QCOMPARE(result[1][0],-6.0);
    QCOMPARE(result[0][1],-2.0);
    QCOMPARE(result[1][1],-10.0);

    result = mat2*val;

    QCOMPARE(result.sizeRow(),size_t(2));
    QCOMPARE(result.sizeColumn(),size_t(2));

    QCOMPARE(result[0][0],10.0);
    QCOMPARE(result[1][0],70.0);
    QCOMPARE(result[0][1],30.0);
    QCOMPARE(result[1][1],110.0);

    resultVec = mat2*vec;

    QCOMPARE(resultVec.size(),size_t(2));

    QCOMPARE(resultVec[0],24.0);
    QCOMPARE(resultVec[1],98.0);
}

void MatrixXdTest::vectorMatrixMultTest() const{
    const std::vector<std::vector<double>> rows({{1.0},{7.0}});
    const MatrixXd mat2(rows);
    const VectorXd vec(1,3.0);
    const VectorXd ref(std::vector<double>{3.0,21.0});
    VectorXd result;

    result = mat2*vec;

    QCOMPARE(result.at(0),ref.at(0));
    QCOMPARE(result.at(1),ref.at(1));
}

void MatrixXdTest::transposeTest() const{
    const std::vector<std::vector<double>> matRaw({{1.0,3.0,7.0},{11.0,13.0,17.0},{23.0,29.0,31.0}});
    const std::vector<std::vector<double>> matRawRef({{1.0,11.0,23.0},{3.0,13.0,29.0},{7.0,17.0,31.0}});
    const MatrixXd mat(matRaw);
    const MatrixXd ref(matRawRef);
    MatrixXd result1;
    MatrixXd result2;

    result1 = MatrixXd::transpose(mat);
    result2 = mat.transpose();

    QCOMPARE(result1.at(0,0),ref.at(0,0));
    QCOMPARE(result1.at(0,1),ref.at(0,1));
    QCOMPARE(result1.at(0,2),ref.at(0,2));
    QCOMPARE(result1.at(1,0),ref.at(1,0));
    QCOMPARE(result1.at(1,1),ref.at(1,1));
    QCOMPARE(result1.at(1,2),ref.at(1,2));
    QCOMPARE(result1.at(2,0),ref.at(2,0));
    QCOMPARE(result1.at(2,1),ref.at(2,1));
    QCOMPARE(result1.at(2,2),ref.at(2,2));

    QCOMPARE(result2.at(0,0),ref.at(0,0));
    QCOMPARE(result2.at(0,1),ref.at(0,1));
    QCOMPARE(result2.at(0,2),ref.at(0,2));
    QCOMPARE(result2.at(1,0),ref.at(1,0));
    QCOMPARE(result2.at(1,1),ref.at(1,1));
    QCOMPARE(result2.at(1,2),ref.at(1,2));
    QCOMPARE(result2.at(2,0),ref.at(2,0));
    QCOMPARE(result2.at(2,1),ref.at(2,1));
    QCOMPARE(result2.at(2,2),ref.at(2,2));

}
