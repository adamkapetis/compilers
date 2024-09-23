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

### LLVM

Download LLVM-16
```
    sudo apt install llvm-16
```

Set LLVM 16 as the default version
```
    sudo update-alternatives --install /usr/bin/llvm-config llvm-config /usr/bin/llvm-config-16 100
```

When creating the Makefile don't nail your parameters. Use `llvm-config` so that you can use it regardless of the system:
```
    CXXFLAGS=-g `$(LLVMCONFIG) --cxxflags` -std=c++20 -fexceptions
    LDFLAGS=`$(LLVMCONFIG) --ldflags --system-libs --libs all`
```


