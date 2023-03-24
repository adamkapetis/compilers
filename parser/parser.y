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