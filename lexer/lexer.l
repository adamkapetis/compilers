%option noyywrap

%{
#define T_eof          0
#define T_and          1001
#define T_char         1002
#define T_div          1003
#define T_do           1004
#define T_else         1005
#define T_fun          1006
#define T_if           1007
#define T_int          1008
#define T_mod          1009
#define T_not          1010
#define T_nothing      1011
#define T_or           1012
#define T_ref          1013
#define T_return       1014
#define T_then         1015
#define T_var          1016
#define T_while        1017
#define T_int_const    1018
#define T_char_const   1019
#define T_id           1020
#define T_string_const 1021
#define T_divider      1022
#define T_operator     1023
int linenumber=1;
%}


L [a-zA-Z]
D [0-9]
W [ \t\r\n]
A [\\x[a-zA-Z0-9]{2}]

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
\'({L}|{D}|{A}|\\n|\\r|\\t|\\0|\\|\\'|\\\")\'              { return T_char_const; }
\"({L}{D}{A}\n\r\t\0\\\'\")+\"                             { return T_string_const;}
[\+\-/%*=\#\<\(<=)(>=)]                                    { return T_operator; }
    [\(\)\[\]\{\}\,\;\:(<\-)]                              { return T_divider; }
\n                                                         { ++linenumber;}
$$[(.*)(.*\n)]+$$                                          { /*nothing*/}
\$.*\n                                                     { ++linenumber;}
{W}+                                                       { /* nothing */ }


.       { fprintf(stderr, "Illegal character with code %d",
                  yytext[0]);
          exit(1);
        }

%%

#ifdef yyFlexLexer
int main () {
  yyFlexLexer lexer;
  int token;
  do {
    token = lexer.yylex();
    printf("token=%d, lexeme=\"%s\"\n", token, lexer.YYText());
  } while (token != T_eof);
}
#else
int main () {
  int token;
  do {
    token = yylex();
    printf("token=%d, lexeme=\"%s\"\n", token, yytext);
  } while (token != T_eof);
}
#endif
