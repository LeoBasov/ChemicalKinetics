#pragma once

#include <fstream>

#include "../../core/common/data_types/state.h"

class View
{
public:
    View();

    void open(const std::string& file);
    void plot(const State& state);

private:
    std::ofstream stream;
};
