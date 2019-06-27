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
#include "../../core/view_boundary/terminalview.hpp"
#include "csvwriterviewtest.h"
#include "../../core/input_boundary/xmlreader.h"

InputData setUpInputData();
InputData dsmcTest();

int main(int ,const char *argv[]){
    std::cout << "=================================CHEMICAL KINETICS==============================" << std::endl;
    std::cout << "Combustion of octan at 2000 K." << std::endl;
    std::cout << "================================================================================" << std::endl;

    try{
        XMLReader reader;
        InputData data;
        Controller controller;
        std::shared_ptr<Presenter> presenter(std::make_shared<Presenter>());
        std::shared_ptr<CSVWriterViewTest> csvWriterViewTest(std::make_shared<CSVWriterViewTest>());
        std::shared_ptr<TerminalView> terminalView(std::make_shared<TerminalView>());

        reader.read(argv[1]);
        data = reader.getData();

        presenter->subscribe(controller.getState());

        csvWriterViewTest->subscribe(presenter->getViewModel());
        terminalView->subscribe(presenter->getViewModel());

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
