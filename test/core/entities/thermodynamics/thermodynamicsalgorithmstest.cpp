#include "thermodynamicsalgorithmstest.h"

ThermodynamicsAlgorithmsTest::ThermodynamicsAlgorithmsTest(const std::string& name)
                                                          :UnitTest(name){

}

void ThermodynamicsAlgorithmsTest::totalEnergyTest() const{
    const double factor(0.5*Constants::boltzmannConst);
    const double bysum(1.0/6.0);
    const VectorXd concentrations({1.0,2.0,3.0});
    const VectorXd temperatures({4.0,5.0,6.0});
    const VectorXd dofs({7.0,8.0,9.0});
    const double res(ThermodynamicsAlgorithms::totalEnergy(concentrations,temperatures,dofs));
    const VectorXd ref({concentrations.at(0)*bysum*(3.0*factor*temperatures.at(0) + dofs.at(0)*factor*temperatures.at(0))
                       ,concentrations.at(1)*bysum*(3.0*factor*temperatures.at(1) + dofs.at(1)*factor*temperatures.at(1))
                       ,concentrations.at(2)*bysum*(3.0*factor*temperatures.at(2) + dofs.at(2)*factor*temperatures.at(2))});

    QCOMPARE(res,ref.sum());
}
