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

To test that everything runs use `make` and then:
``` ./gracec ../grace_programs/hello.grc```

### Run time Libray
You have to go to llvm/lib and run `make` and then take the libgrc.a file and put it in the main llvm folder. 

### Assembly and IMM files
To create the assembly and IMM files you have to run this command:

``` 
    ./gracec ../grace_programs/test.grc
```
and two files in the same directory will be created with the following names: 
test.imm and test.asm
Then to create an executable you have to compile the assembly with the following:
``` 
    clang test.asm ../llvm/libgrc.a -no-pie -o test.out
```
A .out file will be created and you can run it with:
```
    ./test.out
```

- For example to run the `hello.grc`:
```shell
    # Inside the llvm directory:
    ./gracec ../grace_programs/hello.grc
    # Inside the grace_programs directory:
    clang hello.asm ../llvm/libgrc.a -no-pie -o hello.out
    ./hello.out
```
- Or use our run.sh script:
```shell
    ./run.sh hello
```
