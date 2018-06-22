#include "testpresenter.h"

TestPresenter::TestPresenter()
{

}

TestPresenter::~TestPresenter(){

}

void TestPresenter::update(){
    const State& locSt(this->state->getState());

    std::cout << "Temperature = " << locSt.temperature <<  std::endl;
}

void TestPresenter::subscribe(const std::shared_ptr<SimulationState>& state){
    this->state = state;
    this->state->attach(std::make_shared<TestPresenter>(*this));
}
