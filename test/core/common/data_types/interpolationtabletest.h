#pragma once

#include "../../../unittest.h"
#include "../../../../src/core/common/data_types/interpolationtable.h"

class InterpolationTableTest : public UnitTest
{
    Q_OBJECT
public:
    InterpolationTableTest(const std::string& name);

private slots:
    void getSetTest() const;
    void compareOperatorTest() const;
};
