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
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"

#include "ast.h"
#include "yacc.tab.h"
#include <iostream>
#include <memory>
#include <limits.h>

int yylex(YYSTYPE *yylval, YYLTYPE *yylloc);

void yyerror(YYLTYPE *locp, const char* s) {
    std::cerr << "Parser Error at line " << locp->first_line << " column " << locp->first_column << ": " << s << std::endl;
}

using namespace ast;

#line 87 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"

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

#include "yacc.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SHOW = 3,                       /* SHOW  */
  YYSYMBOL_TABLES = 4,                     /* TABLES  */
  YYSYMBOL_CREATE = 5,                     /* CREATE  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_DROP = 7,                       /* DROP  */
  YYSYMBOL_DESC = 8,                       /* DESC  */
  YYSYMBOL_INSERT = 9,                     /* INSERT  */
  YYSYMBOL_INTO = 10,                      /* INTO  */
  YYSYMBOL_VALUES = 11,                    /* VALUES  */
  YYSYMBOL_DELETE = 12,                    /* DELETE  */
  YYSYMBOL_FROM = 13,                      /* FROM  */
  YYSYMBOL_ASC = 14,                       /* ASC  */
  YYSYMBOL_ORDER = 15,                     /* ORDER  */
  YYSYMBOL_BY = 16,                        /* BY  */
  YYSYMBOL_WHERE = 17,                     /* WHERE  */
  YYSYMBOL_UPDATE = 18,                    /* UPDATE  */
  YYSYMBOL_SET = 19,                       /* SET  */
  YYSYMBOL_SELECT = 20,                    /* SELECT  */
  YYSYMBOL_INT = 21,                       /* INT  */
  YYSYMBOL_CHAR = 22,                      /* CHAR  */
  YYSYMBOL_FLOAT = 23,                     /* FLOAT  */
  YYSYMBOL_INDEX = 24,                     /* INDEX  */
  YYSYMBOL_AND = 25,                       /* AND  */
  YYSYMBOL_JOIN = 26,                      /* JOIN  */
  YYSYMBOL_EXIT = 27,                      /* EXIT  */
  YYSYMBOL_HELP = 28,                      /* HELP  */
  YYSYMBOL_TXN_BEGIN = 29,                 /* TXN_BEGIN  */
  YYSYMBOL_TXN_COMMIT = 30,                /* TXN_COMMIT  */
  YYSYMBOL_TXN_ABORT = 31,                 /* TXN_ABORT  */
  YYSYMBOL_TXN_ROLLBACK = 32,              /* TXN_ROLLBACK  */
  YYSYMBOL_ORDER_BY = 33,                  /* ORDER_BY  */
  YYSYMBOL_ENABLE_NESTLOOP = 34,           /* ENABLE_NESTLOOP  */
  YYSYMBOL_ENABLE_SORTMERGE = 35,          /* ENABLE_SORTMERGE  */
  YYSYMBOL_LEQ = 36,                       /* LEQ  */
  YYSYMBOL_NEQ = 37,                       /* NEQ  */
  YYSYMBOL_GEQ = 38,                       /* GEQ  */
  YYSYMBOL_T_EOF = 39,                     /* T_EOF  */
  YYSYMBOL_MAX = 40,                       /* MAX  */
  YYSYMBOL_MIN = 41,                       /* MIN  */
  YYSYMBOL_SUM = 42,                       /* SUM  */
  YYSYMBOL_AVG = 43,                       /* AVG  */
  YYSYMBOL_COUNT = 44,                     /* COUNT  */
  YYSYMBOL_AS = 45,                        /* AS  */
  YYSYMBOL_GROUP = 46,                     /* GROUP  */
  YYSYMBOL_HAVING = 47,                    /* HAVING  */
  YYSYMBOL_LIMIT = 48,                     /* LIMIT  */
  YYSYMBOL_IDENTIFIER = 49,                /* IDENTIFIER  */
  YYSYMBOL_VALUE_STRING = 50,              /* VALUE_STRING  */
  YYSYMBOL_VALUE_INT = 51,                 /* VALUE_INT  */
  YYSYMBOL_VALUE_FLOAT = 52,               /* VALUE_FLOAT  */
  YYSYMBOL_VALUE_BOOL = 53,                /* VALUE_BOOL  */
  YYSYMBOL_EXPLAIN = 54,                   /* EXPLAIN  */
  YYSYMBOL_STATIC_CHECKPOINT = 55,         /* STATIC_CHECKPOINT  */
  YYSYMBOL_CRASH = 56,                     /* CRASH  */
  YYSYMBOL_57_ = 57,                       /* ';'  */
  YYSYMBOL_58_ = 58,                       /* '='  */
  YYSYMBOL_59_ = 59,                       /* '('  */
  YYSYMBOL_60_ = 60,                       /* ')'  */
  YYSYMBOL_61_ = 61,                       /* ','  */
  YYSYMBOL_62_ = 62,                       /* '.'  */
  YYSYMBOL_63_ = 63,                       /* '<'  */
  YYSYMBOL_64_ = 64,                       /* '>'  */
  YYSYMBOL_65_ = 65,                       /* '+'  */
  YYSYMBOL_66_ = 66,                       /* '*'  */
  YYSYMBOL_YYACCEPT = 67,                  /* $accept  */
  YYSYMBOL_start = 68,                     /* start  */
  YYSYMBOL_stmt = 69,                      /* stmt  */
  YYSYMBOL_txnStmt = 70,                   /* txnStmt  */
  YYSYMBOL_dbStmt = 71,                    /* dbStmt  */
  YYSYMBOL_setStmt = 72,                   /* setStmt  */
  YYSYMBOL_sysStmt = 73,                   /* sysStmt  */
  YYSYMBOL_ddl = 74,                       /* ddl  */
  YYSYMBOL_dml = 75,                       /* dml  */
  YYSYMBOL_limit_clause = 76,              /* limit_clause  */
  YYSYMBOL_optGroupByClause = 77,          /* optGroupByClause  */
  YYSYMBOL_optHavingClause = 78,           /* optHavingClause  */
  YYSYMBOL_fieldList = 79,                 /* fieldList  */
  YYSYMBOL_colNameList = 80,               /* colNameList  */
  YYSYMBOL_field = 81,                     /* field  */
  YYSYMBOL_type = 82,                      /* type  */
  YYSYMBOL_valueList = 83,                 /* valueList  */
  YYSYMBOL_value = 84,                     /* value  */
  YYSYMBOL_condition = 85,                 /* condition  */
  YYSYMBOL_optWhereClause = 86,            /* optWhereClause  */
  YYSYMBOL_whereClause = 87,               /* whereClause  */
  YYSYMBOL_col = 88,                       /* col  */
  YYSYMBOL_colList = 89,                   /* colList  */
  YYSYMBOL_op = 90,                        /* op  */
  YYSYMBOL_expr = 91,                      /* expr  */
  YYSYMBOL_setClauses = 92,                /* setClauses  */
  YYSYMBOL_setClause = 93,                 /* setClause  */
  YYSYMBOL_selector = 94,                  /* selector  */
  YYSYMBOL_aggCol = 95,                    /* aggCol  */
  YYSYMBOL_tableList = 96,                 /* tableList  */
  YYSYMBOL_opt_order_clause = 97,          /* opt_order_clause  */
  YYSYMBOL_order_clauses = 98,             /* order_clauses  */
  YYSYMBOL_order_clause = 99,              /* order_clause  */
  YYSYMBOL_opt_asc_desc = 100,             /* opt_asc_desc  */
  YYSYMBOL_set_knob_type = 101,            /* set_knob_type  */
  YYSYMBOL_tbName = 102,                   /* tbName  */
  YYSYMBOL_colName = 103,                  /* colName  */
  YYSYMBOL_alias = 104                     /* alias  */
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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  56
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   204

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  196

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   311


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      59,    60,    66,    65,    61,     2,    62,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    57,
      63,    58,    64,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    65,    65,    70,    75,    80,    88,    89,    90,    91,
      92,    93,    97,   101,   105,   109,   113,   120,   124,   128,
     138,   145,   152,   156,   160,   164,   168,   175,   179,   183,
     187,   194,   199,   206,   209,   216,   217,   224,   228,   235,
     239,   246,   253,   257,   261,   268,   272,   279,   283,   287,
     291,   298,   305,   306,   313,   317,   324,   328,   332,   339,
     343,   350,   354,   358,   362,   366,   370,   377,   381,   388,
     392,   399,   403,   407,   414,   418,   422,   426,   430,   434,
     438,   442,   446,   450,   454,   458,   462,   466,   473,   477,
     481,   488,   492,   496,   500,   507,   514,   515,   516,   520,
     521,   524,   526,   528
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SHOW", "TABLES",
  "CREATE", "TABLE", "DROP", "DESC", "INSERT", "INTO", "VALUES", "DELETE",
  "FROM", "ASC", "ORDER", "BY", "WHERE", "UPDATE", "SET", "SELECT", "INT",
  "CHAR", "FLOAT", "INDEX", "AND", "JOIN", "EXIT", "HELP", "TXN_BEGIN",
  "TXN_COMMIT", "TXN_ABORT", "TXN_ROLLBACK", "ORDER_BY", "ENABLE_NESTLOOP",
  "ENABLE_SORTMERGE", "LEQ", "NEQ", "GEQ", "T_EOF", "MAX", "MIN", "SUM",
  "AVG", "COUNT", "AS", "GROUP", "HAVING", "LIMIT", "IDENTIFIER",
  "VALUE_STRING", "VALUE_INT", "VALUE_FLOAT", "VALUE_BOOL", "EXPLAIN",
  "STATIC_CHECKPOINT", "CRASH", "';'", "'='", "'('", "')'", "','", "'.'",
  "'<'", "'>'", "'+'", "'*'", "$accept", "start", "stmt", "txnStmt",
  "dbStmt", "setStmt", "sysStmt", "ddl", "dml", "limit_clause",
  "optGroupByClause", "optHavingClause", "fieldList", "colNameList",
  "field", "type", "valueList", "value", "condition", "optWhereClause",
  "whereClause", "col", "colList", "op", "expr", "setClauses", "setClause",
  "selector", "aggCol", "tableList", "opt_order_clause", "order_clauses",
  "order_clause", "opt_asc_desc", "set_knob_type", "tbName", "colName",
  "alias", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-96)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-102)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      69,     1,    -4,     7,   -38,    14,    15,   -38,   -26,    62,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   117,   -96,    32,
      -1,   -96,   -96,   -96,   -96,   -96,   -96,   -96,    35,   -38,
     -38,   -96,   -38,   -38,   -96,   -96,   -38,   -38,    38,   -96,
     -96,     8,     9,    16,    31,    48,    53,    65,   -96,   -96,
      70,   120,   -96,    68,   -96,   -96,   -96,   -96,   -38,    77,
      79,   -96,    80,   123,   145,    91,   110,   102,   102,   102,
     102,    75,   102,   -38,    91,   -96,    91,    91,    91,   106,
     102,   -96,   -96,   -11,   -96,   108,   -96,   107,   109,   111,
     112,   113,   114,   -96,   -14,   -96,   -96,   -25,   -96,    99,
     -16,   -96,    19,    97,   -96,   143,   -21,    91,   -96,   103,
     125,   131,   132,   133,   134,   135,   -38,   -38,   136,   -96,
      91,   -96,   122,   -96,   -96,   -96,    91,   -96,   -96,   -96,
     -96,   -96,    49,   -96,   102,   -96,   -96,   -96,   -96,   -96,
     -96,    42,   -96,   -96,   -12,   137,   137,   137,   137,   137,
     137,   -96,   -96,   167,   140,   -96,   138,   -96,   -96,    97,
     -96,   -96,   -96,   -96,    97,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,   -96,   102,   102,   169,   128,   -96,   -96,    70,
     143,   174,   144,   -96,   102,   142,   -96,    59,   130,   -96,
     -96,   -96,   -96,   -96,   102,   -96
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       4,     3,    12,    13,    14,    15,     5,     0,    21,     0,
       0,     9,     6,    10,    11,     7,     8,    17,     0,     0,
       0,    16,     0,     0,   101,    24,     0,     0,     0,    99,
     100,     0,     0,     0,     0,     0,     0,   102,    74,    59,
      75,     0,    58,     0,    57,    19,     1,     2,     0,     0,
       0,    23,     0,     0,    52,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    18,     0,     0,     0,     0,
       0,    28,   102,    52,    69,     0,    20,     0,     0,     0,
       0,     0,     0,    60,    52,    88,    56,     0,    37,     0,
       0,    39,     0,     0,    54,    53,     0,     0,    29,     0,
      82,    83,    84,    85,    87,    86,     0,     0,    33,    22,
       0,    42,     0,    44,    41,    25,     0,    26,    49,    47,
      48,    50,     0,    45,     0,    65,    64,    66,    61,    62,
      63,     0,    70,    71,     0,     0,     0,     0,     0,     0,
       0,    90,    89,     0,    35,    38,     0,    40,    27,     0,
      55,    67,    68,    51,     0,    72,   103,    76,    77,    78,
      79,    81,    80,     0,     0,    92,     0,    46,    73,    34,
      36,     0,    32,    43,     0,     0,    30,    98,    91,    93,
      31,    97,    96,    95,     0,    94
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   177,   -96,
     -96,   -96,   -96,   118,    78,   -96,   -96,   -95,    61,   -76,
      23,    -9,    26,   -96,   -96,   -96,    93,   -96,   -96,   -96,
     -96,   -96,    10,   -96,   -96,    -3,   -55,    11
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,   186,
     154,   175,    97,   100,    98,   124,   132,   133,   104,    81,
     105,   106,    50,   141,   163,    83,    84,    51,    52,    94,
     182,   188,   189,   193,    41,    53,    54,   167
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    35,    29,    80,    38,    27,    80,   108,    39,    40,
      85,    34,   116,    32,   143,   135,   136,   137,   118,    96,
      30,    99,   101,   101,    36,    28,    59,    60,    37,    61,
      62,    33,    56,    63,    64,   119,   120,   138,   128,   129,
     130,   131,   139,   140,   125,   126,   161,   117,    58,   165,
     107,    31,    85,   164,   144,    75,    57,    65,    87,    88,
      89,    90,    92,    93,   177,    99,    66,   191,    67,   178,
      95,   157,     1,   192,     2,    68,     3,     4,     5,   127,
     126,     6,    42,    43,    44,    45,    46,     7,     8,     9,
      69,    47,   128,   129,   130,   131,    10,    11,    12,    13,
      14,    15,    42,    43,    44,    45,    46,    70,    16,   158,
     159,    47,    71,   151,   152,    42,    43,    44,    45,    46,
     121,   122,   123,    17,    47,    18,     5,  -101,    48,     6,
      74,    72,   162,    73,    79,     7,    76,     9,    77,    78,
      82,    91,    42,    43,    44,    45,    46,   128,   129,   130,
     131,    47,    82,   128,   129,   130,   131,   168,   169,   170,
     171,   172,    80,    86,    49,   103,   109,   110,   134,   111,
     145,   112,   113,   114,   115,   187,   146,   147,   148,   149,
     150,   156,   153,   173,   181,   187,   166,   174,   183,   176,
     184,   194,   185,   190,    55,   160,   102,   180,   155,   179,
     142,     0,     0,     0,   195
};

static const yytype_int16 yycheck[] =
{
       9,     4,     6,    17,     7,     4,    17,    83,    34,    35,
      65,    49,    26,     6,   109,    36,    37,    38,    94,    74,
      24,    76,    77,    78,    10,    24,    29,    30,    13,    32,
      33,    24,     0,    36,    37,    60,    61,    58,    50,    51,
      52,    53,    63,    64,    60,    61,   141,    61,    13,   144,
      61,    55,   107,    65,   109,    58,    57,    19,    67,    68,
      69,    70,    71,    72,   159,   120,    58,     8,    59,   164,
      73,   126,     3,    14,     5,    59,     7,     8,     9,    60,
      61,    12,    40,    41,    42,    43,    44,    18,    19,    20,
      59,    49,    50,    51,    52,    53,    27,    28,    29,    30,
      31,    32,    40,    41,    42,    43,    44,    59,    39,    60,
      61,    49,    59,   116,   117,    40,    41,    42,    43,    44,
      21,    22,    23,    54,    49,    56,     9,    62,    66,    12,
      62,    61,   141,    13,    11,    18,    59,    20,    59,    59,
      49,    66,    40,    41,    42,    43,    44,    50,    51,    52,
      53,    49,    49,    50,    51,    52,    53,   146,   147,   148,
     149,   150,    17,    53,   173,    59,    58,    60,    25,    60,
      45,    60,    60,    60,    60,   184,    45,    45,    45,    45,
      45,    59,    46,    16,    15,   194,    49,    47,    60,    51,
      16,    61,    48,    51,    17,   134,    78,   174,   120,   173,
     107,    -1,    -1,    -1,   194
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     7,     8,     9,    12,    18,    19,    20,
      27,    28,    29,    30,    31,    32,    39,    54,    56,    68,
      69,    70,    71,    72,    73,    74,    75,     4,    24,     6,
      24,    55,     6,    24,    49,   102,    10,    13,   102,    34,
      35,   101,    40,    41,    42,    43,    44,    49,    66,    88,
      89,    94,    95,   102,   103,    75,     0,    57,    13,   102,
     102,   102,   102,   102,   102,    19,    58,    59,    59,    59,
      59,    59,    61,    13,    62,   102,    59,    59,    59,    11,
      17,    86,    49,    92,    93,   103,    53,    88,    88,    88,
      88,    66,    88,    88,    96,   102,   103,    79,    81,   103,
      80,   103,    80,    59,    85,    87,    88,    61,    86,    58,
      60,    60,    60,    60,    60,    60,    26,    61,    86,    60,
      61,    21,    22,    23,    82,    60,    61,    60,    50,    51,
      52,    53,    83,    84,    25,    36,    37,    38,    58,    63,
      64,    90,    93,    84,   103,    45,    45,    45,    45,    45,
      45,   102,   102,    46,    77,    81,    59,   103,    60,    61,
      85,    84,    88,    91,    65,    84,    49,   104,   104,   104,
     104,   104,   104,    16,    47,    78,    51,    84,    84,    89,
      87,    15,    97,    60,    16,    48,    76,    88,    98,    99,
      51,     8,    14,   100,    61,    99
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    67,    68,    68,    68,    68,    69,    69,    69,    69,
      69,    69,    70,    70,    70,    70,    70,    71,    71,    71,
      72,    73,    74,    74,    74,    74,    74,    75,    75,    75,
      75,    76,    76,    77,    77,    78,    78,    79,    79,    80,
      80,    81,    82,    82,    82,    83,    83,    84,    84,    84,
      84,    85,    86,    86,    87,    87,    88,    88,    88,    89,
      89,    90,    90,    90,    90,    90,    90,    91,    91,    92,
      92,    93,    93,    93,    94,    94,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    96,    96,
      96,    97,    97,    98,    98,    99,   100,   100,   100,   101,
     101,   102,   103,   104
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     4,     2,
       4,     1,     6,     3,     2,     6,     6,     7,     4,     5,
       9,     2,     0,     0,     3,     0,     2,     1,     3,     1,
       3,     2,     1,     4,     1,     1,     3,     1,     1,     1,
       1,     3,     0,     2,     1,     3,     3,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     4,     5,     1,     1,     6,     6,     6,     6,
       6,     6,     4,     4,     4,     4,     4,     4,     1,     3,
       3,     3,     0,     1,     3,     2,     1,     1,     0,     1,
       1,     1,     1,     1
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
        yyerror (&yylloc, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc);
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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: stmt ';'  */
#line 66 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = (yyvsp[-1].sv_node);
        YYACCEPT;
    }
#line 1716 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 3: /* start: HELP  */
#line 71 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = std::make_shared<Help>();
        YYACCEPT;
    }
#line 1725 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 4: /* start: EXIT  */
#line 76 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1734 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 5: /* start: T_EOF  */
#line 81 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1743 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 12: /* txnStmt: TXN_BEGIN  */
#line 98 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnBegin>();
    }
#line 1751 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 13: /* txnStmt: TXN_COMMIT  */
#line 102 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnCommit>();
    }
#line 1759 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 14: /* txnStmt: TXN_ABORT  */
#line 106 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnAbort>();
    }
#line 1767 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 15: /* txnStmt: TXN_ROLLBACK  */
#line 110 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnRollback>();
    }
#line 1775 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 16: /* txnStmt: CREATE STATIC_CHECKPOINT  */
#line 114 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateCheckPoint>();
    }
#line 1783 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 17: /* dbStmt: SHOW TABLES  */
#line 121 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowTables>();
    }
#line 1791 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 18: /* dbStmt: SHOW INDEX FROM tbName  */
#line 125 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowIndex>((yyvsp[0].sv_str));
    }
#line 1799 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 19: /* dbStmt: EXPLAIN dml  */
#line 129 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        if(auto select = std::dynamic_pointer_cast<SelectStmt>((yyvsp[0].sv_node))){
            select->need_explain = true;
            (yyval.sv_node) = select;
        }
    }
#line 1810 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 20: /* setStmt: SET set_knob_type '=' VALUE_BOOL  */
#line 139 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<SetStmt>((yyvsp[-2].sv_setKnobType), (yyvsp[0].sv_bool));
    }
#line 1818 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 21: /* sysStmt: CRASH  */
#line 146 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CrashStmt>();
    }
#line 1826 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 22: /* ddl: CREATE TABLE tbName '(' fieldList ')'  */
#line 153 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateTable>((yyvsp[-3].sv_str), (yyvsp[-1].sv_fields));
    }
#line 1834 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 23: /* ddl: DROP TABLE tbName  */
#line 157 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropTable>((yyvsp[0].sv_str));
    }
#line 1842 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 24: /* ddl: DESC tbName  */
#line 161 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DescTable>((yyvsp[0].sv_str));
    }
#line 1850 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 25: /* ddl: CREATE INDEX tbName '(' colNameList ')'  */
#line 165 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1858 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 26: /* ddl: DROP INDEX tbName '(' colNameList ')'  */
#line 169 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1866 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 27: /* dml: INSERT INTO tbName VALUES '(' valueList ')'  */
#line 176 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<InsertStmt>((yyvsp[-4].sv_str), (yyvsp[-1].sv_vals));
    }
#line 1874 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 28: /* dml: DELETE FROM tbName optWhereClause  */
#line 180 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DeleteStmt>((yyvsp[-1].sv_str), (yyvsp[0].sv_conds));
    }
#line 1882 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 29: /* dml: UPDATE tbName SET setClauses optWhereClause  */
#line 184 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<UpdateStmt>((yyvsp[-3].sv_str), (yyvsp[-1].sv_set_clauses), (yyvsp[0].sv_conds));
    }
#line 1890 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 30: /* dml: SELECT selector FROM tableList optWhereClause optGroupByClause optHavingClause opt_order_clause limit_clause  */
#line 188 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<SelectStmt>((yyvsp[-7].sv_cols), (yyvsp[-5].sv_strs), (yyvsp[-4].sv_conds), (yyvsp[-3].sv_cols), (yyvsp[-2].sv_conds), (yyvsp[-1].sv_orderbys), (yyvsp[0].sv_int));
    }
#line 1898 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 31: /* limit_clause: LIMIT VALUE_INT  */
#line 195 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_int) = (yyvsp[0].sv_int);
    }
#line 1906 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 32: /* limit_clause: %empty  */
#line 199 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_int) = INT_MAX;
    }
#line 1914 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 33: /* optGroupByClause: %empty  */
#line 206 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols) = {};
    }
#line 1922 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 34: /* optGroupByClause: GROUP BY colList  */
#line 210 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols) = (yyvsp[0].sv_cols);
    }
#line 1930 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 35: /* optHavingClause: %empty  */
#line 216 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                      { /* ignore*/ }
#line 1936 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 36: /* optHavingClause: HAVING whereClause  */
#line 218 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_conds) = (yyvsp[0].sv_conds);
    }
#line 1944 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 37: /* fieldList: field  */
#line 225 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_fields) = std::vector<std::shared_ptr<Field>>{(yyvsp[0].sv_field)};
    }
#line 1952 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 38: /* fieldList: fieldList ',' field  */
#line 229 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_fields).push_back((yyvsp[0].sv_field));
    }
#line 1960 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 39: /* colNameList: colName  */
#line 236 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 1968 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 40: /* colNameList: colNameList ',' colName  */
#line 240 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 1976 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 41: /* field: colName type  */
#line 247 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-1].sv_str), (yyvsp[0].sv_type_len));
    }
#line 1984 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 42: /* type: INT  */
#line 254 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_INT, sizeof(int));
    }
#line 1992 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 43: /* type: CHAR '(' VALUE_INT ')'  */
#line 258 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_STRING, (yyvsp[-1].sv_int));
    }
#line 2000 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 44: /* type: FLOAT  */
#line 262 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_FLOAT, sizeof(float));
    }
#line 2008 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 45: /* valueList: value  */
#line 269 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_vals) = std::vector<std::shared_ptr<Value>>{(yyvsp[0].sv_val)};
    }
#line 2016 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 46: /* valueList: valueList ',' value  */
#line 273 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_vals).push_back((yyvsp[0].sv_val));
    }
#line 2024 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 47: /* value: VALUE_INT  */
#line 280 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<IntLit>((yyvsp[0].sv_int));
    }
#line 2032 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 48: /* value: VALUE_FLOAT  */
#line 284 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<FloatLit>((yyvsp[0].sv_float));
    }
#line 2040 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 49: /* value: VALUE_STRING  */
#line 288 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<StringLit>((yyvsp[0].sv_str));
    }
#line 2048 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 50: /* value: VALUE_BOOL  */
#line 292 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<BoolLit>((yyvsp[0].sv_bool));
    }
#line 2056 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 51: /* condition: col op expr  */
#line 299 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BinaryExpr>((yyvsp[-2].sv_col), (yyvsp[-1].sv_comp_op), (yyvsp[0].sv_expr));
    }
#line 2064 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 52: /* optWhereClause: %empty  */
#line 305 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                      { /* ignore*/ }
#line 2070 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 53: /* optWhereClause: WHERE whereClause  */
#line 307 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_conds) = (yyvsp[0].sv_conds);
    }
#line 2078 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 54: /* whereClause: condition  */
#line 314 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_conds) = std::vector<std::shared_ptr<BinaryExpr>>{(yyvsp[0].sv_cond)};
    }
#line 2086 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 55: /* whereClause: whereClause AND condition  */
#line 318 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_conds).push_back((yyvsp[0].sv_cond));
    }
#line 2094 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 56: /* col: tbName '.' colName  */
#line 325 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
#line 2102 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 57: /* col: colName  */
#line 329 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>("", (yyvsp[0].sv_str));
    }
#line 2110 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 58: /* col: aggCol  */
#line 333 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = (yyvsp[0].sv_col);
    }
#line 2118 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 59: /* colList: col  */
#line 340 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols) = std::vector<std::shared_ptr<Col>>{(yyvsp[0].sv_col)};
    }
#line 2126 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 60: /* colList: colList ',' col  */
#line 344 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols).push_back((yyvsp[0].sv_col));
    }
#line 2134 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 61: /* op: '='  */
#line 351 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_EQ;
    }
#line 2142 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 62: /* op: '<'  */
#line 355 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LT;
    }
#line 2150 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 63: /* op: '>'  */
#line 359 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GT;
    }
#line 2158 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 64: /* op: NEQ  */
#line 363 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_NE;
    }
#line 2166 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 65: /* op: LEQ  */
#line 367 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LE;
    }
#line 2174 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 66: /* op: GEQ  */
#line 371 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GE;
    }
#line 2182 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 67: /* expr: value  */
#line 378 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_val));
    }
#line 2190 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 68: /* expr: col  */
#line 382 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_col));
    }
#line 2198 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 69: /* setClauses: setClause  */
#line 389 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses) = std::vector<std::shared_ptr<SetClause>>{(yyvsp[0].sv_set_clause)};
    }
#line 2206 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 70: /* setClauses: setClauses ',' setClause  */
#line 393 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses).push_back((yyvsp[0].sv_set_clause));
    }
#line 2214 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 71: /* setClause: colName '=' value  */
#line 400 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-2].sv_str), (yyvsp[0].sv_val));
    }
#line 2222 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 72: /* setClause: colName '=' colName value  */
#line 404 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-3].sv_str), (yyvsp[0].sv_val), true);
    }
#line 2230 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 73: /* setClause: colName '=' colName '+' value  */
#line 408 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-4].sv_str), (yyvsp[0].sv_val), true);
    }
#line 2238 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 74: /* selector: '*'  */
#line 415 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols) = {};
    }
#line 2246 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 76: /* aggCol: MAX '(' col ')' AS alias  */
#line 423 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_MAX, (yyvsp[0].sv_str)));
    }
#line 2254 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 77: /* aggCol: MIN '(' col ')' AS alias  */
#line 427 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_MIN, (yyvsp[0].sv_str)));
    }
#line 2262 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 78: /* aggCol: SUM '(' col ')' AS alias  */
#line 431 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_SUM, (yyvsp[0].sv_str)));
    }
#line 2270 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 79: /* aggCol: AVG '(' col ')' AS alias  */
#line 435 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_AVG, (yyvsp[0].sv_str)));
    }
#line 2278 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 80: /* aggCol: COUNT '(' col ')' AS alias  */
#line 439 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_COUNT, (yyvsp[0].sv_str)));
    }
#line 2286 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 81: /* aggCol: COUNT '(' '*' ')' AS alias  */
#line 443 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>("", "*", AGG_COUNT, (yyvsp[0].sv_str)));
    }
#line 2294 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 82: /* aggCol: MAX '(' col ')'  */
#line 447 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_MAX, ""));
    }
#line 2302 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 83: /* aggCol: MIN '(' col ')'  */
#line 451 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_MIN, ""));
    }
#line 2310 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 84: /* aggCol: SUM '(' col ')'  */
#line 455 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_SUM, ""));
    }
#line 2318 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 85: /* aggCol: AVG '(' col ')'  */
#line 459 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_AVG, ""));
    }
#line 2326 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 86: /* aggCol: COUNT '(' col ')'  */
#line 463 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_COUNT, ""));
    }
#line 2334 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 87: /* aggCol: COUNT '(' '*' ')'  */
#line 467 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>("", "*", AGG_COUNT, ""));
    }
#line 2342 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 88: /* tableList: tbName  */
#line 474 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 2350 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 89: /* tableList: tableList ',' tbName  */
#line 478 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2358 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 90: /* tableList: tableList JOIN tbName  */
#line 482 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2366 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 91: /* opt_order_clause: ORDER BY order_clauses  */
#line 489 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    { 
        (yyval.sv_orderbys) = (yyvsp[0].sv_orderbys); 
    }
#line 2374 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 92: /* opt_order_clause: %empty  */
#line 492 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                      { /* ignore*/ }
#line 2380 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 93: /* order_clauses: order_clause  */
#line 497 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_orderbys) = std::vector<std::shared_ptr<OrderBy>>{(yyvsp[0].sv_orderby)};
    }
#line 2388 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 94: /* order_clauses: order_clauses ',' order_clause  */
#line 501 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_orderbys).push_back((yyvsp[0].sv_orderby));
    }
#line 2396 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 95: /* order_clause: col opt_asc_desc  */
#line 508 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    { 
        (yyval.sv_orderby) = std::make_shared<OrderBy>((yyvsp[-1].sv_col), (yyvsp[0].sv_orderby_dir));
    }
#line 2404 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 96: /* opt_asc_desc: ASC  */
#line 514 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_ASC;     }
#line 2410 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 97: /* opt_asc_desc: DESC  */
#line 515 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_DESC;    }
#line 2416 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 98: /* opt_asc_desc: %empty  */
#line 516 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_ASC; }
#line 2422 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 99: /* set_knob_type: ENABLE_NESTLOOP  */
#line 520 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                    { (yyval.sv_setKnobType) = EnableNestLoop; }
#line 2428 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 100: /* set_knob_type: ENABLE_SORTMERGE  */
#line 521 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                         { (yyval.sv_setKnobType) = EnableSortMerge; }
#line 2434 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;


#line 2438 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"

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
  *++yylsp = yyloc;

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
  yyerror (&yylloc, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 529 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"

