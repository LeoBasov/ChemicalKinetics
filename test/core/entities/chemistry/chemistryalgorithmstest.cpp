#include "chemistryalgorithmstest.h"

ChemistryAlgorithmsTest::ChemistryAlgorithmsTest(const std::string& name)
                                                :UnitTest(name){

}

void ChemistryAlgorithmsTest::arrheniusEquationTest(){
    const double preFactor(13.0);
    const double activationEnergy(0.0);
    const double temperature(1.0);

    QCOMPARE(ChemistryAlgorithms::arrheniusEquation(preFactor,activationEnergy,temperature),preFactor);
}
