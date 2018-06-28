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

#include "core/common/math/vectorxdtest.h"
#include "core/common/math/matrixxdtest.h"
#include "core/common/data_types/interpolationtabletest.h"
#include "core/entities/chemistry/chemistryalgorithmstest.h"
#include "core/entities/chemistry/chemistrytest.h"
#include "core/entities/integrator/integratoralgorithmstest.h"
#include "core/entities/integrator/integratortest.h"
#include "core/entities/thermodynamics/thermodynamicsalgorithmstest.h"
#include "core/use_case_interactor/convertertest.h"

int main(int argc, char **argv){
    std::vector<std::shared_ptr<UnitTest>> tests;
    int totalErrors(0);

    tests.push_back(std::make_shared<VectorXdTest>("VectorXdTest"));
    tests.push_back(std::make_shared<MatrixXdTest>("MatrixXdTest"));

    tests.push_back(std::make_shared<InterpolationTableTest>("InterpolationTableTest"));

    tests.push_back(std::make_shared<ChemistryAlgorithmsTest>("ChemistryAlgorithmsTest"));
    tests.push_back(std::make_shared<ChemistryTest>("ChemistryTest"));
    tests.push_back(std::make_shared<IntegratorAlgorithmsTest>("IntegratorAlgorithmsTest"));
    tests.push_back(std::make_shared<IntegratorTest>("IntegratorTest"));
    tests.push_back(std::make_shared<ThermodynamicsAlgorithmsTest>("ThermodynamicsAlgorithmsTest"));

    tests.push_back(std::make_shared<ConverterTest>("ConverterTest"));

    for(std::shared_ptr<UnitTest> test : tests){
        int errors = QTest::qExec(test.get(),argc,argv);

        if(errors!=0){
            QStringList list;
            std::string fileName(test->getName() + ".txt");

            list << "";
            list << "-o";
            list << QString::fromStdString(fileName);

            QTest::qExec(test.get(),list);

            totalErrors += errors;
        }
    }

    tests.clear();

    std::cout << "=============================================================" << std::endl;
    std::cout << totalErrors << " test(s) faild." << std::endl;
    std::cout << "=============================================================" << std::endl;

    return 0;
}
