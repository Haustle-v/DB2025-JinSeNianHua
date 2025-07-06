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
#line 1 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"

#include "ast.h"
#include "yacc.tab.h"
#include <iostream>
#include <memory>
#include <limits.h>
#include <set>
#include <unordered_map>
std::unordered_map<std::string, std::string> alias_map;
std::unordered_map<std::string, std::string> pam_saila;

int yylex(YYSTYPE *yylval, YYLTYPE *yylloc);

void yyerror(YYLTYPE *locp, const char* s) {
    std::cerr << "Parser Error at line " << locp->first_line << " column " << locp->first_column << ": " << s << std::endl;
}

using namespace ast;

#line 91 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"

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
  YYSYMBOL_65_ = 65,                       /* ';'  */
  YYSYMBOL_66_ = 66,                       /* '='  */
  YYSYMBOL_67_ = 67,                       /* '('  */
  YYSYMBOL_68_ = 68,                       /* ')'  */
  YYSYMBOL_69_ = 69,                       /* ','  */
  YYSYMBOL_70_ = 70,                       /* '.'  */
  YYSYMBOL_71_ = 71,                       /* '<'  */
  YYSYMBOL_72_ = 72,                       /* '>'  */
  YYSYMBOL_73_ = 73,                       /* '+'  */
  YYSYMBOL_74_ = 74,                       /* '*'  */
  YYSYMBOL_YYACCEPT = 75,                  /* $accept  */
  YYSYMBOL_start = 76,                     /* start  */
  YYSYMBOL_stmt = 77,                      /* stmt  */
  YYSYMBOL_txnStmt = 78,                   /* txnStmt  */
  YYSYMBOL_dbStmt = 79,                    /* dbStmt  */
  YYSYMBOL_setStmt = 80,                   /* setStmt  */
  YYSYMBOL_io_stmt = 81,                   /* io_stmt  */
  YYSYMBOL_ddl = 82,                       /* ddl  */
  YYSYMBOL_dml = 83,                       /* dml  */
  YYSYMBOL_limit_clause = 84,              /* limit_clause  */
  YYSYMBOL_optGroupByClause = 85,          /* optGroupByClause  */
  YYSYMBOL_optHavingClause = 86,           /* optHavingClause  */
  YYSYMBOL_fieldList = 87,                 /* fieldList  */
  YYSYMBOL_colNameList = 88,               /* colNameList  */
  YYSYMBOL_field = 89,                     /* field  */
  YYSYMBOL_type = 90,                      /* type  */
  YYSYMBOL_valueList = 91,                 /* valueList  */
  YYSYMBOL_value = 92,                     /* value  */
  YYSYMBOL_condition = 93,                 /* condition  */
  YYSYMBOL_optWhereClause = 94,            /* optWhereClause  */
  YYSYMBOL_whereClause = 95,               /* whereClause  */
  YYSYMBOL_col = 96,                       /* col  */
  YYSYMBOL_colList = 97,                   /* colList  */
  YYSYMBOL_op = 98,                        /* op  */
  YYSYMBOL_expr = 99,                      /* expr  */
  YYSYMBOL_setClauses = 100,               /* setClauses  */
  YYSYMBOL_setClause = 101,                /* setClause  */
  YYSYMBOL_selector = 102,                 /* selector  */
  YYSYMBOL_aggCol = 103,                   /* aggCol  */
  YYSYMBOL_tableList = 104,                /* tableList  */
  YYSYMBOL_tbNameWithAlias = 105,          /* tbNameWithAlias  */
  YYSYMBOL_join_exprss = 106,              /* join_exprss  */
  YYSYMBOL_join_exprs = 107,               /* join_exprs  */
  YYSYMBOL_join_expr = 108,                /* join_expr  */
  YYSYMBOL_join_type = 109,                /* join_type  */
  YYSYMBOL_opt_order_clause = 110,         /* opt_order_clause  */
  YYSYMBOL_order_clauses = 111,            /* order_clauses  */
  YYSYMBOL_order_clause = 112,             /* order_clause  */
  YYSYMBOL_opt_asc_desc = 113,             /* opt_asc_desc  */
  YYSYMBOL_set_knob_type = 114,            /* set_knob_type  */
  YYSYMBOL_tbName = 115,                   /* tbName  */
  YYSYMBOL_colName = 116,                  /* colName  */
  YYSYMBOL_alias = 117,                    /* alias  */
  YYSYMBOL_fileName = 118                  /* fileName  */
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
#define YYFINAL  58
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   228

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  226

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   319


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
      67,    68,    74,    73,    69,     2,    70,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    65,
      71,    66,    72,     2,     2,     2,     2,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    71,    71,    76,    81,    86,    91,   100,   101,   102,
     103,   104,   108,   112,   116,   120,   127,   131,   135,   142,
     149,   155,   159,   165,   169,   173,   177,   181,   188,   192,
     196,   200,   204,   222,   227,   234,   237,   244,   245,   253,
     257,   264,   268,   275,   282,   286,   290,   297,   301,   308,
     312,   316,   320,   327,   334,   335,   342,   346,   353,   357,
     361,   368,   372,   379,   383,   387,   391,   395,   399,   406,
     410,   417,   421,   428,   432,   436,   443,   447,   451,   455,
     459,   463,   467,   471,   475,   479,   483,   487,   491,   495,
     502,   506,   517,   521,   529,   539,   543,   549,   555,   556,
     557,   558,   559,   560,   565,   569,   573,   577,   584,   591,
     592,   593,   597,   598,   601,   603,   605,   607
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
  "VALUE_BOOL", "';'", "'='", "'('", "')'", "','", "'.'", "'<'", "'>'",
  "'+'", "'*'", "$accept", "start", "stmt", "txnStmt", "dbStmt", "setStmt",
  "io_stmt", "ddl", "dml", "limit_clause", "optGroupByClause",
  "optHavingClause", "fieldList", "colNameList", "field", "type",
  "valueList", "value", "condition", "optWhereClause", "whereClause",
  "col", "colList", "op", "expr", "setClauses", "setClause", "selector",
  "aggCol", "tableList", "tbNameWithAlias", "join_exprss", "join_exprs",
  "join_expr", "join_type", "opt_order_clause", "order_clauses",
  "order_clause", "opt_asc_desc", "set_knob_type", "tbName", "colName",
  "alias", "fileName", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-122)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-115)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      81,     1,     7,    10,   -47,     5,    30,   -47,   -24,    60,
    -122,  -122,  -122,  -122,  -122,  -122,   143,    -1,  -122,    50,
      18,  -122,  -122,  -122,  -122,  -122,  -122,  -122,    74,   -47,
     -47,   -47,   -47,  -122,  -122,   -47,   -47,    76,  -122,  -122,
      15,    49,    53,    55,    56,    73,    78,    77,  -122,  -122,
      80,   137,  -122,    84,  -122,  -122,  -122,   147,  -122,  -122,
     -47,    93,    95,  -122,   105,   165,   160,   119,  -122,  -122,
     116,     2,     2,     2,     2,    82,     2,   -47,   119,   -47,
    -122,   119,   119,   119,   112,     2,  -122,  -122,   -15,  -122,
     117,  -122,   113,   114,   118,   120,   122,   123,  -122,   -11,
      33,   160,   125,  -122,  -122,   -61,  -122,   115,   -33,  -122,
      23,    54,  -122,   162,    87,   119,  -122,   111,   138,   145,
     146,   148,   149,   150,   -47,   151,  -122,   168,   172,   174,
     175,   176,    33,  -122,   -47,   151,  -122,  -122,  -122,   119,
    -122,   136,  -122,  -122,  -122,   119,  -122,  -122,  -122,  -122,
    -122,    61,  -122,     2,  -122,  -122,  -122,  -122,  -122,  -122,
     -22,  -122,  -122,    34,   125,   125,   125,   125,   125,   125,
    -122,   189,   157,  -122,  -122,  -122,  -122,  -122,  -122,   166,
     157,  -122,   152,  -122,  -122,    54,  -122,  -122,  -122,  -122,
      54,  -122,  -122,  -122,  -122,  -122,  -122,  -122,     2,     2,
     193,     2,   193,   141,  -122,  -122,    80,   162,   194,   161,
     162,   161,  -122,     2,   154,  -122,  -122,    71,   144,  -122,
    -122,  -122,  -122,  -122,     2,  -122
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       4,     3,    12,    13,    14,    15,     0,     0,     5,     0,
       0,    10,     7,    11,     6,     8,     9,    16,     0,     0,
       0,     0,     0,   114,    25,     0,     0,     0,   112,   113,
       0,     0,     0,     0,     0,     0,     0,   115,    76,    61,
      77,     0,    60,     0,    59,    18,   117,     0,     1,     2,
       0,     0,     0,    24,     0,     0,    54,     0,    21,    22,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     0,     0,     0,     0,     0,    29,   115,    54,    71,
       0,    20,     0,     0,     0,     0,     0,     0,    62,    54,
      90,    54,    92,    58,    19,     0,    39,     0,     0,    41,
       0,     0,    56,    55,     0,     0,    30,     0,    84,    85,
      86,    87,    89,    88,     0,    35,    98,     0,     0,     0,
       0,     0,    94,    95,     0,    35,   116,    93,    23,     0,
      44,     0,    46,    43,    26,     0,    27,    51,    49,    50,
      52,     0,    47,     0,    67,    66,    68,    63,    64,    65,
       0,    72,    73,     0,     0,     0,     0,     0,     0,     0,
      91,     0,    37,    99,   100,   101,   102,   103,    96,     0,
      37,    40,     0,    42,    28,     0,    57,    69,    70,    53,
       0,    74,    78,    79,    80,    81,    83,    82,     0,     0,
     105,     0,   105,     0,    48,    75,    36,    38,     0,    34,
      97,    34,    45,     0,     0,    31,    32,   111,   104,   106,
      33,   110,   109,   108,     0,   107
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,   196,     6,
      83,    39,  -122,   139,    85,  -122,  -122,  -108,    67,    47,
    -121,    -9,    25,  -122,  -122,  -122,   106,  -122,  -122,  -122,
     -85,  -122,  -122,    94,  -122,    26,  -122,     3,  -122,  -122,
      -3,   -64,     0,  -122
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,   215,
     172,   200,   105,   108,   106,   143,   151,   152,   112,    86,
     113,   114,    50,   160,   189,    88,    89,    51,    52,    99,
     100,   101,   132,   133,   134,   209,   218,   219,   223,    41,
      53,    54,   137,    57
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    34,    85,    90,    37,    27,    85,   138,   139,   162,
      38,    39,    33,    29,   103,    35,    31,   107,   109,   109,
      42,    43,    44,    45,    46,    28,    61,    62,    63,    64,
      40,    30,    65,    66,    32,   144,   145,    47,   147,   170,
     148,   149,   150,    36,    42,    43,    44,    45,    46,   179,
      58,    90,   187,   163,   115,   191,    68,    80,   124,   126,
      56,    47,    92,    93,    94,    95,    97,    98,    69,   127,
     128,   129,   130,   131,   102,   107,   104,   204,   207,   221,
     210,   183,   205,    59,     1,   222,     2,    60,     3,     4,
       5,   146,   145,     6,   147,    67,   148,   149,   150,     7,
       8,     9,    42,    43,    44,    45,    46,   190,    10,    11,
      12,    13,    14,    15,   147,    70,   148,   149,   150,    47,
      71,   102,    72,    73,    42,    43,    44,    45,    46,   184,
     185,   102,    16,    17,    48,   116,   140,   141,   142,    18,
      74,    47,   154,   155,   156,    75,   125,  -114,   135,    76,
      77,   188,     5,   157,    78,     6,    96,    79,   158,   159,
      81,     7,    82,     9,   192,   193,   194,   195,   196,   197,
      87,   147,    83,   148,   149,   150,    84,    85,    87,   111,
      91,   118,   119,   117,   136,   164,   120,   153,   121,    49,
     122,   123,   165,   166,   173,   167,   168,   169,   174,   171,
     175,   176,   177,   182,   217,   198,   199,   201,   208,   212,
     213,   214,    55,   224,   203,   217,   220,   216,   180,   202,
     186,   161,   110,   206,   181,     0,   178,   225,   211
};

static const yytype_int16 yycheck[] =
{
       9,     4,    17,    67,     7,     4,    17,    68,    69,   117,
      34,    35,    59,     6,    78,    10,     6,    81,    82,    83,
      42,    43,    44,    45,    46,    24,    29,    30,    31,    32,
      54,    24,    35,    36,    24,    68,    69,    59,    60,   124,
      62,    63,    64,    13,    42,    43,    44,    45,    46,   134,
       0,   115,   160,   117,    69,   163,    41,    60,    69,    26,
      61,    59,    71,    72,    73,    74,    75,    76,    53,    36,
      37,    38,    39,    40,    77,   139,    79,   185,   199,     8,
     201,   145,   190,    65,     3,    14,     5,    13,     7,     8,
       9,    68,    69,    12,    60,    19,    62,    63,    64,    18,
      19,    20,    42,    43,    44,    45,    46,    73,    27,    28,
      29,    30,    31,    32,    60,    66,    62,    63,    64,    59,
      67,   124,    67,    67,    42,    43,    44,    45,    46,    68,
      69,   134,    51,    52,    74,    88,    21,    22,    23,    58,
      67,    59,    55,    56,    57,    67,    99,    70,   101,    69,
      13,   160,     9,    66,    70,    12,    74,    10,    71,    72,
      67,    18,    67,    20,   164,   165,   166,   167,   168,   169,
      59,    60,    67,    62,    63,    64,    11,    17,    59,    67,
      64,    68,    68,    66,    59,    47,    68,    25,    68,   198,
      68,    68,    47,    47,    26,    47,    47,    47,    26,    48,
      26,    26,    26,    67,   213,    16,    49,    41,    15,    68,
      16,    50,    16,    69,    62,   224,    62,   211,   135,   180,
     153,   115,    83,   198,   139,    -1,   132,   224,   202
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     7,     8,     9,    12,    18,    19,    20,
      27,    28,    29,    30,    31,    32,    51,    52,    58,    76,
      77,    78,    79,    80,    81,    82,    83,     4,    24,     6,
      24,     6,    24,    59,   115,    10,    13,   115,    34,    35,
      54,   114,    42,    43,    44,    45,    46,    59,    74,    96,
      97,   102,   103,   115,   116,    83,    61,   118,     0,    65,
      13,   115,   115,   115,   115,   115,   115,    19,    41,    53,
      66,    67,    67,    67,    67,    67,    69,    13,    70,    10,
     115,    67,    67,    67,    11,    17,    94,    59,   100,   101,
     116,    64,    96,    96,    96,    96,    74,    96,    96,   104,
     105,   106,   115,   116,   115,    87,    89,   116,    88,   116,
      88,    67,    93,    95,    96,    69,    94,    66,    68,    68,
      68,    68,    68,    68,    69,    94,    26,    36,    37,    38,
      39,    40,   107,   108,   109,    94,    59,   117,    68,    69,
      21,    22,    23,    90,    68,    69,    68,    60,    62,    63,
      64,    91,    92,    25,    55,    56,    57,    66,    71,    72,
      98,   101,    92,   116,    47,    47,    47,    47,    47,    47,
     105,    48,    85,    26,    26,    26,    26,    26,   108,   105,
      85,    89,    67,   116,    68,    69,    93,    92,    96,    99,
      73,    92,   117,   117,   117,   117,   117,   117,    16,    49,
      86,    41,    86,    62,    92,    92,    97,    95,    15,   110,
      95,   110,    68,    16,    50,    84,    84,    96,   111,   112,
      62,     8,    14,   113,    69,   112
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    75,    76,    76,    76,    76,    76,    77,    77,    77,
      77,    77,    78,    78,    78,    78,    79,    79,    79,    79,
      80,    81,    81,    82,    82,    82,    82,    82,    83,    83,
      83,    83,    83,    84,    84,    85,    85,    86,    86,    87,
      87,    88,    88,    89,    90,    90,    90,    91,    91,    92,
      92,    92,    92,    93,    94,    94,    95,    95,    96,    96,
      96,    97,    97,    98,    98,    98,    98,    98,    98,    99,
      99,   100,   100,   101,   101,   101,   102,   102,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     104,   104,   105,   105,   106,   107,   107,   108,   109,   109,
     109,   109,   109,   109,   110,   110,   111,   111,   112,   113,
     113,   113,   114,   114,   115,   116,   117,   118
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     4,     2,     4,
       4,     3,     3,     6,     3,     2,     6,     6,     7,     4,
       5,     9,     9,     2,     0,     0,     3,     0,     2,     1,
       3,     1,     3,     2,     1,     4,     1,     1,     3,     1,
       1,     1,     1,     3,     0,     2,     1,     3,     3,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     4,     5,     1,     1,     6,     6,
       6,     6,     6,     6,     4,     4,     4,     4,     4,     4,
       1,     3,     1,     2,     2,     1,     2,     4,     1,     2,
       2,     2,     2,     2,     3,     0,     1,     3,     2,     1,
       1,     0,     1,     1,     1,     1,     1,     1
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
#line 72 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = (yyvsp[-1].sv_node);
        YYACCEPT;
    }
#line 1754 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 3: /* start: HELP  */
#line 77 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = std::make_shared<Help>();
        YYACCEPT;
    }
#line 1763 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 4: /* start: EXIT  */
#line 82 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1772 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 5: /* start: T_EOF  */
#line 87 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1781 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 6: /* start: io_stmt  */
#line 92 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = (yyvsp[0].sv_node);
        YYACCEPT;
    }
#line 1790 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 12: /* txnStmt: TXN_BEGIN  */
#line 109 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnBegin>();
    }
#line 1798 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 13: /* txnStmt: TXN_COMMIT  */
#line 113 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnCommit>();
    }
#line 1806 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 14: /* txnStmt: TXN_ABORT  */
#line 117 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnAbort>();
    }
#line 1814 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 15: /* txnStmt: TXN_ROLLBACK  */
#line 121 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnRollback>();
    }
#line 1822 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 16: /* dbStmt: SHOW TABLES  */
#line 128 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowTables>();
    }
#line 1830 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 17: /* dbStmt: SHOW INDEX FROM tbName  */
#line 132 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowIndex>((yyvsp[0].sv_str));
    }
#line 1838 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 18: /* dbStmt: EXPLAIN dml  */
#line 136 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        if(auto select = std::dynamic_pointer_cast<SelectStmt>((yyvsp[0].sv_node))){
            select->need_explain = true;
            (yyval.sv_node) = select;
        }
    }
#line 1849 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 19: /* dbStmt: LOAD fileName INTO tbName  */
#line 143 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
         (yyval.sv_node) = std::make_shared<LoadStmt>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
#line 1857 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 20: /* setStmt: SET set_knob_type '=' VALUE_BOOL  */
#line 150 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<SetStmt>((yyvsp[-2].sv_setKnobType), (yyvsp[0].sv_bool));
    }
#line 1865 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 21: /* io_stmt: SET OUTPUT_FILE ON  */
#line 156 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<IoEnable>(true);
    }
#line 1873 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 22: /* io_stmt: SET OUTPUT_FILE OFF  */
#line 160 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<IoEnable>(false);
    }
#line 1881 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 23: /* ddl: CREATE TABLE tbName '(' fieldList ')'  */
#line 166 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateTable>((yyvsp[-3].sv_str), (yyvsp[-1].sv_fields));
    }
#line 1889 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 24: /* ddl: DROP TABLE tbName  */
#line 170 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropTable>((yyvsp[0].sv_str));
    }
#line 1897 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 25: /* ddl: DESC tbName  */
#line 174 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DescTable>((yyvsp[0].sv_str));
    }
#line 1905 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 26: /* ddl: CREATE INDEX tbName '(' colNameList ')'  */
#line 178 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1913 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 27: /* ddl: DROP INDEX tbName '(' colNameList ')'  */
#line 182 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1921 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 28: /* dml: INSERT INTO tbName VALUES '(' valueList ')'  */
#line 189 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<InsertStmt>((yyvsp[-4].sv_str), (yyvsp[-1].sv_vals));
    }
#line 1929 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 29: /* dml: DELETE FROM tbName optWhereClause  */
#line 193 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DeleteStmt>((yyvsp[-1].sv_str), (yyvsp[0].sv_conds));
    }
#line 1937 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 30: /* dml: UPDATE tbName SET setClauses optWhereClause  */
#line 197 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<UpdateStmt>((yyvsp[-3].sv_str), (yyvsp[-1].sv_set_clauses), (yyvsp[0].sv_conds));
    }
#line 1945 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 31: /* dml: SELECT selector FROM tableList optWhereClause optGroupByClause optHavingClause opt_order_clause limit_clause  */
#line 201 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<SelectStmt>((yyvsp[-7].sv_cols), (yyvsp[-5].sv_strs), (yyvsp[-4].sv_conds), (yyvsp[-3].sv_cols), (yyvsp[-2].sv_conds), (yyvsp[-1].sv_orderbys), (yyvsp[0].sv_int));
    }
#line 1953 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 32: /* dml: SELECT selector FROM join_exprss optWhereClause optGroupByClause optHavingClause opt_order_clause limit_clause  */
#line 205 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
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
#line 1972 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 33: /* limit_clause: LIMIT VALUE_INT  */
#line 223 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_int) = (yyvsp[0].sv_int);
    }
#line 1980 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 34: /* limit_clause: %empty  */
#line 227 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_int) = INT_MAX;
    }
#line 1988 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 35: /* optGroupByClause: %empty  */
#line 234 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols) = {};
    }
#line 1996 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 36: /* optGroupByClause: GROUP BY colList  */
#line 238 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols) = (yyvsp[0].sv_cols);
    }
#line 2004 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 37: /* optHavingClause: %empty  */
#line 244 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                      { /* ignore*/ }
#line 2010 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 38: /* optHavingClause: HAVING whereClause  */
#line 246 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_conds) = (yyvsp[0].sv_conds);
    }
#line 2018 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 39: /* fieldList: field  */
#line 254 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_fields) = std::vector<std::shared_ptr<Field>>{(yyvsp[0].sv_field)};
    }
#line 2026 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 40: /* fieldList: fieldList ',' field  */
#line 258 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_fields).push_back((yyvsp[0].sv_field));
    }
#line 2034 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 41: /* colNameList: colName  */
#line 265 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 2042 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 42: /* colNameList: colNameList ',' colName  */
#line 269 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2050 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 43: /* field: colName type  */
#line 276 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-1].sv_str), (yyvsp[0].sv_type_len));
    }
#line 2058 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 44: /* type: INT  */
#line 283 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_INT, sizeof(int));
    }
#line 2066 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 45: /* type: CHAR '(' VALUE_INT ')'  */
#line 287 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_STRING, (yyvsp[-1].sv_int));
    }
#line 2074 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 46: /* type: FLOAT  */
#line 291 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_FLOAT, sizeof(float));
    }
#line 2082 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 47: /* valueList: value  */
#line 298 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_vals) = std::vector<std::shared_ptr<Value>>{(yyvsp[0].sv_val)};
    }
#line 2090 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 48: /* valueList: valueList ',' value  */
#line 302 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_vals).push_back((yyvsp[0].sv_val));
    }
#line 2098 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 49: /* value: VALUE_INT  */
#line 309 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<IntLit>((yyvsp[0].sv_int));
    }
#line 2106 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 50: /* value: VALUE_FLOAT  */
#line 313 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<FloatLit>((yyvsp[0].sv_float));
    }
#line 2114 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 51: /* value: VALUE_STRING  */
#line 317 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<StringLit>((yyvsp[0].sv_str));
    }
#line 2122 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 52: /* value: VALUE_BOOL  */
#line 321 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<BoolLit>((yyvsp[0].sv_bool));
    }
#line 2130 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 53: /* condition: col op expr  */
#line 328 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BinaryExpr>((yyvsp[-2].sv_col), (yyvsp[-1].sv_comp_op), (yyvsp[0].sv_expr));
    }
#line 2138 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 54: /* optWhereClause: %empty  */
#line 334 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                      { /* ignore*/ }
#line 2144 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 55: /* optWhereClause: WHERE whereClause  */
#line 336 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_conds) = (yyvsp[0].sv_conds);
    }
#line 2152 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 56: /* whereClause: condition  */
#line 343 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_conds) = std::vector<std::shared_ptr<BinaryExpr>>{(yyvsp[0].sv_cond)};
    }
#line 2160 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 57: /* whereClause: whereClause AND condition  */
#line 347 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_conds).push_back((yyvsp[0].sv_cond));
    }
#line 2168 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 58: /* col: tbName '.' colName  */
#line 354 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
#line 2176 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 59: /* col: colName  */
#line 358 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>("", (yyvsp[0].sv_str));
    }
#line 2184 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 60: /* col: aggCol  */
#line 362 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = (yyvsp[0].sv_col);
    }
#line 2192 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 61: /* colList: col  */
#line 369 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols) = std::vector<std::shared_ptr<Col>>{(yyvsp[0].sv_col)};
    }
#line 2200 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 62: /* colList: colList ',' col  */
#line 373 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols).push_back((yyvsp[0].sv_col));
    }
#line 2208 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 63: /* op: '='  */
#line 380 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_EQ;
    }
#line 2216 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 64: /* op: '<'  */
#line 384 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LT;
    }
#line 2224 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 65: /* op: '>'  */
#line 388 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GT;
    }
#line 2232 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 66: /* op: NEQ  */
#line 392 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_NE;
    }
#line 2240 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 67: /* op: LEQ  */
#line 396 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LE;
    }
#line 2248 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 68: /* op: GEQ  */
#line 400 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GE;
    }
#line 2256 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 69: /* expr: value  */
#line 407 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_val));
    }
#line 2264 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 70: /* expr: col  */
#line 411 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_col));
    }
#line 2272 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 71: /* setClauses: setClause  */
#line 418 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses) = std::vector<std::shared_ptr<SetClause>>{(yyvsp[0].sv_set_clause)};
    }
#line 2280 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 72: /* setClauses: setClauses ',' setClause  */
#line 422 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses).push_back((yyvsp[0].sv_set_clause));       /*我怎么感觉这里写错了？难道不应该把setClauses先赋值给$$吗？而且setClause也不应该是vector而应该是ptr*/
    }
#line 2288 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 73: /* setClause: colName '=' value  */
#line 429 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-2].sv_str), (yyvsp[0].sv_val));
    }
#line 2296 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 74: /* setClause: colName '=' colName value  */
#line 433 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-3].sv_str), (yyvsp[0].sv_val), true);
    }
#line 2304 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 75: /* setClause: colName '=' colName '+' value  */
#line 437 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-4].sv_str), (yyvsp[0].sv_val), true);
    }
#line 2312 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 76: /* selector: '*'  */
#line 444 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols) = {};
    }
#line 2320 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 78: /* aggCol: MAX '(' col ')' AS alias  */
#line 452 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_MAX, (yyvsp[0].sv_str)));
    }
#line 2328 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 79: /* aggCol: MIN '(' col ')' AS alias  */
#line 456 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_MIN, (yyvsp[0].sv_str)));
    }
#line 2336 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 80: /* aggCol: SUM '(' col ')' AS alias  */
#line 460 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_SUM, (yyvsp[0].sv_str)));
    }
#line 2344 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 81: /* aggCol: AVG '(' col ')' AS alias  */
#line 464 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_AVG, (yyvsp[0].sv_str)));
    }
#line 2352 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 82: /* aggCol: COUNT '(' col ')' AS alias  */
#line 468 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_COUNT, (yyvsp[0].sv_str)));
    }
#line 2360 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 83: /* aggCol: COUNT '(' '*' ')' AS alias  */
#line 472 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>("", "*", AGG_COUNT, (yyvsp[0].sv_str)));
    }
#line 2368 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 84: /* aggCol: MAX '(' col ')'  */
#line 476 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_MAX, ""));
    }
#line 2376 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 85: /* aggCol: MIN '(' col ')'  */
#line 480 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_MIN, ""));
    }
#line 2384 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 86: /* aggCol: SUM '(' col ')'  */
#line 484 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_SUM, ""));
    }
#line 2392 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 87: /* aggCol: AVG '(' col ')'  */
#line 488 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_AVG, ""));
    }
#line 2400 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 88: /* aggCol: COUNT '(' col ')'  */
#line 492 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_COUNT, ""));
    }
#line 2408 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 89: /* aggCol: COUNT '(' '*' ')'  */
#line 496 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>("", "*", AGG_COUNT, ""));
    }
#line 2416 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 90: /* tableList: tbNameWithAlias  */
#line 503 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 2424 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 91: /* tableList: tableList ',' tbNameWithAlias  */
#line 507 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2432 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 92: /* tbNameWithAlias: tbName  */
#line 518 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_str) = (yyvsp[0].sv_str);
    }
#line 2440 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 93: /* tbNameWithAlias: tbName alias  */
#line 522 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        alias_map[(yyvsp[0].sv_str)] = (yyvsp[-1].sv_str);
        pam_saila[(yyvsp[-1].sv_str)] = (yyvsp[0].sv_str);
        (yyval.sv_str) = (yyvsp[-1].sv_str);
    }
#line 2450 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 94: /* join_exprss: tbNameWithAlias join_exprs  */
#line 530 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_join_exprs) = (yyvsp[0].sv_join_exprs);
        for (auto& join_expr : (yyval.sv_join_exprs)) {
            join_expr->left = (yyvsp[-1].sv_str);
        }
    }
#line 2461 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 95: /* join_exprs: join_expr  */
#line 540 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_join_exprs) = std::vector<std::shared_ptr<JoinExpr>>{(yyvsp[0].sv_join_expr)};
    }
#line 2469 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 96: /* join_exprs: join_exprs join_expr  */
#line 544 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_join_exprs).push_back((yyvsp[0].sv_join_expr));
    }
#line 2477 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 97: /* join_expr: join_type tbNameWithAlias ON whereClause  */
#line 550 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_join_expr) = std::make_shared<JoinExpr>("", (yyvsp[-2].sv_str), (yyvsp[0].sv_conds), (yyvsp[-3].join_type_dir));
    }
#line 2485 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 98: /* join_type: JOIN  */
#line 555 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
               { (yyval.join_type_dir) = INNER_JOIN; }
#line 2491 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 99: /* join_type: INNER JOIN  */
#line 556 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                     { (yyval.join_type_dir) = INNER_JOIN; }
#line 2497 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 100: /* join_type: LEFT JOIN  */
#line 557 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                    { (yyval.join_type_dir) = LEFT_JOIN; }
#line 2503 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 101: /* join_type: RIGHT JOIN  */
#line 558 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                     { (yyval.join_type_dir) = RIGHT_JOIN; }
#line 2509 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 102: /* join_type: FULL JOIN  */
#line 559 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                    { (yyval.join_type_dir) = FULL_JOIN; }
#line 2515 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 103: /* join_type: SEMI JOIN  */
#line 560 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                    { (yyval.join_type_dir) = SEMI_JOIN; }
#line 2521 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 104: /* opt_order_clause: ORDER BY order_clauses  */
#line 566 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    { 
        (yyval.sv_orderbys) = (yyvsp[0].sv_orderbys); 
    }
#line 2529 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 105: /* opt_order_clause: %empty  */
#line 569 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                      { /* ignore*/ }
#line 2535 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 106: /* order_clauses: order_clause  */
#line 574 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_orderbys) = std::vector<std::shared_ptr<OrderBy>>{(yyvsp[0].sv_orderby)};
    }
#line 2543 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 107: /* order_clauses: order_clauses ',' order_clause  */
#line 578 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_orderbys).push_back((yyvsp[0].sv_orderby));
    }
#line 2551 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 108: /* order_clause: col opt_asc_desc  */
#line 585 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    { 
        (yyval.sv_orderby) = std::make_shared<OrderBy>((yyvsp[-1].sv_col), (yyvsp[0].sv_orderby_dir));
    }
#line 2559 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 109: /* opt_asc_desc: ASC  */
#line 591 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_ASC;     }
#line 2565 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 110: /* opt_asc_desc: DESC  */
#line 592 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_DESC;    }
#line 2571 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 111: /* opt_asc_desc: %empty  */
#line 593 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_ASC; }
#line 2577 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 112: /* set_knob_type: ENABLE_NESTLOOP  */
#line 597 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                    { (yyval.sv_setKnobType) = EnableNestLoop; }
#line 2583 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 113: /* set_knob_type: ENABLE_SORTMERGE  */
#line 598 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                         { (yyval.sv_setKnobType) = EnableSortMerge; }
#line 2589 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;


#line 2593 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"

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

#line 608 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"

