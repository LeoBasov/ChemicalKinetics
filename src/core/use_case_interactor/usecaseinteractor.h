#pragma once

#include "../common/data_types/state.h"
#include "../common/data_types/inputdata.h"
#include "abortcriterium.h"
#include "../entities/chemistry/chemistry.h"
#include "../entities/integrator/integrator.h"
#include "converter.h"
#include "../output_boundary/simulationstate.h"

class UseCaseInteractor
{
public:
    explicit UseCaseInteractor(const std::shared_ptr<SimulationState>& simState);

    void start(const InputData& data);
    void stop();

private:
    Converter converter;
    State state;
    AbortCriterium abortCriterium;
    Chemistry chemistry;
    Integrator integrator;
    std::shared_ptr<SimulationState> simulationState;

    void initialize(const InputData& data);
    void initializeState(const InputData& data);
    void initializeIntergrator(const InputData::IntegratorData& data);
    void initializeChemistry(const InputData::ChemistryData& data);

    void execute();
    void report();

    Chemistry::Mode chemistryMode(const std::string& str) const;
    Integrator::Mode integratorMode(const std::string& str) const;
};
