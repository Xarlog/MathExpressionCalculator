#include <iostream>
#include <vector>
#include <numbers>
#include <cmath>
#include "MathAnalytical.hpp"
int main(int, char**){
    /*Expression* e=new Addition(new Var(),new Multiplication(new Var(),new Addition(new Var(),new Const(3))));
    e->print();
    std::cout<<'\n';
    e->derivate()->print();
    NatLog(new Const(2)).derivate()->print();*/
    /*Expression* e2= new Sine(new Pow(new Var,new Const(2)));
    e2->print();
    std::cout<<'\n';
    e2->derivate()->derivate()->derivate()->print();*/
    /*Expression* e3= new Negative(new Negative(new Negative(new Subtraction(new Var, new Const(0)))));
    e3->print();
    std::cout<<'\n';
    e3->simplify()->print();*/
    Expression* e4=new Exp(new Multiplication(new Multiplication(new Addition(new Var, new Const(5)),new Addition(new Var, new Const(7))),new Addition(new Var, new Const(4))));
    e4->print();
    std::cout<<'\n';
    e4->derivate()->derivate()->derivate()->print();
    std::cout<<'\n';
    e4->derivate()->derivate()->derivate()->simplify()->print();
}
