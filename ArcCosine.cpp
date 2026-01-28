#include "MathAnalitical.hpp"

ArcCosine::ArcCosine()
{
    args.resize(1);
    args[0] = new Var;
}

ArcCosine::ArcCosine(Expression *op)
{
    args.resize(1);
    args[0] = op;
}

double ArcCosine::eval(double x)
{
    return acos(args[0]->eval(x));
}

Expression *ArcCosine::derivate()
{
    return new Negative(new Division(args[0]->derivate(), new Pow(new Subtraction(new Const(1), new Pow(args[0], new Const(2))), new Const(0.5))));
}

std::string ArcCosine::to_string()
{
    return "arccos(" + args[0]->to_string() + ")";
}

Expression *ArcCosine::simplify()
{
    Expression *e = args[0]->simplify();
    return new ArcCosine(e);
}