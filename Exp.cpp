#include "MathAnalytical.hpp"

Exp::Exp()
{
    args.resize(1);
    args[0] = new Var;
}

Exp::Exp(Expression *op)
{
    args.resize(1);
    args[0] = op;
}

double Exp::eval(double x)
{
    return pow(std::numbers::e_v<double>, x);
}

Expression *Exp::derivate()
{
    return new Multiplication(this, args[0]->derivate());
}

std::string Exp::to_string()
{
    return "exp(" + args[0]->to_string() + ")";
}

Expression *Exp::simplify()
{
    Expression *e = args[0]->simplify();
    if (dynamic_cast<Const *>(e))
        return new Const(pow(std::numbers::e_v<double>, e->eval(0)));
    return new Exp(e);
}