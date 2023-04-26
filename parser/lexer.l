%option noyywrap

%{
#include "lexer.h"
#include "parser.h"
#define T_eof          0

int linenumber=1;
%}


L [a-zA-Z]
D [0-9]
W [ \t\r\n]
HEX [0-9a-fA-F]{2}
COMMON [^'"\\]
DOLLAR [^\$]
%option noyywrap
%x IN_COMMENT
%%

"and"     { return T_and; }
"char"    { return T_char; }
"div"     { return T_div; }
"do"      { return T_do; }
"else"    { return T_else; }
"fun"     { return T_fun; }
"if"      { return T_if; }
"int"     { return T_int; }
"mod"     { return T_mod; }
"not"     { return T_not; }
"nothing" { return T_nothing; }
"or"      { return T_or; }
"ref"     { return T_ref; }
"return" { return T_return; }
"then"    { return T_then; }
"var"     { return T_var; }
"while"   { return T_while;}

{L}({L}|{D}|\_)*                                           { return T_id; }
{D}+                                                       { return T_int_const; }
\'({COMMON}|\\x{HEX}|\\n|\\r|\\t|\\0|\\\\|\\'|\\\")\'      { return T_char_const; } 
\"({COMMON}|\\x{HEX}|\\n|\\r|\\t|\\0|\\\\|\\'|\\\")+\"     { return T_string_const;}
\<\-                                                       { return T_divider;}
[\(\)\{\}\[\]\,\;\:]                                       { return T_divider;}
\<\=                                                       { return T_operator; }
>=                                                         { return T_operator; }
[\+\-/%*=\#\<]                                            { return T_operator; }
\n                                                         { ++linenumber;}
<INITIAL>{
"$$"              BEGIN(IN_COMMENT);
}
<IN_COMMENT>{
"$$"      BEGIN(INITIAL);
[^$\n]+   
\n        linenumber++;
}
\$.*\n                                                     { ++linenumber;}
{W}+                                                       { /* nothing */ }


.       { fprintf(stderr, "Illegal character with code %d",
                  yytext[0]);
          exit(1);
        }

%%

