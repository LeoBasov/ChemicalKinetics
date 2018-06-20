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

void IntegratorAlgorithmsTest::firstOrderTest() const{
    const VectorXd values(std::vector<double>{1.0,3.0,7.0});
    const VectorXd diffs(std::vector<double>{10.0,3.0,7.0});
    const VectorXd ref(std::vector<double>{1.1,3.03,7.07});
    VectorXd results;
    const double timeStep(0.01);

    results = IntegratorAlgorithms::firstOrder(values,diffs,timeStep);

    QCOMPARE(results.at(0),ref.at(0));
    QCOMPARE(results.at(1),ref.at(1));
    QCOMPARE(results.at(2),ref.at(2));
}
