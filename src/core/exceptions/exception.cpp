#include "exception.h"

Exception::Exception():Exception("standart constuctor used",""){

}

Exception::Exception(const std::string &whatArg, const std::string &whereArg)
                    :whatStr(whatArg)
                    ,whereStr(whereArg){

}

Exception::~Exception() noexcept{

}

const char* Exception::what() const noexcept{
    return whatStr.c_str();
}

const char* Exception::where() const noexcept{
    return whereStr.c_str();
}
