/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "yacc.y" /* yacc.c:339  */

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

#line 86 "yacc.tab.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "yacc.tab.hpp".  */
#ifndef YY_YY_YACC_TAB_HPP_INCLUDED
# define YY_YY_YACC_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SHOW = 258,
    TABLES = 259,
    CREATE = 260,
    TABLE = 261,
    DROP = 262,
    DESC = 263,
    INSERT = 264,
    INTO = 265,
    VALUES = 266,
    DELETE = 267,
    FROM = 268,
    ASC = 269,
    ORDER = 270,
    BY = 271,
    WHERE = 272,
    UPDATE = 273,
    SET = 274,
    SELECT = 275,
    INT = 276,
    CHAR = 277,
    FLOAT = 278,
    INDEX = 279,
    AND = 280,
    JOIN = 281,
    EXIT = 282,
    HELP = 283,
    TXN_BEGIN = 284,
    TXN_COMMIT = 285,
    TXN_ABORT = 286,
    TXN_ROLLBACK = 287,
    ORDER_BY = 288,
    ENABLE_NESTLOOP = 289,
    ENABLE_SORTMERGE = 290,
    INNER = 291,
    LEFT = 292,
    RIGHT = 293,
    FULL = 294,
    SEMI = 295,
    ON = 296,
    MAX = 297,
    MIN = 298,
    SUM = 299,
    AVG = 300,
    COUNT = 301,
    AS = 302,
    GROUP = 303,
    HAVING = 304,
    LIMIT = 305,
    EXPLAIN = 306,
    LOAD = 307,
    OFF = 308,
    OUTPUT_FILE = 309,
    LEQ = 310,
    NEQ = 311,
    GEQ = 312,
    T_EOF = 313,
    IDENTIFIER = 314,
    VALUE_STRING = 315,
    VALUE_PATH = 316,
    VALUE_INT = 317,
    VALUE_FLOAT = 318,
    VALUE_BOOL = 319
  };
#endif

/* Value type.  */

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (void *yyscanner);

#endif /* !YY_YY_YACC_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 210 "yacc.tab.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   319

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
static const yytype_uint16 yyrline[] =
{
       0,    73,    73,    78,    83,    88,    93,   102,   103,   104,
     105,   106,   110,   114,   118,   122,   129,   133,   137,   144,
     151,   157,   161,   167,   171,   175,   179,   183,   190,   194,
     198,   202,   206,   224,   229,   236,   239,   246,   247,   255,
     259,   266,   270,   277,   284,   288,   292,   299,   303,   310,
     314,   318,   322,   329,   336,   337,   344,   348,   355,   359,
     363,   370,   374,   381,   385,   389,   393,   397,   401,   408,
     412,   419,   423,   430,   434,   438,   445,   449,   453,   457,
     461,   465,   469,   473,   477,   481,   485,   489,   493,   497,
     504,   508,   519,   523,   531,   541,   545,   551,   557,   558,
     559,   560,   561,   562,   567,   571,   575,   579,   586,   593,
     594,   595,   599,   600,   603,   605,   607,   609
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SHOW", "TABLES", "CREATE", "TABLE",
  "DROP", "DESC", "INSERT", "INTO", "VALUES", "DELETE", "FROM", "ASC",
  "ORDER", "BY", "WHERE", "UPDATE", "SET", "SELECT", "INT", "CHAR",
  "FLOAT", "INDEX", "AND", "JOIN", "EXIT", "HELP", "TXN_BEGIN",
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
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,    59,    61,    40,    41,    44,
      46,    60,    62,    43,    42
};
# endif

#define YYPACT_NINF -122

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-122)))

#define YYTABLE_NINF -115

#define yytable_value_is_error(Yytable_value) \
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
static const yytype_uint8 yydefact[] =
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
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,   215,
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

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
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

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
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

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
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


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
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

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, yyscanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *yyscanner)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (yyscanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *yyscanner)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, yyscanner);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, void *yyscanner)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , yyscanner);
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, void *yyscanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (yyscanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *yyscanner)
{
/* The lookahead symbol.  */
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
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, yyscanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 74 "yacc.y" /* yacc.c:1646  */
    {
        parse_tree = (yyvsp[-1].sv_node);
        YYACCEPT;
    }
#line 1562 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 79 "yacc.y" /* yacc.c:1646  */
    {
        parse_tree = std::make_shared<Help>();
        YYACCEPT;
    }
#line 1571 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 84 "yacc.y" /* yacc.c:1646  */
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1580 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 89 "yacc.y" /* yacc.c:1646  */
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1589 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 94 "yacc.y" /* yacc.c:1646  */
    {
        parse_tree = (yyvsp[0].sv_node);
        YYACCEPT;
    }
#line 1598 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 111 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<TxnBegin>();
    }
#line 1606 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 115 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<TxnCommit>();
    }
#line 1614 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 119 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<TxnAbort>();
    }
#line 1622 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 123 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<TxnRollback>();
    }
#line 1630 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 130 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<ShowTables>();
    }
#line 1638 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 134 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<ShowIndex>((yyvsp[0].sv_str));
    }
#line 1646 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 138 "yacc.y" /* yacc.c:1646  */
    {
        if(auto select = std::dynamic_pointer_cast<SelectStmt>((yyvsp[0].sv_node))){
            select->need_explain = true;
            (yyval.sv_node) = select;
        }
    }
#line 1657 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 145 "yacc.y" /* yacc.c:1646  */
    {
         (yyval.sv_node) = std::make_shared<LoadStmt>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
#line 1665 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 152 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<SetStmt>((yyvsp[-2].sv_setKnobType), (yyvsp[0].sv_bool));
    }
#line 1673 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 158 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<IoEnable>(true);
    }
#line 1681 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 162 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<IoEnable>(false);
    }
#line 1689 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 168 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<CreateTable>((yyvsp[-3].sv_str), (yyvsp[-1].sv_fields));
    }
#line 1697 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 172 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<DropTable>((yyvsp[0].sv_str));
    }
#line 1705 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 176 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<DescTable>((yyvsp[0].sv_str));
    }
#line 1713 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 180 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<CreateIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1721 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 184 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<DropIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1729 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 191 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<InsertStmt>((yyvsp[-4].sv_str), (yyvsp[-1].sv_vals));
    }
#line 1737 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 195 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<DeleteStmt>((yyvsp[-1].sv_str), (yyvsp[0].sv_conds));
    }
#line 1745 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 199 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<UpdateStmt>((yyvsp[-3].sv_str), (yyvsp[-1].sv_set_clauses), (yyvsp[0].sv_conds));
    }
#line 1753 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 203 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_node) = std::make_shared<SelectStmt>((yyvsp[-7].sv_cols), (yyvsp[-5].sv_strs), (yyvsp[-4].sv_conds), (yyvsp[-3].sv_cols), (yyvsp[-2].sv_conds), (yyvsp[-1].sv_orderbys), (yyvsp[0].sv_int));
    }
#line 1761 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 207 "yacc.y" /* yacc.c:1646  */
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
#line 1780 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 225 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_int) = (yyvsp[0].sv_int);
    }
#line 1788 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 229 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_int) = INT_MAX;
    }
#line 1796 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 236 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_cols) = {};
    }
#line 1804 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 240 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_cols) = (yyvsp[0].sv_cols);
    }
#line 1812 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 246 "yacc.y" /* yacc.c:1646  */
    { /* ignore*/ }
#line 1818 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 248 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_conds) = (yyvsp[0].sv_conds);
    }
#line 1826 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 256 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_fields) = std::vector<std::shared_ptr<Field>>{(yyvsp[0].sv_field)};
    }
#line 1834 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 260 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_fields).push_back((yyvsp[0].sv_field));
    }
#line 1842 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 267 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 1850 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 271 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 1858 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 278 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-1].sv_str), (yyvsp[0].sv_type_len));
    }
#line 1866 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 285 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_INT, sizeof(int));
    }
#line 1874 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 289 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_STRING, (yyvsp[-1].sv_int));
    }
#line 1882 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 293 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_FLOAT, sizeof(float));
    }
#line 1890 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 300 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_vals) = std::vector<std::shared_ptr<Value>>{(yyvsp[0].sv_val)};
    }
#line 1898 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 304 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_vals).push_back((yyvsp[0].sv_val));
    }
#line 1906 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 311 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_val) = std::make_shared<IntLit>((yyvsp[0].sv_int));
    }
#line 1914 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 315 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_val) = std::make_shared<FloatLit>((yyvsp[0].sv_float));
    }
#line 1922 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 319 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_val) = std::make_shared<StringLit>((yyvsp[0].sv_str));
    }
#line 1930 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 323 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_val) = std::make_shared<BoolLit>((yyvsp[0].sv_bool));
    }
#line 1938 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 330 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_cond) = std::make_shared<BinaryExpr>((yyvsp[-2].sv_col), (yyvsp[-1].sv_comp_op), (yyvsp[0].sv_expr));
    }
#line 1946 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 336 "yacc.y" /* yacc.c:1646  */
    { /* ignore*/ }
#line 1952 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 338 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_conds) = (yyvsp[0].sv_conds);
    }
#line 1960 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 345 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_conds) = std::vector<std::shared_ptr<BinaryExpr>>{(yyvsp[0].sv_cond)};
    }
#line 1968 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 349 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_conds).push_back((yyvsp[0].sv_cond));
    }
#line 1976 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 356 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_col) = std::make_shared<Col>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
#line 1984 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 360 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_col) = std::make_shared<Col>("", (yyvsp[0].sv_str));
    }
#line 1992 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 364 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_col) = (yyvsp[0].sv_col);
    }
#line 2000 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 371 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_cols) = std::vector<std::shared_ptr<Col>>{(yyvsp[0].sv_col)};
    }
#line 2008 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 375 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_cols).push_back((yyvsp[0].sv_col));
    }
#line 2016 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 382 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_comp_op) = SV_OP_EQ;
    }
#line 2024 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 386 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_comp_op) = SV_OP_LT;
    }
#line 2032 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 390 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_comp_op) = SV_OP_GT;
    }
#line 2040 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 394 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_comp_op) = SV_OP_NE;
    }
#line 2048 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 398 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_comp_op) = SV_OP_LE;
    }
#line 2056 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 402 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_comp_op) = SV_OP_GE;
    }
#line 2064 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 409 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_val));
    }
#line 2072 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 413 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_col));
    }
#line 2080 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 420 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_set_clauses) = std::vector<std::shared_ptr<SetClause>>{(yyvsp[0].sv_set_clause)};
    }
#line 2088 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 424 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_set_clauses).push_back((yyvsp[0].sv_set_clause));       /*我怎么感觉这里写错了？难道不应该把setClauses先赋值给$$吗？而且setClause也不应该是vector而应该是ptr*/
    }
#line 2096 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 431 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-2].sv_str), (yyvsp[0].sv_val));
    }
#line 2104 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 435 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-3].sv_str), (yyvsp[0].sv_val), true);
    }
#line 2112 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 439 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-4].sv_str), (yyvsp[0].sv_val), true);
    }
#line 2120 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 446 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_cols) = {};
    }
#line 2128 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 454 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_MAX, (yyvsp[0].sv_str)));
    }
#line 2136 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 458 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_MIN, (yyvsp[0].sv_str)));
    }
#line 2144 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 462 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_SUM, (yyvsp[0].sv_str)));
    }
#line 2152 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 466 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_AVG, (yyvsp[0].sv_str)));
    }
#line 2160 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 470 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_COUNT, (yyvsp[0].sv_str)));
    }
#line 2168 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 474 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>("", "*", AGG_COUNT, (yyvsp[0].sv_str)));
    }
#line 2176 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 478 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_MAX, ""));
    }
#line 2184 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 482 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_MIN, ""));
    }
#line 2192 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 486 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_SUM, ""));
    }
#line 2200 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 490 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_AVG, ""));
    }
#line 2208 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 494 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_COUNT, ""));
    }
#line 2216 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 498 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>("", "*", AGG_COUNT, ""));
    }
#line 2224 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 505 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 2232 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 509 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2240 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 520 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_str) = (yyvsp[0].sv_str);
    }
#line 2248 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 524 "yacc.y" /* yacc.c:1646  */
    {
        alias_map[(yyvsp[0].sv_str)] = (yyvsp[-1].sv_str);
        pam_saila[(yyvsp[-1].sv_str)] = (yyvsp[0].sv_str);
        (yyval.sv_str) = (yyvsp[-1].sv_str);
    }
#line 2258 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 532 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_join_exprs) = (yyvsp[0].sv_join_exprs);
        for (auto& join_expr : (yyval.sv_join_exprs)) {
            join_expr->left = (yyvsp[-1].sv_str);
        }
    }
#line 2269 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 542 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_join_exprs) = std::vector<std::shared_ptr<JoinExpr>>{(yyvsp[0].sv_join_expr)};
    }
#line 2277 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 546 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_join_exprs).push_back((yyvsp[0].sv_join_expr));
    }
#line 2285 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 552 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_join_expr) = std::make_shared<JoinExpr>("", (yyvsp[-2].sv_str), (yyvsp[0].sv_conds), (yyvsp[-3].join_type_dir));
    }
#line 2293 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 557 "yacc.y" /* yacc.c:1646  */
    { (yyval.join_type_dir) = INNER_JOIN; }
#line 2299 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 558 "yacc.y" /* yacc.c:1646  */
    { (yyval.join_type_dir) = INNER_JOIN; }
#line 2305 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 559 "yacc.y" /* yacc.c:1646  */
    { (yyval.join_type_dir) = LEFT_JOIN; }
#line 2311 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 560 "yacc.y" /* yacc.c:1646  */
    { (yyval.join_type_dir) = RIGHT_JOIN; }
#line 2317 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 561 "yacc.y" /* yacc.c:1646  */
    { (yyval.join_type_dir) = FULL_JOIN; }
#line 2323 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 562 "yacc.y" /* yacc.c:1646  */
    { (yyval.join_type_dir) = SEMI_JOIN; }
#line 2329 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 568 "yacc.y" /* yacc.c:1646  */
    { 
        (yyval.sv_orderbys) = (yyvsp[0].sv_orderbys); 
    }
#line 2337 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 571 "yacc.y" /* yacc.c:1646  */
    { /* ignore*/ }
#line 2343 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 576 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_orderbys) = std::vector<std::shared_ptr<OrderBy>>{(yyvsp[0].sv_orderby)};
    }
#line 2351 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 580 "yacc.y" /* yacc.c:1646  */
    {
        (yyval.sv_orderbys).push_back((yyvsp[0].sv_orderby));
    }
#line 2359 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 587 "yacc.y" /* yacc.c:1646  */
    { 
        (yyval.sv_orderby) = std::make_shared<OrderBy>((yyvsp[-1].sv_col), (yyvsp[0].sv_orderby_dir));
    }
#line 2367 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 593 "yacc.y" /* yacc.c:1646  */
    { (yyval.sv_orderby_dir) = OrderBy_ASC;     }
#line 2373 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 594 "yacc.y" /* yacc.c:1646  */
    { (yyval.sv_orderby_dir) = OrderBy_DESC;    }
#line 2379 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 595 "yacc.y" /* yacc.c:1646  */
    { (yyval.sv_orderby_dir) = OrderBy_ASC; }
#line 2385 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 599 "yacc.y" /* yacc.c:1646  */
    { (yyval.sv_setKnobType) = EnableNestLoop; }
#line 2391 "yacc.tab.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 600 "yacc.y" /* yacc.c:1646  */
    { (yyval.sv_setKnobType) = EnableSortMerge; }
#line 2397 "yacc.tab.cpp" /* yacc.c:1646  */
    break;


#line 2401 "yacc.tab.cpp" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, yyscanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, yyscanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp, yylsp, yyscanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, yyscanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp, yylsp, yyscanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 610 "yacc.y" /* yacc.c:1906  */

