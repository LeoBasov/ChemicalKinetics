#include "convertertest.h"

ConverterTest::ConverterTest(const std::string& name)
                            :UnitTest(name){

}

void ConverterTest::convertTest() const{
    const std::vector<std::string> species{"Spec1","Spec2","Spec3"};
    const std::vector<std::string> reactions{"React1","React2"};

    const std::vector<std::pair<std::string,double>> concetrations{{"Spec3",0.1},{"Spec2",0.2},{"Spec1",0.3}};
    const std::vector<std::pair<std::string,double>> rateConstants{{"React2",0.4},{"React1",0.5}};
    const VectorXd concetrationsVec(std::vector<double>{0.3,0.2,0.1});
    const VectorXd rateConstantsVec(std::vector<double>{0.5,0.4});
    VectorXd vecRes;

    Converter converter;

    converter.setUp(species,reactions);

    vecRes = converter.vector(concetrations,Converter::species);

    QCOMPARE(vecRes.at(0),concetrationsVec.at(0));
    QCOMPARE(vecRes.at(1),concetrationsVec.at(1));
    QCOMPARE(vecRes.at(2),concetrationsVec.at(2));
}
