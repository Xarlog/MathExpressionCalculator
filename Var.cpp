#include "MathAnalytical.hpp"

double Var::eval(double x) {
    return x;
}

Expression* Var::derivate(){
    return new Const(1);
}

std::string Var::to_string(){
    return "x";
}

Expression* Var::copy(){
    return new Var();
}