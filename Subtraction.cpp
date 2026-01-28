#include "MathAnalitical.hpp"

Subtraction::Subtraction(Expression* op1, Expression* op2){
    args.resize(2);
    args[0]=op1;
    args[1]=op2;
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

Expression* Subtraction::simplify(){
    Expression* e1=args[0]->simplify();
    Expression* e2=args[1]->simplify();
    if(dynamic_cast<Const*>(e1)&&dynamic_cast<Const*>(e2))
    {
        return new Const(e1->eval(0)-e2->eval(0));
    }
    if(dynamic_cast<Const*>(e1)&&e1->eval(0)==0) return new Negative(e2);
    if(dynamic_cast<Const*>(e2)&&e2->eval(0)==0) return e1;
    return new Subtraction(e1,e2); 
}