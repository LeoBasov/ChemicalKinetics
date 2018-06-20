#pragma once

#include "../../../unittest.h"
#include "../../../../src/core/entities/chemistry/chemistryalgorithms.h"

class ChemistryAlgorithmsTest : public UnitTest
{
    Q_OBJECT
public:
    ChemistryAlgorithmsTest(const std::string& name);

private slots:
    void arrheniusEquationTest() const;
    void reactionRatePowLawTest() const;
};
