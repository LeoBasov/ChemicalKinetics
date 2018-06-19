#include <iostream>

#include "core/common/math/vectorxdtest.h"
#include "core/common/math/matrixxdtest.h"

int main(int argc, char **argv){
    std::vector<std::shared_ptr<UnitTest>> tests;
    int totalErrors(0);

    tests.push_back(std::make_shared<VectorXdTest>("VectorXdTest"));
    tests.push_back(std::make_shared<MatrixXdTest>("MatrixXdTest"));

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
