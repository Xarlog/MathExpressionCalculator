#include "MathAnalytical.hpp"

Cosine::Cosine()
{
    args.resize(1);
    args[0] = new Var;
}

Cosine::Cosine(Expression *op)
{
    args.resize(1);
    args[0] = op;
}
double Cosine::eval(double x)
{
    return cos(args[0]->eval(x));
}
Expression *Cosine::derivate()
{
    return new Multiplication(new Negative(new Sine(args[0])), args[0]->derivate());
}
std::string Cosine::to_string()
{
    return "cos(" + args[0]->to_string() + ")";
}
Expression* Cosine::simplify() 
{
    Expression* e=args[0]->simplify();
    if(dynamic_cast<Negative*>(e)) return e->args[0];
    if(dynamic_cast<ArcCosine*>(e)) return e->args[0];
    return new Cosine(e);
}