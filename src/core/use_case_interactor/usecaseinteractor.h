#pragma once

#include "../common/data_types/state.h"
#include "abortcriterium.h"
#include "../entities/chemistry/chemistry.h"
#include "../entities/integrator/integrator.h"

class UseCaseInteractor
{
public:
    UseCaseInteractor();

    void start();

private:
    State state;
    AbortCriterium abortCriterium;
    Chemistry chemistry;
    Integrator integrator;

    void initialize();
    void execute();
    void report();
};
