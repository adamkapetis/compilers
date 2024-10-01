/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_eof = 258,                   /* "eof"  */
    T_and = 259,                   /* "and"  */
    T_char = 260,                  /* "char"  */
    T_div = 261,                   /* "div"  */
    T_do = 262,                    /* "do"  */
    T_else = 263,                  /* "else"  */
    T_fun = 264,                   /* "fun"  */
    T_if = 265,                    /* "if"  */
    T_int = 266,                   /* "int"  */
    T_mod = 267,                   /* "mod"  */
    T_not = 268,                   /* "not"  */
    T_nothing = 269,               /* "nothing"  */
    T_or = 270,                    /* "or"  */
    T_ref = 271,                   /* "ref"  */
    T_return = 272,                /* "return"  */
    T_then = 273,                  /* "then"  */
    T_var = 274,                   /* "var"  */
    T_while = 275,                 /* "while"  */
    T_lesseq = 276,                /* "<="  */
    T_greateq = 277,               /* ">="  */
    T_arrow = 278,                 /* "<-"  */
    T_int_const = 279,             /* T_int_const  */
    T_char_const = 280,            /* T_char_const  */
    T_id = 281,                    /* T_id  */
    T_string_const = 282,          /* T_string_const  */
    T_divider = 283,               /* T_divider  */
    T_operator = 284               /* T_operator  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 76 "parser.y"

    Function * function;
    Fpar_list * fpar_list;
    Fpar_def * fpar_def;
    Header * header;
    Func_def * func_def;
    Var_def * var_def;
    L_def * local_def;
    Def_list * deflist;
    Type * type;
    Id_list * id_list;
    Dims *dlist;
    Dtype dtype;
    If_then_else* if_then_else;
    Stmt *stmt;
    Expr *expr;
    Cond *cond;
    Block *blk;
    L_value* l_value;
    Func_call* func_call;
    Exprc* exprc;
//    Id * ident;
    char var;
    int num;
    char op;
    char div;
    char* def;
    char* op_s;
    char* div_s;
    char* str;
    char* id;

#line 126 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
