%{
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
%}

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
/* %token T_lesseq "<="
%token T_greateq ">="
%token T_arrow "<-" */

%token T_int_const 
%token T_char_const 
%token T_id 
%token T_string_const 
%token T_divider 
%token T_operator   

%left '+' '-'
%left '*' '/' '%'

%%

program: 
    func_def
;
ld: /*nothing*/
|   local_def ld
;
func_def:
    header ld block
;
fd: /*nothing*/
|   ';' fpar_def fd
|   fpar_def fd
;
header:
    "fun" T_id '(' fd ')' ':' ret_type
;
td: /*nothing*/
|  ',' T_id  td
;
fpar_def:
    "ref" T_id td ':' fpar_type 
|   T_id td ':' fpar_type     
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
    T_id 
|   T_string_const
|   l_value '[' expr ']'
;
expr: 
    T_int_const 
|   T_char_const 
|   l_value
|   '(' expr ')' 
|   func_call
|   '+' expr 
|   '-' expr
| expr '+' expr
| expr '-' expr
| expr '*' expr
| expr "div" expr
| expr "mod" expr
;
cond: 
    '(' cond ')'
|   "not" cond
|   cond "or" cond
|   cond "and" cond   
|   expr '=' expr
|   expr '#' expr
|   expr '<' expr
|   expr '>' expr
|   expr "<=" expr   
|   expr ">=" expr             
;

%%

void yyerror(const char *msg) {
    printf("Syntax error:%s\n",msg);
    exit(42);
}

int main() {
    #ifdef YYDEBUG
    yydebug = 1;
    #endif
    int res = yyparse();
    if(res == 0) printf("Successful parsing\n");
    return res;
}