#ifndef __AST_HPP__
#define __AST_HPP__

#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "lexer.hpp"
#include "symbol.hpp"

enum Dtype { Type_int, Type_char, Type_bool, Type_void };


class AST {
  public: 
    virtual void sem() {}
    virtual void printAST(std::ostream &out) const = 0;
};

inline std::ostream &operator<<(std::ostream &out, const AST &ast) {
  ast.printAST(out);
  return out;
}



class Stmt : public AST {
  public:
  //virtual void printAST(std::ostream &out) const = 0;
};

class Expr : public AST {
 public:
  //virtual void printAST(std::ostream &out) const = 0;
  //virtual int eval() const = 0;
  void check_type(Dtype t){
    sem();
    if(t!=exprtype) yyerror("type missmatch");
  }
  void set_type(Dtype t) {
    exprtype=t;
  }
  Dtype expr_type(){
    return exprtype;
  }
  private:
  Dtype exprtype;
};

class Id : public Expr {
  public: 
    Id(const char* c) : id(c){}
    void printAST(std::ostream &out) const override {
      out <<"Id: " << id ; 
    }
    const char * name(){
      return id;
    }
  private:
  const char* id;
};

class Cond : public AST {
  public:
    virtual void printAST(std::ostream &out) const = 0;
  void check_type(Dtype t){
    sem();
    if(t!=condtype) yyerror("type missmatch");
  }
  void set_type(Dtype t) {
    condtype=t;
  }
  Dtype cond_type(){
    return condtype;
  }
  private:
  Dtype condtype;
};

class If_then_else : public Stmt {
  public:
    If_then_else(Cond* con,Stmt * st1, Stmt* st2 =nullptr ): cond(con),stmt1(st1),stmt2(st2) {}
    void printAST(std::ostream &out) const override {
      out << "if: ->" << *cond <<"<- " <<" then => {\n" << *stmt1 <<"}\n" ;
      if(stmt2!=nullptr) out << " else => {\n"<< *stmt2 << "}\n";
    } 
  private:
    Cond* cond;
    Stmt* stmt1;
    Stmt* stmt2;
};

class While_stmt : public Stmt {
  public:
    While_stmt(Cond* con, Stmt* st):cond(con),stmt(st){}
    void printAST(std::ostream &out) const override {
      out << "while( " << *cond << " ) \n\r do {" << *stmt << "}\n";
    }
  private:
    Cond* cond;
    Stmt* stmt;
};

class Return_stmt: public Stmt {
  public: 
    Return_stmt(Expr * ex=nullptr):expr(ex){}
    void printAST(std::ostream &out) const override {
      if(expr != nullptr) out<< "return (" << *expr << ")";
      else out << " return nothing" ;
    }
  private:
    Expr* expr;
};

class Block : public Stmt {
 public:
  Block() : stmt_list() {}
  void append(Stmt *s) { 
    stmt_list.push_back(s); 
  }
  void printAST(std::ostream &out) const override {
    out << "Block{\n";
    bool first = true;
    for (const auto &s : stmt_list) {
      if (!first) out << ", ";
      first = false;
      out << *s;
    }
    out << "}Block\n";
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
      out <<"(" <<*s << ")";
    }
    out << ")"; 
    }
  private:
    std::vector<Expr *> exprc;
};

class Func_call : public Expr , public Stmt{
  public:
    Func_call(Id* id, Exprc* exp = nullptr) : Tid(id), exprc(exp){}
    void printAST(std::ostream &out) const override {
      out << *Tid << "(" << *exprc << ")"; 
    }
  private:
    Id* Tid;
    Exprc* exprc;
};


class String_const : public AST{
  public: 
    String_const(char* c) : str(c){}
    void printAST(std::ostream &out) const override {
      out << "[string: " << str <<"]"; 
    }
  private:
  char* str;
};

class L_value : public Expr {
  public:
    L_value(Id* i):id(i){}
    L_value(String_const* i):str(i){}
    void append_expr(Expr* ex){
      expr_list.push_back(ex);
    }
    void sem() override {
    }
    void printAST(std::ostream &out) const override {
      if(id==nullptr) out << *str;
      else out << " " << *id;
      for( const auto &s : expr_list){
        out<< "[ "<<*s<<" ]";
      }
    }
  private:
    Id* id;
    String_const * str;
    std::vector<Expr *> expr_list;
};
// class L_value : public Expr{
//   public :
//     L_value(L_value* val, Expr* ex):var(val), expr(ex) {}
//     void printAST(std::ostream &out) const override {
//       out << *var << "[" << *expr <<"]"; 
//     }
//   private:
//     L_value* var;
//     Expr* expr;

// };

class Int_const : public Expr {
  public: 
    Int_const(int n) : num(n){}
    void printAST(std::ostream &out) const override {
      out << "[int: " << num <<"]"; 
    }
    void sem() override {
      set_type(Type_int);
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
      out << "[char: " << var <<" ]"; 
    }
    void sem() override {
      set_type(Type_char);
    }
  private:
  char var;
};


class BinOp : public Expr {
  public:
    BinOp(Expr* e1, char o, Expr* e2=nullptr): exprl(e1), op(o), exprr(e2){}
    BinOp(Expr* e1, char* o, Expr* e2=nullptr): exprl(e1), op_s(o), exprr(e2){}
    void printAST(std::ostream &out) const override {
    if(op_s == nullptr) out << op;
    else out << op_s;
    out << "(" << *exprl ;
    if(exprr==nullptr) out << ")";
    else out << ", " << *exprr << ")";
    }
    void sem() override{
      exprl->check_type(Type_int);
      exprr->check_type(Type_int);
      set_type(Type_int);
    }
  private:
    Expr* exprl;
    Expr* exprr;
    char op;
    char* op_s=nullptr;
};

// class Cond : public AST{
//   public:
//     Cond(Expr * ex1,int op, Expr* ex2 = nullptr ): expr1(ex1),oper(op),expr2(ex2){}
//     void printAST(std::ostream &out) const override{
//       if(expr2==nullptr){
//         out << "not" << *expr1;
//       }
//       else {
//         out << *expr1 << "logop" << *expr2;
//       }
//     }
//   private: 
//   Expr* expr1;
//   int oper;
//   Expr* expr2;
// };



class LogOp : public Cond {
  public: 
    LogOp(Cond* left , char* o, Cond* right=nullptr): condl(left), op(o), condr(right){} 
    void printAST(std::ostream &out) const override {
      if(condl == nullptr){
        out << " not (" << *condr << ")";
      }
      else if (op == "or"){
        out << "(" << *condl << ") or (" << *condr << ")";
      }
      else { 
        out << "(" << *condl << ") and (" << *condr << ")";
      }
    }
    void sem() override{
      condl->sem();
      condl->check_type(Type_bool);
      if(condr!=nullptr){
        condr->sem();
        condr->check_type(Type_bool);
        }
      set_type(Type_bool);
    }
  private:
    Cond* condl;
    char* op;
    Cond* condr;
};

class ComOp : public Cond {
  public:
    ComOp(Expr* e1, char o, Expr* e2): exprl(e1), op(o),op_s(nullptr), exprr(e2){}
    ComOp(Expr* e1, char* o, Expr* e2): exprl(e1), op_s(o), exprr(e2){}
    void printAST(std::ostream &out) const override {
      if(op_s==nullptr) out << op << "(" << *exprl << ", " << *exprr << ")";
      else out << op_s << "(" << *exprl << ", " << *exprr << ")";
    }
    void sem() override{
      if(exprl->expr_type()!=Type_char&&exprl->expr_type()!=Type_int) yyerror("can't compare ");
      exprl->check_type(exprr->expr_type());
      set_type(Type_bool);
    }
  private:
    Expr* exprl;
    Expr* exprr;
    char* op_s;
    char op;
};

class Dim : public AST {
  public:
    Dim(int inte):range(inte){}
    void printAST(std::ostream &out) const override {
      out<< "[" << range << "]";
    }
  private:
    int range;
};

class Dims : public AST {
  public:
    Dims(){}
    void append(Dim * dim){
      dims.push_back(dim);
    }
    void set_type(Dtype dt) {type=dt;}
    void printAST(std::ostream &out) const override {
      for(const auto &s: dims ){
        out << *s;
      }
    }
  private:
    std::vector<Dim *> dims;
    Dtype type;
};

class Type : public AST{
  public: 
    Type(Dtype typ, Dims* dms = nullptr):dtyp(typ),dims(dms) {}
    void printAST(std::ostream &out) const override {
      if(dtyp==0) out << " int";
      else if(dtyp==1) out << " char";
      else if(dtyp==2) out << " bool";
      else out << " void";
      if(dims != nullptr) out << *dims ;
    }
    Dtype basic_type(){
      return dtyp;
    }

  private:
    Dtype dtyp;
    Dims* dims;
};

class Local_def: public AST{
  public:
  private:
};

class Id_list : public Local_def{
  public:
    Id_list(){}
    void append(Id* id){
      Idlist.push_back(id);
    }
    void id_type(Dtype t){
      for( const auto &s : Idlist){
        s->set_type(t);
      }
    }
    void printAST(std::ostream &out) const override{
      bool i=false;
      for(const auto &s: Idlist){
        if(i==true) out << ",";
        out << *s;
        i=true;
      }
    }
  private:
  std::vector<Id*> Idlist;
};

class Def_list : public Local_def{
  public:
    Def_list(){}
    void append(Local_def* ld){
      deflist.push_back(ld);
    }
    void printAST(std::ostream &out) const override {
      for(const auto &s : deflist){
        out << *s;
      }
    }
  private:
    std::vector<Local_def*> deflist; 
};

class Fpar_def : public Local_def {
  public: 
    Fpar_def(Id_list* list,Type* typ, bool re=false):ref(re), type(typ),idlist(list){}
    void printAST(std::ostream &out) const override{
      if(ref==true) out << "ref ";
      out << *idlist << " : " << *type;
    }
  private:
    Id_list* idlist;
    Type* type;
    bool ref;
};

class Fpar_list : public Local_def {
  public:
    Fpar_list(Fpar_def*fpar){par_list.push_back(fpar);}
    void append(Fpar_def* fd){
      par_list.push_back(fd);
    }
    void printAST(std::ostream &out) const override {
      for ( const auto &s : par_list){
        out << *s ;
      }
    }
  private:
    std::vector<Fpar_def*> par_list;
};


class Header : public Local_def {
  public:
    Header(Id *i,Type * typ, Fpar_list* par_l=nullptr):id(i),type(typ),par_list(par_l) {}
    void printAST(std::ostream &out) const override {
      out << "fun " << *id << "(" ;
      if(par_list==nullptr) out<<") :";
      else out <<  *par_list << ") :" ; 
      out<< *type;
    }
  private:
    Id* id;
    Type * type;
    Fpar_list* par_list;
};

class Func_def : public Local_def {
  public:
  private:
};

class Var_def : public Local_def {
  public:
    Var_def(Id_list* idl, Type* ty):id_list(idl), type(ty){
    }
    void printAST(std::ostream &out) const override {
      out << "var [" << *id_list << " - type:" << *type<< "]";
    }
    void sem(){
      id_list->id_type(type->basic_type());
    }
  private:
    Id_list * id_list;
    Type* type;
};

class Function : public Local_def {
  public: 
    Function(Header* head, Def_list* d_list, Block* bl): header(head), def_list(d_list), block(bl){}
    void printAST(std::ostream &out) const override {
      out << *header << std::endl << *def_list << std::endl << *block;
    }
    void sem() override{
      st.push_scope();
      for()

    }
  private:
    Header* header;
    Def_list* def_list;
    Block* block;

};

class Valuation : public Stmt {
  public: 
    Valuation(L_value * val, Expr* exp):expr(exp), var(val){}
    void printAST(std::ostream &out) const override {
      out << *var << " = " << *expr ;
    }
  private: 
    Expr* expr;
    L_value * var;
};
#endif