# Compilers

### Lexical Analysis
The lexical analysis is performed by going to the lexer folder and run these commands:
Command to create the lexer.c file:
```
    flex -o lexer.c lexer.l
```
Command to create the lexer executable:
```
    gcc -o lexer lexer.c 
```    
Command to run lexer on a test2 program:
```
    ./lexer < ../grace_programs/test2.grc
```



