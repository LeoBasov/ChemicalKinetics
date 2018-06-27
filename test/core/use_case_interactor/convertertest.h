#pragma once

#include "../../unittest.h"
#include "../../../src/core/use_case_interactor/converter.h"

class ConverterTest : public UnitTest
{
    Q_OBJECT
public:
    ConverterTest(const std::string& name);

private:
    InputData getState() const;
    InputData::Reaction::Mode modeToMode(const Chemistry::Mode& mode) const;

private slots:
    void setUpTest() const;
    void chemModesTest() const;
    void concentrationsTest() const;
    void concentrationsDiffsTest() const;
    void reactionRatesTest() const;
    void rateConstantsTest() const;
    void excessEnergiesTest() const;
    void rateConstantsTablesTest() const;
    void stoichiometricCoeffEductsTest() const;
    void stoichiometricCoeffProductsTest() const;
    void reactionPowersTest() const;
    void arrheniusCoefficientsTest() const;
    void integratorModeTest() const;
};
