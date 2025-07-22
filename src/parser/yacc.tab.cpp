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
#include <set>
#include <unordered_map>
std::unordered_map<std::string, std::string> alias_map;
std::unordered_map<std::string, std::string> pam_saila;

int yylex(YYSTYPE *yylval, YYLTYPE *yylloc,void *yyscanner);

void yyerror(YYLTYPE *locp, void *yyscanner , const char* s) {
    std::cerr << "Parser Error at line " << locp->first_line << " column " << locp->first_column << ": " << s << std::endl;
}

using namespace ast;

#line 91 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"

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
  YYSYMBOL_INNER = 36,                     /* INNER  */
  YYSYMBOL_LEFT = 37,                      /* LEFT  */
  YYSYMBOL_RIGHT = 38,                     /* RIGHT  */
  YYSYMBOL_FULL = 39,                      /* FULL  */
  YYSYMBOL_SEMI = 40,                      /* SEMI  */
  YYSYMBOL_ON = 41,                        /* ON  */
  YYSYMBOL_MAX = 42,                       /* MAX  */
  YYSYMBOL_MIN = 43,                       /* MIN  */
  YYSYMBOL_SUM = 44,                       /* SUM  */
  YYSYMBOL_AVG = 45,                       /* AVG  */
  YYSYMBOL_COUNT = 46,                     /* COUNT  */
  YYSYMBOL_AS = 47,                        /* AS  */
  YYSYMBOL_GROUP = 48,                     /* GROUP  */
  YYSYMBOL_HAVING = 49,                    /* HAVING  */
  YYSYMBOL_LIMIT = 50,                     /* LIMIT  */
  YYSYMBOL_EXPLAIN = 51,                   /* EXPLAIN  */
  YYSYMBOL_LOAD = 52,                      /* LOAD  */
  YYSYMBOL_OFF = 53,                       /* OFF  */
  YYSYMBOL_OUTPUT_FILE = 54,               /* OUTPUT_FILE  */
  YYSYMBOL_LEQ = 55,                       /* LEQ  */
  YYSYMBOL_NEQ = 56,                       /* NEQ  */
  YYSYMBOL_GEQ = 57,                       /* GEQ  */
  YYSYMBOL_T_EOF = 58,                     /* T_EOF  */
  YYSYMBOL_IDENTIFIER = 59,                /* IDENTIFIER  */
  YYSYMBOL_VALUE_STRING = 60,              /* VALUE_STRING  */
  YYSYMBOL_VALUE_PATH = 61,                /* VALUE_PATH  */
  YYSYMBOL_VALUE_INT = 62,                 /* VALUE_INT  */
  YYSYMBOL_VALUE_FLOAT = 63,               /* VALUE_FLOAT  */
  YYSYMBOL_VALUE_BOOL = 64,                /* VALUE_BOOL  */
  YYSYMBOL_STATIC_CHECKPOINT = 65,         /* STATIC_CHECKPOINT  */
  YYSYMBOL_CRASH = 66,                     /* CRASH  */
  YYSYMBOL_67_ = 67,                       /* ';'  */
  YYSYMBOL_68_ = 68,                       /* '='  */
  YYSYMBOL_69_ = 69,                       /* '('  */
  YYSYMBOL_70_ = 70,                       /* ')'  */
  YYSYMBOL_71_ = 71,                       /* ','  */
  YYSYMBOL_72_ = 72,                       /* '.'  */
  YYSYMBOL_73_ = 73,                       /* '<'  */
  YYSYMBOL_74_ = 74,                       /* '>'  */
  YYSYMBOL_75_ = 75,                       /* '+'  */
  YYSYMBOL_76_ = 76,                       /* '*'  */
  YYSYMBOL_YYACCEPT = 77,                  /* $accept  */
  YYSYMBOL_start = 78,                     /* start  */
  YYSYMBOL_stmt = 79,                      /* stmt  */
  YYSYMBOL_txnStmt = 80,                   /* txnStmt  */
  YYSYMBOL_dbStmt = 81,                    /* dbStmt  */
  YYSYMBOL_setStmt = 82,                   /* setStmt  */
  YYSYMBOL_sysStmt = 83,                   /* sysStmt  */
  YYSYMBOL_io_stmt = 84,                   /* io_stmt  */
  YYSYMBOL_ddl = 85,                       /* ddl  */
  YYSYMBOL_dml = 86,                       /* dml  */
  YYSYMBOL_limit_clause = 87,              /* limit_clause  */
  YYSYMBOL_optGroupByClause = 88,          /* optGroupByClause  */
  YYSYMBOL_optHavingClause = 89,           /* optHavingClause  */
  YYSYMBOL_fieldList = 90,                 /* fieldList  */
  YYSYMBOL_colNameList = 91,               /* colNameList  */
  YYSYMBOL_field = 92,                     /* field  */
  YYSYMBOL_type = 93,                      /* type  */
  YYSYMBOL_valueList = 94,                 /* valueList  */
  YYSYMBOL_value = 95,                     /* value  */
  YYSYMBOL_condition = 96,                 /* condition  */
  YYSYMBOL_optWhereClause = 97,            /* optWhereClause  */
  YYSYMBOL_whereClause = 98,               /* whereClause  */
  YYSYMBOL_col = 99,                       /* col  */
  YYSYMBOL_colList = 100,                  /* colList  */
  YYSYMBOL_op = 101,                       /* op  */
  YYSYMBOL_expr = 102,                     /* expr  */
  YYSYMBOL_setClauses = 103,               /* setClauses  */
  YYSYMBOL_setClause = 104,                /* setClause  */
  YYSYMBOL_selector = 105,                 /* selector  */
  YYSYMBOL_aggCol = 106,                   /* aggCol  */
  YYSYMBOL_tableList = 107,                /* tableList  */
  YYSYMBOL_tbNameWithAlias = 108,          /* tbNameWithAlias  */
  YYSYMBOL_join_exprss = 109,              /* join_exprss  */
  YYSYMBOL_join_exprs = 110,               /* join_exprs  */
  YYSYMBOL_join_expr = 111,                /* join_expr  */
  YYSYMBOL_join_type = 112,                /* join_type  */
  YYSYMBOL_opt_order_clause = 113,         /* opt_order_clause  */
  YYSYMBOL_order_clauses = 114,            /* order_clauses  */
  YYSYMBOL_order_clause = 115,             /* order_clause  */
  YYSYMBOL_opt_asc_desc = 116,             /* opt_asc_desc  */
  YYSYMBOL_set_knob_type = 117,            /* set_knob_type  */
  YYSYMBOL_tbName = 118,                   /* tbName  */
  YYSYMBOL_colName = 119,                  /* colName  */
  YYSYMBOL_alias = 120,                    /* alias  */
  YYSYMBOL_fileName = 121                  /* fileName  */
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
#define YYFINAL  61
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   230

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  120
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  229

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   321


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
      69,    70,    76,    75,    71,     2,    72,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    67,
      73,    68,    74,     2,     2,     2,     2,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    75,    75,    80,    85,    90,    95,   104,   105,   106,
     107,   108,   109,   113,   117,   121,   125,   129,   136,   140,
     144,   151,   158,   165,   172,   176,   182,   186,   190,   194,
     198,   205,   209,   213,   217,   221,   239,   244,   251,   254,
     261,   262,   270,   274,   281,   285,   292,   299,   303,   307,
     314,   318,   325,   329,   333,   337,   344,   351,   352,   359,
     363,   370,   374,   378,   385,   389,   396,   400,   404,   408,
     412,   416,   423,   427,   434,   438,   445,   449,   453,   460,
     464,   468,   472,   476,   480,   484,   488,   492,   496,   500,
     504,   508,   512,   519,   523,   534,   538,   546,   556,   560,
     566,   572,   573,   574,   575,   576,   577,   582,   586,   590,
     594,   601,   608,   609,   610,   614,   615,   618,   620,   622,
     624
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
  "ENABLE_SORTMERGE", "INNER", "LEFT", "RIGHT", "FULL", "SEMI", "ON",
  "MAX", "MIN", "SUM", "AVG", "COUNT", "AS", "GROUP", "HAVING", "LIMIT",
  "EXPLAIN", "LOAD", "OFF", "OUTPUT_FILE", "LEQ", "NEQ", "GEQ", "T_EOF",
  "IDENTIFIER", "VALUE_STRING", "VALUE_PATH", "VALUE_INT", "VALUE_FLOAT",
  "VALUE_BOOL", "STATIC_CHECKPOINT", "CRASH", "';'", "'='", "'('", "')'",
  "','", "'.'", "'<'", "'>'", "'+'", "'*'", "$accept", "start", "stmt",
  "txnStmt", "dbStmt", "setStmt", "sysStmt", "io_stmt", "ddl", "dml",
  "limit_clause", "optGroupByClause", "optHavingClause", "fieldList",
  "colNameList", "field", "type", "valueList", "value", "condition",
  "optWhereClause", "whereClause", "col", "colList", "op", "expr",
  "setClauses", "setClause", "selector", "aggCol", "tableList",
  "tbNameWithAlias", "join_exprss", "join_exprs", "join_expr", "join_type",
  "opt_order_clause", "order_clauses", "order_clause", "opt_asc_desc",
  "set_knob_type", "tbName", "colName", "alias", "fileName", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-178)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-118)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      78,     2,    -1,     9,   -37,    34,    35,   -37,   -24,    -4,
    -178,  -178,  -178,  -178,  -178,  -178,    25,    -5,  -178,  -178,
      51,     8,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
      49,   -37,   -37,  -178,   -37,   -37,  -178,  -178,   -37,   -37,
      54,  -178,  -178,   -29,    10,    13,    15,    19,    48,    56,
      55,  -178,  -178,    52,   115,  -178,    71,  -178,  -178,  -178,
     135,  -178,  -178,   -37,    77,    83,  -178,    84,   146,   152,
     122,  -178,  -178,   110,    76,    76,    76,    76,    57,    76,
     -37,   122,   -37,  -178,   122,   122,   122,   114,    76,  -178,
    -178,   -10,  -178,   116,  -178,   112,   117,   118,   119,   120,
     121,  -178,    -8,   111,   152,   126,  -178,  -178,   -17,  -178,
     157,   -12,  -178,    24,   113,  -178,   161,    58,   122,  -178,
     108,   147,   148,   149,   150,   151,   153,   -37,   145,  -178,
     173,   175,   176,   177,   178,   111,  -178,   -37,   145,  -178,
    -178,  -178,   122,  -178,   136,  -178,  -178,  -178,   122,  -178,
    -178,  -178,  -178,  -178,    41,  -178,    76,  -178,  -178,  -178,
    -178,  -178,  -178,    96,  -178,  -178,    29,   126,   126,   126,
     126,   126,   126,  -178,   190,   159,  -178,  -178,  -178,  -178,
    -178,  -178,   168,   159,  -178,   154,  -178,  -178,   113,  -178,
    -178,  -178,  -178,   113,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,    76,    76,   195,    76,   195,   141,  -178,  -178,    52,
     161,   196,   163,   161,   163,  -178,    76,   155,  -178,  -178,
       6,   143,  -178,  -178,  -178,  -178,  -178,    76,  -178
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       4,     3,    13,    14,    15,    16,     0,     0,     5,    23,
       0,     0,    10,     7,    11,    12,     6,     8,     9,    18,
       0,     0,     0,    17,     0,     0,   117,    28,     0,     0,
       0,   115,   116,     0,     0,     0,     0,     0,     0,     0,
     118,    79,    64,    80,     0,    63,     0,    62,    20,   120,
       0,     1,     2,     0,     0,     0,    27,     0,     0,    57,
       0,    24,    25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,     0,     0,     0,     0,    32,
     118,    57,    74,     0,    22,     0,     0,     0,     0,     0,
       0,    65,    57,    93,    57,    95,    61,    21,     0,    42,
       0,     0,    44,     0,     0,    59,    58,     0,     0,    33,
       0,    87,    88,    89,    90,    92,    91,     0,    38,   101,
       0,     0,     0,     0,     0,    97,    98,     0,    38,   119,
      96,    26,     0,    47,     0,    49,    46,    29,     0,    30,
      54,    52,    53,    55,     0,    50,     0,    70,    69,    71,
      66,    67,    68,     0,    75,    76,     0,     0,     0,     0,
       0,     0,     0,    94,     0,    40,   102,   103,   104,   105,
     106,    99,     0,    40,    43,     0,    45,    31,     0,    60,
      72,    73,    56,     0,    77,    81,    82,    83,    84,    86,
      85,     0,     0,   108,     0,   108,     0,    51,    78,    39,
      41,     0,    37,   100,    37,    48,     0,     0,    34,    35,
     114,   107,   109,    36,   113,   112,   111,     0,   110
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,   199,
       5,    82,    38,  -178,   137,    80,  -178,  -178,  -117,    68,
     -83,  -177,    -9,    26,  -178,  -178,  -178,   107,  -178,  -178,
    -178,   -80,  -178,  -178,    91,  -178,    23,  -178,     3,  -178,
    -178,    -3,   -68,    -6,  -178
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    20,    21,    22,    23,    24,    25,    26,    27,    28,
     218,   175,   203,   108,   111,   109,   146,   154,   155,   115,
      89,   116,   117,    53,   163,   192,    91,    92,    54,    55,
     102,   103,   104,   135,   136,   137,   212,   221,   222,   226,
      44,    56,    57,   140,    60
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      52,    37,    93,   165,    40,    31,    29,    88,   119,    88,
      41,    42,    71,   106,   224,    34,   110,   112,   112,   128,
     225,   138,    36,    32,    72,   210,    30,   213,    64,    65,
      43,    66,    67,    35,     5,    68,    69,     6,    45,    46,
      47,    48,    49,     7,    38,     9,   190,   173,    39,   194,
      93,    61,   166,   141,   142,    50,    59,   182,   147,   148,
      83,   118,    63,   127,    33,    95,    96,    97,    98,   100,
     101,   207,    51,    70,   110,    62,   208,   105,    73,   107,
     186,     1,    74,     2,    75,     3,     4,     5,    76,   150,
       6,   151,   152,   153,   149,   148,     7,     8,     9,    45,
      46,    47,    48,    49,   193,    10,    11,    12,    13,    14,
      15,   187,   188,   157,   158,   159,    50,    77,    45,    46,
      47,    48,    49,    79,   105,    78,   160,  -117,    80,    16,
      17,   161,   162,    99,   105,    50,    18,   129,    45,    46,
      47,    48,    49,    81,    19,    82,    84,   130,   131,   132,
     133,   134,    85,    86,   191,    50,   150,    87,   151,   152,
     153,   195,   196,   197,   198,   199,   200,    90,   150,    88,
     151,   152,   153,   150,    94,   151,   152,   153,   143,   144,
     145,    90,   121,   114,   120,   139,   156,   122,   123,   124,
     125,   126,    52,   174,   167,   168,   169,   170,   171,   176,
     172,   177,   178,   179,   180,   185,   201,   220,   202,   204,
     211,   215,   216,   217,   227,    58,   206,   223,   220,   219,
     183,   205,   184,   113,   189,   164,   181,   209,   214,     0,
     228
};

static const yytype_int16 yycheck[] =
{
       9,     4,    70,   120,     7,     6,     4,    17,    91,    17,
      34,    35,    41,    81,     8,     6,    84,    85,    86,   102,
      14,   104,    59,    24,    53,   202,    24,   204,    31,    32,
      54,    34,    35,    24,     9,    38,    39,    12,    42,    43,
      44,    45,    46,    18,    10,    20,   163,   127,    13,   166,
     118,     0,   120,    70,    71,    59,    61,   137,    70,    71,
      63,    71,    13,    71,    65,    74,    75,    76,    77,    78,
      79,   188,    76,    19,   142,    67,   193,    80,    68,    82,
     148,     3,    69,     5,    69,     7,     8,     9,    69,    60,
      12,    62,    63,    64,    70,    71,    18,    19,    20,    42,
      43,    44,    45,    46,    75,    27,    28,    29,    30,    31,
      32,    70,    71,    55,    56,    57,    59,    69,    42,    43,
      44,    45,    46,    71,   127,    69,    68,    72,    13,    51,
      52,    73,    74,    76,   137,    59,    58,    26,    42,    43,
      44,    45,    46,    72,    66,    10,    69,    36,    37,    38,
      39,    40,    69,    69,   163,    59,    60,    11,    62,    63,
      64,   167,   168,   169,   170,   171,   172,    59,    60,    17,
      62,    63,    64,    60,    64,    62,    63,    64,    21,    22,
      23,    59,    70,    69,    68,    59,    25,    70,    70,    70,
      70,    70,   201,    48,    47,    47,    47,    47,    47,    26,
      47,    26,    26,    26,    26,    69,    16,   216,    49,    41,
      15,    70,    16,    50,    71,    16,    62,    62,   227,   214,
     138,   183,   142,    86,   156,   118,   135,   201,   205,    -1,
     227
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     7,     8,     9,    12,    18,    19,    20,
      27,    28,    29,    30,    31,    32,    51,    52,    58,    66,
      78,    79,    80,    81,    82,    83,    84,    85,    86,     4,
      24,     6,    24,    65,     6,    24,    59,   118,    10,    13,
     118,    34,    35,    54,   117,    42,    43,    44,    45,    46,
      59,    76,    99,   100,   105,   106,   118,   119,    86,    61,
     121,     0,    67,    13,   118,   118,   118,   118,   118,   118,
      19,    41,    53,    68,    69,    69,    69,    69,    69,    71,
      13,    72,    10,   118,    69,    69,    69,    11,    17,    97,
      59,   103,   104,   119,    64,    99,    99,    99,    99,    76,
      99,    99,   107,   108,   109,   118,   119,   118,    90,    92,
     119,    91,   119,    91,    69,    96,    98,    99,    71,    97,
      68,    70,    70,    70,    70,    70,    70,    71,    97,    26,
      36,    37,    38,    39,    40,   110,   111,   112,    97,    59,
     120,    70,    71,    21,    22,    23,    93,    70,    71,    70,
      60,    62,    63,    64,    94,    95,    25,    55,    56,    57,
      68,    73,    74,   101,   104,    95,   119,    47,    47,    47,
      47,    47,    47,   108,    48,    88,    26,    26,    26,    26,
      26,   111,   108,    88,    92,    69,   119,    70,    71,    96,
      95,    99,   102,    75,    95,   120,   120,   120,   120,   120,
     120,    16,    49,    89,    41,    89,    62,    95,    95,   100,
      98,    15,   113,    98,   113,    70,    16,    50,    87,    87,
      99,   114,   115,    62,     8,    14,   116,    71,   115
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    77,    78,    78,    78,    78,    78,    79,    79,    79,
      79,    79,    79,    80,    80,    80,    80,    80,    81,    81,
      81,    81,    82,    83,    84,    84,    85,    85,    85,    85,
      85,    86,    86,    86,    86,    86,    87,    87,    88,    88,
      89,    89,    90,    90,    91,    91,    92,    93,    93,    93,
      94,    94,    95,    95,    95,    95,    96,    97,    97,    98,
      98,    99,    99,    99,   100,   100,   101,   101,   101,   101,
     101,   101,   102,   102,   103,   103,   104,   104,   104,   105,
     105,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   107,   107,   108,   108,   109,   110,   110,
     111,   112,   112,   112,   112,   112,   112,   113,   113,   114,
     114,   115,   116,   116,   116,   117,   117,   118,   119,   120,
     121
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     4,
       2,     4,     4,     1,     3,     3,     6,     3,     2,     6,
       6,     7,     4,     5,     9,     9,     2,     0,     0,     3,
       0,     2,     1,     3,     1,     3,     2,     1,     4,     1,
       1,     3,     1,     1,     1,     1,     3,     0,     2,     1,
       3,     3,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     4,     5,     1,
       1,     6,     6,     6,     6,     6,     6,     4,     4,     4,
       4,     4,     4,     1,     3,     1,     2,     2,     1,     2,
       4,     1,     2,     2,     2,     2,     2,     3,     0,     1,
       3,     2,     1,     1,     0,     1,     1,     1,     1,     1,
       1
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
        yyerror (&yylloc, yyscanner, YY_("syntax error: cannot back up")); \
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
                  Kind, Value, Location, yyscanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *yyscanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (yyscanner);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *yyscanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, yyscanner);
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
                 int yyrule, void *yyscanner)
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
                       &(yylsp[(yyi + 1) - (yynrhs)]), yyscanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, yyscanner); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, void *yyscanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (yyscanner);
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
yyparse (void *yyscanner)
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
      yychar = yylex (&yylval, &yylloc, yyscanner);
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
#line 76 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = (yyvsp[-1].sv_node);
        YYACCEPT;
    }
#line 1765 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 3: /* start: HELP  */
#line 81 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = std::make_shared<Help>();
        YYACCEPT;
    }
#line 1774 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 4: /* start: EXIT  */
#line 86 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1783 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 5: /* start: T_EOF  */
#line 91 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1792 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 6: /* start: io_stmt  */
#line 96 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = (yyvsp[0].sv_node);
        YYACCEPT;
    }
#line 1801 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 13: /* txnStmt: TXN_BEGIN  */
#line 114 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnBegin>();
    }
#line 1809 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 14: /* txnStmt: TXN_COMMIT  */
#line 118 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnCommit>();
    }
#line 1817 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 15: /* txnStmt: TXN_ABORT  */
#line 122 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnAbort>();
    }
#line 1825 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 16: /* txnStmt: TXN_ROLLBACK  */
#line 126 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnRollback>();
    }
#line 1833 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 17: /* txnStmt: CREATE STATIC_CHECKPOINT  */
#line 130 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateCheckPoint>();
    }
#line 1841 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 18: /* dbStmt: SHOW TABLES  */
#line 137 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowTables>();
    }
#line 1849 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 19: /* dbStmt: SHOW INDEX FROM tbName  */
#line 141 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowIndex>((yyvsp[0].sv_str));
    }
#line 1857 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 20: /* dbStmt: EXPLAIN dml  */
#line 145 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        if(auto select = std::dynamic_pointer_cast<SelectStmt>((yyvsp[0].sv_node))){
            select->need_explain = true;
            (yyval.sv_node) = select;
        }
    }
#line 1868 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 21: /* dbStmt: LOAD fileName INTO tbName  */
#line 152 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
         (yyval.sv_node) = std::make_shared<LoadStmt>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
#line 1876 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 22: /* setStmt: SET set_knob_type '=' VALUE_BOOL  */
#line 159 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<SetStmt>((yyvsp[-2].sv_setKnobType), (yyvsp[0].sv_bool));
    }
#line 1884 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 23: /* sysStmt: CRASH  */
#line 166 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CrashStmt>();
    }
#line 1892 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 24: /* io_stmt: SET OUTPUT_FILE ON  */
#line 173 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<IoEnable>(true);
    }
#line 1900 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 25: /* io_stmt: SET OUTPUT_FILE OFF  */
#line 177 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<IoEnable>(false);
    }
#line 1908 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 26: /* ddl: CREATE TABLE tbName '(' fieldList ')'  */
#line 183 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateTable>((yyvsp[-3].sv_str), (yyvsp[-1].sv_fields));
    }
#line 1916 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 27: /* ddl: DROP TABLE tbName  */
#line 187 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropTable>((yyvsp[0].sv_str));
    }
#line 1924 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 28: /* ddl: DESC tbName  */
#line 191 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DescTable>((yyvsp[0].sv_str));
    }
#line 1932 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 29: /* ddl: CREATE INDEX tbName '(' colNameList ')'  */
#line 195 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1940 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 30: /* ddl: DROP INDEX tbName '(' colNameList ')'  */
#line 199 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1948 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 31: /* dml: INSERT INTO tbName VALUES '(' valueList ')'  */
#line 206 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<InsertStmt>((yyvsp[-4].sv_str), (yyvsp[-1].sv_vals));
    }
#line 1956 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 32: /* dml: DELETE FROM tbName optWhereClause  */
#line 210 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DeleteStmt>((yyvsp[-1].sv_str), (yyvsp[0].sv_conds));
    }
#line 1964 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 33: /* dml: UPDATE tbName SET setClauses optWhereClause  */
#line 214 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<UpdateStmt>((yyvsp[-3].sv_str), (yyvsp[-1].sv_set_clauses), (yyvsp[0].sv_conds));
    }
#line 1972 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 34: /* dml: SELECT selector FROM tableList optWhereClause optGroupByClause optHavingClause opt_order_clause limit_clause  */
#line 218 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<SelectStmt>((yyvsp[-7].sv_cols), (yyvsp[-5].sv_strs), (yyvsp[-4].sv_conds), (yyvsp[-3].sv_cols), (yyvsp[-2].sv_conds), (yyvsp[-1].sv_orderbys), (yyvsp[0].sv_int));
    }
#line 1980 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 35: /* dml: SELECT selector FROM join_exprss optWhereClause optGroupByClause optHavingClause opt_order_clause limit_clause  */
#line 222 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        /*$$ = std::make_shared<SelectStmt>($2, $4, $5, $6);*/
        /*必须要把所有表名赋值给SelectStmt的tabs，后面需要用*/
        auto sel_stmt = std::make_shared<SelectStmt>((yyvsp[-7].sv_cols), (yyvsp[-5].sv_join_exprs), (yyvsp[-4].sv_conds), (yyvsp[-3].sv_cols), (yyvsp[-2].sv_conds), (yyvsp[-1].sv_orderbys), (yyvsp[0].sv_int));
        std::set<std::string> tab_set;
        for (const auto &join_expr : (yyvsp[-5].sv_join_exprs)) {
            if (join_expr) {
                tab_set.insert(join_expr->left);
                tab_set.insert(join_expr->right);
            }
        }
        sel_stmt->tabs.assign(tab_set.begin(), tab_set.end());
        (yyval.sv_node) = sel_stmt;
    }
#line 1999 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 36: /* limit_clause: LIMIT VALUE_INT  */
#line 240 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_int) = (yyvsp[0].sv_int);
    }
#line 2007 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 37: /* limit_clause: %empty  */
#line 244 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_int) = INT_MAX;
    }
#line 2015 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 38: /* optGroupByClause: %empty  */
#line 251 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols) = {};
    }
#line 2023 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 39: /* optGroupByClause: GROUP BY colList  */
#line 255 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols) = (yyvsp[0].sv_cols);
    }
#line 2031 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 40: /* optHavingClause: %empty  */
#line 261 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                      { /* ignore*/ }
#line 2037 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 41: /* optHavingClause: HAVING whereClause  */
#line 263 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_conds) = (yyvsp[0].sv_conds);
    }
#line 2045 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 42: /* fieldList: field  */
#line 271 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_fields) = std::vector<std::shared_ptr<Field>>{(yyvsp[0].sv_field)};
    }
#line 2053 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 43: /* fieldList: fieldList ',' field  */
#line 275 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_fields).push_back((yyvsp[0].sv_field));
    }
#line 2061 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 44: /* colNameList: colName  */
#line 282 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 2069 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 45: /* colNameList: colNameList ',' colName  */
#line 286 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2077 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 46: /* field: colName type  */
#line 293 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-1].sv_str), (yyvsp[0].sv_type_len));
    }
#line 2085 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 47: /* type: INT  */
#line 300 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_INT, sizeof(int));
    }
#line 2093 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 48: /* type: CHAR '(' VALUE_INT ')'  */
#line 304 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_STRING, (yyvsp[-1].sv_int));
    }
#line 2101 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 49: /* type: FLOAT  */
#line 308 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_FLOAT, sizeof(float));
    }
#line 2109 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 50: /* valueList: value  */
#line 315 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_vals) = std::vector<std::shared_ptr<Value>>{(yyvsp[0].sv_val)};
    }
#line 2117 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 51: /* valueList: valueList ',' value  */
#line 319 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_vals).push_back((yyvsp[0].sv_val));
    }
#line 2125 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 52: /* value: VALUE_INT  */
#line 326 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<IntLit>((yyvsp[0].sv_int));
    }
#line 2133 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 53: /* value: VALUE_FLOAT  */
#line 330 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<FloatLit>((yyvsp[0].sv_float));
    }
#line 2141 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 54: /* value: VALUE_STRING  */
#line 334 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<StringLit>((yyvsp[0].sv_str));
    }
#line 2149 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 55: /* value: VALUE_BOOL  */
#line 338 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<BoolLit>((yyvsp[0].sv_bool));
    }
#line 2157 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 56: /* condition: col op expr  */
#line 345 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BinaryExpr>((yyvsp[-2].sv_col), (yyvsp[-1].sv_comp_op), (yyvsp[0].sv_expr));
    }
#line 2165 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 57: /* optWhereClause: %empty  */
#line 351 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                      { /* ignore*/ }
#line 2171 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 58: /* optWhereClause: WHERE whereClause  */
#line 353 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_conds) = (yyvsp[0].sv_conds);
    }
#line 2179 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 59: /* whereClause: condition  */
#line 360 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_conds) = std::vector<std::shared_ptr<BinaryExpr>>{(yyvsp[0].sv_cond)};
    }
#line 2187 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 60: /* whereClause: whereClause AND condition  */
#line 364 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_conds).push_back((yyvsp[0].sv_cond));
    }
#line 2195 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 61: /* col: tbName '.' colName  */
#line 371 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
#line 2203 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 62: /* col: colName  */
#line 375 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>("", (yyvsp[0].sv_str));
    }
#line 2211 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 63: /* col: aggCol  */
#line 379 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = (yyvsp[0].sv_col);
    }
#line 2219 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 64: /* colList: col  */
#line 386 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols) = std::vector<std::shared_ptr<Col>>{(yyvsp[0].sv_col)};
    }
#line 2227 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 65: /* colList: colList ',' col  */
#line 390 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols).push_back((yyvsp[0].sv_col));
    }
#line 2235 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 66: /* op: '='  */
#line 397 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_EQ;
    }
#line 2243 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 67: /* op: '<'  */
#line 401 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LT;
    }
#line 2251 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 68: /* op: '>'  */
#line 405 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GT;
    }
#line 2259 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 69: /* op: NEQ  */
#line 409 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_NE;
    }
#line 2267 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 70: /* op: LEQ  */
#line 413 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LE;
    }
#line 2275 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 71: /* op: GEQ  */
#line 417 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GE;
    }
#line 2283 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 72: /* expr: value  */
#line 424 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_val));
    }
#line 2291 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 73: /* expr: col  */
#line 428 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_col));
    }
#line 2299 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 74: /* setClauses: setClause  */
#line 435 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses) = std::vector<std::shared_ptr<SetClause>>{(yyvsp[0].sv_set_clause)};
    }
#line 2307 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 75: /* setClauses: setClauses ',' setClause  */
#line 439 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses).push_back((yyvsp[0].sv_set_clause));       /*我怎么感觉这里写错了？难道不应该把setClauses先赋值给$$吗？而且setClause也不应该是vector而应该是ptr*/
    }
#line 2315 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 76: /* setClause: colName '=' value  */
#line 446 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-2].sv_str), (yyvsp[0].sv_val));
    }
#line 2323 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 77: /* setClause: colName '=' colName value  */
#line 450 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-3].sv_str), (yyvsp[0].sv_val), true);
    }
#line 2331 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 78: /* setClause: colName '=' colName '+' value  */
#line 454 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-4].sv_str), (yyvsp[0].sv_val), true);
    }
#line 2339 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 79: /* selector: '*'  */
#line 461 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols) = {};
    }
#line 2347 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 81: /* aggCol: MAX '(' col ')' AS alias  */
#line 469 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_MAX, (yyvsp[0].sv_str)));
    }
#line 2355 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 82: /* aggCol: MIN '(' col ')' AS alias  */
#line 473 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_MIN, (yyvsp[0].sv_str)));
    }
#line 2363 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 83: /* aggCol: SUM '(' col ')' AS alias  */
#line 477 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_SUM, (yyvsp[0].sv_str)));
    }
#line 2371 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 84: /* aggCol: AVG '(' col ')' AS alias  */
#line 481 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_AVG, (yyvsp[0].sv_str)));
    }
#line 2379 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 85: /* aggCol: COUNT '(' col ')' AS alias  */
#line 485 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_COUNT, (yyvsp[0].sv_str)));
    }
#line 2387 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 86: /* aggCol: COUNT '(' '*' ')' AS alias  */
#line 489 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>("", "*", AGG_COUNT, (yyvsp[0].sv_str)));
    }
#line 2395 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 87: /* aggCol: MAX '(' col ')'  */
#line 493 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_MAX, ""));
    }
#line 2403 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 88: /* aggCol: MIN '(' col ')'  */
#line 497 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_MIN, ""));
    }
#line 2411 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 89: /* aggCol: SUM '(' col ')'  */
#line 501 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_SUM, ""));
    }
#line 2419 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 90: /* aggCol: AVG '(' col ')'  */
#line 505 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_AVG, ""));
    }
#line 2427 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 91: /* aggCol: COUNT '(' col ')'  */
#line 509 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_COUNT, ""));
    }
#line 2435 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 92: /* aggCol: COUNT '(' '*' ')'  */
#line 513 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>("", "*", AGG_COUNT, ""));
    }
#line 2443 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 93: /* tableList: tbNameWithAlias  */
#line 520 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 2451 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 94: /* tableList: tableList ',' tbNameWithAlias  */
#line 524 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2459 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 95: /* tbNameWithAlias: tbName  */
#line 535 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_str) = (yyvsp[0].sv_str);
    }
#line 2467 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 96: /* tbNameWithAlias: tbName alias  */
#line 539 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        alias_map[(yyvsp[0].sv_str)] = (yyvsp[-1].sv_str);
        pam_saila[(yyvsp[-1].sv_str)] = (yyvsp[0].sv_str);
        (yyval.sv_str) = (yyvsp[-1].sv_str);
    }
#line 2477 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 97: /* join_exprss: tbNameWithAlias join_exprs  */
#line 547 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_join_exprs) = (yyvsp[0].sv_join_exprs);
        for (auto& join_expr : (yyval.sv_join_exprs)) {
            join_expr->left = (yyvsp[-1].sv_str);
        }
    }
#line 2488 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 98: /* join_exprs: join_expr  */
#line 557 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_join_exprs) = std::vector<std::shared_ptr<JoinExpr>>{(yyvsp[0].sv_join_expr)};
    }
#line 2496 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 99: /* join_exprs: join_exprs join_expr  */
#line 561 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_join_exprs).push_back((yyvsp[0].sv_join_expr));
    }
#line 2504 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 100: /* join_expr: join_type tbNameWithAlias ON whereClause  */
#line 567 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_join_expr) = std::make_shared<JoinExpr>("", (yyvsp[-2].sv_str), (yyvsp[0].sv_conds), (yyvsp[-3].join_type_dir));
    }
#line 2512 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 101: /* join_type: JOIN  */
#line 572 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
               { (yyval.join_type_dir) = INNER_JOIN; }
#line 2518 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 102: /* join_type: INNER JOIN  */
#line 573 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                     { (yyval.join_type_dir) = INNER_JOIN; }
#line 2524 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 103: /* join_type: LEFT JOIN  */
#line 574 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                    { (yyval.join_type_dir) = LEFT_JOIN; }
#line 2530 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 104: /* join_type: RIGHT JOIN  */
#line 575 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                     { (yyval.join_type_dir) = RIGHT_JOIN; }
#line 2536 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 105: /* join_type: FULL JOIN  */
#line 576 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                    { (yyval.join_type_dir) = FULL_JOIN; }
#line 2542 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 106: /* join_type: SEMI JOIN  */
#line 577 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                    { (yyval.join_type_dir) = SEMI_JOIN; }
#line 2548 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 107: /* opt_order_clause: ORDER BY order_clauses  */
#line 583 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    { 
        (yyval.sv_orderbys) = (yyvsp[0].sv_orderbys); 
    }
#line 2556 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 108: /* opt_order_clause: %empty  */
#line 586 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                      { /* ignore*/ }
#line 2562 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 109: /* order_clauses: order_clause  */
#line 591 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_orderbys) = std::vector<std::shared_ptr<OrderBy>>{(yyvsp[0].sv_orderby)};
    }
#line 2570 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 110: /* order_clauses: order_clauses ',' order_clause  */
#line 595 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_orderbys).push_back((yyvsp[0].sv_orderby));
    }
#line 2578 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 111: /* order_clause: col opt_asc_desc  */
#line 602 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
    { 
        (yyval.sv_orderby) = std::make_shared<OrderBy>((yyvsp[-1].sv_col), (yyvsp[0].sv_orderby_dir));
    }
#line 2586 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 112: /* opt_asc_desc: ASC  */
#line 608 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_ASC;     }
#line 2592 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 113: /* opt_asc_desc: DESC  */
#line 609 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_DESC;    }
#line 2598 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 114: /* opt_asc_desc: %empty  */
#line 610 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_ASC; }
#line 2604 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 115: /* set_knob_type: ENABLE_NESTLOOP  */
#line 614 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                    { (yyval.sv_setKnobType) = EnableNestLoop; }
#line 2610 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 116: /* set_knob_type: ENABLE_SORTMERGE  */
#line 615 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"
                         { (yyval.sv_setKnobType) = EnableSortMerge; }
#line 2616 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;


#line 2620 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.tab.cpp"

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
        yyerror (&yylloc, yyscanner, yymsgp);
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
                      yytoken, &yylval, &yylloc, yyscanner);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, yyscanner);
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
  yyerror (&yylloc, yyscanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, yyscanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, yyscanner);
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

#line 625 "/home/ubuntu/db2025-jinsenianhua/src/parser/yacc.y"

