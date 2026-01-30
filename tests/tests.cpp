#include "MathAnalytical.hpp"
#include <cassert>
#include <string.h>
#include <memory>
typedef std::unique_ptr<Expression> Expr;
int main(int argc, char** argv){
    if(argc!=2) return 1;
    if(strcmp(argv[1],"Addition")==0){
        Expr e(new Addition(new Var,new Const(3)));
        assert(e->eval(4)==7);
        Expr e2(e->copy());
        e.reset();
        assert(e2->eval(5)==8);
    }else if(strcmp(argv[1],"ArcCosine")==0){
        Expr e(new ArcCosine);
        assert(e->eval(1)==acos(1));
        Expr e2(e->copy());
        e.reset();
        assert(e2->eval(1)==acos(1));
    }else if(strcmp(argv[1],"ArcSine")==0){
        Expr e(new ArcSine);
        assert(e->eval(1)==asin(1));
        Expr e2(e->copy());
        e.reset();
        assert(e2->eval(1)==asin(1));
    }else if(strcmp(argv[1],"ArcTangent")==0){
        Expr e(new ArcTangent);
        assert(e->eval(1)==atan(1));
        Expr e2(e->copy());
        e.reset();
        assert(e2->eval(1)==atan(1));
    }else if(strcmp(argv[1],"Const")==0){
        Expr e(new Const(3));
        assert(e->eval(1)==3);
        Expr e2(e->copy());
        assert(e2->eval(2)==3);
    }else if(strcmp(argv[1],"Cosine")==0){
        Expr e(new Cosine);
        assert(e->eval(1)==cos(1));
        Expr e2(e->copy());
        e.reset();
        assert(e2->eval(1)==cos(1));
    }else if(strcmp(argv[1],"Division")==0){
        Expr e(new Division(new Var,new Const(3)));
        assert(e->eval(6)==2);
        Expr e2(e->copy());
        e.reset();
        assert(e2->eval(9)==3);
    }else if(strcmp(argv[1],"Exp")==0){
        Expr e(new Exp);
        assert(e->eval(1)==exp(1));
        Expr e2(e->copy());
        e.reset();
        assert(e2->eval(1)==exp(1));
    }else if(strcmp(argv[1],"Multiplication")==0){
        Expr e(new Multiplication(new Var,new Const(3)));
        assert(e->eval(4)==12);
        Expr e2(e->copy());
        e.reset();
        assert(e2->eval(5)==15);
    }else if(strcmp(argv[1],"NatLog")==0){
        Expr e(new NatLog);
        assert(e->eval(1)==log(1));
        Expr e2(e->copy());
        e.reset();
        assert(e2->eval(1)==log(1));
    }else if(strcmp(argv[1],"Negative")==0){
        Expr e(new Negative);
        assert(e->eval(4)==-4);
        Expr e2(e->copy());
        e.reset();
        assert(e2->eval(5)==-5);
    }else if(strcmp(argv[1],"Pow")==0){
        Expr e(new Pow(new Var,new Const(3)));
        assert(e->eval(4)==64);
        Expr e2(e->copy());
        e.reset();
        assert(e2->eval(5)==125);
    }else if(strcmp(argv[1],"Sine")==0){
        Expr e(new Sine);
        assert(e->eval(1)==sin(1));
        Expr e2(e->copy());
        e.reset();
        assert(e2->eval(1)==sin(1));
    }else if(strcmp(argv[1],"Subtraction")==0){
        Expr e(new Subtraction(new Var,new Const(3)));
        assert(e->eval(4)==1);
        Expr e2(e->copy());
        e.reset();
        assert(e2->eval(5)==2);
    }else if(strcmp(argv[1],"Tangent")==0){
        Expr e(new Tangent);
        assert(e->eval(1)==tan(1));
        Expr e2(e->copy());
        e.reset();
        assert(e2->eval(1)==tan(1));
    }else if(strcmp(argv[1],"Var")==0){
        Expr e(new Var);
        assert(e->eval(1)==1);
        Expr e2(e->copy());
        e.reset();
        assert(e2->eval(5)==5);
    }else return -100;
}