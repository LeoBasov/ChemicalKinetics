#include "view.h"

View::View()
{

}

void View::open(const std::string& file){
    this->stream.open(file);
}

void View::plot(const State& state){
    this->stream << state.time << ",";

    for(size_t i(0);i<state.concentrations.size();i++){
        this->stream <<state.concentrations.at(i) << ", ";
    }

   this->stream << std::endl;
}
