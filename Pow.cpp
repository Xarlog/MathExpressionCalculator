#include "MathAnalytical.hpp"

Pow::Pow(Expression *op1, Expression *op2)
{
    args.resize(2);
    args[0] = op1;
    args[1] = op2;
}

double Pow::eval(double x)
{
    return pow(args[0]->eval(x), args[1]->eval(x));
}
Expression *Pow::derivate()
{
    return new Multiplication(new Exp(new Multiplication(new NatLog(args[0]), args[1])), (new Multiplication(new NatLog(args[0]), args[1]))->derivate());
}

std::string Pow::to_string()
{
    return "pow(" + args[0]->to_string() + "," + args[1]->to_string() + ")";
}

Expression *Pow::simplify()
{
    Expression *e1 = args[0]->simplify();
    Expression *e2 = args[1]->simplify();
    return new Pow(e1, e2);
}

Expression* Pow::copy(){
    return new Pow(args[0]->copy(),args[1]->copy());
}