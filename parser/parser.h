/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_eof = 258,
     T_and = 259,
     T_char = 260,
     T_div = 261,
     T_do = 262,
     T_else = 263,
     T_fun = 264,
     T_if = 265,
     T_int = 266,
     T_mod = 267,
     T_not = 268,
     T_nothing = 269,
     T_or = 270,
     T_ref = 271,
     T_return = 272,
     T_then = 273,
     T_var = 274,
     T_while = 275,
     T_lesseq = 276,
     T_greateq = 277,
     T_arrow = 278,
     T_int_const = 279,
     T_char_const = 280,
     T_id = 281,
     T_string_const = 282,
     T_divider = 283,
     T_operator = 284
   };
#endif
/* Tokens.  */
#define T_eof 258
#define T_and 259
#define T_char 260
#define T_div 261
#define T_do 262
#define T_else 263
#define T_fun 264
#define T_if 265
#define T_int 266
#define T_mod 267
#define T_not 268
#define T_nothing 269
#define T_or 270
#define T_ref 271
#define T_return 272
#define T_then 273
#define T_var 274
#define T_while 275
#define T_lesseq 276
#define T_greateq 277
#define T_arrow 278
#define T_int_const 279
#define T_char_const 280
#define T_id 281
#define T_string_const 282
#define T_divider 283
#define T_operator 284




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

