#include "MathAnalytical.hpp"

Sine::Sine()
{
    args.resize(1);
    args[0].reset(new Var);
}
Sine::Sine(Expression *op)
{
    args.resize(1);
    args[0].reset(op);
}
double Sine::eval(double x)
{
    return sin(args[0]->eval(x));
}
Expression *Sine::derivate()
{
    return new Multiplication(new Cosine(args[0]->copy()), args[0]->derivate());
}

std::string Sine::to_string()
{
    return "sin(" + args[0]->to_string() + ")";
}
#define is_of_type(x,type) dynamic_cast<type*>(x.get())
Expression *Sine::simplify()
{
    std::unique_ptr<Expression> e ( args[0]->simplify());
    if (is_of_type(e,ArcSine))
        return e->args[0].release();
    return new Sine(e.release());
}

Expression* Sine::copy(){
    return new Sine(args[0]->copy());
}