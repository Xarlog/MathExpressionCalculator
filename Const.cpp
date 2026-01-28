#include "MathAnalitical.hpp"
#include <format>
double Const::eval(const double x){
    return value;
}
Expression* Const::derivate(){
    return new Const(0);
}
std::string Const::to_string(){
    return std::format("{}",value);
}