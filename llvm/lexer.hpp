#ifndef __LEXER_HPP__
#define __LEXER_HPP__

extern int linenumber;
extern char* yytext;
extern char* start;
int yylex();
void yyerror(const char *msg);

#endif