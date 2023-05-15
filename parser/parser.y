%{
#include <cstdio>
#include <string>
#include <cstdlib>
#include "lexer.hpp"
#include "ast.hpp"
#define YYDEBUG 1
%}
%union {
  Stmt *stmt;
  Expr *expr;
  Cond *cond;
  Block *blk;
  L_value* l_value;
  Func_call* func_call;
  Exprc* exprc;
  char var;
  int num;
  char op;
  char* op_s;
  char* div_s;
  char* str;
  char* id;
}

/* %define parse.trace true */
%token T_eof "eof"
%token<op_s> T_and "and"
%token T_char "char"
%token<op_s> T_div "div"
%token T_do "do"
%token T_else "else"
%token T_fun "fun"
%token T_if "if"
%token T_int "int"
%token<op_s> T_mod "mod"
%token<op_s> T_not "not"
%token T_nothing "nothing"
%token<op_s> T_or "or"
%token T_ref "ref"
%token T_return "return"
%token T_then "then"
%token T_var "var"
%token T_while "while"
%token T_lesseq "<="
%token T_greateq ">="
%token T_arrow "<-"

%token<num> T_int_const 
%token<var> T_char_const 
%token<id> T_id 
%token<str> T_string_const 
%token T_divider 
%token T_operator   

%left<op> '+' '-'
%left<op> '*' '/' '%'

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
    func_def	 {  }
;
ld: /*nothing*/
|   local_def ld 
;
func_def:
    header ld block
;
header:
    "fun" T_id '(' fd ')' ':' ret_type
;
fd: /*nothing*/
|   ';' fpar_def fd
|   fpar_def fd
;

fpar_def:
    "ref" T_id td ':' fpar_type 
|   T_id td ':' fpar_type     
;
td: /*nothing*/
|  ',' T_id  td
;
data_type:
    "int" 
|   "char"
;
cd: /*nothing*/
|  '[' T_int_const ']'  cd
;
type: 
    data_type cd
;
ret_type:
    data_type
|   "nothing"
;
fpard: /*nothing*/
|  '[' T_int_const ']'  fpard
;
fpar_type:
    data_type '[' ']' fpard 
|   data_type  fpard
;
local_def:
    func_def 
|   func_decl
|   var_def              
;
func_decl:
    header ';'
;    
var_def:
    "var" T_id td ':' type ';' 
;
stmt:
    ';' 
|   l_value "<-" expr ';' 
|   block                   {$$=$1}
|   func_call ';'
|   "if" cond "then" stmt "else" stmt
|   "if" cond "then" stmt
|   "while" cond "do" stmt 
|   "return" expr ';'
|   "return" ';'
;
stmtd: /*nothing*/          {$$ = new Block()}
|   stmtd stmt              {$1->append($2); $$=$1;}
;
block: 
    '{' stmtd '}'           {$$=$2}
;
exprc: /*nothing*/      
    expr                    {$$ = new Exprc($1);}
|   exprc ',' expr          {$1->append($3); $$ = $1;}
;
func_call:
    T_id '(' exprc ')'      {$$ = new Func_call($1,$3);}
|   T_id '(' ')'            {$$ = new Func_call($1);}
;
l_value:
    T_id                { $$ = new Id($1); }
|   T_string_const      { $$ = new String_const($1); }
|   l_value '[' expr ']'{ $$ = new L_value($1, $3); } 
;

expr: 
    T_int_const         { $$ = new Int_const($1); }
|   T_char_const        { $$ = new Char_const($1); }
|   l_value             { $$ = $1; }
|   '(' expr ')'        { $$ = $2; }
|   func_call           { $$ = $1; }
|   '+' expr            { $$ = new BinOp($1, $2); }
|   '-' expr            { $$ = new BinOp($1, $2); }
| expr '+' expr         { $$ = new BinOp($1, $2, $3); }
| expr '-' expr         { $$ = new BinOp($1, $2, $3); }
| expr '*' expr         { $$ = new BinOp($1, $2, $3); }
| expr "div" expr       { $$ = new BinOp($1, $2, $3); }
| expr "mod" expr       { $$ = new BinOp($1, $2, $3); }
;
cond: 
    '(' cond ')'        { $$ = $2; }
|   "not" cond          { $$ = new LogOp($1, $2); }
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
    printf("Syntax error:%s at line: %d\n",msg, linenumber);
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