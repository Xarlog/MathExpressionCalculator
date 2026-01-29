#include "MathAnalytical.hpp"

NatLog::NatLog()
{
    args.resize(1);
    args[0].reset(new Var);
}

NatLog::NatLog(Expression *op)
{
    args.resize(1);
    args[0].reset(op);
}
double NatLog::eval(double x)
{
    return log(x) / log(std::numbers::e_v<double>);
}

Expression *NatLog::derivate()
{
    return new Division(args[0]->derivate(), args[0]->copy());
}
std::string NatLog::to_string()
{
    return "ln(" + args[0]->to_string() + ")";
}

Expression *NatLog::simplify()
{
    Expression *e = args[0]->simplify();
    return new NatLog(e);
}

Expression* NatLog::copy(){
    return new NatLog(args[0]->copy());
}