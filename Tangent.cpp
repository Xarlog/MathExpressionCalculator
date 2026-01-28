#include "MathAnalitical.hpp"

Tangent::Tangent()
{
    args.resize(1);
    args[0] = new Var;
}

Tangent::Tangent(Expression *op)
{
    args.resize(1);
    args[0] = op;
}

double Tangent::eval(double x)
{
    return tan(args[0]->eval(x));
}

Expression *Tangent::derivate()
{
    return new Division(args[0]->derivate(), new Pow(new Cosine(new Var), new Const(2)));
}

std::string Tangent::to_string()
{
    return "tg(" + args[0]->to_string() + ")";
}

Expression *Tangent::simplify()
{
    Expression *e = args[0]->simplify();
    if (dynamic_cast<ArcTangent *>(e))
        return e->args[0];
    return new Tangent(e);
}