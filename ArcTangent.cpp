#include "MathAnalytical.hpp"

ArcTangent::ArcTangent()
{
    args.resize(1);
    args[0] = new Var;
}
ArcTangent::ArcTangent(Expression *op)
{
    args.resize(1);
    args[0] = op;
}

double ArcTangent::eval(double x)
{
    return atan(args[0]->eval(x));
}
Expression *ArcTangent::derivate()
{
    return new Division(args[0]->derivate(), new Addition(new Const(1), new Pow(args[0], new Const(2))));
}

std::string ArcTangent::to_string()
{
    return "arctg(" + args[0]->to_string() + ")";
}

Expression *ArcTangent::simplify()
{
    Expression *e = args[0]->simplify();
    return new ArcTangent(e);
}