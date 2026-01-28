#include "MathAnalytical.hpp"
Multiplication::Multiplication(Expression* op1, Expression* op2){
    args.resize(2);
    args[0]=op1;
    args[1]=op2;
}

double Multiplication::eval(double x){
    return args[0]->eval(x)*args[1]->eval(x);
}

Expression* Multiplication::derivate(){
    return new Addition(new Multiplication(args[0]->derivate(),args[1]),new Multiplication(args[0],args[1]->derivate()));
}

std::string Multiplication::to_string(){
    return "("+args[0]->to_string()+"*"+args[1]->to_string()+")";
}

Expression* Multiplication::simplify(){
    Expression* e1=args[0]->simplify();
    Expression* e2=args[1]->simplify();
    if(dynamic_cast<Const*>(e1)&&dynamic_cast<Const*>(e2))
    {
        return new Const(e1->eval(0)*e2->eval(0));
    }
    if(dynamic_cast<Const*>(e1)&&e1->eval(0)==1) return e2;
    if(dynamic_cast<Const*>(e2)&&e2->eval(0)==1) return e1;
    if(dynamic_cast<Const*>(e1)&&e1->eval(0)==0) return new Const(0);
    if(dynamic_cast<Const*>(e2)&&e2->eval(0)==0) return new Const(0);
    if(dynamic_cast<Negative*>(e1)&&dynamic_cast<Negative*>(e2)) return new Multiplication(e1,e2);
    return new Multiplication(e1,e2); 
}