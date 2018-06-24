#pragma once

#include  "../common/data_types/state.h"

class AbortCriterium
{
public:
    AbortCriterium();

    void reset();
    void abort();

    bool valid(const State &state);

private:
    bool validVal = true;
    bool firstRun = true;
    State lastState;

    bool checkCriterium(const State &state) const;
};
