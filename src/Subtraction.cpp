#include "MathAnalytical.hpp"

Subtraction::Subtraction(Expression* op1, Expression* op2){
    args.resize(2);
    args[0].reset(op1);
    args[1].reset(op2);
}
double Subtraction::eval(double x){
    return args[0]->eval(x)-args[1]->eval(x);
}

Expression* Subtraction::derivate(){
    return new Subtraction(args[0]->derivate(),args[1]->derivate());
}

std::string Subtraction::to_string(){
    return "("+args[0]->to_string()+"-"+args[1]->to_string()+")";
}
#define is_of_type(x,type) dynamic_cast<type*>(x.get())
Expression* Subtraction::simplify(){
    std::unique_ptr<Expression> e1(args[0]->simplify());
    std::unique_ptr<Expression> e2(args[1]->simplify());
    if(is_of_type(e1,Const) && is_of_type(e2,Const))
    {
        return new Const(e1->eval(0)-e2->eval(0));
    }
    if(is_of_type(e1,Const) && e1->eval(0)==0) return new Negative(e2.release());
    if(is_of_type(e2,Const) && e2->eval(0)==0) return e1.release();
    return new Subtraction(e1.release(),e2.release()); 
}

Expression* Subtraction::copy(){
    return new Subtraction(args[0]->copy(),args[1]->copy());
}