%option noyywrap

%{
#include <iostream>
#include <string>
#include "lexer.hpp"
#include "ast.hpp"
int linenumber=1;
bool newline=true;
char * start;
#include "parser.hpp"
// #define T_eof          0
int length( char * c){
        if(c==nullptr) return 0;
        else{
                int counter=0;
                while(c[counter]!='\0'){
                        counter++;
                }
                return counter;
        }
}


%}


L [a-zA-Z]
D [0-9]
W [ \t\r]
HEX [0-9a-fA-F]{2}
COMMON [^'"\\]
DOLLAR [^\$]
%option noyywrap
%x IN_COMMENT
%%

"and"     { /*printf("lexeme=\"%s\"\n",yytext);*/if(newline){newline=false;start=yytext;}yylval.op_s="and";return T_and; }
"char"    { /*printf("lexeme=\"%s\"\n",yytext);*/if(newline){newline=false;start=yytext;}return T_char; }
"div"     { /*printf("lexeme=\"%s\"\n",yytext);*/if(newline){newline=false;start=yytext;}yylval.op_s="div";return T_div; }
"do"      { /*printf("lexeme=\"%s\"\n",yytext);*/if(newline){newline=false;start=yytext;}return T_do; }
"else"    { /*printf("lexeme=\"%s\"\n",yytext);*/if(newline){newline=false;start=yytext;}return T_else; }
"fun"     { /*printf("lexeme=\"%s\"\n",yytext);*/if(newline){newline=false;start=yytext;}yylval.def="fun";return T_fun; }
"if"      { /*printf("lexeme=\"%s\"\n",yytext);*/if(newline){newline=false;start=yytext;}return T_if; }
"int"     { /*printf("lexeme=\"%s\"\n",yytext);*/if(newline){newline=false;start=yytext;}return T_int; }
"mod"     { /*printf("lexeme=\"%s\"\n",yytext);*/if(newline){newline=false;start=yytext;}yylval.op_s="mod";return T_mod; }
"not"     { /*printf("lexeme=\"%s\"\n",yytext);*/if(newline){newline=false;start=yytext;}yylval.op_s="not";return T_not; }
"nothing" { /*printf("lexeme=\"%s\"\n",yytext);*/if(newline){newline=false;start=yytext;}return T_nothing; }
"or"      { /*printf("lexeme=\"%s\"\n",yytext);*/if(newline){newline=false;start=yytext;}yylval.op_s="or";return T_or; }
"ref"     { /*printf("lexeme=\"%s\"\n",yytext);*/if(newline){newline=false;start=yytext;}return T_ref; }
"return"  { /*printf("lexeme=\"%s\"\n",yytext);*/if(newline){newline=false;start=yytext;} return T_return; }
"then"    { /*printf("lexeme=\"%s\"\n",yytext);*/if(newline){newline=false;start=yytext;}return T_then; }
"var"     { /*printf("lexeme=\"%s\"\n",yytext);*/if(newline){newline=false;start=yytext;}yylval.def="var";return T_var; }
"while"   { /*printf("lexeme=\"%s\"\n",yytext);*/if(newline){newline=false;start=yytext;}return T_while;}
{L}({L}|{D}|\_)*                                           {if(newline){newline=false;start=yytext;}/*printf("T_id lexeme=\"%s \" of length %d\n", yytext,length(yytext));*/yylval.id=(char*)malloc(strlen(yytext)+1);strcpy(yylval.id,yytext);return T_id; }
{D}+                                                       {if(newline){newline=false;start=yytext;}/*printf("lexeme=\"%s\"\n", yytext);*/yylval.num = atoi(yytext); return T_int_const; }
\'({COMMON}|\\x{HEX}|\\n|\\r|\\t|\\0|\\\\|\\'|\\\")\'      {if(newline){newline=false;start=yytext;}/*printf("lexeme=\"%s\"\n", yytext);*/yylval.var = yytext[1]; return T_char_const; } 
\"({COMMON}|\\x{HEX}|\\n|\\r|\\t|\\0|\\\\|\\'|\\\")+\"     {if(newline){newline=false;start=yytext;}/*printf("lexeme=\"%s\"\n", yytext);*/yylval.str = (char*)malloc(strlen(yytext)+1);strcpy(yylval.str,yytext); return T_string_const;}
\<\-                                                       {if(newline){newline=false;start=yytext;}/*printf("lexeme=\"%s\"\n", yytext);*/yylval.div_s = (char*)malloc(strlen(yytext)+1);strcpy(yylval.div_s,yytext); return T_arrow;}
[\(\)\{\}\[\]\,\;\:]                                       {if(newline){newline=false;start=yytext;}/*printf("lexeme=\"%s\"\n", yytext);yylval.div = yytext[0];*/ return yytext[0];}
\<\=                                                       {if(newline){newline=false;start=yytext;}/*printf("lexeme=\"%s\"\n", yytext);*/yylval.op_s = (char*)malloc(strlen(yytext)+1);strcpy(yylval.op_s,yytext); return T_lesseq; }
>=                                                         {if(newline){newline=false;start=yytext;}/*printf("lexeme=\"%s\"\n", yytext);*/yylval.op_s = (char*)malloc(strlen(yytext)+1);strcpy(yylval.op_s,yytext); return T_greateq; }
[\+\-/%*=\#\<\>]                                           {if(newline){newline=false;start=yytext;}/*printf("lexeme=\"%s\"\n", yytext);*/yylval.op = yytext[0]; return yytext[0]; }

<INITIAL>{
"$$"              BEGIN(IN_COMMENT);
}
<IN_COMMENT>{
"$$"      BEGIN(INITIAL);
[^$\n]+   
\n        linenumber++;newline=true;
}
\n                                                         { ++linenumber;newline=true;}
\$.*\n                                                     { ++linenumber;newline=true;}
{W}+                                                       { /* nothing */ }
.    {   
        std::cout << "illegal character with code " << yytext << "at line" << linenumber << "lexeme" << yytext ;           
         // exit(1);
        }
%%

