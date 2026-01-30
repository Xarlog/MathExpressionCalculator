#include "MathAnalytical.hpp"

Tangent::Tangent()
{
    args.resize(1);
    args[0].reset(new Var);
}

Tangent::Tangent(Expression *op)
{
    args.resize(1);
    args[0].reset(op);
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
#define is_of_type(x,type) dynamic_cast<type*>(x.get())
Expression *Tangent::simplify()
{
    std::unique_ptr<Expression> e ( args[0]->simplify());
    if (is_of_type(e,ArcTangent))
        return e->args[0].release();
    return new Tangent(e.release());
}

Expression* Tangent::copy(){
    return new Tangent(args[0]->copy());
}