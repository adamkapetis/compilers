%{
#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include "lexer.hpp"
#include "ast.hpp"

#define YYDEBUG 1
%}
/* %define parse.trace true */
%union {
    Function * function;
    Fpar_list * fpar_list;
    Fpar_def * fpar_def;
    Header * header;
    Func_def * func_def;
    Var_def * var_def;
    Local_def * local_def;
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
    char* op_s;
    char* div_s;
    char* str;
    char* id;
}


%token T_eof "eof"
%token T_and "and"
%token T_char "char"
%token T_div "div"
%token T_do "do"
%token T_else "else"
%token T_fun "fun"
%token T_if "if"
%token T_int "int"
%token T_mod "mod"
%token T_not "not"
%token T_nothing "nothing"
%token T_or "or"
%token T_ref "ref"
%token T_return "return"
%token T_then "then"
%token T_var "var"
%token T_while "while"
%token T_lesseq "<="
%token T_greateq ">="
%token T_arrow  "<-"

%token <num> T_int_const 
%token <var> T_char_const 
%token <id> T_id 
%token <str> T_string_const 
%token T_divider 
%token T_operator 
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
    func_def	 { std::cout << "AST: " << *$1 << std::endl; }
;
ld: /*nothing*/                     {$$=new Def_list();}
|   local_def ld                    {$2->append($1);$$=$2;}
;
func_def:                           
    header ld block                 {$$=new Function($1,$2,$3);}
;
header:
    "fun" T_id '(' fd ')' ':' ret_type  {$$= new Header(new Id($2),$4,$7);}
;
fd: /*nothing*/                     {$$=new Fpar_list();}
|   ';' fpar_def fd                 {$3->append($2);$$=$3;}
|   fpar_def fd                     {$2->append($1);$$=$2;}
;

fpar_def:
    "ref" T_id td ':' fpar_type     {$3->append(new Id($2));$$=new Fpar_def($3,$5,true);}
|   T_id td ':' fpar_type           {$2->append(new Id($1));$$=new Fpar_def($2,$4);}
;
td: /*nothing*/                     {$$=new Id_list();}
|  ',' T_id  td                     {$3->append(new Id($2));$$=$3;}
;
data_type:                          
    "int"                           {$$=Type_int;}
|   "char"                          {$$=Type_char;}
;           
cd: /*nothing*/                     {$$ = new Dims();}
|  '[' T_int_const ']'  cd          {$4->append(new Dim($2)); $$=$4;}
;
type: 
    data_type cd                    {$$ = new Type($1,$2);}
;
ret_type:                           
    data_type                       {$$=$1;}
|   "nothing"                       {$$=Type_void;}
;

fpar_type:
    data_type '[' ']' cd            {$4->append(new Dim(0));$$ = new Type($1,$4);}
|   data_type  cd                   {$$ = new Type($1,$2);}
;
local_def:
    func_def                                {$$=$1;}
|   header ';'                              {$$=$1;}
|   var_def                                 {$$=$1;}
;
   
var_def:
    "var" T_id td ':' type ';'              {$3->append(new Id($2));$$=new Var_def($3,$5);}
;
stmt:
    ';' 
|   l_value "<-" expr ';'                   {$$=new Valuation($1,$3);}
|   block                                   {$$=$1;} // kalytera to block sto stmtd kai merge ton 2 block
|   func_call ';'                           {$$=$1;}
|   "if" cond "then" stmt "else" stmt       {$$=new If_then_else($2,$4,$6);}
|   "if" cond "then" stmt                   {$$=new If_then_else($2,$4);}
|   "while" cond "do" stmt                  {$$=new While_stmt($2,$4);}
|   "return" expr ';'                       {$$=new Return_stmt($2);}
|   "return" ';'                            {$$=new Return_stmt();}    
;
stmtd: /*nothing*/          {$$ = new Block();}
|   stmtd stmt              {$1->append($2); $$=$1;}
;
block: 
    '{' stmtd '}'           {$$=$2;}
;
exprc: /*nothing*/      
    expr                    { $$ = new Exprc($1); }
|   exprc ',' expr          { $1->append($3); $$ = $1; }
;
func_call:
    T_id '(' exprc ')'      { $$ = new Func_call(new Id($1),$3); }
|   T_id '(' ')'            { $$ = new Func_call(new Id($1)); }
;
l_value:
    T_id                { $$->set_id($1); }
|   T_string_const      { $$->set_str($1); }
|   l_value '[' expr ']'{ $1->append_expr($3);$$=$1; } 
;

expr: 
    T_int_const         { $$ = new Int_const($1); }
|   T_char_const        { $$ = new Char_const($1); }
|   l_value             { $$=new L_value(); $$ = $1; }
|   '(' expr ')'        { $$ = $2; }
|   func_call           { $$ = $1; }
|   '+' expr            { $$ = new BinOp($2,$1); }
|   '-' expr            { $$ = new BinOp($2,$1); }
| expr '+' expr         { $$ = new BinOp($1, $2, $3); }
| expr '-' expr         { $$ = new BinOp($1, $2, $3); }
| expr '*' expr         { $$ = new BinOp($1, $2, $3); }
| expr "div" expr       { $$ = new BinOp($1, 'd', $3); } // alladh edo gia na pairnei "div"
| expr "mod" expr       { $$ = new BinOp($1, 'm', $3); } // alladh edo gia na pairnei "mod"
;
cond: 
    '(' cond ')'        { $$ = $2; }
|   "not" cond          { $$ = new LogOp($2, 0); }
|   cond "or" cond      { $$ = new LogOp($1, 1, $3); }  
|   cond "and" cond     { $$ = new LogOp($1, 2, $3); } 
|   expr '=' expr       { $$ = new ComOp($1, '=', $3); } 
|   expr '#' expr       { $$ = new ComOp($1, '#', $3); } 
|   expr '<' expr       { $$ = new ComOp($1, '<', $3); } 
|   expr '>' expr       { $$ = new ComOp($1, '>', $3); } 
|   expr "<=" expr      { $$ = new ComOp($1, "<=", $3); } 
|   expr ">=" expr      { $$ = new ComOp($1, ">=", $3); }        
;

%%

void yyerror(const char *msg) {
    printf("Syntax error:%s at line :%d, token : %s\n",msg,linenumber,yytext);
    exit(42);
}

int main() {
    /* #ifdef YYDEBUG
    yydebug = 1;
    #endif */
    int res = yyparse();
    if(res == 0) printf("Successful parsing\n");
    return res;
}