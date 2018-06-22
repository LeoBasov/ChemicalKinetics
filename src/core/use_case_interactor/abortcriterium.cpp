#include "abortcriterium.h"

AbortCriterium::AbortCriterium()
{

}

bool AbortCriterium::valid(){
    if(this->validVal){
        this->validVal = false;
        return true;
    }else{
        return false;
    }
}

void AbortCriterium::abort(){
    this->validVal = false;
}
