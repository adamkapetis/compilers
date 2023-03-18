# compilers
Command to create the lexer.c file:
flex -o lexer.c lexer.l
Command to create the lexer executable:
gcc -o lexer lexer.c 
Command to run lexer on a test2 program:
./lexer < ../grace_programs/test2.grc



\$\$({DOLLAR}*|{DOLLAR}*\n)+\$\$                        { /*nothing*/}
<INITIAL>{
"/*"              BEGIN(IN_COMMENT);
}
<IN_COMMENT>{
"*/"      BEGIN(INITIAL);
[^*\n]+   // eat comment in chunks
"*"       // eat the lone star
\n        yylineno++;
}