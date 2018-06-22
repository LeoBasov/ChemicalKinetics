#pragma once

class AbortCriterium
{
public:
    AbortCriterium();

    void abort();

    bool valid();

private:
    bool validVal = true;
};
