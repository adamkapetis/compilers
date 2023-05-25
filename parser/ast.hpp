#ifndef __AST_HPP__
#define __AST_HPP__

#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <string>

enum dtype { Type_int, Type_bool };


class AST {
  public: 
    virtual void printAST(std::ostream &out) const = 0;
};

inline std::ostream &operator<<(std::ostream &out, const AST &ast) {
  ast.printAST(out);
  return out;
}

class Expr : public AST {
 public:
  virtual int eval() const = 0;
};

class Stmt : public AST {

};

class If_then_else : public Stmt {
  public:
    If_then_else(Cond* con,Stmt * st1, Stmt* st2 =nullptr ): cond(con),stmt1(st1),stmt2(st2) {}
    void printAST(std::ostream &out) const override {
      out << "if:" << *cond <<" then " << *stmt1 ;
      if(stmt2!=nullptr) out << " else "<< *stmt2;
    } 
  private:
    Cond* cond;
    Stmt* stmt1;
    Stmt* stmt2;
};

class Block : public Stmt {
 public:
  Block() : stmt_list() {}
  void append(Stmt *s) { 
    stmt_list.push_back(s); 
  }
  void printAST(std::ostream &out) const override {
    out << "Block(";
    bool first = true;
    for (const auto &s : stmt_list) {
      if (!first) out << ", ";
      first = false;
      out << *s;
    }
    out << ")";
  }
 private:
  std::vector<Stmt *> stmt_list;
};

class Exprc : public AST {
  public: 
    Exprc(Expr* exp) { 
      exprc.push_back(exp) ;
    }
    void append(Expr* expr) {
      exprc.push_back(expr);
    }
    void printAST(std::ostream &out) const override {
      out << "parameters(";
    bool first = true;
    for (const auto &s : exprc) {
      if (!first) out << ", ";
      first = false;
      out << *s;
    }
    out << ")"; 
    }
  private:
    std::vector<Expr *> exprc;
};

class Func_call : public Stmt {
  public:
    Func_call(Id* id, Exprc* exp = nullptr) : Tid(id), exprc(exp){}
    void printAST(std::ostream &out) const override {
      out << *Tid << "(" << *exprc << ")"; 
    }
  private:
    Id* Tid;
    Exprc* exprc;
};

class L_value : public Expr{
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
    int eval() {
      return num;
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

class String_const : public AST{
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

class Cond : public AST{

};

class LogOp : public Cond {
  public: 
    LogOp(Cond* left = nullptr, char* o = "not" , Cond* right=nullptr): condl(left), op(o), condr(right){} 
    void printAST(std::ostream &out) const override {
      if(condl == nullptr){
        out << " not (" << *condr << ")";
      }
      else if (op == "or"){
        out << "(" << *condl << " or " << *condr << ")";
      }
      else { 
        out << "(" << *condl << " and " << *condr << ")";
      }
    }
  private:
    Cond* condl;
    char* op;
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

class Dim : public {
  public:
    Dim(Int_const* inte):range(inte->eval()){}
  private:
    int range;
};

class Dims : public {
  public:
    Dims(){}
    void append(Dim * dim){
      dims.push_back(dim);
    }
    void set_type(dtype *dt) {type=dt;}
  private:
    std::vector<Dim *> dims;
    dtype* type;
};

class Id_list : public{
  public:
    Id_list(){}
    void append(Id* id){
      Idlist.push_back(id);
    }
  private:
  std::vector<Id*> Idlist;
};

class Type : public{
  public: 
    Type(dtype* typ, Dims* dims)
};

#endif