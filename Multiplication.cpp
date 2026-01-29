#include "MathAnalytical.hpp"
Multiplication::Multiplication(Expression* op1, Expression* op2){
    args.resize(2);
    args[0].reset(op1);
    args[1].reset(op2);
}

double Multiplication::eval(double x){
    return args[0]->eval(x)*args[1]->eval(x);
}

Expression* Multiplication::derivate(){
    return new Addition(
        new Multiplication(args[0]->derivate(),args[1]->copy()),
        new Multiplication(args[0]->copy(),args[1]->derivate()));
}

std::string Multiplication::to_string(){
    return "("+args[0]->to_string()+"*"+args[1]->to_string()+")";
}
#define is_of_type(x,type) dynamic_cast<type*>(x.get())
Expression* Multiplication::simplify(){
    std::unique_ptr<Expression> e1(args[0]->simplify());
    std::unique_ptr<Expression> e2(args[1]->simplify());
    if(is_of_type(e1,Const) && is_of_type(e2,Const))
    {
        return new Const(e1->eval(0)*e2->eval(0));
    }
    if(is_of_type(e1,Const) && e1->eval(0)==1) return e2.release();
    if(is_of_type(e2,Const) && e2->eval(0)==1) return e1.release();
    if(is_of_type(e1, Const) && e1->eval(0)==0) return new Const(0);
    if(is_of_type(e2, Const) && e2->eval(0)==0) return new Const(0);
    if(is_of_type(e1,Negative) && is_of_type(e2,Negative)) return new Multiplication(e1.release(),e2.release());
    return new Multiplication(e1.release(),e2.release()); 
}

Expression* Multiplication::copy(){
    return new Multiplication(args[0]->copy(),args[1]->copy());
}