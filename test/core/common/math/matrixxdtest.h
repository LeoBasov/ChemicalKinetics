#pragma once

#include "../../../unittest.h"
#include "../../../../src/core/common/math/matrixxd.h"

class MatrixXdTest : public UnitTest
{
    Q_OBJECT
public:
    MatrixXdTest(const std::string& name);

private slots:
    void constructorTest() const;
    void assignOperatorTest() const;
    void arithmeticOperatorsTest() const;
    void vectorMatrixMultTest() const;
    void transposeTest() const;
};
