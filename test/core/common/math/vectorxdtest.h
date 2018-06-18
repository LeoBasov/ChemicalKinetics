#pragma once

#include "../../../unittest.h"
#include "../../../../src/core/common/math/vectorxd.h"

class VectorXdTest : public UnitTest
{
    Q_OBJECT
public:
    VectorXdTest(const std::string& name);

private slots:
    void constuctorTest() const;

    void assignOperatorTest() const;
    void compareOperatorTest() const;
    void arithmeticOperatorTest() const;

    void moduleTest() const;
};
