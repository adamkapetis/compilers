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
    func-def
;
ld: /*nothing*/
|   local-def ld
;
func-def:
    header ld block
;
fd: /*nothing*/
|   ';' fpar-def fd
;
header:
    "fun" T_id '(' fpar-def fd ')' ':' ret-type
;
td: /*nothing*/
|  ',' T_id  td
;
fpar-def:
    "ref" T_id td ':' fpar-type 
|   T_id td ':' fpar-type     
;
data-type:
    "int" 
|   "char"
;
cd: /*nothing*/
|  '[' T_int_const ']'  cd
;
type: 
    data-type cd
;
ret-type:
    data-type
|   "nothing"
;
fpard: /*nothing*/
|  '[' T_int_const ']'  fpard
;
fpar-type:
    data-type '[' ']' fpard 
|   data-type  fpard
;
local-def:
    func-def 
|   func-decl
|   var-def              
;
func-decl:
    header ';'
;    
var-def:
    "var" T_id td ':' type ';' 
;
stmt:
    ';' 
|   l-value '<-' expr ';' 
|   block
|   func-call ';'
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
func-call:
    T_id '(' expr exprc ')'
|   T_id '(' ')'    
;
l-value:
    T_id 
|   T_string_const
|   l-value '[' expr ']'
;
expr: 
    T_int_const 
|   T_char_const 
|   l-value
|   '(' expr ')' 
|   func-call
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
|   expr '<=' expr   
|   expr '>=' expr             
;

%%

void yyerror(const char *msg) {
    printf("Syntax error:%s\n",msg);
    exit(42);
}

int main() {
    int res = yyparser();
    if(res == 0) printf("Successful parsing\n");
    return res;
}