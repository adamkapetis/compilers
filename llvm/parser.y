%{
#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include "lexer.hpp"
//#include "symbol.hpp"
#include "ast.hpp"
#include "cxxopts.hpp"


#define YYDEBUG 1
SymbolTable st;
bool optimize;
bool intermediate;

%}

//%define lr.default-reduction consistent
/* %define parse.trace true */
%union {
    Function * function;
    Fpar_list * fpar_list;
    Fpar_def * fpar_def;
    Header * header;
    Func_def * func_def;
    Var_def * var_def;
    L_def * local_def;
    Def_list * deflist;
    Type * type;
    Id_list * id_list;
    Dims *dlist;
    Dtype dtype;
    If_then_else* if_then_else;
    Stmt *stmt;
    Expr *expr;
    Cond *cond;
    Block *blk;
    L_value* l_value;
    Func_call* func_call;
    Exprc* exprc;
//    Id * ident;
    char var;
    int num;
    char op;
    char div;
    char* def;
    char* op_s;
    char* div_s;
    char* str;
    char* id;
}


%token T_eof "eof"
%token <op_s>T_and "and"
%token <def>T_char "char"
%token <op_s>T_div "div"
%token <def>T_do "do"
%token <def>T_else "else"
%token <def>T_fun "fun"
%token <def>T_if "if"
%token <def>T_int "int"
%token <op_s> T_mod "mod"
%token <op_s>T_not "not"
%token <def>T_nothing "nothing"
%token <op_s>T_or "or"
%token <def>T_ref "ref"
%token <def>T_return "return"
%token <def>T_then "then"
%token <def> T_var "var"
%token <def>T_while "while"
%token <op_s>T_lesseq "<="
%token <op_s>T_greateq ">="
%token <op_s>T_arrow  "<-"

%token <num> T_int_const 
%token <var> T_char_const 
%token <id>  T_id 
%token <str> T_string_const 
%token <div> T_divider '('')''{''}''['']'','':'';'
%token <op>  T_operator '<''>''#''=' 
%left <op> '+' '-'
%left <op> '*' '/' '%'

%type <function> func_def
%type <fpar_list> fd
%type <fpar_def> fpar_def
%type <header> header
%type <type> fpar_type
%type <dtype> ret_type
%type <local_def> local_def
%type <deflist> ld
%type <type> type
%type <id_list> td
%type <dlist> cd
%type <dtype> data_type
%type <var_def> var_def
%type <exprc> exprc
%type <func_call> func_call
%type <expr> expr
%type <cond> cond
%type <l_value> l_value
%type <blk> stmtd
%type <blk> block
%type <stmt> stmt

%%

program: 
    func_def	                            { std::cout << "AST : " << *$1 << std::endl ;
                                                    $1->sem(); 
                                                    $1->llvm_compile_and_dump(optimize, intermediate);
                                            }
;
ld:                                         { $$=new Def_list(); }
|   ld local_def                            { $1->append($2);$$=$1; }
;       
func_def:                                   
    header ld block                         { $$=new Function($1,$2,$3); }
;
header:
    "fun" T_id '(' fd ')' ':' ret_type      { $$= new Header(new Id($2),new Type($7,new Dims()),$4); }
|    "fun" T_id '(' ')' ':' ret_type        { $$= new Header(new Id($2),new Type($6,new Dims())); }
;
fd: fpar_def                                { $$=new Fpar_list($1); }
|   fd ';' fpar_def                         { $1->append($3);$$=$1; }
; 



fpar_def:       
    "ref" T_id td ':' fpar_type             { $3->append_front(new Id($2));$$=new Fpar_def($3,$5,true); }
|   T_id td ':' fpar_type                   { $2->append_front(new Id($1));$$=new Fpar_def($2,$4); }
;       
td: /*nothing */                            { /*std::cout<<"No new id on list\n" ;*/$$=new Id_list(); }
|  td  ',' T_id                             { /*std::cout<<"new id on list\n"    ;*/$1->append(new Id($3));$$=$1; }
;        
data_type:                                  
    "int"                                   { $$=Type_int; } 
|   "char"                                  { $$=Type_char; } 
;                   
cd: /*nothing*/                             { $$ = new Dims(); }
|  cd  '[' T_int_const ']'                  { /*std::cout << "number" <<$3 ;*/$1->append($3); $$=$1; }
;       
type:       
    data_type cd                            { $$ = new Type($1,$2); }
;       
ret_type:                                   
    data_type                               { $$=$1; }
|   "nothing"                               { $$=Type_void; }
;       

fpar_type:      
    data_type '[' ']' cd                    { $4->append(0);$$ = new Type($1,$4); }
|   data_type  cd                           { $$ = new Type($1,$2); }
;       
local_def:      
    func_def                                { $$=$1; }
|   var_def                                 { $$=$1; }
;
   
var_def:
    "var" T_id td ':' type ';'              { /*std::cout <<"printing a variable: "<<$1 << $2 ;*/$3->append_front(new Id($2));$$=new Var_def($3,$5);/*std::cout << "AST: " << *$$ <<" type "<< *$5 << std::endl;*/ }
;
stmt:
    ';'                                     { $$=new End();} //maybe put $$ = nullptr;
|   l_value "<-" expr ';'                   { $$=new Valuation($1,$3);/* std::cout << *$$;      */}//{$1=new L_value();$$=new Valuation($1,$3);}
|   block                                   { $$=$1;                        } // kalytera to block sto stmtd kai merge ton 2 block
|   func_call ';'                           { $$=$1;                        }
|   "if" cond "then" stmt "else" stmt       { $$=new If_then_else($2,$4,$6); }
|   "if" cond "then" stmt                   { $$=new If_then_else($2,$4);   }
|   "while" cond "do" stmt                  { $$=new While_stmt($2,$4);     }
|   "return" expr ';'                       { $$=new Return_stmt($2);       }
|   "return" ';'                            { $$=new Return_stmt();         }    
;
stmtd: /*nothing*/          { /*std::cout<<"created new block \n" ;*/$$ = new Block(); }
|   stmtd stmt              { /*std::cout << "appended to block stmt:" << *$2<<std::endl;*/ $1->append($2); $$=$1; }
;
block: 
    '{' stmtd '}'           { $$=$2; }
;
exprc: /*nothing*/      
    expr                    { $$ = new Exprc($1); }
|   exprc ',' expr          { $1->append($3); $$ = $1; } 
;
func_call:
    T_id '(' exprc ')'      { std::cout<<"calling function "<<$1 <<std::endl ;$$ = new Func_call(new Id($1),$3); }
|   T_id '(' ')'            { $$ = new Func_call(new Id($1)); }
;
l_value:
    T_id                {$$=new L_value(new Id($1));}//{ $$->set_id($1); }
|   T_string_const      {$$=new L_value(new String_const($1));}//{ $$->set_str($1); }
|   l_value '[' expr ']'{ $1->append_expr($3);$$=$1; } 
;

expr: 
    T_int_const         { $$ = new Int_const($1); }
|   T_char_const        { $$ = new Char_const($1); }
|   l_value             { $$=$1; }//{ $$=new L_value(); }
|   '(' expr ')'        { $$ = $2;  }
|   func_call           { $$ = $1;  }
|   '+' expr            { $$ = new UniOp($1, $2); }
|   '-' expr            { $$ = new UniOp($1, $2); }
| expr '+' expr         { $$ = new BinOp($1, $2, $3); /*$$->sem();*/ }
| expr '-' expr         { $$ = new BinOp($1, $2, $3);  }
| expr '*' expr         { $$ = new BinOp($1, $2, $3);  }
| expr "div" expr       { $$ = new BinOp($1, $2, $3);  } // alladh edo gia na pairnei "div"
| expr "mod" expr       { $$ = new BinOp($1, $2, $3);  } // alladh edo gia na pairnei "mod"
;
cond: 
    '(' cond ')'        { $$ = $2; }
|   "not" cond          { $$ = new LogOp($2, $1); }
|   cond "or" cond      { $$ = new LogOp($1, $2, $3); }  
|   cond "and" cond     { $$ = new LogOp($1, $2, $3); } 
|   expr '=' expr       { $$ = new ComOp($1, $2, $3); } 
|   expr '#' expr       { $$ = new ComOp($1, $2, $3); } 
|   expr '<' expr       { $$ = new ComOp($1, $2, $3); } 
|   expr '>' expr       { $$ = new ComOp($1, $2, $3); } 
|   expr "<=" expr      { $$ = new ComOp($1, $2, $3); } 
|   expr ">=" expr      { $$ = new ComOp($1, $2, $3); }        
;

%%

void yyerror(const char *msg) {
    printf("Syntax error:%s at line :%d, token : %s\n",msg,linenumber,start);
    exit(42);
}

// int main() {
//     /* #ifdef YYDEBUG
//     yydebug = 1;
//     #endif */
//     int res = yyparse();
//     if(res == 0) printf("Successful parsing\n");
//     return res;
// }

int main(int argc, char** argv) {
    //fill_names();
    optimize = false;
    intermediate = false;
    cxxopts::Options options("Gracec", "Compiler for the Grace Language");

    options.add_options()
        ("o,optimize", "Optimize code")
        ("f,final", "Print final code")
        ("i,intermediate", "Print intermediade representation")
        ("h,help", "Show this help message")
        ("filename", "File containing grace code", cxxopts::value<std::string>())
    ;

    options.parse_positional({"filename"});
    cxxopts::ParseResult result;
     try {
      result = options.parse(argc, argv);
    } catch (const std::exception& ex) {
      std::cerr << ex.what() << ". Emit '-h' flag for usage." << std::endl;
      exit(1);
    }

    if (!result.arguments().size()) {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    optimize = result["optimize"].as<bool>();

    intermediate = result["intermediate"].as<bool>();

    if(result["final"].as<bool>()) {
        /* yyparse();
        AST::compile_to_asm(); */
        exit(0);
    }

    std::string filename;
    if(result.count("filename")) {
        filename = result["filename"].as<std::string>();

        auto found = filename.find_last_of('.');
        auto title = filename.substr(0, found);

        std::ifstream file(filename, std::ios::in);
        if(!file.is_open()) {
            std::cerr << "Gracec: could not open file " << filename << std::endl;
            exit(1);
        }

        int fd = open(filename.c_str(), O_RDONLY);
        if(fd == -1) {
            std::cerr << "Gracec: could not open file " << filename << std::endl;
            exit(1);
        }

        if(dup2(fd, 0) == -1) {
            std::cerr << "Gracec: failed" << std::endl;
            exit(1);
        }
        close(fd);

        yyparse();
        file.close();
        
        std::error_code error;
        llvm::raw_fd_ostream _imm(title + ".imm", error);
        if(!error) {
            AST::TheModule->print(_imm, nullptr);
            _imm.flush();
        } else {
            std::cerr << "Gracec: error creating file" << std::endl;
            exit(1);
        }

        char command[256];
        sprintf(command, "llc-16 -o %s.asm %s.imm", title.c_str(), title.c_str());
        if(system(command)) {
            std::cerr << "Gracec: error compiling imm code" << std::endl;
            exit(1);
        }
    }

    return 0;
}