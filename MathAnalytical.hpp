#ifndef MATH_ANALYTICAL_HPP
#define MATH_ANALYTICAL_HPP
#include <vector>
#include <cmath>
#include <string>
#include <memory>
class Expression
{
    public:
    std::vector<std::unique_ptr<Expression>> args;
    virtual double eval(double x){return 0;};
    virtual Expression* derivate(){return nullptr;};
    virtual std::string to_string(){return "UNDEFINED";}; 
    virtual Expression* simplify(){return this;}
    virtual Expression* copy(){return nullptr;};
    protected:
    Expression(){}
};
class Const:public Expression
{
    public:
    Const(double v):value{v}{}
    double value;
    double eval(const double x) override;
    Expression* derivate() override;
    std::string to_string() override;
    Expression* copy() override;
};
class Var:public Expression
{
    public:
    double eval(const double x) override;
    Expression* derivate() override;
    std::string to_string() override;
    Expression* copy() override;
};
class Negative: public Expression
{
    public:
    Negative();
    Negative(Expression* op);
    double eval(double x) override;
    Expression* derivate() override;
    std::string to_string() override;
    Expression* simplify() override;
    Expression* copy() override;
};
class Addition: public Expression
{
    public:
    Addition(Expression* op1, Expression* op2);
    double eval(double x) override;
    Expression* derivate() override;
    std::string to_string() override;
    Expression* simplify() override;
    Expression* copy() override;
};
class Subtraction: public Expression
{
    public:
    Subtraction(Expression* op1, Expression* op2);
    double eval(double x) override;
    Expression* derivate() override;
    std::string to_string() override;
    Expression* simplify() override;
    Expression* copy() override;
};
class Multiplication: public Expression
{
    public:
    Multiplication(Expression* op1, Expression* op2);
    double eval(double x) override;
    Expression* derivate() override;
    std::string to_string() override;
    Expression* simplify() override;
    Expression* copy() override;
};
class Exp: public Expression
{
public:
    Exp();
    Exp(Expression* op);
    double eval(double x) override;
    Expression* derivate() override;
    std::string to_string() override;
    Expression* simplify() override;
    Expression* copy() override;
};
class Division: public Expression
{
    public:
    Division(Expression* op1, Expression* op2);
    double eval(double x) override;
    Expression* derivate() override;
    std::string to_string() override;
    Expression* simplify() override;
    Expression* copy() override;
};
class NatLog:public Expression
{
    public:
    NatLog();
    NatLog(Expression* op);
    double eval(double x) override;
    Expression* derivate() override;
    std::string to_string() override;
    Expression* simplify() override;
    Expression* copy() override;
};
class Pow: public Expression
{
    public:
    Pow(Expression* op1, Expression* op2);
    double eval(double x) override;
    Expression* derivate() override;
    std::string to_string() override;
    Expression* simplify() override;
    Expression* copy() override;
};
class Cosine: public Expression
{
    public:
    Cosine();
    Cosine(Expression* op);
    double eval(double x) override;
    Expression* derivate() override;
    std::string to_string() override;
    Expression* simplify() override;
    Expression* copy() override;
};
class Sine: public Expression
{
    public:
    Sine();
    Sine(Expression* op);
    double eval(double x) override;
    Expression* derivate() override;
    std::string to_string() override;
    Expression* simplify() override;
    Expression* copy() override;
};
class Tangent: public Expression
{
    public:
    Tangent();
    Tangent(Expression* op);
    double eval(double x) override;
    Expression* derivate() override;
    std::string to_string() override;
    Expression* simplify() override;
    Expression* copy() override;
};
class ArcSine: public Expression
{
    public:
    ArcSine();
    ArcSine(Expression* op);
    double eval(double x) override;
    Expression* derivate() override;
    std::string to_string() override;
    Expression* simplify() override;
    Expression* copy() override;
};
class ArcCosine:public Expression
{
    public:
    ArcCosine();
    ArcCosine(Expression* op);
    double eval(double x) override;
    Expression* derivate() override;
    std::string to_string() override;
    Expression* simplify() override;
    Expression* copy() override;
};
class ArcTangent:public Expression
{
    public:
    ArcTangent();
    ArcTangent(Expression* op);
    double eval(double x) override;
    Expression* derivate() override;
    std::string to_string() override;
    Expression* simplify() override;
    Expression* copy() override;
};

#endif