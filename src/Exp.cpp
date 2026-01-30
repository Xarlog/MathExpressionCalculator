#include "MathAnalytical.hpp"

Exp::Exp()
{
    args.resize(1);
    args[0].reset(new Var);
}

Exp::Exp(Expression *op)
{
    args.resize(1);
    args[0].reset(op);
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
#define is_of_type(x,type) dynamic_cast<type*>(x.get())
Expression *Exp::simplify()
{
    std::unique_ptr<Expression>e( args[0]->simplify());
    if (is_of_type(e,Const))
        return new Const(pow(std::numbers::e_v<double>, e->eval(0)));
    return new Exp(e.release());
}

Expression* Exp::copy(){
    return new Exp(args[0]->copy());
}