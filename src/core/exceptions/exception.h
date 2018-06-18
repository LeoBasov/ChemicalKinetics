#pragma once

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
    Exception();
    Exception(const std::string &where,const std::string &what);
    ~Exception() noexcept override;

    const char* what() const noexcept override;
    const char* where() const noexcept;

private:
    std::string wherestr;
    std::string whatstr;
};
