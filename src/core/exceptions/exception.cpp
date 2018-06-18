#include "exception.h"

Exception::Exception():Exception("","standart constuctor used"){

}

Exception::Exception(const std::string &where, const std::string &what)
                    :wherestr(where)
                    ,whatstr(what){

}

Exception::~Exception() noexcept{

}

const char* Exception::what() const noexcept{
    return whatstr.c_str();
}

const char* Exception::where() const noexcept{
    return wherestr.c_str();
}
