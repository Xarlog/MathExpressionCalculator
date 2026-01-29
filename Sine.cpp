#include "MathAnalytical.hpp"

Sine::Sine()
{
    args.resize(1);
    args[0] = new Var;
}
Sine::Sine(Expression *op)
{
    args.resize(1);
    args[0] = op;
}
double Sine::eval(double x)
{
    return sin(args[0]->eval(x));
}
Expression *Sine::derivate()
{
    return new Multiplication(new Cosine(args[0]), args[0]->derivate());
}

std::string Sine::to_string()
{
    return "sin(" + args[0]->to_string() + ")";
}

Expression *Sine::simplify()
{
    Expression *e = args[0]->simplify();
    if (dynamic_cast<ArcSine *>(e))
        return e->args[0];
    return new Sine(e);
}

Expression* Sine::copy(){
    return new Sine(args[0]->copy());
}