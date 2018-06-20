#pragma once

class AbortCriterium
{
public:
    AbortCriterium();

    void abort();

    bool valid() const;

private:
    bool validVal = false;
};
