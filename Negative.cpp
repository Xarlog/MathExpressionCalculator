#include "MathAnalytical.hpp"

Negative::Negative(){
    args.resize(1);
    args[0].reset(new Var);
}

Negative::Negative(Expression* op){
    args.resize(1);
    args[0].reset(op);
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
#define is_of_type(x,type) dynamic_cast<type*>(x.get())
Expression* Negative::simplify(){
    std::unique_ptr<Expression> e(args[0]->simplify());
    if(is_of_type(e,Negative))
    {
        return e->args[0].release();
    }
    return new Negative(e.release());
}

Expression* Negative::copy(){
    return new Negative(args[0]->copy());
}