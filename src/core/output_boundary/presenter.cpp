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

#include "presenter.h"

Presenter::Presenter():viewModel(std::make_shared<ViewModel>()){

}

Presenter::~Presenter(){

}

void Presenter::update(){
    this->viewModel->setState(this->state->getState());
    this->viewModel->notify();
}

void Presenter::subscribe(const std::shared_ptr<SimulationState>& state){
    this->state = state;
    this->state->attach(shared_from_this());
}

std::shared_ptr<ViewModel> Presenter::getViewModel(){
    return this->viewModel;
}
