/* =============================================================================================
 * ChemicalKinetics
 *
 * A tool to calculate chemistry kinetics
 * ---------------------------------------------------------------------------------------------
 * Copyright (C) 2018  Leo Basov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public Licens
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * =============================================================================================
 */

#include <iostream>

#include "../../core/use_case_interactor/usecaseinteractor.h"
#include "../../core/input_boundary/controller.h"
#include "../../core/output_boundary/presenter.h"

InputData setUpInputData();
InputData dsmcTest();

/*int main()
{
    std::shared_ptr<TestPresenter> presenter(std::make_shared<TestPresenter>());
    std::shared_ptr<SimulationState> state(std::make_shared<SimulationState>());
    UseCaseInteractor interactor(state);
    InputData data(dsmcTest());

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
}*/

int main(){
    std::cout << "=================================CHEMICAL KINETICS==============================" << std::endl;
    std::cout << "Combustion of octan at 2000 K." << std::endl;
    std::cout << "================================================================================" << std::endl;

    try{
        InputData data(dsmcTest());
        Controller controller;
        std::shared_ptr<Presenter> presenter(std::make_shared<Presenter>());

        presenter->subscribe(controller.getState());
        controller.startSim(data);
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
    reac.mode = InputData::Reaction::const_k;
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

    state.integratorData.mode = InputData::IntegratorData::var_dt;
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

InputData dsmcTest(){
    InputData state;
    InputData::Species spec1;
    InputData::Species spec2;
    InputData::Species spec3;
    InputData::Reaction reac;

    //-------------------------------------------------------------------------------

    spec1.name = "e";
    spec2.name = "Ar";
    spec3.name = "Ar+";

    spec1.concentration = 2500.0e+15;
    spec2.concentration = 5000.0e+15;
    spec3.concentration = 0.0;

    //-------------------------------------------------------------------------------

    std::vector<InputData::RateConstPair> pairs;

    const double adRateConstants[] =
    {
         7.21567611449757e-22
        ,1.33740518914577e-20
        ,1.14009803160005e-19
        ,5.88461647651399e-19
        ,2.15528619580826e-18
        ,6.17843686709903e-18
        ,1.47765011784131e-17
        ,3.0791327962719e-17
        ,5.76375320651903e-17
        ,9.90834774916954e-17
        ,1.59015213013754e-16
        ,2.412211109298e-16
        ,3.49218243634981e-16
        ,4.86127795305664e-16
        ,6.54597734650026e-16
        ,8.56766091219458e-16
        ,1.09425630317451e-15
        ,1.3681960834467e-15
        ,1.67925220475511e-15
        ,2.0276749516988e-15
        ,2.4133473884986e-15
        ,2.83583586672916e-15
        ,3.29443927407249e-15
        ,3.78823538696457e-15
        ,4.31612335150937e-15
        ,4.87686180591094e-15
        ,5.46910250522939e-15
        ,6.09141954544782e-15
        ,6.74233443498105e-15
        ,7.42033734986234e-15
        ,8.12390495162128e-15
        ,8.8515151581682e-15
        ,9.60165924838742e-15
        ,1.03728516584697e-14
        ,1.11636377979796e-14
        ,1.19726001802664e-14
        ,1.27983631278164e-14
        ,1.36395962802722e-14
        ,1.44950171021886e-14
        ,1.53633925597125e-14
        ,1.62435401105078e-14
        ,1.71343281293853e-14
        ,1.8034675873106e-14
        ,1.89435530714736e-14
        ,1.98599792178642e-14
        ,2.07830226204623e-14
        ,2.17117992654346e-14
        ,2.2645471534804e-14
        ,2.35832468146661e-14
        ,2.45243760234128e-14
    };

    const double adTemperatures[] =
    {
        10000.0
        ,11836.7346938776
        ,13673.4693877551
        ,15510.2040816327
        ,17346.9387755102
        ,19183.6734693878
        ,21020.4081632653
        ,22857.1428571429
        ,24693.8775510204
        ,26530.612244898
        ,28367.3469387755
        ,30204.0816326531
        ,32040.8163265306
        ,33877.5510204082
        ,35714.2857142857
        ,37551.0204081633
        ,39387.7551020408
        ,41224.4897959184
        ,43061.2244897959
        ,44897.9591836735
        ,46734.693877551
        ,48571.4285714286
        ,50408.1632653061
        ,52244.8979591837
        ,54081.6326530612
        ,55918.3673469388
        ,57755.1020408163
        ,59591.8367346939
        ,61428.5714285714
        ,63265.306122449
        ,65102.0408163265
        ,66938.7755102041
        ,68775.5102040816
        ,70612.2448979592
        ,72448.9795918367
        ,74285.7142857143
        ,76122.4489795918
        ,77959.1836734694
        ,79795.9183673469
        ,81632.6530612245
        ,83469.387755102
        ,85306.1224489796
        ,87142.8571428571
        ,88979.5918367347
        ,90816.3265306122
        ,92653.0612244898
        ,94489.7959183674
        ,96326.5306122449
        ,98163.2653061225
        ,100000.0
    };

    size_t arraySize(sizeof(adRateConstants)/sizeof(adRateConstants[0]));

    for(size_t i(0);i<arraySize;++i){
        pairs.push_back(InputData::RateConstPair(adTemperatures[i],adRateConstants[i]));
    }


    reac.name = "collision";
    reac.mode = InputData::Reaction::interpol_k;
    reac.rateConstantTable = pairs;
    reac.stoichiometricCoeffEducts = {InputData::SpeciesValuePair(spec1.name,1.0)
                                     ,InputData::SpeciesValuePair(spec2.name,1.0)
                                     ,InputData::SpeciesValuePair(spec3.name,0.0)};
    reac.stoichiometricCoeffProducts = {InputData::SpeciesValuePair(spec1.name,2.0)
                                       ,InputData::SpeciesValuePair(spec2.name,0.0)
                                       ,InputData::SpeciesValuePair(spec3.name,1.0)};
    reac.reactionPowers = {InputData::SpeciesValuePair(spec1.name,1.0)
                          ,InputData::SpeciesValuePair(spec2.name,1.0)
                          ,InputData::SpeciesValuePair(spec3.name,0.0)};

    //-------------------------------------------------------------------------------

    state.integratorData.mode = InputData::IntegratorData::var_dt;
    state.integratorData.parameter = 0.1;
    state.integratorData.timeStep = 0.1;

    state.chemistryData.species.push_back(spec1);
    state.chemistryData.species.push_back(spec2);
    state.chemistryData.species.push_back(spec3);

    state.chemistryData.reactions.push_back(reac);

    state.chemistryData.temperature = 60000.0;

    return state;
}
