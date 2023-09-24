extern int linenumber;
extern char* yytext;
extern char* start;
int yylex();
void yyerror(const char *msg);
