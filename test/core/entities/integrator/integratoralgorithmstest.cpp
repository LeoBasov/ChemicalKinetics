#include "integratoralgorithmstest.h"

IntegratorAlgorithmsTest::IntegratorAlgorithmsTest(const std::string& name)
                                                  :UnitTest(name){

}

void IntegratorAlgorithmsTest::timeStepTest() const{
    const VectorXd values(std::vector<double>{1.0,3.0,7.0});
    const VectorXd diffs(std::vector<double>{10.0,3.0,7.0});
    const double frac(0.1);
    const double refVal(0.01);

    QCOMPARE(IntegratorAlgorithms::timeStep(values,diffs,frac),refVal);
}
