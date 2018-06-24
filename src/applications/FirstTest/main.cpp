#include <iostream>

#include "testpresenter.h"
#include "../../core/use_case_interactor/usecaseinteractor.h"

InputData setUpInputData();

int main()
{
    std::shared_ptr<TestPresenter> presenter(std::make_shared<TestPresenter>());
    std::shared_ptr<SimulationState> state(std::make_shared<SimulationState>());
    UseCaseInteractor interactor(state);
    InputData data(setUpInputData());

    presenter->subscribe(state);

    std::cout << "=================================CHEMICAL KINETICS==============================" << std::endl;
    std::cout << "Combustion of octan at 2000 K." << std::endl;
    std::cout << "================================================================================" << std::endl;

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
    }catch(std::exception e){
        std::cout << "==================================STD::EXCEPTION=====================================" << std::endl;
        std::cout << "WAHT: " << e.what() << std::endl;
        std::cout << "================================================================================" << std::endl;
    }

    std::cout << "==================================DONE==========================================" << std::endl;

    return 0;
}

InputData setUpInputData(){
    InputData state;
    InputData::Species spec1;
    InputData::Species spec2;
    InputData::Species spec3;
    InputData::Species spec4;
    InputData::Reaction reac;

    spec1.name = "C8H18";
    spec2.name = "O2";
    spec3.name = "CO2";
    spec4.name = "H2O";

    spec1.concentration = 4.0;
    spec2.concentration = 4.0;
    spec3.concentration = 0.0;
    spec4.concentration = 0.0;

    reac.name = "combustion";
    reac.mode = "const_k";
    reac.rateConstant = 2.83583586672916e-15;
    reac.stoichiometricCoeffEducts = {InputData::SpeciesValuePair(spec1.name,1.0)
                                     ,InputData::SpeciesValuePair(spec2.name,7/2.0)
                                     ,InputData::SpeciesValuePair(spec3.name,0.0)
                                     ,InputData::SpeciesValuePair(spec4.name,0.0)};
    reac.stoichiometricCoeffProducts = {InputData::SpeciesValuePair(spec1.name,0.0)
                                       ,InputData::SpeciesValuePair(spec2.name,0.0)
                                       ,InputData::SpeciesValuePair(spec3.name,2.0)
                                       ,InputData::SpeciesValuePair(spec4.name,3.0)};
    reac.reactionPowers = {InputData::SpeciesValuePair(spec1.name,0.1)
                          ,InputData::SpeciesValuePair(spec2.name,1.65)
                          ,InputData::SpeciesValuePair(spec3.name,0.0)
                          ,InputData::SpeciesValuePair(spec4.name,0.0)};

    state.integratorData.mode = "var_dt";
    state.integratorData.parameter = 0.1;
    state.integratorData.timeStep = 0.1;

    state.chemistryData.species.push_back(spec1);
    state.chemistryData.species.push_back(spec2);
    state.chemistryData.species.push_back(spec3);
    state.chemistryData.species.push_back(spec4);

    state.chemistryData.reactions.push_back(reac);

    state.chemistryData.temperature = 2000.0;

    return state;
}
