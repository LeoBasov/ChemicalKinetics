#include "unittest.h"

UnitTest::UnitTest(const std::string &name, QObject *parent)
                  :QObject(parent)
                  ,name(name)
{

}

std::string UnitTest::getName() const{
    return this->name;
}
