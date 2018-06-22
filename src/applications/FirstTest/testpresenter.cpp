#include "testpresenter.h"

TestPresenter::TestPresenter()
{

}

TestPresenter::~TestPresenter(){

}

void TestPresenter::update(){
    const State& locSt(this->state->getState());

    std::cout << "Temperature = " << locSt.temperature <<  std::endl;

    for(size_t i(0);i<locSt.concentrations.size();i++){
        std::cout << locSt.speciesMap.at(i) << " = " << locSt.concentrations.at(i) << ", ";
    }

    std::cout << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
}

void TestPresenter::subscribe(const std::shared_ptr<SimulationState>& state){
    this->state = state;
    this->state->attach(std::make_shared<TestPresenter>(*this));
}
