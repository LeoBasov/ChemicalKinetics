#pragma once

#include "../common/data_types/state.h"
#include "../common/data_types/inputdata.h"
#include "abortcriterium.h"
#include "../entities/chemistry/chemistry.h"
#include "../entities/integrator/integrator.h"

class UseCaseInteractor
{
public:
    UseCaseInteractor();

    void start(const InputData& data);
    void stop();

private:
    State state;
    AbortCriterium abortCriterium;
    Chemistry chemistry;
    Integrator integrator;

    void initialize(const InputData& data);
    void initializeState(const InputData& data);
    void initializeIntergrator(const InputData::IntegratorData& data);
    void initializeChemistry(const InputData::ChemistryData& data);

    void execute();
    void report();
};
