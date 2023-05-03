%{
#include <cstdio>
#include <string>
#include <cstdlib>
#include "lexer.hpp"
#include "ast.hpp"
#define YYDEBUG 1
%}
/* %define parse.trace true */
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
%token T_arrow "<-"

%token T_int_const 
%token T_char_const 
%token T_id 
%token T_string_const 
%token T_divider 
%token T_operator   

%left '+' '-'
%left '*' '/' '%'

%union {
  Stmt *stmt;
  Expr *expr;
  Cond *cond;
  Block *blk;
  char var;
  int num;
  char op;
  char* op_s;
  char* div_s;
  char* str;
  char* id;
}
%type <expr> expr
%type <cond> cond
%type <l_value> l_value

%%

program: 
    func_def	 { $1->execute(); }
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
|   block
|   func_call ';'
|   "if" cond "then" stmt "else" stmt
|   "if" cond "then" stmt
|   "while" cond "do" stmt 
|   "return" expr ';'
|   "return" ';'
;
stmtd: /*nothing*/
|   stmt stmtd
;
block: 
    '{' stmtd '}'
;
exprc: /*nothing*/
|   ',' expr exprc
;
func_call:
    T_id '(' expr exprc ')'
|   T_id '(' ')'    
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
    printf("Syntax error:%s\n",msg);
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