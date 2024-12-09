#!/bin/bash

./gracec ../grace_programs/$1.grc >> /dev/null
cd ../grace_programs
clang $1.asm ../llvm/libgrc.a -no-pie -o $1.out
./$1.out
