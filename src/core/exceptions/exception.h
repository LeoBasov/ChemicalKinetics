#pragma once

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
    Exception();
    Exception(const std::string &whatArg,const std::string &whereArg);
    ~Exception() noexcept override;

    const char* what() const noexcept override;
    const char* where() const noexcept;

private:
    std::string whatStr;
    std::string whereStr;
};
