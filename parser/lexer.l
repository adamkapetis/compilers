%option noyywrap

%{
#include "parser.hpp"
#include "ast.hpp"
#include "lexer.hpp"
// #define T_eof          0

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

{L}({L}|{D}|\_)*                                           { yylval.id = yytext; return T_id; }
{D}+                                                       { yylval.num = atoi(yytext); return T_int_const; }
\'({COMMON}|\\x{HEX}|\\n|\\r|\\t|\\0|\\\\|\\'|\\\")\'      { yylval.var = yytext[0]; return T_char_const; } 
\"({COMMON}|\\x{HEX}|\\n|\\r|\\t|\\0|\\\\|\\'|\\\")+\"     { yylval.str = yytext; return T_string_const;}
\<\-                                                       { yylval.div_s = yytext; return T_arrow;}
[\(\)\{\}\[\]\,\;\:]                                       { yylval.div = yytext[0]; return yytext[0];}
\<\=                                                       { yylval.op_s = yytext; return T_lesseq; }
>=                                                         { yylval.op_s = yytext; return T_greateq; }
[\+\-/%*=\#\<\>]                                           { yylval.op = yytext[0]; return yytext[0]; }
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

