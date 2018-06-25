#pragma once

#include "../../../unittest.h"
#include "../../../../src/core/entities/chemistry/chemistry.h"
#include "../../../../src/core/use_case_interactor/converter.h"

class ChemistryTest : public UnitTest
{
    Q_OBJECT
public:
    ChemistryTest(const std::string& name);

private:
    InputData getState() const;
    Chemistry setUpChemisty() const;

private slots:
    void getRateConstantsTest() const;
    void getReactionRates() const;
};
