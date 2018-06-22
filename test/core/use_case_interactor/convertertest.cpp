#include "convertertest.h"

ConverterTest::ConverterTest(const std::string& name)
                            :UnitTest(name){

}

void ConverterTest::convertVector() const{
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

    vecRes = converter.vector(rateConstants,Converter::reaction);

    QCOMPARE(vecRes.at(0),rateConstantsVec.at(0));
    QCOMPARE(vecRes.at(1),rateConstantsVec.at(1));
}

void ConverterTest::convertVectorPair() const{
    const std::vector<std::string> species{"Spec1","Spec2","Spec3"};
    const std::vector<std::string> reactions{"React1","React2"};

    const std::vector<std::pair<std::string,std::pair<double,double>>> specVec{{"Spec3",{0.1,0.2}},{"Spec2",{0.3,0.4}},{"Spec1",{0.5,0.6}}};
    const std::vector<std::pair<std::string,std::pair<double,double>>> reactVec{{"React2",{0.7,0.8}},{"React1",{0.9,1.0}}};
    const std::vector<std::pair<double,double>> specVecRef{{0.5,0.6},{0.3,0.4},{0.1,0.2}};
    const std::vector<std::pair<double,double>> reactVecRef{{0.9,1.0},{0.7,0.8}};
    std::vector<std::pair<double,double>> vecRes;

    Converter converter;

    converter.setUp(species,reactions);

    vecRes = converter.vectorPair(specVec,Converter::species);

    QCOMPARE(vecRes.at(0),specVecRef.at(0));
    QCOMPARE(vecRes.at(1),specVecRef.at(1));
    QCOMPARE(vecRes.at(2),specVecRef.at(2));

    vecRes = converter.vectorPair(reactVec,Converter::reaction);

    QCOMPARE(vecRes.at(0),reactVecRef.at(0));
    QCOMPARE(vecRes.at(1),reactVecRef.at(1));
}

void ConverterTest::convertMatrix() const{
    const std::vector<std::string> species{"Spec1","Spec2","Spec3"};
    const std::vector<std::string> reactions{"React1","React2"};

    const std::vector<std::pair<std::string,double>> row1{{"Spec3",0.1},{"Spec2",0.2},{"Spec1",0.3}};
    const std::vector<std::pair<std::string,double>> row2{{"Spec2",0.4},{"Spec1",0.5},{"Spec3",0.6}};
    const std::vector<std::pair<std::string,std::vector<std::pair<std::string,double>>>> matRawInp{{"React2",row1},{"React1",row2}};
    const std::vector<std::vector<double>> matRaw{{0.5,0.4,0.6},{0.3,0.2,0.1}};
    const MatrixXd mat(matRaw);
    MatrixXd matRes;

    Converter converter;

    converter.setUp(species,reactions);

    matRes = converter.matrix(matRawInp);

    QCOMPARE(matRes.at(0,0),mat.at(0,0));
    QCOMPARE(matRes.at(0,1),mat.at(0,1));
    QCOMPARE(matRes.at(1,0),mat.at(1,0));
    QCOMPARE(matRes.at(1,1),mat.at(1,1));
}
