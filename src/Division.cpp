#include "MathAnalytical.hpp"

Division::Division(Expression *op1, Expression *op2)
{
    args.resize(2);
    args[0] .reset(op1);
    args[1] .reset(op2);
}

double Division::eval(double x)
{
    return args[0]->eval(x) / args[1]->eval(x);
}
Expression *Division::derivate()
{
    return new Division(new Subtraction(new Multiplication(args[0]->derivate(), args[1]->copy()), new Multiplication(args[0]->copy(), args[1]->derivate())), new Multiplication(args[1]->copy(), args[1]->copy()));
}

std::string Division::to_string()
{
    return "(" + args[0]->to_string() + "/" + args[1]->to_string() + ")";
}

Expression *Division::simplify()
{
    Expression *e1 = args[0]->simplify();
    Expression *e2 = args[1]->simplify();
    return new Division(e1, e2);
}

Expression* Division::copy(){
    return new Division(args[0]->copy(),args[1]->copy());
}