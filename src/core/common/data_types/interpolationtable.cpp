#include "interpolationtable.h"

InterpolationTable::InterpolationTable(){

}

InterpolationTable::InterpolationTable(const std::vector<std::pair<double,double>>& valueTable)
                                      :valueTable(valueTable){
    std::sort(this->valueTable.begin(),this->valueTable.end());
}

void InterpolationTable::clear(){
    std::vector<std::pair<double,double>> ().swap(valueTable);
}

double InterpolationTable::getValue(const double &valueFirst) const{
    double returnValue(0.0);

    if(this->valueTable.size()<2){
        throw  Exception("InterpolationTable::" + std::string(__FUNCTION__),"At least two values required in interpolation table. Given <"
                                                                           + std::to_string(this->valueTable.size()) + ">");
    }

    for(auto iter(++(this->valueTable.begin()));iter!=this->valueTable.end();++iter){
        double x_0((iter-1)->first);
        double x_1(iter->first);
        double y_0((iter-1)->second);
        double y_1(iter->second);

        if((x_0<=valueFirst) && (x_1>=valueFirst)){
            returnValue = interpolate(x_0,x_1,y_0,y_1,valueFirst);
            break;
        }
    }

    return returnValue;
}

void InterpolationTable::addValuePair(const double &valueFirst,const double &valueSecond){
    auto pair(std::make_pair(valueFirst,valueSecond));
    this->valueTable.push_back(pair);
    std::sort(this->valueTable.begin(),this->valueTable.end());
}

double InterpolationTable::interpolate(const double &x_0, const double &x_1, const double &y_0, const double &y_1, const double &x) const{
    const double fraction((y_1 - y_0)/(x_1 - x_0));
    const double returnValue(y_0 + fraction*(x - x_0));
    return returnValue;
}

const std::vector<std::pair<double,double>> &InterpolationTable::getValueTable() const{
    return this->valueTable;
}

InterpolationTable& InterpolationTable::operator=(const InterpolationTable& other){
    if(this!=&other){
        this->valueTable = other.getValueTable();
    }

    return *this;
}

bool InterpolationTable::operator==(const InterpolationTable& other) const{
    std::vector<std::pair<double,double>> valueTable(other.getValueTable());
    bool equal(true);

    if(valueTable.size()!=this->valueTable.size()){
        equal = false;
    }else{
        for(size_t st(0);st<valueTable.size();++st){
            if(valueTable.at(st)!=this->valueTable.at(st)){
                equal = false;
                break;
            }
        }
    }

    return equal;
}

bool InterpolationTable::operator!=(const InterpolationTable& other) const{
    return !(*this==other);
}
