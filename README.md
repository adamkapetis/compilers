# compilers
Command to create the lexer.c file:
flex -o lexer.c lexer.l
Command to create the lexer executable:


\'({L}|{D}|\\x{HEX}|\\n|\\r|\\t|\\0|\\|\\'|\\\")\'         { return T_char_const; } 