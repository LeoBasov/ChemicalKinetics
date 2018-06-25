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
    std::string modeToStr(const Chemistry::Mode& mode) const;

private slots:
    void setUpTest() const;
    void chemModesTest() const;
};
