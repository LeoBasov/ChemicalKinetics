#pragma once

#include "../../unittest.h"
#include "../../../src/core/use_case_interactor/converter.h"

class ConverterTest : public UnitTest
{
    Q_OBJECT
public:
    ConverterTest(const std::string& name);

private slots:
    void convertVector() const;
    void convertMatrix() const;
};
