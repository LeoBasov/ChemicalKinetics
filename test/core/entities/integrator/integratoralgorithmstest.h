#pragma once

#include "../../../unittest.h"
#include "../../../../src/core/entities/integrator/integratoralgorithms.h"

class IntegratorAlgorithmsTest : public UnitTest
{
    Q_OBJECT
public:
    IntegratorAlgorithmsTest(const std::string& name);

private slots:
    void timeStepTest() const;
    void firstOrderTest() const;
};
