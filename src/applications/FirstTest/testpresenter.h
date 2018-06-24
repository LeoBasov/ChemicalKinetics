#pragma once

#include <iostream>
#include  <fstream>

#include "../../core/output_boundary/observer.h"
#include "../../core/output_boundary/simulationstate.h"

class TestPresenter : public Observer, public std::enable_shared_from_this<TestPresenter>
{
public:
    TestPresenter();
    ~TestPresenter() override;

    void update() override;

    void subscribe(const std::shared_ptr<SimulationState>& state);

private:
    std::shared_ptr<SimulationState> state;
    std::ofstream stream;
};
