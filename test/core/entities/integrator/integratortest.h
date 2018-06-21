#pragma once

#include "../../../unittest.h"
#include "../../../../src/core/entities/integrator/integrator.h"

class IntegratorTest : public UnitTest
{
    Q_OBJECT
public:
    IntegratorTest(const std::string& name);

private slots:
    void integratorTest() const;
};
