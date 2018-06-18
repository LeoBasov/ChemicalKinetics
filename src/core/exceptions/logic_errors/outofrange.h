#pragma once

#include <stdexcept>

class OutOfRange : public std::out_of_range
{
public:
    explicit OutOfRange(const std::string& whatArg,const std::string& whereArg);
    explicit OutOfRange(const char* whatArg,const char* whereArg);

    const char* where() const noexcept;

private:
    std::string whereStr;
};
