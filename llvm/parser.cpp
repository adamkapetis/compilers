/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include "lexer.hpp"
//#include "symbol.hpp"
#include "ast.hpp"


#define YYDEBUG 1
SymbolTable st;


#line 86 "parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_eof = 3,                      /* "eof"  */
  YYSYMBOL_T_and = 4,                      /* "and"  */
  YYSYMBOL_T_char = 5,                     /* "char"  */
  YYSYMBOL_T_div = 6,                      /* "div"  */
  YYSYMBOL_T_do = 7,                       /* "do"  */
  YYSYMBOL_T_else = 8,                     /* "else"  */
  YYSYMBOL_T_fun = 9,                      /* "fun"  */
  YYSYMBOL_T_if = 10,                      /* "if"  */
  YYSYMBOL_T_int = 11,                     /* "int"  */
  YYSYMBOL_T_mod = 12,                     /* "mod"  */
  YYSYMBOL_T_not = 13,                     /* "not"  */
  YYSYMBOL_T_nothing = 14,                 /* "nothing"  */
  YYSYMBOL_T_or = 15,                      /* "or"  */
  YYSYMBOL_T_ref = 16,                     /* "ref"  */
  YYSYMBOL_T_return = 17,                  /* "return"  */
  YYSYMBOL_T_then = 18,                    /* "then"  */
  YYSYMBOL_T_var = 19,                     /* "var"  */
  YYSYMBOL_T_while = 20,                   /* "while"  */
  YYSYMBOL_T_lesseq = 21,                  /* "<="  */
  YYSYMBOL_T_greateq = 22,                 /* ">="  */
  YYSYMBOL_T_arrow = 23,                   /* "<-"  */
  YYSYMBOL_T_int_const = 24,               /* T_int_const  */
  YYSYMBOL_T_char_const = 25,              /* T_char_const  */
  YYSYMBOL_T_id = 26,                      /* T_id  */
  YYSYMBOL_T_string_const = 27,            /* T_string_const  */
  YYSYMBOL_T_divider = 28,                 /* T_divider  */
  YYSYMBOL_29_ = 29,                       /* '('  */
  YYSYMBOL_30_ = 30,                       /* ')'  */
  YYSYMBOL_31_ = 31,                       /* '{'  */
  YYSYMBOL_32_ = 32,                       /* '}'  */
  YYSYMBOL_33_ = 33,                       /* '['  */
  YYSYMBOL_34_ = 34,                       /* ']'  */
  YYSYMBOL_35_ = 35,                       /* ','  */
  YYSYMBOL_36_ = 36,                       /* ':'  */
  YYSYMBOL_37_ = 37,                       /* ';'  */
  YYSYMBOL_T_operator = 38,                /* T_operator  */
  YYSYMBOL_39_ = 39,                       /* '<'  */
  YYSYMBOL_40_ = 40,                       /* '>'  */
  YYSYMBOL_41_ = 41,                       /* '#'  */
  YYSYMBOL_42_ = 42,                       /* '='  */
  YYSYMBOL_43_ = 43,                       /* '+'  */
  YYSYMBOL_44_ = 44,                       /* '-'  */
  YYSYMBOL_45_ = 45,                       /* '*'  */
  YYSYMBOL_46_ = 46,                       /* '/'  */
  YYSYMBOL_47_ = 47,                       /* '%'  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_program = 49,                   /* program  */
  YYSYMBOL_ld = 50,                        /* ld  */
  YYSYMBOL_func_def = 51,                  /* func_def  */
  YYSYMBOL_header = 52,                    /* header  */
  YYSYMBOL_fd = 53,                        /* fd  */
  YYSYMBOL_fpar_def = 54,                  /* fpar_def  */
  YYSYMBOL_td = 55,                        /* td  */
  YYSYMBOL_data_type = 56,                 /* data_type  */
  YYSYMBOL_cd = 57,                        /* cd  */
  YYSYMBOL_type = 58,                      /* type  */
  YYSYMBOL_ret_type = 59,                  /* ret_type  */
  YYSYMBOL_fpar_type = 60,                 /* fpar_type  */
  YYSYMBOL_local_def = 61,                 /* local_def  */
  YYSYMBOL_var_def = 62,                   /* var_def  */
  YYSYMBOL_stmt = 63,                      /* stmt  */
  YYSYMBOL_stmtd = 64,                     /* stmtd  */
  YYSYMBOL_block = 65,                     /* block  */
  YYSYMBOL_exprc = 66,                     /* exprc  */
  YYSYMBOL_func_call = 67,                 /* func_call  */
  YYSYMBOL_l_value = 68,                   /* l_value  */
  YYSYMBOL_expr = 69,                      /* expr  */
  YYSYMBOL_cond = 70                       /* cond  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   233

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  136

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   284


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    41,     2,    47,     2,     2,
      29,    30,    45,    43,    35,    44,     2,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    36,    37,
      39,    42,    40,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    33,     2,    34,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   108,   108,   114,   115,   118,   121,   122,   124,   125,
     131,   132,   134,   135,   138,   139,   141,   142,   145,   148,
     149,   153,   154,   157,   158,   162,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   175,   176,   179,   182,   183,
     186,   187,   190,   191,   192,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"eof\"", "\"and\"",
  "\"char\"", "\"div\"", "\"do\"", "\"else\"", "\"fun\"", "\"if\"",
  "\"int\"", "\"mod\"", "\"not\"", "\"nothing\"", "\"or\"", "\"ref\"",
  "\"return\"", "\"then\"", "\"var\"", "\"while\"", "\"<=\"", "\">=\"",
  "\"<-\"", "T_int_const", "T_char_const", "T_id", "T_string_const",
  "T_divider", "'('", "')'", "'{'", "'}'", "'['", "']'", "','", "':'",
  "';'", "T_operator", "'<'", "'>'", "'#'", "'='", "'+'", "'-'", "'*'",
  "'/'", "'%'", "$accept", "program", "ld", "func_def", "header", "fd",
  "fpar_def", "td", "data_type", "cd", "type", "ret_type", "fpar_type",
  "local_def", "var_def", "stmt", "stmtd", "block", "exprc", "func_call",
  "l_value", "expr", "cond", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-65)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -6,    -4,     6,   -65,   -65,    37,   -65,    -2,   112,    22,
     -65,   -65,   -65,   -65,   -65,    43,   -65,    41,    52,   -65,
     -65,   130,   -65,    59,    10,    54,     9,    77,   110,   162,
     110,    79,   -65,   -65,   -65,   -65,   -65,    88,    -3,   129,
     103,    60,   -65,   -65,   -65,   -65,   -65,    10,   -65,    60,
     110,   -65,   -65,   110,   189,   189,   -65,   100,    75,   137,
     189,   -65,    -1,    63,   168,   -65,   189,   189,    60,   -65,
     133,   -65,   -65,   -65,   106,    19,    62,    96,     4,     4,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   110,   110,   153,     2,   -65,   153,   -65,    56,     7,
      87,   115,   -65,   114,   135,   135,   -65,   -65,   -65,     7,
       7,     7,     7,     7,     7,     7,     7,     4,     4,   139,
      19,    19,   161,   -65,   -65,   189,   -65,   -65,   -65,   147,
     153,     7,   135,   138,   -65,   -65
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     3,     0,     1,     0,     0,     0,
      35,    23,     4,    24,     5,     0,    12,     0,     0,     8,
      12,     0,    12,     0,     0,     0,     0,     0,     0,     0,
       0,    42,    43,    37,    26,    36,    28,     0,     0,     0,
       0,     0,    15,    14,    20,    19,     7,     0,     9,     0,
       0,    45,    46,     0,     0,     0,    49,    47,     0,     0,
       0,    34,     0,     0,     0,    29,     0,     0,     0,    13,
      16,    11,     6,    16,     0,    58,     0,     0,    50,    51,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33,     0,    41,     0,    38,
       0,     0,    10,     0,    22,    18,    25,    48,    57,    55,
      56,    65,    66,    63,    64,    62,    61,    52,    53,    54,
      60,    59,    31,    32,    40,     0,    27,    44,    16,     0,
       0,    39,    21,     0,    30,    17
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -65,   -65,   -65,   167,   -65,   -65,   149,   124,   -37,   -64,
     -65,   131,   108,   -65,   -65,    -8,   -65,   170,   -65,   -21,
     -20,   -27,   -12
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     7,     3,     4,    18,    19,    23,    45,   104,
      74,    46,    71,    12,    13,    35,    21,    36,    98,    56,
      57,    58,    59
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      37,    38,    62,     1,    70,    80,     6,     1,    80,   105,
      80,    81,    73,    80,    81,    42,    81,     9,    63,    81,
      66,    43,     5,    91,    44,    15,    76,    78,    79,    10,
      67,    70,   107,    94,    92,    16,    95,    99,    75,   100,
     101,    77,    88,    89,    90,    88,    89,    90,    20,    90,
      88,    89,    90,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   132,    42,     8,    91,    80,    22,
      96,    43,    37,    38,    81,    37,    38,    24,    92,   120,
     121,    80,    25,    82,    83,   122,   124,    81,   123,    26,
      47,   125,   107,    80,    40,    41,    82,    83,   131,    81,
      91,    84,    85,    86,    87,    88,    89,    90,    64,    37,
      38,    92,    40,    49,    84,    85,    86,    87,    88,    89,
      90,    80,   134,    50,   126,    65,   108,    81,    15,    69,
      88,    89,    90,    67,    51,    52,    31,    32,    16,    53,
      28,    91,    17,   106,    27,    80,    39,    29,   128,   127,
      30,    81,    92,    54,    55,    93,    31,    32,    88,    89,
      90,    10,    33,    28,    40,    68,   103,    34,   129,   130,
      29,   133,   135,    30,    11,    48,   102,    14,    72,    31,
      32,     0,     0,     0,    10,     0,    51,    52,    31,    32,
      34,    60,    51,    52,    31,    32,     0,    60,    97,    61,
       0,     0,     0,     0,     0,    54,    55,     0,     0,     0,
       0,    54,    55,    51,    52,    31,    32,     0,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    54,    55
};

static const yytype_int16 yycheck[] =
{
      21,    21,    29,     9,    41,     6,     0,     9,     6,    73,
       6,    12,    49,     6,    12,     5,    12,    19,    30,    12,
      23,    11,    26,     4,    14,    16,    53,    54,    55,    31,
      33,    68,    30,    60,    15,    26,    37,    64,    50,    66,
      67,    53,    43,    44,    45,    43,    44,    45,    26,    45,
      43,    44,    45,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,   128,     5,    29,     4,     6,    26,
       7,    11,    93,    93,    12,    96,    96,    36,    15,    91,
      92,     6,    30,    21,    22,    93,    30,    12,    96,    37,
      36,    35,    30,     6,    35,    36,    21,    22,   125,    12,
       4,    39,    40,    41,    42,    43,    44,    45,    29,   130,
     130,    15,    35,    36,    39,    40,    41,    42,    43,    44,
      45,     6,   130,    13,    37,    37,    30,    12,    16,    26,
      43,    44,    45,    33,    24,    25,    26,    27,    26,    29,
      10,     4,    30,    37,    20,     6,    22,    17,    34,    34,
      20,    12,    15,    43,    44,    18,    26,    27,    43,    44,
      45,    31,    32,    10,    35,    36,    33,    37,    33,     8,
      17,    24,    34,    20,     7,    26,    68,     7,    47,    26,
      27,    -1,    -1,    -1,    31,    -1,    24,    25,    26,    27,
      37,    29,    24,    25,    26,    27,    -1,    29,    30,    37,
      -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,
      -1,    43,    44,    24,    25,    26,    27,    -1,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    49,    51,    52,    26,     0,    50,    29,    19,
      31,    51,    61,    62,    65,    16,    26,    30,    53,    54,
      26,    64,    26,    55,    36,    30,    37,    55,    10,    17,
      20,    26,    27,    32,    37,    63,    65,    67,    68,    55,
      35,    36,     5,    11,    14,    56,    59,    36,    54,    36,
      13,    24,    25,    29,    43,    44,    67,    68,    69,    70,
      29,    37,    69,    70,    29,    37,    23,    33,    36,    26,
      56,    60,    59,    56,    58,    70,    69,    70,    69,    69,
       6,    12,    21,    22,    39,    40,    41,    42,    43,    44,
      45,     4,    15,    18,    69,    37,     7,    30,    66,    69,
      69,    69,    60,    33,    57,    57,    37,    30,    30,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      70,    70,    63,    63,    30,    35,    37,    34,    34,    33,
       8,    69,    57,    24,    63,    34
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    52,    52,    53,    53,
      54,    54,    55,    55,    56,    56,    57,    57,    58,    59,
      59,    60,    60,    61,    61,    62,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    64,    64,    65,    66,    66,
      67,    67,    68,    68,    68,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     7,     6,     1,     3,
       5,     4,     0,     3,     1,     1,     0,     4,     2,     1,
       1,     4,     2,     1,     1,     6,     1,     4,     1,     2,
       6,     4,     4,     3,     2,     0,     2,     3,     1,     3,
       4,     3,     1,     1,     4,     1,     1,     1,     3,     1,
       2,     2,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: func_def  */
#line 108 "parser.y"
                                            { std::cout << "AST : " << *(yyvsp[0].function) << std::endl ;
                                            (yyvsp[0].function)->sem(); 
                                            (yyvsp[0].function)->llvm_compile_and_dump();
                                            //delete $1;
                                            }
#line 1252 "parser.cpp"
    break;

  case 3: /* ld: %empty  */
#line 114 "parser.y"
                                            { (yyval.deflist)=new Def_list(); }
#line 1258 "parser.cpp"
    break;

  case 4: /* ld: ld local_def  */
#line 115 "parser.y"
                                            { (yyvsp[-1].deflist)->append((yyvsp[0].local_def));(yyval.deflist)=(yyvsp[-1].deflist); }
#line 1264 "parser.cpp"
    break;

  case 5: /* func_def: header ld block  */
#line 118 "parser.y"
                                            { (yyval.function)=new Function((yyvsp[-2].header),(yyvsp[-1].deflist),(yyvsp[0].blk)); }
#line 1270 "parser.cpp"
    break;

  case 6: /* header: "fun" T_id '(' fd ')' ':' ret_type  */
#line 121 "parser.y"
                                            { (yyval.header)= new Header(new Id((yyvsp[-5].id)),new Type((yyvsp[0].dtype),new Dims()),(yyvsp[-3].fpar_list)); }
#line 1276 "parser.cpp"
    break;

  case 7: /* header: "fun" T_id '(' ')' ':' ret_type  */
#line 122 "parser.y"
                                            { (yyval.header)= new Header(new Id((yyvsp[-4].id)),new Type((yyvsp[0].dtype),new Dims())); }
#line 1282 "parser.cpp"
    break;

  case 8: /* fd: fpar_def  */
#line 124 "parser.y"
                                            { (yyval.fpar_list)=new Fpar_list((yyvsp[0].fpar_def)); }
#line 1288 "parser.cpp"
    break;

  case 9: /* fd: fd ';' fpar_def  */
#line 125 "parser.y"
                                            { (yyvsp[-2].fpar_list)->append((yyvsp[0].fpar_def));(yyval.fpar_list)=(yyvsp[-2].fpar_list); }
#line 1294 "parser.cpp"
    break;

  case 10: /* fpar_def: "ref" T_id td ':' fpar_type  */
#line 131 "parser.y"
                                            { (yyvsp[-2].id_list)->append(new Id((yyvsp[-3].id)));(yyval.fpar_def)=new Fpar_def((yyvsp[-2].id_list),(yyvsp[0].type),true); }
#line 1300 "parser.cpp"
    break;

  case 11: /* fpar_def: T_id td ':' fpar_type  */
#line 132 "parser.y"
                                            { (yyvsp[-2].id_list)->append(new Id((yyvsp[-3].id)));(yyval.fpar_def)=new Fpar_def((yyvsp[-2].id_list),(yyvsp[0].type)); }
#line 1306 "parser.cpp"
    break;

  case 12: /* td: %empty  */
#line 134 "parser.y"
                                            { /*std::cout<<"No new id on list\n" ;*/(yyval.id_list)=new Id_list(); }
#line 1312 "parser.cpp"
    break;

  case 13: /* td: td ',' T_id  */
#line 135 "parser.y"
                                            { /*std::cout<<"new id on list\n"    ;*/(yyvsp[-2].id_list)->append(new Id((yyvsp[0].id)));(yyval.id_list)=(yyvsp[-2].id_list); }
#line 1318 "parser.cpp"
    break;

  case 14: /* data_type: "int"  */
#line 138 "parser.y"
                                            { (yyval.dtype)=Type_int; }
#line 1324 "parser.cpp"
    break;

  case 15: /* data_type: "char"  */
#line 139 "parser.y"
                                            { (yyval.dtype)=Type_char; }
#line 1330 "parser.cpp"
    break;

  case 16: /* cd: %empty  */
#line 141 "parser.y"
                                            { (yyval.dlist) = new Dims(); }
#line 1336 "parser.cpp"
    break;

  case 17: /* cd: cd '[' T_int_const ']'  */
#line 142 "parser.y"
                                            { /*std::cout << "number" <<$3 ;*/(yyvsp[-3].dlist)->append((yyvsp[-1].num)); (yyval.dlist)=(yyvsp[-3].dlist); }
#line 1342 "parser.cpp"
    break;

  case 18: /* type: data_type cd  */
#line 145 "parser.y"
                                            { (yyval.type) = new Type((yyvsp[-1].dtype),(yyvsp[0].dlist)); }
#line 1348 "parser.cpp"
    break;

  case 19: /* ret_type: data_type  */
#line 148 "parser.y"
                                            { (yyval.dtype)=(yyvsp[0].dtype); }
#line 1354 "parser.cpp"
    break;

  case 20: /* ret_type: "nothing"  */
#line 149 "parser.y"
                                            { (yyval.dtype)=Type_void; }
#line 1360 "parser.cpp"
    break;

  case 21: /* fpar_type: data_type '[' ']' cd  */
#line 153 "parser.y"
                                            { (yyvsp[0].dlist)->append(0);(yyval.type) = new Type((yyvsp[-3].dtype),(yyvsp[0].dlist)); }
#line 1366 "parser.cpp"
    break;

  case 22: /* fpar_type: data_type cd  */
#line 154 "parser.y"
                                            { (yyval.type) = new Type((yyvsp[-1].dtype),(yyvsp[0].dlist)); }
#line 1372 "parser.cpp"
    break;

  case 23: /* local_def: func_def  */
#line 157 "parser.y"
                                            { (yyval.local_def)=(yyvsp[0].function); }
#line 1378 "parser.cpp"
    break;

  case 24: /* local_def: var_def  */
#line 158 "parser.y"
                                            { (yyval.local_def)=(yyvsp[0].var_def); }
#line 1384 "parser.cpp"
    break;

  case 25: /* var_def: "var" T_id td ':' type ';'  */
#line 162 "parser.y"
                                            { /*std::cout <<"printing a variable: "<<$1 << $2 ;*/(yyvsp[-3].id_list)->append(new Id((yyvsp[-4].id)));(yyval.var_def)=new Var_def((yyvsp[-3].id_list),(yyvsp[-1].type));/*std::cout << "AST: " << *$$ <<" type "<< *$5 << std::endl;*/ }
#line 1390 "parser.cpp"
    break;

  case 26: /* stmt: ';'  */
#line 165 "parser.y"
                                            { (yyval.stmt)=new End();}
#line 1396 "parser.cpp"
    break;

  case 27: /* stmt: l_value "<-" expr ';'  */
#line 166 "parser.y"
                                            { (yyval.stmt)=new Valuation((yyvsp[-3].l_value),(yyvsp[-1].expr));/* std::cout << *$$;      */}
#line 1402 "parser.cpp"
    break;

  case 28: /* stmt: block  */
#line 167 "parser.y"
                                            { (yyval.stmt)=(yyvsp[0].blk);                        }
#line 1408 "parser.cpp"
    break;

  case 29: /* stmt: func_call ';'  */
#line 168 "parser.y"
                                            { (yyval.stmt)=(yyvsp[-1].func_call);                        }
#line 1414 "parser.cpp"
    break;

  case 30: /* stmt: "if" cond "then" stmt "else" stmt  */
#line 169 "parser.y"
                                            { (yyval.stmt)=new If_then_else((yyvsp[-4].cond),(yyvsp[-2].stmt),(yyvsp[0].stmt));}
#line 1420 "parser.cpp"
    break;

  case 31: /* stmt: "if" cond "then" stmt  */
#line 170 "parser.y"
                                            { (yyval.stmt)=new If_then_else((yyvsp[-2].cond),(yyvsp[0].stmt));   }
#line 1426 "parser.cpp"
    break;

  case 32: /* stmt: "while" cond "do" stmt  */
#line 171 "parser.y"
                                            { (yyval.stmt)=new While_stmt((yyvsp[-2].cond),(yyvsp[0].stmt));     }
#line 1432 "parser.cpp"
    break;

  case 33: /* stmt: "return" expr ';'  */
#line 172 "parser.y"
                                            { (yyval.stmt)=new Return_stmt((yyvsp[-1].expr));       }
#line 1438 "parser.cpp"
    break;

  case 34: /* stmt: "return" ';'  */
#line 173 "parser.y"
                                            { (yyval.stmt)=new Return_stmt();         }
#line 1444 "parser.cpp"
    break;

  case 35: /* stmtd: %empty  */
#line 175 "parser.y"
                            { /*std::cout<<"created new block \n" ;*/(yyval.blk) = new Block(); }
#line 1450 "parser.cpp"
    break;

  case 36: /* stmtd: stmtd stmt  */
#line 176 "parser.y"
                            { /*std::cout << "appended to block stmt:" << *$2<<std::endl;*/ (yyvsp[-1].blk)->append((yyvsp[0].stmt)); (yyval.blk)=(yyvsp[-1].blk); }
#line 1456 "parser.cpp"
    break;

  case 37: /* block: '{' stmtd '}'  */
#line 179 "parser.y"
                            { (yyval.blk)=(yyvsp[-1].blk); }
#line 1462 "parser.cpp"
    break;

  case 38: /* exprc: expr  */
#line 182 "parser.y"
                            { (yyval.exprc) = new Exprc((yyvsp[0].expr)); }
#line 1468 "parser.cpp"
    break;

  case 39: /* exprc: exprc ',' expr  */
#line 183 "parser.y"
                            { (yyvsp[-2].exprc)->append((yyvsp[0].expr)); (yyval.exprc) = (yyvsp[-2].exprc); }
#line 1474 "parser.cpp"
    break;

  case 40: /* func_call: T_id '(' exprc ')'  */
#line 186 "parser.y"
                            { std::cout<<"calling function "<<(yyvsp[-3].id) <<std::endl ;(yyval.func_call) = new Func_call(new Id((yyvsp[-3].id)),(yyvsp[-1].exprc)); }
#line 1480 "parser.cpp"
    break;

  case 41: /* func_call: T_id '(' ')'  */
#line 187 "parser.y"
                            { (yyval.func_call) = new Func_call(new Id((yyvsp[-2].id))); }
#line 1486 "parser.cpp"
    break;

  case 42: /* l_value: T_id  */
#line 190 "parser.y"
                        {(yyval.l_value)=new L_value(new Id((yyvsp[0].id)));}
#line 1492 "parser.cpp"
    break;

  case 43: /* l_value: T_string_const  */
#line 191 "parser.y"
                        {(yyval.l_value)=new L_value(new String_const((yyvsp[0].str)));}
#line 1498 "parser.cpp"
    break;

  case 44: /* l_value: l_value '[' expr ']'  */
#line 192 "parser.y"
                        { (yyvsp[-3].l_value)->append_expr((yyvsp[-1].expr));(yyval.l_value)=(yyvsp[-3].l_value); }
#line 1504 "parser.cpp"
    break;

  case 45: /* expr: T_int_const  */
#line 196 "parser.y"
                        { (yyval.expr) = new Int_const((yyvsp[0].num)); }
#line 1510 "parser.cpp"
    break;

  case 46: /* expr: T_char_const  */
#line 197 "parser.y"
                        { (yyval.expr) = new Char_const((yyvsp[0].var)); }
#line 1516 "parser.cpp"
    break;

  case 47: /* expr: l_value  */
#line 198 "parser.y"
                        { (yyval.expr)=(yyvsp[0].l_value); }
#line 1522 "parser.cpp"
    break;

  case 48: /* expr: '(' expr ')'  */
#line 199 "parser.y"
                        { (yyval.expr) = (yyvsp[-1].expr);  }
#line 1528 "parser.cpp"
    break;

  case 49: /* expr: func_call  */
#line 200 "parser.y"
                        { (yyval.expr) = (yyvsp[0].func_call);  }
#line 1534 "parser.cpp"
    break;

  case 50: /* expr: '+' expr  */
#line 201 "parser.y"
                        { (yyval.expr) = new BinOp((yyvsp[0].expr),(yyvsp[-1].op)); }
#line 1540 "parser.cpp"
    break;

  case 51: /* expr: '-' expr  */
#line 202 "parser.y"
                        { (yyval.expr) = new BinOp((yyvsp[0].expr),(yyvsp[-1].op)); }
#line 1546 "parser.cpp"
    break;

  case 52: /* expr: expr '+' expr  */
#line 203 "parser.y"
                        { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[-1].op), (yyvsp[0].expr)); /*$$->sem();*/ }
#line 1552 "parser.cpp"
    break;

  case 53: /* expr: expr '-' expr  */
#line 204 "parser.y"
                        { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[-1].op), (yyvsp[0].expr));  }
#line 1558 "parser.cpp"
    break;

  case 54: /* expr: expr '*' expr  */
#line 205 "parser.y"
                        { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[-1].op), (yyvsp[0].expr));  }
#line 1564 "parser.cpp"
    break;

  case 55: /* expr: expr "div" expr  */
#line 206 "parser.y"
                        { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[-1].op_s), (yyvsp[0].expr));  }
#line 1570 "parser.cpp"
    break;

  case 56: /* expr: expr "mod" expr  */
#line 207 "parser.y"
                        { (yyval.expr) = new BinOp((yyvsp[-2].expr), (yyvsp[-1].op_s), (yyvsp[0].expr));  }
#line 1576 "parser.cpp"
    break;

  case 57: /* cond: '(' cond ')'  */
#line 210 "parser.y"
                        { (yyval.cond) = (yyvsp[-1].cond); }
#line 1582 "parser.cpp"
    break;

  case 58: /* cond: "not" cond  */
#line 211 "parser.y"
                        { (yyval.cond) = new LogOp((yyvsp[0].cond), (yyvsp[-1].op_s)); }
#line 1588 "parser.cpp"
    break;

  case 59: /* cond: cond "or" cond  */
#line 212 "parser.y"
                        { (yyval.cond) = new LogOp((yyvsp[-2].cond), (yyvsp[-1].op_s), (yyvsp[0].cond)); }
#line 1594 "parser.cpp"
    break;

  case 60: /* cond: cond "and" cond  */
#line 213 "parser.y"
                        { (yyval.cond) = new LogOp((yyvsp[-2].cond), (yyvsp[-1].op_s), (yyvsp[0].cond)); }
#line 1600 "parser.cpp"
    break;

  case 61: /* cond: expr '=' expr  */
#line 214 "parser.y"
                        { (yyval.cond) = new ComOp((yyvsp[-2].expr), (yyvsp[-1].op), (yyvsp[0].expr)); }
#line 1606 "parser.cpp"
    break;

  case 62: /* cond: expr '#' expr  */
#line 215 "parser.y"
                        { (yyval.cond) = new ComOp((yyvsp[-2].expr), (yyvsp[-1].op), (yyvsp[0].expr)); }
#line 1612 "parser.cpp"
    break;

  case 63: /* cond: expr '<' expr  */
#line 216 "parser.y"
                        { (yyval.cond) = new ComOp((yyvsp[-2].expr), (yyvsp[-1].op), (yyvsp[0].expr)); }
#line 1618 "parser.cpp"
    break;

  case 64: /* cond: expr '>' expr  */
#line 217 "parser.y"
                        { (yyval.cond) = new ComOp((yyvsp[-2].expr), (yyvsp[-1].op), (yyvsp[0].expr)); }
#line 1624 "parser.cpp"
    break;

  case 65: /* cond: expr "<=" expr  */
#line 218 "parser.y"
                        { (yyval.cond) = new ComOp((yyvsp[-2].expr), (yyvsp[-1].op_s), (yyvsp[0].expr)); }
#line 1630 "parser.cpp"
    break;

  case 66: /* cond: expr ">=" expr  */
#line 219 "parser.y"
                        { (yyval.cond) = new ComOp((yyvsp[-2].expr), (yyvsp[-1].op_s), (yyvsp[0].expr)); }
#line 1636 "parser.cpp"
    break;


#line 1640 "parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 222 "parser.y"


void yyerror(const char *msg) {
    printf("Syntax error:%s at line :%d, token : %s\n",msg,linenumber,start);
    exit(42);
}

int main() {
    /* #ifdef YYDEBUG
    yydebug = 1;
    #endif */
    int res = yyparse();
    if(res == 0) printf("Successful parsing\n");
    return res;
}
