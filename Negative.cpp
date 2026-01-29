#include "MathAnalytical.hpp"

Negative::Negative(){
    args.resize(1);
    args[0]=new Var;
}

Negative::Negative(Expression* op){
    args.resize(1);
    args[0]=op;
}

double Negative::eval(double x){
    return -args[0]->eval(x);
}

Expression* Negative::derivate(){
    return new Negative(args[0]->derivate());
}

std::string Negative::to_string(){
    return "-("+args[0]->to_string()+")";
}

Expression* Negative::simplify(){
    Expression* e=args[0]->simplify();
    if(dynamic_cast<Negative*>(e))
    {
        return e->args[0];
    }
    return new Negative(e);
}

Expression* Negative::copy(){
    return new Negative(args[0]->copy());
}