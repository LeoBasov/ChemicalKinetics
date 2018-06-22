#include "subject.h"

Subject::Subject(){

}

Subject::~Subject(){

}

void Subject::attach(const std::shared_ptr<Observer>& observer){
    if(!isAttached(observer)){
        this->observers.push_back(observer);
    }
}

void Subject::detach(const std::shared_ptr<Observer>& observer){
    for(auto iter(this->observers.begin());iter!=this->observers.end();++iter){
        if(*iter==observer){
            this->observers.erase(iter);
            break;
        }
    }
}

void Subject::notify() const{
    for(auto observer : this->observers){
        observer->update();
    }
}

bool Subject::isAttached(const std::shared_ptr<Observer>& observer) const{
    for(auto obsr : this->observers){
        if(observer==obsr){
            return true;
        }
    }

    return false;
}
