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
func-def:
    header (local-def)* block
;
header:
    "fun" T_id '(' fpar-def (';' fpar-def)* ')' ':' ret-type
;
fpar-def:
    ["ref"] T_id (',' T_id)* ':' fpar-type 
;
data-type:
    "int" 
|   "char"
;
type: 
    data-type ('[' T_int_const ']')*
;
ret-type:
    data-type
|   "nothing"
;
fpar-type:
    data-type ['[' ']'] ('[' T_int_const ']')   
;
local-def:
    func-def 
|   func-decl
|   var-def              
;
func-decl:
    header ';'
var-def:
    "var" T_id (',' T_id)* ':' type ';' 
;
stmt:
    ';' 
|   l-value "<-" expr ';' 
|   block
|   func-call ';'
|   "if" cond "then" stmt ["else" stmt]
|   "while" cond "do" stmt 
|   "return" [expr] ';'
;
block: 
    '{' (stmt)* '}'
;
func-call:
    T_id '(' expr (',' expr)* ')'
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
|   ('+' | '-' expr) 
|   expr ('+' | '-' | '*' 'div' 'mod') expr 
;
cond: 
    '(' cond ')'
|   "not" cond
|   cond ("and" | "or") cond
|   expr ('=' | '#' | '<' | '>' | '<=' '>=') expr                      
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