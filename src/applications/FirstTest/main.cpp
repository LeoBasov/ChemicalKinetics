#include <iostream>

#include "testpresenter.h"
#include "../../core/use_case_interactor/usecaseinteractor.h"

int main()
{
    TestPresenter presenter;
    std::shared_ptr<SimulationState> state(std::make_shared<SimulationState>());
    UseCaseInteractor interactor(state);
    InputData data;

    presenter.subscribe(state);

    data.integratorData.mode = "const_dt";
    data.integratorData.parameter = 0.1;
    data.integratorData.timeStep = 0.1;

    data.chemistryData.mode = "const_k";
    data.chemistryData.temperature = 10000.0;
    data.chemistryData.speciesNames = {"spec1","spec2"};
    data.chemistryData.reactionNames = {"reac1","reac2"};
    data.chemistryData.concentrations = {{"spec1",0.1},{"spec2",0.2}};
    data.chemistryData.reactionRates = {{"reac1",0.1},{"reac2",0.2}};
    data.chemistryData.rateConstants = {{"reac1",0.1},{"reac2",0.2}};
    data.chemistryData.rateConstantsTables = {{"reac1",{{0.1,0.2},{0.3,0.4}}},{"reac2",{{0.1,0.2},{0.3,0.4}}}};
    data.chemistryData.arrheniusCoefficients = {{"reac1",{0.1,0.2}},{"reac2",{0.1,0.2}}};
    data.chemistryData.stoichiometricCoeffEducts = {{"reac1",{{"spec1",0.1},{"spec2",0.1}}},{"reac2",{{"spec1",0.1},{"spec2",0.1}}}};
    data.chemistryData.stoichiometricCoeffProducts = {{"reac1",{{"spec1",0.1},{"spec2",0.1}}},{"reac2",{{"spec1",0.1},{"spec2",0.1}}}};
    data.chemistryData.reactionPowers = {{"reac1",{{"spec1",0.1},{"spec2",0.1}}},{"reac2",{{"spec1",0.1},{"spec2",0.1}}}};

    try{
        interactor.start(data);
    }catch(OutOfRange& e){
        std::cout << "==================================OUT OF RANGE==================================" << std::endl;
        std::cout << "WAHT: " << e.what() << std::endl << "WHERE: " << e.where() << std::endl;
        std::cout << "================================================================================" << std::endl;
    }catch(Exception& e){
        std::cout << "==================================EXCEPTION=====================================" << std::endl;
        std::cout << "WAHT: " << e.what() << std::endl << "WHERE: " << e.where() << std::endl;
        std::cout << "================================================================================" << std::endl;
    }

    return 0;
}
