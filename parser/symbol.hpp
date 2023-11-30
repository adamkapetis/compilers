#ifndef __SYMBOL_HPP__
#define __SYMBOL_HPP__
//#include "ast.hpp"
#include <map>
#include <vector>
//#include "lexer.hpp"

struct StrCompare : public std::binary_function<const char*, const char*, bool> {
public:
    bool operator() (const char* str1, const char* str2) const
    { return strcmp(str1, str2) < 0; }
};

extern void yyerror(const char *msg);

struct VAREntry{
  Type* type;
  VAREntry(){}
  VAREntry(Type* t) : type(t){}
};

struct FUNEntry{
  Dtype type;
  //int args=0;
  std::vector<VAREntry *> arg;
  FUNEntry(){}
  FUNEntry(Dtype t) :type(t) {}
};

struct STEntry {
  VAREntry* var ;
  FUNEntry* fun ;
  STEntry() {}
  STEntry(FUNEntry *fu) : fun(fu), var(nullptr) {}
  STEntry(VAREntry *va) : var(va), fun(nullptr) {}
};

class Scope {
 public:
  Scope() {}
  STEntry *lookup(const char* c) {
    if (locals.find(c) == locals.end()) return nullptr;
    return &(locals[c]);
  }
  void insert(const char* c, Type* t) {
    if (locals.find(c) != locals.end()){
      //printf("problem with %s\n",c);
      yyerror("Duplicate variable declaration");}
    locals[c] = STEntry(new VAREntry(t));
    std::cout<< *t;
    printf("inserted VAREntry %s\n",c);
    if(func!=nullptr) {
      const char * tmp = (const char *)func;
      printf("trying insert %s on funetry %s vector\n",c,tmp);
      if (locals.find(tmp) == locals.end()){
      printf("cant find funtion\n");
      }
      //if(locals[tmp].fun==nullptr)printf("cant find function\n");
      //locals[func].fun->arg.push_back(new VAREntry(t));
      //printf("inserted %s on funetry vector\n",func);
    }
  }
  void funcend(){
    free(func);
    func=nullptr;
  }
  void insertf(const char* c, Dtype t) {
    if (locals.count(c)!=(unsigned long)0){
      printf("problem with %s and map size is %d, bsort exists %d times\n ",c,locals.size(),locals.count(c));
      yyerror("Duplicate variable declaration");}
    locals[c] = STEntry(new FUNEntry(t));
    func = new char[strlen(c)+1];
    strncpy(func,c,strlen(c)+1);
    //func +='\0';
    printf("inserted STEntry %s\n",c);
  }
  int size(){
    return locals.size();
  }
  int setfargs(int i){
    for(auto it=locals.cbegin(); it!=locals.cend();++it)
    printf("2nd entry name: %s\n", (it->first));
    //locals.begin()->second.fun->args=i; // prothetoume sthn synarthsh ton aritmo ton arguement
  }
 private:
  std::map<const char *, STEntry,StrCompare> locals;
  char * func =nullptr;

};

class SymbolTable {
 public:
  STEntry *lookup(const char* c) {
    for (auto s = scopes.rbegin(); s != scopes.rend(); ++s) {
      STEntry *e = s->lookup(c);
      if (e != nullptr) return e;
    }
    yyerror("Variable not found");
    return nullptr;
  }
  void insert(const char* c, Type* t) {
    scopes.back().insert(c, t);
  }
  void insertf(const char* c, Dtype t) {
    //printf("inserting into map %s\n",c);
    scopes.back().insertf(c, t);
  }
  void push_scope() {
    scopes.push_back(Scope());
    //printf("scopes in st %d \n",scopes.size());
  }
  void pop_scope() {
    scopes.pop_back();
  }
  bool check_empty(){
    return scopes.empty();
  }
  int scope_size(){
    return scopes.back().size();
  }
  void f_args(int i){
    scopes.back().setfargs(i);
  }
  void stopfunc(){
    scopes.back().funcend();
  }
 private:
  std::vector<Scope> scopes;
};

extern SymbolTable st;

#endif