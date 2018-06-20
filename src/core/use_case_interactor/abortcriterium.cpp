#include "abortcriterium.h"

AbortCriterium::AbortCriterium()
{

}

bool AbortCriterium::valid() const{
    return this->validVal;
}

void AbortCriterium::abort(){
    this->validVal = false;
}
