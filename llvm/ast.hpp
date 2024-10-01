#ifndef __AST_HPP__
#define __AST_HPP__

#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <string.h>
#include "lexer.hpp"


#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/Attributes.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Utils.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/Host.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/GlobalVariable.h>

//using namespace llvm;

enum Dtype { Type_int, Type_char, Type_bool, Type_void };

class AST {
  public: 
    virtual void sem() {}
    virtual void printAST(std::ostream &out) const = 0;
    virtual llvm::Value *compile() { return nullptr; }

    llvm::Function *init_compile(llvm::Value* main_function)
    {   

        llvm::FunctionType *funcType = llvm::FunctionType::get(i64, {}, false); // false indicates the function does not take variadic arguments.
        llvm::Function *main = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", TheModule.get());

        llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", main);
        Builder.SetInsertPoint(BB);

        Builder.CreateCall(llvm::dyn_cast<llvm::Function>(main_function));
        Builder.CreateRet(c64(0));

        return main;
    }
    llvm::Value* LogErrorV(const char *Str) const{
      fprintf(stderr, "Error: %s\n", Str);
      return nullptr;
      }
      llvm::Type* getLLVMType(Dtype type, llvm::LLVMContext& context, int size) {
          switch (type) {
              case Type_int:
                  printf("THe size of the array is %d\n",size);
                  if (size > 1) {
                    
                    return llvm::ArrayType::get(llvm::Type::getInt64Ty(context), size);
                  }
                  else
                    return llvm::Type::getInt64Ty(context);  
              case Type_char:
                if (size > 1) {
                    return llvm::ArrayType::get(llvm::Type::getInt8Ty(context), size);
                  }
                  else
                    return llvm::Type::getInt8Ty(context);   
              case Type_bool:
                  return llvm::Type::getInt1Ty(context);  
              case Type_void:
                  return llvm::Type::getVoidTy(context);   
              default:
                  return nullptr;  //maybe put reference or arrays
          }
      }     

    void llvm_compile_and_dump(bool optimize=true) {
      // Initialize
      TheModule = std::make_unique<llvm::Module>("grace program", TheContext);
      // Function Pass Manager (for optimizing)
      TheFPM = std::make_unique<llvm::legacy::FunctionPassManager>(TheModule.get());
      if(optimize) {
        TheFPM->add(llvm::createPromoteMemoryToRegisterPass());
        TheFPM->add(llvm::createInstructionCombiningPass());
        TheFPM->add(llvm::createReassociatePass());
        TheFPM->add(llvm::createGVNPass());
        TheFPM->add(llvm::createCFGSimplificationPass());
      }
      TheFPM->doInitialization();

      // Initialize types
      i8 = llvm::IntegerType::get(TheContext, 8);
      i32 = llvm::IntegerType::get(TheContext, 32);
      i64 = llvm::IntegerType::get(TheContext, 64);

      // Initialize library functions
      llvm::FunctionType *writeInteger_type =llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), {i64}, false);
      TheWriteInteger = llvm::Function::Create(writeInteger_type, llvm::Function::ExternalLinkage, "writeInteger", TheModule.get());

      llvm::FunctionType *writeString_type = llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), {llvm::PointerType::get(i8, 0)}, false);
      TheWriteString = llvm::Function::Create(writeString_type, llvm::Function::ExternalLinkage, "writeString", TheModule.get());

      llvm::FunctionType *writeChar_type =llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), {i8}, false);
      TheWriteChar = llvm::Function::Create(writeChar_type, llvm::Function::ExternalLinkage, "writeChar", TheModule.get());

      llvm::FunctionType *readInteger_type =llvm::FunctionType::get(llvm::Type::getInt32Ty(TheContext), {}, false);
      TheReadInteger = llvm::Function::Create(readInteger_type, llvm::Function::ExternalLinkage, "readInteger", TheModule.get());

      llvm::FunctionType *readChar_type =llvm::FunctionType::get(llvm::Type::getInt8Ty(TheContext), {}, false);
      TheReadChar = llvm::Function::Create(readChar_type, llvm::Function::ExternalLinkage, "readChar", TheModule.get());

      llvm::FunctionType *readString_type =llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), {i64, llvm::PointerType::get(i8, 0)}, false);
      TheReadString = llvm::Function::Create(readString_type, llvm::Function::ExternalLinkage, "readString", TheModule.get());

      llvm::FunctionType *ascii_type =llvm::FunctionType::get(llvm::Type::getInt32Ty(TheContext), {i8}, false);
      TheAscii = llvm::Function::Create(ascii_type, llvm::Function::ExternalLinkage, "ascii", TheModule.get());

      llvm::FunctionType *chr_type =llvm::FunctionType::get(llvm::Type::getInt8Ty(TheContext), {i64}, false);
      TheChr = llvm::Function::Create(chr_type, llvm::Function::ExternalLinkage, "chr", TheModule.get());

      llvm::FunctionType *strlen_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(TheContext), {llvm::PointerType::get(i8, 0)}, false);
      TheStrlen = llvm::Function::Create(strlen_type, llvm::Function::ExternalLinkage, "strlen", TheModule.get());

      llvm::FunctionType *strcmp_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(TheContext), {llvm::PointerType::get(i8, 0), llvm::PointerType::get(i8, 0)}, false);
      TheStrcmp = llvm::Function::Create(strcmp_type, llvm::Function::ExternalLinkage, "strcmp", TheModule.get());

      llvm::FunctionType *strcpy_type = llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), {llvm::PointerType::get(i8, 0), llvm::PointerType::get(i8, 0)}, false);
      TheStrcpy = llvm::Function::Create(strcpy_type, llvm::Function::ExternalLinkage, "strcpy", TheModule.get());

      llvm::FunctionType *strcat_type = llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), {llvm::PointerType::get(i8, 0), llvm::PointerType::get(i8, 0)}, false);
      TheStrcat = llvm::Function::Create(strcat_type, llvm::Function::ExternalLinkage, "strcat", TheModule.get());

      llvm::Value *main_function = compile();
      llvm::Function *main = init_compile(main_function);

      // Emit the program code
      // llvm::Value *main_function = compile(); //grafei ola ton kodika tou programmatos  

      // Define and start the main function
      // llvm::FunctionType *funcType = llvm::FunctionType::get(i64, {}, false); 
      // llvm::Function *main = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", TheModule.get());
      
      // llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", main);
      // Builder.SetInsertPoint(BB);

      //Builder.CreateCall(llvm::dyn_cast<llvm::Function>(main_function));
      

      // llvm::Value *main_function = compile();
      // compile();

      // Builder.CreateRet(c64(0));
      // Verify the IR.
      bool bad = verifyModule(*TheModule, &llvm::errs());
      if (bad)
      {
          std::cerr << "The IR is bad!" << std::endl;
          TheModule->print(llvm::errs(), nullptr);
          std::exit(1);
      }

      // Optimizer
      //TheFPM->run(*main);

      // Print out the IR.
      TheModule->print(llvm::outs(), nullptr);
      


      }
    static std::unique_ptr<llvm::Module> TheModule;

  protected:
    static llvm::LLVMContext TheContext;
    static llvm::IRBuilder<> Builder;
    static std::unique_ptr<llvm::legacy::FunctionPassManager> TheFPM;

    static std::map<std::string, llvm::Value*> NamedValues;
    static std::map<llvm::Value *, llvm::Type *> PointerTypes;
    static std::map<std::string, std::pair<llvm::Function *, std::vector<char>>> NamedFunctions;
    static std::map<std::string, std::pair<llvm::Value *, std::pair<llvm::Type *, llvm::Type *>>> FunctionArguments;
    static std::vector<std::string> FunctionArgumentStack;
    static std::vector<llvm::Function *> FunctionStack;
    static std::vector<llvm::Function *> LocalFunctions;
    static std::vector<llvm::Value *> LocalDefs;

    static unsigned naming_idx;

    static llvm::Function *TheWriteInteger;
    static llvm::Function *TheWriteString;
    static llvm::Function *TheWriteChar;
    static llvm::Function *TheReadInteger;
    static llvm::Function *TheReadChar;
    static llvm::Function *TheReadString;
    static llvm::Function *TheAscii;
    static llvm::Function *TheChr;
    static llvm::Function *TheStrlen;
    static llvm::Function *TheStrcmp;
    static llvm::Function *TheStrcpy;
    static llvm::Function *TheStrcat;

    static llvm::Type *i8;
    static llvm::Type *i32;
    static llvm::Type *i64;

    static llvm::ConstantInt* c8(char c) {
      return llvm::ConstantInt::get(TheContext, llvm::APInt(8, c, true));
    }
    static llvm::ConstantInt* c32(int n) {
      return llvm::ConstantInt::get(TheContext, llvm::APInt(32, n, true));
    }
    static llvm::ConstantInt* c64(long n) {
      return llvm::ConstantInt::get(TheContext, llvm::APInt(64, n, true));
    }

    // static llvm::Type* parse_type(Type t, std::vector<int> dim_sizes=std::vector<int>(), bool ref=false) {
    //   llvm::ArrayType * at;

    //   if (!dim_sizes.empty()) {
    //     for(auto it = dim_sizes.rbegin(); it != dim_sizes.rend(); ++it) {
    //       if (*it == 0) *it = 64;

    //       if(it == dim_sizes.rbegin()) {
    //         if (t == 2)
    //           at = llvm::ArrayType::get(i32, *it);
    //         else
    //           at = llvm::ArrayType::get(i8, *it);
    //       }
    //       else
    //         at = llvm::ArrayType::get(at, *it);
    //     }
    //   }


    //   switch(t) {
    //     case 0: return ref ? llvm::PointerType::get(i32, 0) : i32;
    //     case 1: return ref ? llvm::PointerType::get(i8, 0) : i8;
    //     case 2: if(ref) return llvm::PointerType::get(i32, 0); else return at;  /////!array
    //     case 3: if(ref) return llvm::PointerType::get(i8, 0); else return at;  /////!array
    //     case 5: return llvm::Type::getVoidTy(TheContext);
    //     default: return nullptr;
    //   }
    // }

    static llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction, const llvm::StringRef &VarName, llvm::Type *VarType) {
      llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
      return TmpB.CreateAlloca(VarType, nullptr, VarName);
    }

    static auto *GetVal(llvm::Value * loadedValue) {
      llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
      llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, "ldtmp", loadedValue->getType());
      Builder.CreateStore(loadedValue, Alloca);
      return Alloca;
    }
};





inline std::ostream &operator<<(std::ostream &out, const AST &ast) {
  ast.printAST(out);
  return out;
}



class Stmt : public AST {
  
  public:
  Stmt(){}
  // virtual void printAST(std::ostream &out) const = 0;
  // virtual void sem() const =0;
};


// class Dim : public AST {
//   public:
//     Dim(int inte):range(inte){}
//     void printAST(std::ostream &out) const override {
//       out<< "[" << range << "]";
//     }
//   private:
//     int range;
// };

class Dims : public AST { //eisagontai anapoda ta dims opote prepei na ta diabazoume anapoda
  public:
    Dims(){}
    void append(int dim){
      dims.push_back(dim);
    }
    void printAST(std::ostream &out) const override {
      for(auto s: dims ){
        out << "[" << s << "]";
      }
    }
    bool operator != (Dims & d){
      bool t=true;
      if(dims.size()==d.length()) t=false;
      return t;
    }
    int length(){
      return dims.size();
    }
    int dimI(int i){
      return dims[i];
    }
    bool empty(){
      return dims.empty();
    }
  private:
    std::vector<int> dims;
};

class Type : public AST{
  public: 
    Type(Dtype typ, Dims* dms ):dtyp(typ),dims(dms) {}
    void printAST(std::ostream &out) const override {
      if(dtyp==0) out << " int";
      else if(dtyp==1) out << " char";
      else if(dtyp==2) out << " bool";
      else out << " void";
      if(dims != nullptr) out << *dims ;
    }
    int array_dim(int dimnum) {
      return dims->dimI(dimnum);
    }
    Dtype basic_type(){
      return dtyp;
    }
    bool operator == (Type  t){
      printf("comparing 2 types\n");
      bool f=false;
      if(dtyp==t.dtyp){
        f=true;}

      if(dims->empty()){
        std::cout<< "first arguements dims empty\n";
        if(!t.dims->empty()) {
          std::cout<< "type: " <<*this <<" not equal to type: " << t <<std::endl;
          yyerror("");
        }
      }
      else if(!dims->empty()){
        std::cout<< "first arguements dims not empty\n";
        if(t.dims->empty()) {
          std::cout<< "type: " <<*this <<" not equal to type: " << t <<std::endl;
          yyerror("");
        }
        if(*dims != *(t.dims))f=false;
      }
        
      return f;
    }
    int dimensions (){
      return dims->length();
    }
    virtual llvm::Type* get_llvm_type(llvm::LLVMContext& context,int dim){
      if(dim>1){
        return llvm::ArrayType::get(get_llvm_type(context,dim-1), array_dim(dim-1));
      }
      if(dim==1){
        switch (dtyp) {
          case Type_int:
                return llvm::ArrayType::get(llvm::Type::getInt64Ty(context),array_dim(dim-1));
          case Type_char:
                return llvm::ArrayType::get(llvm::Type::getInt8Ty(context), array_dim(dim-1)); 
          default:
              return nullptr;  //maybe put reference or arrays
        }
      }
      else{
        switch (dtyp) {
          case Type_int:
                return llvm::Type::getInt64Ty(context);  
          case Type_char:
                return llvm::Type::getInt8Ty(context);   
          case Type_bool:
              return llvm::Type::getInt1Ty(context);  
          case Type_void:
              return llvm::Type::getVoidTy(context);   
          default:
              return nullptr;  //maybe put reference or arrays
        }
      }
    }
  private:
    Dtype dtyp;
    Dims* dims;
};


#include "symbol.hpp"

class Expr : public AST {
 public:
  //virtual void printAST(std::ostream &out) const = 0;
  //virtual int eval() const = 0;
  void check_type(Dtype t){
    if(t!=exprtype->basic_type()) yyerror("type missmatch");
  }
  void set_type(Dtype t) {
    exprtype= new Type(t,new Dims());
  }
  void set_typedims(Type* t){
    exprtype= t;
  }
  Dtype expr_btype(){
    return exprtype->basic_type();
  }
  Type* expr_type(){
    return exprtype;
  }
  private:
  Type* exprtype;
  //Dtype exprtype;
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
    void sem() override {
      //char *b;
      //strcpy(b,id);
      //printf("inserting id %s\n", id);
      st.insert(id ,expr_type());
    }
    void fsem() {
      //char *b;
      //strcpy(b,id);
      //printf("inserting function %s\n", id);
      st.insertf(id ,expr_btype()); // eisagoume mono onoma kai afou eisaxthoun oi metablhtes prosthetoume poses einai
    }

    virtual llvm::Value* compile() override {
      // psaxno gia tin metabliti
      std::string name = std::string(id);
      llvm::Value* LValAddr = NamedValues[name]; //maybe search in stack frame
      if (!LValAddr) {
        std::string msg = "Unknown variable name: " + std::string(id) + ".";
        return LogErrorV(msg.c_str());
      }
      Dtype varType = expr_btype();
      llvm::Type* llvmVarType = getLLVMType(varType, TheContext,0);  
      // maybe ad for reference
      return Builder.CreateLoad(llvmVarType, LValAddr);

    }
    llvm::Value* compile_ptr()  {
      std::string name = std::string(id);
      llvm::Value* LValAddr = NamedValues[name]; //maybe search in stack frame
      if (!LValAddr) {
        std::string msg = "Unknown variable name: " + std::string(id) + ".";
        return LogErrorV(msg.c_str());
      }
      return LValAddr;
    }

  private:
  const char* id;
};

class Cond : public AST {
  public:
    virtual void printAST(std::ostream &out) const = 0;
  void check_type(Dtype t){
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

class End :public Stmt{
  public:
  End(){
  }
  void printAST(std::ostream &out) const override {
  }
  void sem() override {

  }
};

class If_then_else : public Stmt {
  public:
    If_then_else(Cond* con,Stmt * st1, Stmt* st2 =nullptr ): cond(con),stmt1(st1),stmt2(st2) {}
    void printAST(std::ostream &out) const override {
      out << "if: ->" << *cond <<"<- " <<" then => {\n" << *stmt1 <<"}\n" ;
      if(stmt2!=nullptr) out << " else => {\n"<< *stmt2 << "}\n";
    } 
    void sem() override {
      cond->sem();
      stmt1->sem();
      if(stmt2!=nullptr)stmt2->sem();
    }
    virtual llvm::Value* compile() override {

      llvm::Value *v = cond->compile();

      llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();

      llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(TheContext, "then", TheFunction);
      llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(TheContext, "else", TheFunction);
      llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(TheContext, "endif", TheFunction);

      Builder.CreateCondBr(v, ThenBB, ElseBB);

      Builder.SetInsertPoint(ThenBB);
      if (stmt1 != nullptr)
          stmt1->compile();

      if (!Builder.GetInsertBlock()->getTerminator())
          Builder.CreateBr(AfterBB); 

      Builder.SetInsertPoint(ElseBB);
      if (stmt2 != nullptr)
          stmt2->compile();

      if (!Builder.GetInsertBlock()->getTerminator())
          Builder.CreateBr(AfterBB);
      Builder.SetInsertPoint(AfterBB);

      return nullptr;
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
    void sem() override {
      printf("while cond sem\n");
      cond->sem();
      printf("while stmt sem\n");
      stmt->sem();
    }
    virtual llvm::Value* compile() override{

      llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();

      llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(TheContext, "while_loop", TheFunction);
      llvm::BasicBlock *BodyBB = llvm::BasicBlock::Create(TheContext, "while_body", TheFunction);
      llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(TheContext, "endwhile", TheFunction);

      Builder.CreateBr(LoopBB);

      Builder.SetInsertPoint(LoopBB);

      llvm::Value *CondV = cond->compile();

      Builder.CreateCondBr(CondV, BodyBB, AfterBB);
      Builder.SetInsertPoint(BodyBB);

      stmt->compile();

      // Maybe skip this if(not necessary)
      if (!Builder.GetInsertBlock()->getTerminator())
          Builder.CreateBr(LoopBB);

      Builder.SetInsertPoint(AfterBB);

      return nullptr;
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
    void sem() override{
      expr->sem();
    }
    virtual llvm::Value *compile() override{
      if (expr != nullptr)
          Builder.CreateRet(expr->compile());
      else
          Builder.CreateRetVoid();

      return nullptr;
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
  void sem() override{
    std::cout<<"analyzing block " << *this <<std::endl;
    for(const auto &s : stmt_list){
      s->sem();
    }
  }
  virtual llvm::Value* compile() override {

    for(Stmt *s: stmt_list) { //maybe reverse list (not needed)
      // if(s == nullptr) continue;

      s->compile();

      // if (dynamic_cast<Return *> (s)) //maybe not needed
      //       break;
    }
    return nullptr;
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
    std::vector <Type *> argtypes() {
      std::vector< Type *> t;
      for(const auto &s: exprc){
        s->sem();
        t.push_back(s->expr_type());
      }
      return t;
    }
    std::vector<Expr *> getExpr() {
      return exprc;
    }
  private:
    std::vector<Expr *> exprc;
};

class Func_call : public Expr , public Stmt{
  public:
    Func_call(Id* id, Exprc* exp = nullptr) : Tid(id), exprc(exp){}
    void printAST(std::ostream &out) const override {
      out << *Tid << "(" ;
      if(exprc!=nullptr) out << *exprc ;
      out << ")"; 
    }
    void sem() override{
      const char *c = Tid->name();
      std::vector<Type *> t ;
      if(exprc!=nullptr)t= exprc->argtypes();
      printf("read expression types vector\n");
      STEntry* func = st.lookup(c);
      if(func==nullptr)printf("cant find function %s to call\n",c );
      else {
        if(func->fun==nullptr){
          std::cout << c;//tha eprepe na einai yyerror, prosthiki format sthn yyerror
          yyerror("invalid function\n");
        }
        printf("found the function %s on st\n",c);
        Type* typeit=*func->fun->arg.rbegin();
        std::cout << *typeit <<std::endl;
        auto exprs = t.rbegin();
        auto expre = t.rend();
        printf("starting to compare types of function %s arguements\n",c);
        if(func->fun->arg.rbegin()==func->fun->arg.rend()) printf("empty type vector on funciton\n");
        for(auto s = (func->fun->arg.rbegin()); s!=func->fun->arg.rend(); ++s){
          if(*exprs == *expre) {
            yyerror(" wrong arguements ");
          }
          if((**s)==(**exprs)) std::cout<< "correct arguement " << **s << " = " << **exprs << std::endl;
          else {
            std::cout<< "wrong arguement " << **s << " != " << **exprs << std::endl;
            yyerror("wrong arguements");
          }
          exprs++;

        // }
        }
      //lookup sto st gia to Tid->name();
      }
      printf(" valid function call\n");
    }

    virtual llvm::Value * compile() override {
      std::string name = std::string(Tid->name());
      llvm::Function *Fcall = TheModule->getFunction(name);
      if (!Fcall) {
          std::string msg = "Function call for unknown fucntion: " + name;
          return Expr::LogErrorV(msg.c_str());
      }
      std::vector<Expr *> Args = (exprc) ? exprc->getExpr() : std::vector<Expr *>{};
      std::vector<llvm::Value *> ArgsV;

      // isos baloume kati gia stack gia na to sindesoume
      // if (!isTopLevel(mangled_name))
      // {
      //     ref.push_back(true);
      //     llvm::Value *stackFrameAddr = getStackFrameAddr(callee_depth, caller_depth);
      //     ArgsV.push_back(stackFrameAddr);
      // }

      for (auto arg : Args) 
      {
          llvm::Value *expr = arg->compile();
          ArgsV.push_back(expr);
          if (!ArgsV.back())
              return nullptr;
      }
      //girnas ena call piso
      Builder.CreateCall(Fcall, ArgsV);
      return nullptr;
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

  virtual llvm::Value* compile() override{
    llvm::Value *strValue = Builder.CreateGlobalStringPtr(llvm::StringRef(str), "strconst");
    if (!strValue)
    {
        //std::string msg = "Error while compiling String_Cosnt: " + c_str(str) + ".";
        //return LogErrorV(msg.c_str());
    }
    return strValue;

  }
  private:
  char* str;
};

class L_value : public Expr {
  public:
    L_value(Id* i):id(i), str(nullptr){ }
    L_value(String_const* i):str(i),id(nullptr){}
    void append_expr(Expr* ex){
      expr_list.push_back(ex);
    }
    void sem() override {
      int i;
      if(str!=nullptr){
        Dims* d= new Dims();
        d->append(0);
        set_typedims(new Type(Type_char,d));
        return;
      }
      const char *c=id->name();
      STEntry * val = st.lookup(c);
      if(val==nullptr){
        printf("cant find the id %s on st\n",c);
        yyerror("");
      }
      else {
        if(val->var==nullptr) yyerror("invalid variable entry\n");
        for(auto s:expr_list){
          s->sem();
          if(s->expr_btype()!=Type_int){
            std::cout<< "expr :" << (*s) << " needs to have type int" << std::endl;
            yyerror("");
          }
        }
        // if(expr_list.size()!=val->var->type->dimensions()){
          // std::cout<< "variable " << c << " has "<< val->var->type->dimensions() << " dimensions and we have " <<expr_list.size() << " expressions"<< std::endl;
          // yyerror("");
        // }
        i=val->var->type->dimensions()-expr_list.size();
        if(i<0){
          std::cout << *this << "more dimensions than variable than variable " << c << "has \n"; 
        }
        else {
          Dims* d = new Dims();
          for(i; i>0 ; i--){
            d->append(0);
          }
          set_typedims(new Type(val->var->type->basic_type(),d));
          id->set_typedims(new Type(val->var->type->basic_type(),d));
        }
        //set_type(val->var->type->basic_type());
        std::cout<< "succesful varibale " << c << *(this->expr_type()) <<"lookup \n";
      }
      //printf("l_value sem\n");
    }
    void printAST(std::ostream &out) const override {
      if(id==nullptr) out << *str;
      else out << " " << *id;
      for( const auto &s : expr_list){
        out<< "[ "<<*s<<" ]";
      }
    }

  virtual llvm::Value* compile() override {

    llvm::Value* result = nullptr;

    // Case 1: The L_value is an identifier
    if (id != nullptr) {
        if (!expr_list.empty()) {

            std::vector<llvm::Value*> offsets;
            llvm::Type* elementType;

            for (Expr* expr : expr_list) {
                llvm::Value* compiledExpr = expr->compile();
                if (!compiledExpr) {
                    return LogErrorV("Error compiling index expression.");
                }
                offsets.push_back(compiledExpr);
            }

            result = id->compile();

            //result = id->compile_arr(&offsets, &elementType);
            if (!result) {
                return LogErrorV("Error compiling array element address.");
            }

            result = Builder.CreateGEP(elementType, result, offsets);

        } else {
            printf("Inside correct branch compiling id\n");
            result = id->compile();

        }
    }
    // Case 2: The L_value is a string constant
    else if (str != nullptr) {

        result = str->compile();
        if (!result) {
            return LogErrorV("Error compiling string constant.");
        }
    }
    // if (!expr_list.empty() && result) {
    //     llvm::Type* elementType = getLLVMType(expr_type(), TheContext); 
    //     result = Builder.CreateLoad(elementType, result);  
    // }

    return result;
  }
  llvm::Value* compile_ptr()  {

    llvm::Value* result = nullptr;

    // Case 1: The L_value is an identifier
    if (id != nullptr) {
        if (!expr_list.empty()) {

            std::vector<llvm::Value*> offsets;
            llvm::Type* elementType;

            for (Expr* expr : expr_list) {
                llvm::Value* compiledExpr = expr->compile();
                if (!compiledExpr) {
                    return LogErrorV("Error compiling index expression.");
                }
                offsets.push_back(compiledExpr);
            }

            result = id->compile_ptr();

            //result = id->compile_arr(&offsets, &elementType);
            if (!result) {
                return LogErrorV("Error compiling array element address.");
            }

            result = Builder.CreateGEP(elementType, result, offsets);

        } else {
            result = id->compile_ptr();

        }
    }
    // Case 2: The L_value is a string constant
    else if (str != nullptr) {

        result = str->compile();
        if (!result) {
            return LogErrorV("Error compiling string constant.");
        }
    }
    // if (!expr_list.empty() && result) {
    //     llvm::Type* elementType = getLLVMType(expr_type(), TheContext); 
    //     result = Builder.CreateLoad(elementType, result);  
    // }

    return result;
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
    virtual llvm::Value* compile() override {
      std::cout << num << std::endl;
      return c64(num);
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
    virtual llvm::Value* compile() override{
       return c8(var);
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
      exprl->sem();
      exprr->sem();
      exprl->check_type(Type_int);
      exprr->check_type(Type_int);
      set_type(Type_int);
    }
    virtual llvm::Value* compile() override {
      std::string str_op;

      llvm::Value *L = exprl->compile();
      llvm::Value *R = exprr->compile();

      if(!L || !R)
          return nullptr;
      

      if(op_s == nullptr) {
        //std::string str_op = std::string(op);
        str_op.push_back(op);

      }
      else 
        str_op = std::string(op_s);

      if (str_op == "+")
          return Builder.CreateAdd(L, R, "addtmp");
      else if (str_op == "-")
          return Builder.CreateSub(L, R, "subtmp");
      else if (str_op == "*")
          return Builder.CreateMul(L, R, "multmp");
      else if (str_op == "div")
          return Builder.CreateSDiv(L, R, "divtmp");
      else if (str_op == "mod")
          return Builder.CreateSRem(L, R, "modtmp");
      else
          return nullptr;
    }

  private:
    Expr* exprl;
    Expr* exprr;
    char op;
    char* op_s=nullptr;
};
  
class UniOp : public Expr {
  public:
    UniOp(char s, Expr *e): op(s), exprr(e) {}
    void printAST(std::ostream &out) const override {
      out << op << "(" << *exprr << ")";
    }
    void sem() override {
    exprr->sem();
    exprr->check_type(Type_int);
    set_type(Type_int);
    }
    virtual llvm::Value* compile() override {
      llvm::Value* R = exprr->compile();
      std::string op_str;
      op_str.push_back(op);
      if(op_str == "+")
          return R;
      else if (op_str == "-")
          return Builder.CreateNeg(R, "unarytemp");
      else
          return nullptr;
    }
  private:
    char op;
    Expr *exprr;
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
      else if (strcmp(op,"or") == 0){
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

    virtual llvm::Value* compile() override{
    llvm::Value *L = nullptr;
    llvm::Value *R = nullptr;
    std::string opStr = std::string(op);

    // Not
    if (condr == nullptr) {
        L = condl->compile();
        if (!L) 
            return nullptr;

        if (opStr == "not")
            return Builder.CreateNot(L, "nottemp");
        else
            return LogErrorV("Invalid unary operator in opcond");
    }
    // And, Or
    else {
        L = condl->compile();
        if (!L)
            return nullptr;

        llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
        llvm::BasicBlock *EvaluateRightBB = llvm::BasicBlock::Create(TheContext, "evalright", TheFunction);
        llvm::BasicBlock *SkipRightBB = llvm::BasicBlock::Create(TheContext, "skipright", TheFunction);
        llvm::BasicBlock *CurrentBB = Builder.GetInsertBlock();

        if (opStr == "and")
            Builder.CreateCondBr(L, EvaluateRightBB, SkipRightBB);
        else if (opStr == "or")
            Builder.CreateCondBr(L, SkipRightBB, EvaluateRightBB);
        else
            return LogErrorV("Invalid binary operator in opcond");

        // Set insertion point to 'EvaluateRightBB' and compile the right condition if necessary
        Builder.SetInsertPoint(EvaluateRightBB);
        R = condr->compile();
        if (!R)
            return nullptr;

        // Get the result of the binary operation
        llvm::Value *Result = nullptr;
        if (opStr == "and")
            Result = Builder.CreateAnd(L, R, "andtemp");
        else if (opStr == "or")
            Result = Builder.CreateOr(L, R, "ortemp");

        llvm::BasicBlock *AfterRightBB = Builder.GetInsertBlock();
        Builder.CreateBr(SkipRightBB);

        // Set insertion point to 'SkipRightBB'
        Builder.SetInsertPoint(SkipRightBB);
        // Create PHI node to select the correct result
        llvm::PHINode *PhiNode = Builder.CreatePHI(L->getType(), 2, "result");
        
        // Add incoming value from the current block (left condition result)
        PhiNode->addIncoming(L, CurrentBB);
        // Add incoming value from the block after evaluating the right condition
        PhiNode->addIncoming(Result, AfterRightBB);

        return PhiNode;
    }
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
      printf("ComOp left sem\n");
      exprl->sem();
      printf("ComOp right sem\n");
      exprr->sem();
      //prepei to exprl na exei typo opote prepei na ginei to lookup
      if(exprl->expr_btype()!=Type_char&&exprl->expr_btype()!=Type_int) yyerror("can't compare ");
      exprl->check_type(exprr->expr_btype());
      set_type(Type_bool);
    }

    virtual llvm::Value* compile() override {
    llvm::Value* l = exprl->compile();
    llvm::Value* r = exprr->compile();

    std::string str_op;

    if(op_s == nullptr) {
      //std::string str_op = std::string(op);
      str_op.push_back(op);
    }
    else 
      str_op = std::string(op_s);

    if(str_op == "<") return Builder.CreateICmpSLT(l, r, "lttmp");
    if(str_op == ">") return Builder.CreateICmpSGT(l, r, "gttmp");
    if(str_op == "<=") return Builder.CreateICmpSLE(l, r, "ltetmp");
    if(str_op == ">=") return Builder.CreateICmpSGE(l, r, "gtetmp");
    if(str_op == "=") return Builder.CreateICmpEQ(l, r, "eqtmp");
    if(str_op == "#") return Builder.CreateICmpNE(l, r, "netmp");

    return nullptr;
  }

  private:
    Expr* exprl;
    Expr* exprr;
    char* op_s;
    char op;
};

class Local_def: public AST{
  public:
  private:
};

class L_def : public Local_def{
  public:
    virtual void namesem() {}
  private:
};

class Id_list : public Local_def{
  public:
    Id_list(){}
    void append(Id* id){
      Idlist.push_back(id);
    }
    void id_type(Type* t){
      for( const auto &s : Idlist){
        s->set_typedims(t);
      }
    }
    std::vector<Id*> getList() {
      return Idlist;
    }
    void sem() override {
      for(auto s =Idlist.rbegin(); s!=Idlist.rend(); ++s) (*s)->sem();
    }
    void printAST(std::ostream &out) const override{
      bool i=false;
      for(const auto &s: Idlist){
        if(i==true) out << ",";
        out << *s;
        i=true;
      }
    }
    virtual llvm::Value* compile() override{
      llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
      Type * vartype = Idlist[0]->expr_type();
      llvm::Type* llvm_type=vartype->get_llvm_type(TheContext,vartype->dimensions());
      //int dims=0;
      //if(vartype->dimensions()>0) dims=vartype->array_dim(0);
      //llvm::Type *llvm_type = getLLVMType(vartype->basic_type(), TheContext,dims);

      for(auto id =Idlist.begin(); id!=Idlist.end(); ++id)
      {
        // maybe add something for the scope
          llvm::StringRef varName = (*id)->name();
          std::string name = (*id)->name();
          llvm::AllocaInst *allocaInst = CreateEntryBlockAlloca(TheFunction, varName, llvm_type);
          NamedValues[name] = allocaInst;
      }
      return nullptr;
    }


  private:
  std::vector<Id*> Idlist;
};

class Def_list : public Local_def{
  public:
    Def_list(){}
    void append(L_def* ld){
      deflist.push_back(ld);
    }
    void printAST(std::ostream &out) const override {
      for(const auto &s : deflist){
        out << *s;
      }
    }
    void sem() override {
      for(const auto &s : deflist){
        s->sem();
      }
    }
    std::vector<L_def*> getList(){
      return deflist;
    }

    virtual llvm::Value* compile() override {
      for (auto def: deflist)
      {
        def->compile();
        //Builder.SetInsertPoint(BB);
      }
      return nullptr;
    }
  private:
    std::vector<L_def*> deflist; 
};

class Fpar_def : public Local_def {
  public: 
    Fpar_def(Id_list* list,Type* typ, bool re=false):ref(re), type(typ),idlist(list){}
    void printAST(std::ostream &out) const override{
      if(ref==true) out << "ref ";
      out << *idlist << " : " << *type;
    }
    void sem() override{
      //printf("setting id_list type\n");
      idlist->id_type(type);
      //printf("idlist->sem\n");
      idlist->sem();      
    } 
    virtual llvm::Value* compile() override {
      return LogErrorV("Fpar_def error");
    }
    llvm::Value* compile(std::vector<std::string> * param_names, std::vector<llvm::Type*> *param_types){
      llvm::Type * t= getLLVMType(type->basic_type(),TheContext,type->dimensions()/*prepei na to ftiaksoume afto*/);
      for(auto *s : idlist->getList()){
        param_types -> push_back(t);
        std::string name = std::string(s->name());
        param_names -> push_back(name);
        //isos prepei na ftiaksoume kai gia id->name();
      }
      return nullptr;
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
    void sem() override{
      //printf("entered par_list\n");
      for(auto s =par_list.begin(); s!=par_list.end(); ++s) (*s)->sem();
    }
    virtual llvm::Value* compile() override{
      for(auto *s : par_list){
        s->compile();
      }
      return nullptr;
    }

    llvm::Value* compile(std::vector<std::string> * param_names, std::vector<llvm::Type*> *param_types) {
      for(auto *s : par_list){
        s->compile(param_names, param_types);
      }
      return nullptr;
    }
  private:
    std::vector<Fpar_def*> par_list;
};


class Header : public L_def {
  public:
    Header(Id *i,Type * typ, Fpar_list* par_l=nullptr):id(i),type(typ),par_list(par_l) {}
    void printAST(std::ostream &out) const override {
      out << "fun " << *id << "(" ;
      if(par_list==nullptr) out<<") :";
      else out <<  *par_list << ") :" ; 
      out<< *type;
    }
    void sem() override{
      //printf("entering par_list\n");
      if(par_list==nullptr); //printf("null parlist abort");
      else par_list->sem();
    }
    void namesem() override{
      id->set_type(type->basic_type());
      //printf("using fsem\n");
      id->fsem(); // prepei na apothikeboyme kai oti einai sygekrimena synarthsh kai posa orismata.
    }
    virtual llvm::Function * compile() override{

      // and den einai i top sinartisi tote 
      // kapoio elegxo kai link sto stack ths prohgoumenhs synarthshs

      if (par_list)
        par_list->compile(&fparam_names, &fparam_types);//pithanotata me arguements// tha prepei na gyrnaei type gia kathe parameter
      
      std::string name = std::string(id->name());
      llvm::Function * function = TheModule->getFunction(name);
      if (!function)
        {
            llvm::Type *return_type = getLLVMType(type->basic_type(),TheContext,0);
            llvm::FunctionType *funcType = llvm::FunctionType::get(return_type, fparam_types, false);
            function = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, name, TheModule.get());
        }
        return function;
    }
    std::vector<llvm::Type *> getfparam_types()
    {
        return fparam_types;
    }

    std::vector<std::string> getfparam_names()
    {
        return fparam_names;
    }
    Type* getType(){
      return type;
    }
  private:
    Id* id;
    Type * type;
    Fpar_list* par_list;
    std::vector<llvm::Type*> fparam_types;
    std::vector<std::string> fparam_names;
};

class Func_def : public Local_def {
  public:
  private:
};

class Var_def : public L_def {
  public:
    Var_def(Id_list* idl, Type* ty):id_list(idl), type(ty){
    }
    void printAST(std::ostream &out) const override {
      out << "var [" << *id_list << " - type:" << *type<< "]";
    }
    void sem() override {
      id_list->id_type(type);
      id_list->sem();
    }
    virtual llvm::Value* compile() override{
      std::cout << "the type is " << type->basic_type() << " and size " << type->dimensions();
      id_list->compile();
      return nullptr;
    }

  private:
    Id_list * id_list;
    Type* type;
};

class Function : public L_def {
  public: 
    Function(Header* head, Def_list* d_list, Block* bl): header(head), def_list(d_list), block(bl){}
    void printAST(std::ostream &out) const override {
      out << *header << std::endl << *def_list << std::endl << *block;
    }
    void sem() override{
      int i;
      
      //printf("entered Function class sem\n");
      if(!st.check_empty()) {
        printf("st not empty");
        header->namesem();
        //header->sem();
        st.stopfunc();
      }
      //printf("pushing scope");
      st.push_scope();
      header->namesem(); 
      //printf("header->sem\n");
      header->sem();
      st.stopfunc();
      st.copyfun();
      //st.copyfunc();
      //printf("fuction read\n");
      st.f_args();//diabazoume to megethos tou scope mexri tora kai to anathetoume sta argoumenet ths synarthshs
      //printf("function arguements read, number : %d\n", i);
      //std::cout<< "def_list " << *def_list <<std::endl;
      def_list->sem();
      printf("definitions of this function ended\n");
      printf("block->sem\n");
      block->sem();
      printf("popping scope\n");
      if(!st.check_empty()) st.pop_scope();
    }

  virtual llvm::Function* compile() override {
    // Get the insertion point of the previous function.
    llvm::BasicBlock *BB_ofAbovelvelFunc = Builder.GetInsertBlock();

    // ***Compile the header
    llvm::Function *function = header->compile();
    if (!function)
        return nullptr;


    // For testing only instead of header
    // **************
    // llvm::Type *intType = llvm::Type::getInt64Ty(TheContext);
    // llvm::FunctionType *funcType = llvm::FunctionType::get(intType, false); // No arguments
    // llvm::Function *function = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "simpleFunction", TheModule.get());
    // ***************

    llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", function);
    Builder.SetInsertPoint(BB);

    //***Get names/types of the parameters and save the args in the NamedValues table
    unsigned int current_arg = 0;
    std::vector<std::string> fparam_names = header->getfparam_names();
    std::vector<llvm::Type *> fparam_types = header->getfparam_types();

    // Create allocation for each arguments
    for (auto &Arg : function->args())
    {
        llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(function, llvm::StringRef(fparam_names[current_arg]), fparam_types[current_arg]);
        Builder.CreateStore(&Arg, Alloca);
        NamedValues[fparam_names[current_arg++]] = Alloca;
    }

    //***prepei na ftiaxtei kapoio stackframe gia tin sinartisi kai tis parametrous */


    // ***Compile the Def List
    std::vector<L_def*> deflist = def_list->getList();
    for (auto def: deflist)
      {
        def->compile();
        Builder.SetInsertPoint(BB);
      }

    // ***Compile The Block
    block -> compile();

    if (!Builder.GetInsertBlock()->getTerminator())
    {   
        Type* t = header->getType();
        if (t->basic_type() == Type_int)
          Builder.CreateRet(c64(0));
        else if (t->basic_type() == Type_char)
          Builder.CreateRet(c64(0));
        else
            Builder.CreateRetVoid();
    }

    Builder.SetInsertPoint(BB_ofAbovelvelFunc);

    return function;

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
    void sem() override{
      printf("starting valuation\n");
      expr->sem();
      var->sem();
      var->check_type(expr->expr_btype());
      printf("valuation sem\n");
    }
    virtual llvm::Value * compile() override {
      printf("The evaluation is starting");
      llvm::Value *LValAddr = var->compile_ptr();
      if (!LValAddr)
          return LogErrorV("Valuation: LValue(var) could not be compiled.");

      llvm::Value *ExprValue = expr->compile();
      if (!ExprValue)
          return LogErrorV("Valuation: Expression(expr) could not be compiled.");

      Builder.CreateStore(ExprValue, LValAddr);
      return nullptr;
    }
  private: 
    Expr* expr;
    L_value * var;
};
#endif