#include "MathAnalytical.hpp"

ArcSine::ArcSine()
{
    args.resize(1);
    args[0] = new Var;
}

ArcSine::ArcSine(Expression *op)
{
    args.resize(1);
    args[0] = op;
}

double ArcSine::eval(double x)
{
    return asin(args[0]->eval(x));
}

Expression *ArcSine::derivate()
{
    return new Division(args[0]->derivate(), new Pow(new Subtraction(new Const(1), new Pow(args[0], new Const(2))), new Const(0.5)));
}
std::string ArcSine::to_string()
{
    return "arcsin(" + args[0]->to_string() + ")";
}

Expression *ArcSine::simplify()
{
    Expression *e = args[0]->simplify();
    return new ArcSine(e);
}

Expression* ArcSine::copy(){
    return new ArcSine(args[0]->copy());
}