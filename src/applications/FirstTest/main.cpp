#include <iostream>

#include "testpresenter.h"
#include "../../core/use_case_interactor/usecaseinteractor.h"

int main()
{
    std::shared_ptr<TestPresenter> presenter(std::make_shared<TestPresenter>());
    std::shared_ptr<SimulationState> state(std::make_shared<SimulationState>());
    UseCaseInteractor interactor(state);
    InputData data;

    presenter->subscribe(state);

    data.integratorData.mode = "var_dt";
    data.integratorData.parameter = 0.1;
    data.integratorData.timeStep = 1.0e+10;

    data.chemistryData.mode = "const_k";
    data.chemistryData.temperature = 2000.0;
    data.chemistryData.speciesNames = {"C8H18","O2","C02","H2O"};
    data.chemistryData.reactionNames = {"combustion"};
    data.chemistryData.concentrations = {{"C8H18",4.0},{"O2",4.0},{"C02",0.0},{"H2O",0.0}};
    data.chemistryData.concentrationDiffs = {{"C8H18",.0},{"O2",0.0},{"C02",0.0},{"H2O",0.0}};
    data.chemistryData.reactionRates = {{"combustion",0.0}};
    data.chemistryData.rateConstants = {{"combustion",2.83583586672916e-15}};
    data.chemistryData.rateConstantsTables = {{"combustion",{{0.1,0.2},{0.3,0.4}}}};
    data.chemistryData.arrheniusCoefficients = {{"combustion",{0.1,0.2}}};
    data.chemistryData.stoichiometricCoeffEducts = {{"combustion",{{"C8H18",1.0},{"O2",(7/2.0)},{"C02",0.0},{"H2O",0.0}}}};
    data.chemistryData.stoichiometricCoeffProducts = {{"combustion",{{"C8H18",0.0},{"O2",(0.0)},{"C02",2.0},{"H2O",3.0}}}};
    data.chemistryData.reactionPowers = {{"combustion",{{"C8H18",0.1},{"O2",(1.65)},{"C02",0.0},{"H2O",0.0}}}};


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
