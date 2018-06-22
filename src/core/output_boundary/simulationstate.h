#pragma once

#include "subject.h"
#include "../common/data_types/state.h"

class SimulationState : public Subject
{
public:
    SimulationState();
    ~SimulationState() override;

    const State& getState() const;
    void setState(const State& state);

private:
    State state;
};
