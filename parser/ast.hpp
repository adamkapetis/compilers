#ifndef __AST_HPP__
#define __AST_HPP__

#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <string>

enum dtype { Type_int, Type_bool, Type_void };


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
class Valuation : public Stmt {
  public: 
    Valuation(L_value* val, Expr* exp):expr(exp), var(val){}
  private: 
    Expr* expr;
    L_value* var;
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

class Dim : public AST {
  public:
    Dim(Int_const* inte):range(inte->eval()){}
  private:
    int range;
};

class Dims : public AST {
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

class Id_list : public Local_def{
  public:
    Id_list(){}
    void append(Id* id){
      Idlist.push_back(id);
    }
  private:
  std::vector<Id*> Idlist;
};

class Type : public Local_def{
  public: 
    Type(dtype* typ, Dims* dims = nullptr):dtyp(typ),Dims(dims) {}
  private:
    dtype* dtyp;
    Dims* Dims;
};

class Local_def: public AST{
  public:
  private:
};

class Def_list : public Local_def{
  public:
    Def_list(){}
  private:
    std::vector<Local_def*> deflist; 
};

class Local_def : public AST {

};

class Header : public Local_def {
  public:
    Header(Id *i, Fpar_list* par_l,dtype * typ):id(i),type(typ),par_list(par_l) {}
  private:
    Id* id;
    dtype* type;
    Fpar_list* par_list;
};

class Func_def : public Local_def {
  public:
  private:
};

class Var_def : public Local_def {
  public:
  private:
};

class Fpar_def : public Local_def {
  public: 
    Fpar_def(Id_list* list,Type* typ, bool re=false):ref(re), type(typ){}
  private:
    Type* type;
    bool ref;
};

class Fpar_list : public Local_def {
  public:
    Fpar_list(){}
  private:
    std::vector<Fpar_def*> par_list;
};

class Function : public AST {
  public: 
    Function(Header* head, Def_list* d_list, Block* bl): header(head), def_list(d_list), block(bl){}
  private:
    Header* header;
    Def_list* def_list;
    Block* block;

};


#endif