#pragma once

#include<vector>
#include<memory>

#include "observer.h"

class Subject
{
public:
    Subject();
    virtual ~Subject() = 0;

    void attach(const std::shared_ptr<Observer>& observer);
    void detach(const std::shared_ptr<Observer>& observer);
    void notify() const;

private:
    std::vector<std::shared_ptr<Observer>> observers;

    bool isAttached(const std::shared_ptr<Observer>& observer) const;
};
