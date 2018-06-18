#include "outofrange.h"

OutOfRange::OutOfRange(const std::string& whatArg,const std::string& whereArg)
                      :std::out_of_range(whatArg)
                      ,whereStr(whereArg){

}

OutOfRange::OutOfRange(const char* whatArg,const char* whereArg)
                      :std::out_of_range(whatArg)
                      ,whereStr(whereArg){

}

const char* OutOfRange::where() const noexcept{
    return whereStr.c_str();
}
