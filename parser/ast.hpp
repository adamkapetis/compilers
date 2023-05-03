#ifndef __AST_HPP__
#define __AST_HPP__

#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <string>

enum logics { not , or ,  and};

class AST {

};

class Expr : public AST {
 public:
  virtual int eval() const = 0;
};

class L_value : public {
  public :
    L_value(L_value* val, Expr* ex):var(val), expr(ex) {}
    void printAST(std::ostream &out) const override {
      out << *var << "[" << *expr <<"]"; 
    }
  private:
    L_value* var;
    Expr* expr;

};

class Int_const : public Expr {
  public: 
    Int_const(int n) : num(n){}
    void printAST(std::ostream &out) const override {
      out << "integer (" << num <<")"; 
    }
  private:
  int num;
};

class Char_const : public Expr {
  public: 
    Char_const(char c) : var(c){}
    void printAST(std::ostream &out) const override {
      out << "char (" << var <<")"; 
    }
  private:
  char var;
};

class String_const : public {
  public: 
    String_const(char* c) : str(c){}
    void printAST(std::ostream &out) const override {
      out << "string (" << str <<")"; 
    }
  private:
  char* str;
};

class Id : public Expr {
  public: 
    Id(char* c) : id(c){}
    void printAST(std::ostream &out) const override {
      out << "identifier (" << id <<")"; 
    }
  private:
  char* id;
};

class BinOp : public Expr {
  public:
    BinOp(Expr* e1, char o, Expr* e2): exprl(e1), op(o), exprr(e2){}
    void printAST(std::ostream &out) const override {
    out << op << "(" << *exprl << ", " << *exprr << ")";
    }
  private:
    Expr* exprl;
    Expr* exprr;
    char op;
};

class Cond {

};

class LogOp : public Cond {
  public: 
    LogOp(Cond* left = nullptr, logics o = 1 , Cond* right=nullptr): condl(left), op(o), condr(right){} 
    void printAST(std::ostream &out) const override {
      if(condl == nullptr){
        out << " not (" << *condr << ")";
      }
      else if (op == 1){
        out << "(" << *condl << " or " << *condr << ")";
      }
      else { 
        out << "(" << *condl << " and " << *condr << ")";
      }
    }
  private:
    Cond* condl;
    logics op;
    Cond* condr;
};

class ComOp : public Cond {
  public:
    ComOp(Expr* e1, char* o, Expr* e2): exprl(e1), op(o), exprr(e2){}
    void printAST(std::ostream &out) const override {
    out << op << "(" << *exprl << ", " << *exprr << ")";
    }
  private:
    Expr* exprl;
    Expr* exprr;
    char* op;
};

#endif