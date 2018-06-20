#pragma once

class AbortCriterium
{
public:
    AbortCriterium();

    bool valid() const;

private:
    bool validVal = false;
};
