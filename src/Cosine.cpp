#include "MathAnalytical.hpp"

Cosine::Cosine()
{
    args.resize(1);
    args[0].reset(new Var);
}

Cosine::Cosine(Expression *op)
{
    args.resize(1);
    args[0].reset(op);
}
double Cosine::eval(double x)
{
    return cos(args[0]->eval(x));
}
Expression *Cosine::derivate()
{
    return new Multiplication(new Negative(new Sine(args[0]->copy())), args[0]->derivate());
}
std::string Cosine::to_string()
{
    return "cos(" + args[0]->to_string() + ")";
}
#define is_of_type(x,type) dynamic_cast<type*>(x.get())
Expression* Cosine::simplify() 
{
    std::unique_ptr<Expression> e(args[0]->simplify());
    if(is_of_type(e,Negative)) return e->args[0].release();
    if(is_of_type(e,ArcCosine)) return e->args[0].release();
    return new Cosine(e.release());
}

Expression* Cosine::copy(){
    return new Cosine(args[0]->copy());
}