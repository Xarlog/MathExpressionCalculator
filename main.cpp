#include <iostream>
#include <vector>
#include <numbers>
#include <cmath>
class Expression
{
    public:
    std::vector<Expression*> args;
    virtual double eval(double x){return 0;};
    virtual Expression* derivate(){return nullptr;};
    virtual void print(){}; 
    virtual Expression* simplify(){return this;}
    protected:
    Expression(){}
};
class Const:public Expression
{
    public:
    Const(double v):value{v}{}
    double value;
    double eval(double x) override
    {
        return value;
    }
    Expression* derivate() override
    {
        return new Const(0);
    }
    void print() override
    {
        std::cout<<value;
    }
};
class Var:public Expression
{
    public:
    double eval(double x) override
    {
        return x;
    }
    Expression* derivate() override
    {
        return new Const(1);
    }
    void print() override
    {
        std::cout<<"x";
    }
};
class Negative: public Expression
{
    public:
    Negative()
    {
        args.resize(1);
        args[0]=new Var;
    }
    Negative(Expression* op)
    {
        args.resize(1);
        args[0]=op;
    }
    double eval(double x) override
    {
        return -args[0]->eval(x);
    }
    Expression* derivate() override
    {
        return new Negative(args[0]->derivate());
    }
    void print() override
    {
        std::cout<<"-(";
        args[0]->print();
        std::cout<<')';
    }
    Expression* simplify() override
    {
        Expression* e=args[0]->simplify();
        if(dynamic_cast<Negative*>(e))
        {
            return e->args[0];
        }
        return new Negative(e);
    }
};
class Addition: public Expression
{
    public:
    Addition(Expression* op1, Expression* op2)
    {
        args.resize(2);
        args[0]=op1;
        args[1]=op2;
    }
    double eval(double x) override
    {
        return args[0]->eval(x)+args[1]->eval(x);
    }
    Expression* derivate() override
    {
        return new Addition(args[0]->derivate(),args[1]->derivate());
    }
    void print() override
    {
        std::cout<<'(';
        args[0]->print();
        std::cout<<'+';
        args[1]->print();
        std::cout<<')';
    }
    Expression* simplify() override
    {
        Expression* e1=args[0]->simplify();
        Expression* e2=args[1]->simplify();
        if(dynamic_cast<Const*>(e1)&&dynamic_cast<Const*>(e2))
        {
            return new Const(e1->eval(0)+e2->eval(0));
        }
        if(dynamic_cast<Const*>(e1)&&e1->eval(0)==0) return e2;
        if(dynamic_cast<Const*>(e2)&&e2->eval(0)==0) return e1;
        return new Addition(e1,e2); 
    }
};
class Subtraction: public Expression
{
    public:
    Subtraction(Expression* op1, Expression* op2)
    {
        args.resize(2);
        args[0]=op1;
        args[1]=op2;
    }
    double eval(double x) override
    {
        return args[0]->eval(x)-args[1]->eval(x);
    }
    Expression* derivate() override
    {
        return new Subtraction(args[0]->derivate(),args[1]->derivate());
    }
    void print() override
    {
        std::cout<<'(';
        args[0]->print();
        std::cout<<'-';
        args[1]->print();
        std::cout<<')';
    }
    Expression* simplify() override
    {
        Expression* e1=args[0]->simplify();
        Expression* e2=args[1]->simplify();
        if(dynamic_cast<Const*>(e1)&&dynamic_cast<Const*>(e2))
        {
            return new Const(e1->eval(0)-e2->eval(0));
        }
        if(dynamic_cast<Const*>(e1)&&e1->eval(0)==0) return new Negative(e2);
        if(dynamic_cast<Const*>(e2)&&e2->eval(0)==0) return e1;
        return new Subtraction(e1,e2); 
    }
};
class Multiplication: public Expression
{
    public:
    Multiplication(Expression* op1, Expression* op2)
    {
        args.resize(2);
        args[0]=op1;
        args[1]=op2;
    }
    double eval(double x) override
    {
        return args[0]->eval(x)*args[1]->eval(x);
    }
    Expression* derivate() override //refferals to old args needs to be replaced with copying
    {
        return new Addition(new Multiplication(args[0]->derivate(),args[1]),new Multiplication(args[0],args[1]->derivate()));
    }
    void print() override
    {
        std::cout<<'(';
        args[0]->print();
        std::cout<<'*';
        args[1]->print();
        std::cout<<')';
    }
    Expression* simplify() override
    {
        Expression* e1=args[0]->simplify();
        Expression* e2=args[1]->simplify();
        if(dynamic_cast<Const*>(e1)&&dynamic_cast<Const*>(e2))
        {
            return new Const(e1->eval(0)*e2->eval(0));
        }
        if(dynamic_cast<Const*>(e1)&&e1->eval(0)==1) return e2;
        if(dynamic_cast<Const*>(e2)&&e2->eval(0)==1) return e1;
        if(dynamic_cast<Const*>(e1)&&e1->eval(0)==0) return new Const(0);
        if(dynamic_cast<Const*>(e2)&&e2->eval(0)==0) return new Const(0);
        if(dynamic_cast<Negative*>(e1)&&dynamic_cast<Negative*>(e2)) return new Multiplication(e1,e2);
        return new Multiplication(e1,e2); 
    }
};
class Exp: public Expression
{
public:
    Exp()
    {
        args.resize(1);
        args[0]=new Var;
    }
    Exp(Expression* op)
    {
        args.resize(1);
        args[0]=op;
    }
    double eval(double x) override
    {
        return pow(std::numbers::e_v<double>,x);
    }
    Expression* derivate() override //Replace self-refference
    {
        return new Multiplication(this,args[0]->derivate());
    }
    void print() override
    {
        std::cout<<"exp(";
        args[0]->print();
        std::cout<<")";
    }
    Expression* simplify() override
    {
        Expression* e=args[0]->simplify();
        if(dynamic_cast<Const*>(e)) return new Const(pow(std::numbers::e_v<double>,e->eval(0)));
        return new Exp(e);
    }
};
class Division: public Expression
{
    public:
    Division(Expression* op1, Expression* op2)
    {
        args.resize(2);
        args[0]=op1;
        args[1]=op2;
    }
    double eval(double x) override
    {
        return args[0]->eval(x)/args[1]->eval(x);
    }
    Expression* derivate() override //refferals to old args needs to be replaced with copying
    {
        return new Division(new Subtraction(new Multiplication(args[0]->derivate(),args[1]),new Multiplication(args[0],args[1]->derivate())),new Multiplication(args[1],args[1]));
    }
    void print() override
    {
        std::cout<<'(';
        args[0]->print();
        std::cout<<'/';
        args[1]->print();
        std::cout<<')';
    }
    Expression* simplify() override
    {
        Expression* e1=args[0]->simplify();
        Expression* e2=args[1]->simplify();
        return new Division(e1,e2); 
    }
};
class NatLog:public Expression
{
    public:
    NatLog()
    {
        args.resize(1);
        args[0]=new Var;
    }
    NatLog(Expression* op)
    {
        args.resize(1);
        args[0]=op;
    }
    double eval(double x) override
    {
        return log(x)/log(std::numbers::e_v<double>);
    }
    Expression* derivate() override
    {
        return new Division(args[0]->derivate(),args[0]);
    }
    void print() override
    {
        std::cout<<"ln(";
        args[0]->print();
        std::cout<<")";
    }
    Expression* simplify() override
    {
        Expression* e = args[0]->simplify();
        return new NatLog(e);
    }
};
class Pow: public Expression
{
    public:
    Pow(Expression* op1, Expression* op2)
    {
        args.resize(2);
        args[0]=op1;
        args[1]=op2;
    }
    double eval(double x) override
    {
        return pow(args[0]->eval(x),args[1]->eval(x));
    }
    Expression* derivate() override //same as other places
    {
        return new Multiplication(new Exp(new Multiplication(new NatLog(args[0]),args[1])) , (new Multiplication(new NatLog(args[0]),args[1]))->derivate());
    }
    void print() override
    {
        std::cout<<"pow(";
        args[0]->print();
        std::cout<<',';
        args[1]->print();
        std::cout<<')';
    }
    Expression* simplify() override
    {
        Expression* e1=args[0]->simplify();
        Expression* e2=args[1]->simplify();
        return new Pow(e1,e2);
    }
};
class Cosine: public Expression
{
    public:
    Cosine()
    {
        args.resize(1);
        args[0]=new Var;
    }
    Cosine(Expression* op);
    double eval(double x) override;
    Expression* derivate() override;
    void print() override;
    Expression* simplify() override;
};
class Sine: public Expression
{
    public:
    Sine()
    {
        args.resize(1);
        args[0]=new Var;
    }
    Sine(Expression* op)
    {
        args.resize(1);
        args[0]=op;
    }
    double eval(double x) override
    {
        return sin(args[0]->eval(x));
    }
    Expression* derivate() override
    {
        return new Multiplication(new Cosine(args[0]),args[0]->derivate());
    }
    void print() override
    {
        std::cout<<"sin(";
        args[0]->print();
        std::cout<<')';
    }
    Expression* simplify() override;
};
Cosine::Cosine(Expression* op)
{
    args.resize(1);
    args[0]=op;
}
double Cosine::eval(double x)
{
    return cos(args[0]->eval(x));
}
Expression* Cosine::derivate()
{
    return new Multiplication(new Negative(new Sine(args[0])),args[0]->derivate());
}
void Cosine::print()
{
    std::cout<<"cos(";
    args[0]->print();
    std::cout<<')';
}
class Tangent: public Expression
{
    public:
    Tangent()
    {
        args.resize(1);
        args[0]=new Var;
    }
    Tangent(Expression* op)
    {
        args.resize(1);
        args[0]=op;
    }
    double eval(double x) override
    {
        return tan(args[0]->eval(x));
    }
    Expression* derivate() override
    {
        return new Division(args[0]->derivate(),new Pow(new Cosine(new Var),new Const(2)));
    }
    void print() override
    {
        std::cout<<"tg(";
        args[0]->print();
        std::cout<<')';
    }
    Expression* simplify() override;
};
class ArcSine: public Expression
{
    public:
    ArcSine()
    {
        args.resize(1);
        args[0]=new Var;
    }
    ArcSine(Expression* op)
    {
        args.resize(1);
        args[0]=op;
    }
    double eval(double x) override
    {
        return asin(args[0]->eval(x));
    }
    Expression* derivate() override
    {
        return new Division(args[0]->derivate(),new Pow(new Subtraction(new Const(1),new Pow(args[0],new Const(2))),new Const(0.5)));
    }
    void print() override
    {
        std::cout<<"arcsin(";
        args[0]->print();
        std::cout<<')';
    }
    Expression* simplify() override
    {
        Expression* e=args[0]->simplify();
        return new ArcSine(e);
    }
};
class ArcCosine:public Expression
{
    public:
    ArcCosine()
    {
        args.resize(1);
        args[0]=new Var;
    }
    ArcCosine(Expression* op)
    {
        args.resize(1);
        args[0]=op;
    }
    double eval(double x) override
    {
        return acos(args[0]->eval(x));
    }
    Expression* derivate() override
    {
        return new Negative(new Division(args[0]->derivate(),new Pow(new Subtraction(new Const(1),new Pow(args[0],new Const(2))),new Const(0.5))) );
    }
    void print() override
    {
        std::cout<<"arccos(";
        args[0]->print();
        std::cout<<')';
    }
    Expression* simplify() override
    {
        Expression* e=args[0]->simplify();
        return new ArcCosine(e);
    }
};
class ArcTangent:public Expression
{
    public:
    ArcTangent()
    {
        args.resize(1);
        args[0]=new Var;
    }
    ArcTangent(Expression* op)
    {
        args.resize(1);
        args[0]=op;
    }
    double eval(double x) override
    {
        return atan(args[0]->eval(x));
    }
    Expression* derivate() override
    {
        return new Division(args[0]->derivate(),new Addition(new Const(1),new Pow(args[0],new Const(2))));
    }
    void print() override
    {
        std::cout<<"arctg(";
        args[0]->print();
        std::cout<<')';
    }
    Expression* simplify() override
    {
        Expression* e= args[0]->simplify();
        return new ArcTangent(e);
    }
};
Expression* Sine::simplify()
{
    Expression* e=args[0]->simplify();
    if(dynamic_cast<ArcSine*>(e)) return e->args[0];
    return new Sine(e);
}
Expression* Cosine::simplify() 
{
    Expression* e=args[0]->simplify();
    if(dynamic_cast<Negative*>(e)) return e->args[0];
    if(dynamic_cast<ArcCosine*>(e)) return e->args[0];
    return new Cosine(e);
}
Expression* Tangent::simplify() 
{
    Expression* e=args[0]->simplify();
    if(dynamic_cast<ArcTangent*>(e)) return e->args[0];
    return new Tangent(e);
}
int main(int, char**){
    /*Expression* e=new Addition(new Var(),new Multiplication(new Var(),new Addition(new Var(),new Const(3))));
    e->print();
    std::cout<<'\n';
    e->derivate()->print();
    NatLog(new Const(2)).derivate()->print();*/
    /*Expression* e2= new Sine(new Pow(new Var,new Const(2)));
    e2->print();
    std::cout<<'\n';
    e2->derivate()->derivate()->derivate()->print();*/
    /*Expression* e3= new Negative(new Negative(new Negative(new Subtraction(new Var, new Const(0)))));
    e3->print();
    std::cout<<'\n';
    e3->simplify()->print();*/
    Expression* e4=new Exp(new Multiplication(new Multiplication(new Addition(new Var, new Const(5)),new Addition(new Var, new Const(7))),new Addition(new Var, new Const(4))));
    e4->print();
    std::cout<<'\n';
    e4->derivate()->derivate()->derivate()->print();
    std::cout<<'\n';
    e4->derivate()->derivate()->derivate()->simplify()->print();
}
