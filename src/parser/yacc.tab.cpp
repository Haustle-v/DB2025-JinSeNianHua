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
<<<<<<< HEAD
#line 1 "yacc.y"

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

#line 87 "yacc.tab.cpp"
=======
#line 1 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"

#include "ast.h"
#include "yacc.tab.h"
#include <iostream>
#include <memory>
#include <set>
#include <unordered_map>
std::unordered_map<std::string, std::string> alias_map;
std::unordered_map<std::string, std::string> pam_saila; 

int yylex(YYSTYPE *yylval, YYLTYPE *yylloc);

void yyerror(YYLTYPE *locp, const char* s) {
    std::cerr << "Parser Error at line " << locp->first_line << " column " << locp->first_column << ": " << s << std::endl;
}

using namespace ast;

#line 90 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
>>>>>>> origin/p4

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

#include "yacc.tab.hpp"
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
<<<<<<< HEAD
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
  YYSYMBOL_55_ = 55,                       /* ';'  */
  YYSYMBOL_56_ = 56,                       /* '='  */
  YYSYMBOL_57_ = 57,                       /* '('  */
  YYSYMBOL_58_ = 58,                       /* ')'  */
  YYSYMBOL_59_ = 59,                       /* ','  */
  YYSYMBOL_60_ = 60,                       /* '.'  */
  YYSYMBOL_61_ = 61,                       /* '<'  */
  YYSYMBOL_62_ = 62,                       /* '>'  */
  YYSYMBOL_63_ = 63,                       /* '+'  */
  YYSYMBOL_64_ = 64,                       /* '*'  */
  YYSYMBOL_YYACCEPT = 65,                  /* $accept  */
  YYSYMBOL_start = 66,                     /* start  */
  YYSYMBOL_stmt = 67,                      /* stmt  */
  YYSYMBOL_txnStmt = 68,                   /* txnStmt  */
  YYSYMBOL_dbStmt = 69,                    /* dbStmt  */
  YYSYMBOL_setStmt = 70,                   /* setStmt  */
  YYSYMBOL_ddl = 71,                       /* ddl  */
  YYSYMBOL_dml = 72,                       /* dml  */
  YYSYMBOL_limit_clause = 73,              /* limit_clause  */
  YYSYMBOL_optGroupByClause = 74,          /* optGroupByClause  */
  YYSYMBOL_optHavingClause = 75,           /* optHavingClause  */
  YYSYMBOL_fieldList = 76,                 /* fieldList  */
  YYSYMBOL_colNameList = 77,               /* colNameList  */
  YYSYMBOL_field = 78,                     /* field  */
  YYSYMBOL_type = 79,                      /* type  */
  YYSYMBOL_valueList = 80,                 /* valueList  */
  YYSYMBOL_value = 81,                     /* value  */
  YYSYMBOL_condition = 82,                 /* condition  */
  YYSYMBOL_optWhereClause = 83,            /* optWhereClause  */
  YYSYMBOL_whereClause = 84,               /* whereClause  */
  YYSYMBOL_col = 85,                       /* col  */
  YYSYMBOL_colList = 86,                   /* colList  */
  YYSYMBOL_op = 87,                        /* op  */
  YYSYMBOL_expr = 88,                      /* expr  */
  YYSYMBOL_setClauses = 89,                /* setClauses  */
  YYSYMBOL_setClause = 90,                 /* setClause  */
  YYSYMBOL_selector = 91,                  /* selector  */
  YYSYMBOL_aggCol = 92,                    /* aggCol  */
  YYSYMBOL_tableList = 93,                 /* tableList  */
  YYSYMBOL_opt_order_clause = 94,          /* opt_order_clause  */
  YYSYMBOL_order_clauses = 95,             /* order_clauses  */
  YYSYMBOL_order_clause = 96,              /* order_clause  */
  YYSYMBOL_opt_asc_desc = 97,              /* opt_asc_desc  */
  YYSYMBOL_set_knob_type = 98,             /* set_knob_type  */
  YYSYMBOL_tbName = 99,                    /* tbName  */
  YYSYMBOL_colName = 100,                  /* colName  */
  YYSYMBOL_alias = 101                     /* alias  */
=======
  YYSYMBOL_INNER = 36,                     /* INNER  */
  YYSYMBOL_LEFT = 37,                      /* LEFT  */
  YYSYMBOL_RIGHT = 38,                     /* RIGHT  */
  YYSYMBOL_FULL = 39,                      /* FULL  */
  YYSYMBOL_SEMI = 40,                      /* SEMI  */
  YYSYMBOL_ON = 41,                        /* ON  */
  YYSYMBOL_EXPLAIN = 42,                   /* EXPLAIN  */
  YYSYMBOL_LEQ = 43,                       /* LEQ  */
  YYSYMBOL_NEQ = 44,                       /* NEQ  */
  YYSYMBOL_GEQ = 45,                       /* GEQ  */
  YYSYMBOL_T_EOF = 46,                     /* T_EOF  */
  YYSYMBOL_IDENTIFIER = 47,                /* IDENTIFIER  */
  YYSYMBOL_VALUE_STRING = 48,              /* VALUE_STRING  */
  YYSYMBOL_VALUE_INT = 49,                 /* VALUE_INT  */
  YYSYMBOL_VALUE_FLOAT = 50,               /* VALUE_FLOAT  */
  YYSYMBOL_VALUE_BOOL = 51,                /* VALUE_BOOL  */
  YYSYMBOL_52_ = 52,                       /* ';'  */
  YYSYMBOL_53_ = 53,                       /* '='  */
  YYSYMBOL_54_ = 54,                       /* '('  */
  YYSYMBOL_55_ = 55,                       /* ')'  */
  YYSYMBOL_56_ = 56,                       /* ','  */
  YYSYMBOL_57_ = 57,                       /* '.'  */
  YYSYMBOL_58_ = 58,                       /* '<'  */
  YYSYMBOL_59_ = 59,                       /* '>'  */
  YYSYMBOL_60_ = 60,                       /* '*'  */
  YYSYMBOL_YYACCEPT = 61,                  /* $accept  */
  YYSYMBOL_start = 62,                     /* start  */
  YYSYMBOL_stmt = 63,                      /* stmt  */
  YYSYMBOL_txnStmt = 64,                   /* txnStmt  */
  YYSYMBOL_dbStmt = 65,                    /* dbStmt  */
  YYSYMBOL_setStmt = 66,                   /* setStmt  */
  YYSYMBOL_ddl = 67,                       /* ddl  */
  YYSYMBOL_dml = 68,                       /* dml  */
  YYSYMBOL_fieldList = 69,                 /* fieldList  */
  YYSYMBOL_colNameList = 70,               /* colNameList  */
  YYSYMBOL_field = 71,                     /* field  */
  YYSYMBOL_type = 72,                      /* type  */
  YYSYMBOL_valueList = 73,                 /* valueList  */
  YYSYMBOL_value = 74,                     /* value  */
  YYSYMBOL_condition = 75,                 /* condition  */
  YYSYMBOL_optWhereClause = 76,            /* optWhereClause  */
  YYSYMBOL_whereClause = 77,               /* whereClause  */
  YYSYMBOL_col = 78,                       /* col  */
  YYSYMBOL_colList = 79,                   /* colList  */
  YYSYMBOL_op = 80,                        /* op  */
  YYSYMBOL_expr = 81,                      /* expr  */
  YYSYMBOL_setClauses = 82,                /* setClauses  */
  YYSYMBOL_setClause = 83,                 /* setClause  */
  YYSYMBOL_selector = 84,                  /* selector  */
  YYSYMBOL_tableList = 85,                 /* tableList  */
  YYSYMBOL_tbNameWithAlias = 86,           /* tbNameWithAlias  */
  YYSYMBOL_join_exprss = 87,               /* join_exprss  */
  YYSYMBOL_join_exprs = 88,                /* join_exprs  */
  YYSYMBOL_join_expr = 89,                 /* join_expr  */
  YYSYMBOL_join_type = 90,                 /* join_type  */
  YYSYMBOL_opt_order_clause = 91,          /* opt_order_clause  */
  YYSYMBOL_order_clause = 92,              /* order_clause  */
  YYSYMBOL_opt_asc_desc = 93,              /* opt_asc_desc  */
  YYSYMBOL_set_knob_type = 94,             /* set_knob_type  */
  YYSYMBOL_tbName = 95,                    /* tbName  */
  YYSYMBOL_colName = 96,                   /* colName  */
  YYSYMBOL_alias = 97                      /* alias  */
>>>>>>> origin/p4
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
<<<<<<< HEAD
#define YYFINAL  53
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   200

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  193

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   309
=======
#define YYFINAL  46
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   142

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  159

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   306
>>>>>>> origin/p4


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
<<<<<<< HEAD
      57,    58,    64,    63,    59,     2,    60,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    55,
      61,    56,    62,     2,     2,     2,     2,     2,     2,     2,
=======
      54,    55,    60,     2,    56,     2,    57,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    52,
      58,    53,    59,     2,     2,     2,     2,     2,     2,     2,
>>>>>>> origin/p4
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
<<<<<<< HEAD
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
=======
      45,    46,    47,    48,    49,    50,    51
>>>>>>> origin/p4
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
<<<<<<< HEAD
       0,    65,    65,    70,    75,    80,    88,    89,    90,    91,
      92,    96,   100,   104,   108,   115,   119,   123,   133,   140,
     144,   148,   152,   156,   163,   167,   171,   175,   182,   187,
     194,   197,   204,   205,   212,   216,   223,   227,   234,   241,
     245,   249,   256,   260,   267,   271,   275,   279,   286,   293,
     294,   301,   305,   312,   316,   320,   327,   331,   338,   342,
     346,   350,   354,   358,   365,   369,   376,   380,   387,   391,
     395,   402,   406,   410,   414,   418,   422,   426,   430,   434,
     438,   442,   446,   450,   454,   461,   465,   469,   476,   480,
     484,   488,   495,   502,   503,   504,   508,   509,   512,   514,
     516
=======
       0,    66,    66,    71,    76,    81,    89,    90,    91,    92,
      93,    97,   101,   105,   109,   116,   120,   130,   137,   141,
     145,   149,   153,   160,   164,   168,   172,   176,   194,   198,
     205,   209,   216,   223,   227,   231,   238,   242,   249,   253,
     257,   261,   268,   275,   276,   283,   287,   294,   298,   305,
     309,   316,   320,   324,   328,   332,   336,   343,   347,   354,
     358,   365,   372,   376,   380,   384,   395,   399,   407,   417,
     421,   427,   433,   434,   435,   436,   437,   438,   443,   447,
     451,   458,   459,   460,   464,   465,   468,   470,   472
>>>>>>> origin/p4
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
<<<<<<< HEAD
  "ENABLE_SORTMERGE", "LEQ", "NEQ", "GEQ", "T_EOF", "MAX", "MIN", "SUM",
  "AVG", "COUNT", "AS", "GROUP", "HAVING", "LIMIT", "IDENTIFIER",
  "VALUE_STRING", "VALUE_INT", "VALUE_FLOAT", "VALUE_BOOL", "EXPLAIN",
  "';'", "'='", "'('", "')'", "','", "'.'", "'<'", "'>'", "'+'", "'*'",
  "$accept", "start", "stmt", "txnStmt", "dbStmt", "setStmt", "ddl", "dml",
  "limit_clause", "optGroupByClause", "optHavingClause", "fieldList",
  "colNameList", "field", "type", "valueList", "value", "condition",
  "optWhereClause", "whereClause", "col", "colList", "op", "expr",
  "setClauses", "setClause", "selector", "aggCol", "tableList",
  "opt_order_clause", "order_clauses", "order_clause", "opt_asc_desc",
  "set_knob_type", "tbName", "colName", "alias", YY_NULLPTR
=======
  "ENABLE_SORTMERGE", "INNER", "LEFT", "RIGHT", "FULL", "SEMI", "ON",
  "EXPLAIN", "LEQ", "NEQ", "GEQ", "T_EOF", "IDENTIFIER", "VALUE_STRING",
  "VALUE_INT", "VALUE_FLOAT", "VALUE_BOOL", "';'", "'='", "'('", "')'",
  "','", "'.'", "'<'", "'>'", "'*'", "$accept", "start", "stmt", "txnStmt",
  "dbStmt", "setStmt", "ddl", "dml", "fieldList", "colNameList", "field",
  "type", "valueList", "value", "condition", "optWhereClause",
  "whereClause", "col", "colList", "op", "expr", "setClauses", "setClause",
  "selector", "tableList", "tbNameWithAlias", "join_exprss", "join_exprs",
  "join_expr", "join_type", "opt_order_clause", "order_clause",
  "opt_asc_desc", "set_knob_type", "tbName", "colName", "alias", YY_NULLPTR
>>>>>>> origin/p4
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

<<<<<<< HEAD
#define YYPACT_NINF (-96)
=======
#define YYPACT_NINF (-84)
>>>>>>> origin/p4

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

<<<<<<< HEAD
#define YYTABLE_NINF (-99)
=======
#define YYTABLE_NINF (-87)
>>>>>>> origin/p4

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
<<<<<<< HEAD
      66,    11,    -1,     8,   -36,    60,    16,   -36,    19,    39,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   128,    41,    17,
     -96,   -96,   -96,   -96,   -96,   -96,    74,   -36,   -36,   -36,
     -36,   -96,   -96,   -36,   -36,    73,   -96,   -96,    35,    47,
      50,    51,    52,    61,    46,   -96,   -96,    58,   106,   -96,
      67,   -96,   -96,   -96,   -96,   -36,    71,    81,   -96,    90,
     119,   122,   100,   109,   101,   101,   101,   101,    72,   101,
     -36,   100,   -96,   100,   100,   100,   107,   101,   -96,   -96,
     -15,   -96,   110,   -96,   105,   111,   112,   113,   115,   116,
     -96,   -14,   -96,   -96,   -37,   -96,    42,   -11,   -96,    18,
      49,   -96,   140,   -28,   100,   -96,   102,   123,   130,   131,
     132,   133,   134,   -36,   -36,   121,   -96,   100,   -96,   124,
     -96,   -96,   -96,   100,   -96,   -96,   -96,   -96,   -96,    31,
     -96,   101,   -96,   -96,   -96,   -96,   -96,   -96,    82,   -96,
     -96,   -13,   135,   135,   135,   135,   135,   135,   -96,   -96,
     164,   136,   -96,   137,   -96,   -96,    49,   -96,   -96,   -96,
     -96,    49,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     101,   101,   170,   129,   -96,   -96,    58,   140,   173,   138,
     -96,   101,   139,   -96,    28,   141,   -96,   -96,   -96,   -96,
     -96,   101,   -96
=======
      60,    11,     7,     8,   -11,    43,    49,   -11,    36,   -44,
     -84,   -84,   -84,   -84,   -84,   -84,    39,   -84,    56,    12,
     -84,   -84,   -84,   -84,   -84,   -84,   -11,   -11,   -11,   -11,
     -84,   -84,   -11,   -11,    75,   -84,   -84,    13,    38,   -84,
     -84,    41,    92,    50,   -84,   -84,   -84,   -84,    54,    55,
     -84,    57,    99,    95,    66,    63,    68,   -11,    66,    66,
      66,    66,    64,    68,   -84,   -84,    -7,   -84,    67,   -84,
     -84,    -6,     1,    95,    70,   -84,    21,   -84,    52,    26,
     -84,    45,    -5,   -84,    94,    40,    66,   -84,    -5,   -11,
     106,   -84,    96,    97,    98,   100,   101,     1,   -84,   -11,
     106,   -84,   -84,   -84,    66,   -84,    71,   -84,   -84,   -84,
      66,   -84,   -84,   -84,   -84,   -84,    48,   -84,    68,   -84,
     -84,   -84,   -84,   -84,   -84,   -30,   -84,   -84,   -84,   112,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,    88,   -84,   -84,
      81,   -84,   -84,    -5,   -84,   -84,   -84,   -84,    68,    68,
      76,   -84,    47,   -84,    94,   -84,   -84,   -84,   -84
>>>>>>> origin/p4
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
<<<<<<< HEAD
       4,     3,    11,    12,    13,    14,     5,     0,     0,     0,
       9,     6,    10,     7,     8,    15,     0,     0,     0,     0,
       0,    98,    21,     0,     0,     0,    96,    97,     0,     0,
       0,     0,     0,     0,    99,    71,    56,    72,     0,    55,
       0,    54,    17,     1,     2,     0,     0,     0,    20,     0,
       0,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    16,     0,     0,     0,     0,     0,    25,    99,
      49,    66,     0,    18,     0,     0,     0,     0,     0,     0,
      57,    49,    85,    53,     0,    34,     0,     0,    36,     0,
       0,    51,    50,     0,     0,    26,     0,    79,    80,    81,
      82,    84,    83,     0,     0,    30,    19,     0,    39,     0,
      41,    38,    22,     0,    23,    46,    44,    45,    47,     0,
      42,     0,    62,    61,    63,    58,    59,    60,     0,    67,
      68,     0,     0,     0,     0,     0,     0,     0,    87,    86,
       0,    32,    35,     0,    37,    24,     0,    52,    64,    65,
      48,     0,    69,   100,    73,    74,    75,    76,    78,    77,
       0,     0,    89,     0,    43,    70,    31,    33,     0,    29,
      40,     0,     0,    27,    95,    88,    90,    28,    94,    93,
      92,     0,    91
=======
       4,     3,    11,    12,    13,    14,     0,     5,     0,     0,
       9,     6,    10,     7,     8,    15,     0,     0,     0,     0,
      86,    20,     0,     0,     0,    84,    85,     0,    87,    62,
      49,    63,     0,     0,    48,    16,     1,     2,     0,     0,
      19,     0,     0,    43,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    24,    87,    43,    59,     0,    17,
      50,    43,    64,    43,    66,    47,     0,    28,     0,     0,
      30,     0,     0,    45,    44,     0,     0,    25,     0,     0,
      79,    72,     0,     0,     0,     0,     0,    68,    69,     0,
      79,    88,    67,    18,     0,    33,     0,    35,    32,    21,
       0,    22,    40,    38,    39,    41,     0,    36,     0,    55,
      54,    56,    51,    52,    53,     0,    60,    61,    65,     0,
      26,    73,    74,    75,    76,    77,    70,     0,    27,    29,
       0,    31,    23,     0,    46,    57,    58,    42,     0,     0,
       0,    37,    83,    78,    71,    34,    82,    81,    80
>>>>>>> origin/p4
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
<<<<<<< HEAD
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   174,   -96,   -96,
     -96,   -96,   117,    76,   -96,   -96,   -95,    63,   -74,    24,
      -9,    26,   -96,   -96,   -96,    93,   -96,   -96,   -96,   -96,
     -96,     7,   -96,   -96,    -3,   -55,    13
=======
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   116,   -84,    72,
      30,   -84,   -84,   -83,    17,   -38,   -13,    -9,   -84,   -84,
     -84,   -84,    51,   -84,   -84,   -77,   -84,   -84,    44,   -84,
      42,   -84,   -84,   -84,    -3,   -52,   -84
>>>>>>> origin/p4
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
<<<<<<< HEAD
       0,    18,    19,    20,    21,    22,    23,    24,   183,   151,
     172,    94,    97,    95,   121,   129,   130,   101,    78,   102,
     103,    47,   138,   160,    80,    81,    48,    49,    91,   179,
     185,   186,   190,    38,    50,    51,   164
=======
       0,    18,    19,    20,    21,    22,    23,    24,    76,    79,
      77,   108,   116,   117,    83,    64,    84,    85,    41,   125,
     147,    66,    67,    42,    71,    72,    73,    97,    98,    99,
     130,   153,   158,    37,    43,    44,   102
>>>>>>> origin/p4
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
<<<<<<< HEAD
      46,    32,    77,    77,    35,    27,   105,    82,   132,   133,
     134,   140,   113,    31,    29,    25,    93,   115,    96,    98,
      98,   116,   117,    28,    56,    57,    58,    59,   135,    34,
      60,    61,    30,   136,   137,    26,   188,   125,   126,   127,
     128,    53,   189,   158,   104,   114,   162,   122,   123,    82,
     161,   141,    72,    36,    37,    84,    85,    86,    87,    89,
      90,   174,    96,   118,   119,   120,   175,    92,   154,     1,
      33,     2,    54,     3,     4,     5,   124,   123,     6,    39,
      40,    41,    42,    43,     7,     8,     9,    55,    44,   155,
     156,    63,    62,    10,    11,    12,    13,    14,    15,   125,
     126,   127,   128,    45,    64,    16,   -98,    65,    66,    67,
     148,   149,    39,    40,    41,    42,    43,    69,    68,    70,
      17,    44,    39,    40,    41,    42,    43,    71,    73,   159,
      76,    44,   125,   126,   127,   128,    88,     5,    74,    77,
       6,    39,    40,    41,    42,    43,     7,    75,     9,    79,
      44,    79,   125,   126,   127,   128,   165,   166,   167,   168,
     169,    46,    83,   107,   100,   131,   106,   150,   142,   108,
     109,   110,   184,   111,   112,   143,   144,   145,   146,   147,
     170,   153,   184,   171,   163,   178,   182,   180,   173,   181,
     187,    52,    99,   152,   157,   177,   176,   139,   192,     0,
     191
=======
      40,    31,    68,    38,    34,   127,    75,    78,    80,    80,
      63,    63,   128,    26,    28,    25,    39,    38,   112,   113,
     114,   115,   137,    48,    49,    50,    51,    91,    87,    52,
      53,    27,    29,    90,    68,   100,    30,    92,    93,    94,
      95,    96,   145,   112,   113,   114,   115,    70,     5,    86,
      89,     6,    78,    32,    74,   156,    46,     7,   141,     9,
     151,   157,    33,     1,    47,     2,    55,     3,     4,     5,
      35,    36,     6,   105,   106,   107,   103,   104,     7,     8,
       9,   109,   110,   119,   120,   121,    74,    10,    11,    12,
      13,    14,    15,   122,    54,   -86,    74,    56,   123,   124,
     111,   110,    16,   142,   143,    57,    17,    58,    59,    60,
      62,    61,    63,    65,    69,    38,   146,   101,    82,   118,
      88,   129,   131,   132,   133,   140,   134,   135,   148,   149,
     150,   155,    45,    81,   139,   144,   154,   126,     0,   152,
       0,   136,   138
>>>>>>> origin/p4
};

static const yytype_int16 yycheck[] =
{
<<<<<<< HEAD
       9,     4,    17,    17,     7,     6,    80,    62,    36,    37,
      38,   106,    26,    49,     6,     4,    71,    91,    73,    74,
      75,    58,    59,    24,    27,    28,    29,    30,    56,    13,
      33,    34,    24,    61,    62,    24,     8,    50,    51,    52,
      53,     0,    14,   138,    59,    59,   141,    58,    59,   104,
      63,   106,    55,    34,    35,    64,    65,    66,    67,    68,
      69,   156,   117,    21,    22,    23,   161,    70,   123,     3,
      10,     5,    55,     7,     8,     9,    58,    59,    12,    40,
      41,    42,    43,    44,    18,    19,    20,    13,    49,    58,
      59,    56,    19,    27,    28,    29,    30,    31,    32,    50,
      51,    52,    53,    64,    57,    39,    60,    57,    57,    57,
     113,   114,    40,    41,    42,    43,    44,    59,    57,    13,
      54,    49,    40,    41,    42,    43,    44,    60,    57,   138,
      11,    49,    50,    51,    52,    53,    64,     9,    57,    17,
      12,    40,    41,    42,    43,    44,    18,    57,    20,    49,
      49,    49,    50,    51,    52,    53,   143,   144,   145,   146,
     147,   170,    53,    58,    57,    25,    56,    46,    45,    58,
      58,    58,   181,    58,    58,    45,    45,    45,    45,    45,
      16,    57,   191,    47,    49,    15,    48,    58,    51,    16,
      51,    17,    75,   117,   131,   171,   170,   104,   191,    -1,
      59
=======
       9,     4,    54,    47,     7,    88,    58,    59,    60,    61,
      17,    17,    89,     6,     6,     4,    60,    47,    48,    49,
      50,    51,    99,    26,    27,    28,    29,    26,    66,    32,
      33,    24,    24,    71,    86,    73,    47,    36,    37,    38,
      39,    40,   125,    48,    49,    50,    51,    56,     9,    56,
      56,    12,   104,    10,    57,     8,     0,    18,   110,    20,
     143,    14,    13,     3,    52,     5,    53,     7,     8,     9,
      34,    35,    12,    21,    22,    23,    55,    56,    18,    19,
      20,    55,    56,    43,    44,    45,    89,    27,    28,    29,
      30,    31,    32,    53,    19,    57,    99,    56,    58,    59,
      55,    56,    42,    55,    56,    13,    46,    57,    54,    54,
      11,    54,    17,    47,    51,    47,   125,    47,    54,    25,
      53,    15,    26,    26,    26,    54,    26,    26,    16,    41,
      49,    55,    16,    61,   104,   118,   149,    86,    -1,   148,
      -1,    97,   100
>>>>>>> origin/p4
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     7,     8,     9,    12,    18,    19,    20,
<<<<<<< HEAD
      27,    28,    29,    30,    31,    32,    39,    54,    66,    67,
      68,    69,    70,    71,    72,     4,    24,     6,    24,     6,
      24,    49,    99,    10,    13,    99,    34,    35,    98,    40,
      41,    42,    43,    44,    49,    64,    85,    86,    91,    92,
      99,   100,    72,     0,    55,    13,    99,    99,    99,    99,
      99,    99,    19,    56,    57,    57,    57,    57,    57,    59,
      13,    60,    99,    57,    57,    57,    11,    17,    83,    49,
      89,    90,   100,    53,    85,    85,    85,    85,    64,    85,
      85,    93,    99,   100,    76,    78,   100,    77,   100,    77,
      57,    82,    84,    85,    59,    83,    56,    58,    58,    58,
      58,    58,    58,    26,    59,    83,    58,    59,    21,    22,
      23,    79,    58,    59,    58,    50,    51,    52,    53,    80,
      81,    25,    36,    37,    38,    56,    61,    62,    87,    90,
      81,   100,    45,    45,    45,    45,    45,    45,    99,    99,
      46,    74,    78,    57,   100,    58,    59,    82,    81,    85,
      88,    63,    81,    49,   101,   101,   101,   101,   101,   101,
      16,    47,    75,    51,    81,    81,    86,    84,    15,    94,
      58,    16,    48,    73,    85,    95,    96,    51,     8,    14,
      97,    59,    96
=======
      27,    28,    29,    30,    31,    32,    42,    46,    62,    63,
      64,    65,    66,    67,    68,     4,     6,    24,     6,    24,
      47,    95,    10,    13,    95,    34,    35,    94,    47,    60,
      78,    79,    84,    95,    96,    68,     0,    52,    95,    95,
      95,    95,    95,    95,    19,    53,    56,    13,    57,    54,
      54,    54,    11,    17,    76,    47,    82,    83,    96,    51,
      78,    85,    86,    87,    95,    96,    69,    71,    96,    70,
      96,    70,    54,    75,    77,    78,    56,    76,    53,    56,
      76,    26,    36,    37,    38,    39,    40,    88,    89,    90,
      76,    47,    97,    55,    56,    21,    22,    23,    72,    55,
      56,    55,    48,    49,    50,    51,    73,    74,    25,    43,
      44,    45,    53,    58,    59,    80,    83,    74,    86,    15,
      91,    26,    26,    26,    26,    26,    89,    86,    91,    71,
      54,    96,    55,    56,    75,    74,    78,    81,    16,    41,
      49,    74,    78,    92,    77,    55,     8,    14,    93
>>>>>>> origin/p4
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
<<<<<<< HEAD
       0,    65,    66,    66,    66,    66,    67,    67,    67,    67,
      67,    68,    68,    68,    68,    69,    69,    69,    70,    71,
      71,    71,    71,    71,    72,    72,    72,    72,    73,    73,
      74,    74,    75,    75,    76,    76,    77,    77,    78,    79,
      79,    79,    80,    80,    81,    81,    81,    81,    82,    83,
      83,    84,    84,    85,    85,    85,    86,    86,    87,    87,
      87,    87,    87,    87,    88,    88,    89,    89,    90,    90,
      90,    91,    91,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    93,    93,    93,    94,    94,
      95,    95,    96,    97,    97,    97,    98,    98,    99,   100,
     101
=======
       0,    61,    62,    62,    62,    62,    63,    63,    63,    63,
      63,    64,    64,    64,    64,    65,    65,    66,    67,    67,
      67,    67,    67,    68,    68,    68,    68,    68,    69,    69,
      70,    70,    71,    72,    72,    72,    73,    73,    74,    74,
      74,    74,    75,    76,    76,    77,    77,    78,    78,    79,
      79,    80,    80,    80,    80,    80,    80,    81,    81,    82,
      82,    83,    84,    84,    85,    85,    86,    86,    87,    88,
      88,    89,    90,    90,    90,    90,    90,    90,    91,    91,
      92,    93,    93,    93,    94,    94,    95,    96,    97
>>>>>>> origin/p4
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
<<<<<<< HEAD
       1,     1,     1,     1,     1,     2,     4,     2,     4,     6,
       3,     2,     6,     6,     7,     4,     5,     9,     2,     0,
       0,     3,     0,     2,     1,     3,     1,     3,     2,     1,
       4,     1,     1,     3,     1,     1,     1,     1,     3,     0,
       2,     1,     3,     3,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     4,
       5,     1,     1,     6,     6,     6,     6,     6,     6,     4,
       4,     4,     4,     4,     4,     1,     3,     3,     3,     0,
       1,     3,     2,     1,     1,     0,     1,     1,     1,     1,
       1
=======
       1,     1,     1,     1,     1,     2,     2,     4,     6,     3,
       2,     6,     6,     7,     4,     5,     6,     6,     1,     3,
       1,     3,     2,     1,     4,     1,     1,     3,     1,     1,
       1,     1,     3,     0,     2,     1,     3,     3,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     1,     1,     1,     3,     1,     2,     2,     1,
       2,     4,     1,     2,     2,     2,     2,     2,     3,     0,
       2,     1,     1,     0,     1,     1,     1,     1,     1
>>>>>>> origin/p4
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
<<<<<<< HEAD
#line 66 "yacc.y"
    {
        parse_tree = (yyvsp[-1].sv_node);
        YYACCEPT;
    }
#line 1711 "yacc.tab.cpp"
    break;

  case 3: /* start: HELP  */
#line 71 "yacc.y"
    {
        parse_tree = std::make_shared<Help>();
        YYACCEPT;
    }
#line 1720 "yacc.tab.cpp"
    break;

  case 4: /* start: EXIT  */
#line 76 "yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1729 "yacc.tab.cpp"
    break;

  case 5: /* start: T_EOF  */
#line 81 "yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1738 "yacc.tab.cpp"
    break;

  case 11: /* txnStmt: TXN_BEGIN  */
#line 97 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnBegin>();
    }
#line 1746 "yacc.tab.cpp"
    break;

  case 12: /* txnStmt: TXN_COMMIT  */
#line 101 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnCommit>();
    }
#line 1754 "yacc.tab.cpp"
    break;

  case 13: /* txnStmt: TXN_ABORT  */
#line 105 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnAbort>();
    }
#line 1762 "yacc.tab.cpp"
    break;

  case 14: /* txnStmt: TXN_ROLLBACK  */
#line 109 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnRollback>();
    }
#line 1770 "yacc.tab.cpp"
    break;

  case 15: /* dbStmt: SHOW TABLES  */
#line 116 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowTables>();
    }
#line 1778 "yacc.tab.cpp"
    break;

  case 16: /* dbStmt: SHOW INDEX FROM tbName  */
#line 120 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowIndex>((yyvsp[0].sv_str));
    }
#line 1786 "yacc.tab.cpp"
    break;

  case 17: /* dbStmt: EXPLAIN dml  */
#line 124 "yacc.y"
    {
        if(auto select = std::dynamic_pointer_cast<SelectStmt>((yyvsp[0].sv_node))){
            select->need_explain = true;
            (yyval.sv_node) = select;
        }
    }
#line 1797 "yacc.tab.cpp"
    break;

  case 18: /* setStmt: SET set_knob_type '=' VALUE_BOOL  */
#line 134 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<SetStmt>((yyvsp[-2].sv_setKnobType), (yyvsp[0].sv_bool));
    }
#line 1805 "yacc.tab.cpp"
    break;

  case 19: /* ddl: CREATE TABLE tbName '(' fieldList ')'  */
#line 141 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateTable>((yyvsp[-3].sv_str), (yyvsp[-1].sv_fields));
    }
#line 1813 "yacc.tab.cpp"
    break;

  case 20: /* ddl: DROP TABLE tbName  */
#line 145 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropTable>((yyvsp[0].sv_str));
    }
#line 1821 "yacc.tab.cpp"
    break;

  case 21: /* ddl: DESC tbName  */
#line 149 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DescTable>((yyvsp[0].sv_str));
    }
#line 1829 "yacc.tab.cpp"
    break;

  case 22: /* ddl: CREATE INDEX tbName '(' colNameList ')'  */
#line 153 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1837 "yacc.tab.cpp"
    break;

  case 23: /* ddl: DROP INDEX tbName '(' colNameList ')'  */
#line 157 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1845 "yacc.tab.cpp"
    break;

  case 24: /* dml: INSERT INTO tbName VALUES '(' valueList ')'  */
#line 164 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<InsertStmt>((yyvsp[-4].sv_str), (yyvsp[-1].sv_vals));
    }
#line 1853 "yacc.tab.cpp"
    break;

  case 25: /* dml: DELETE FROM tbName optWhereClause  */
#line 168 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DeleteStmt>((yyvsp[-1].sv_str), (yyvsp[0].sv_conds));
    }
#line 1861 "yacc.tab.cpp"
    break;

  case 26: /* dml: UPDATE tbName SET setClauses optWhereClause  */
#line 172 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<UpdateStmt>((yyvsp[-3].sv_str), (yyvsp[-1].sv_set_clauses), (yyvsp[0].sv_conds));
    }
#line 1869 "yacc.tab.cpp"
    break;

  case 27: /* dml: SELECT selector FROM tableList optWhereClause optGroupByClause optHavingClause opt_order_clause limit_clause  */
#line 176 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<SelectStmt>((yyvsp[-7].sv_cols), (yyvsp[-5].sv_strs), (yyvsp[-4].sv_conds), (yyvsp[-3].sv_cols), (yyvsp[-2].sv_conds), (yyvsp[-1].sv_orderbys), (yyvsp[0].sv_int));
    }
#line 1877 "yacc.tab.cpp"
    break;

  case 28: /* limit_clause: LIMIT VALUE_INT  */
#line 183 "yacc.y"
    {
        (yyval.sv_int) = (yyvsp[0].sv_int);
    }
#line 1885 "yacc.tab.cpp"
    break;

  case 29: /* limit_clause: %empty  */
#line 187 "yacc.y"
    {
        (yyval.sv_int) = INT_MAX;
    }
#line 1893 "yacc.tab.cpp"
    break;

  case 30: /* optGroupByClause: %empty  */
#line 194 "yacc.y"
    {
        (yyval.sv_cols) = {};
    }
#line 1901 "yacc.tab.cpp"
    break;

  case 31: /* optGroupByClause: GROUP BY colList  */
#line 198 "yacc.y"
    {
        (yyval.sv_cols) = (yyvsp[0].sv_cols);
    }
#line 1909 "yacc.tab.cpp"
    break;

  case 32: /* optHavingClause: %empty  */
#line 204 "yacc.y"
                      { /* ignore*/ }
#line 1915 "yacc.tab.cpp"
    break;

  case 33: /* optHavingClause: HAVING whereClause  */
#line 206 "yacc.y"
    {
        (yyval.sv_conds) = (yyvsp[0].sv_conds);
    }
#line 1923 "yacc.tab.cpp"
    break;

  case 34: /* fieldList: field  */
#line 213 "yacc.y"
    {
        (yyval.sv_fields) = std::vector<std::shared_ptr<Field>>{(yyvsp[0].sv_field)};
    }
#line 1931 "yacc.tab.cpp"
    break;

  case 35: /* fieldList: fieldList ',' field  */
#line 217 "yacc.y"
    {
        (yyval.sv_fields).push_back((yyvsp[0].sv_field));
    }
#line 1939 "yacc.tab.cpp"
    break;

  case 36: /* colNameList: colName  */
#line 224 "yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 1947 "yacc.tab.cpp"
    break;

  case 37: /* colNameList: colNameList ',' colName  */
#line 228 "yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 1955 "yacc.tab.cpp"
    break;

  case 38: /* field: colName type  */
#line 235 "yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-1].sv_str), (yyvsp[0].sv_type_len));
    }
#line 1963 "yacc.tab.cpp"
    break;

  case 39: /* type: INT  */
#line 242 "yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_INT, sizeof(int));
    }
#line 1971 "yacc.tab.cpp"
    break;

  case 40: /* type: CHAR '(' VALUE_INT ')'  */
#line 246 "yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_STRING, (yyvsp[-1].sv_int));
    }
#line 1979 "yacc.tab.cpp"
    break;

  case 41: /* type: FLOAT  */
#line 250 "yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_FLOAT, sizeof(float));
    }
#line 1987 "yacc.tab.cpp"
    break;

  case 42: /* valueList: value  */
#line 257 "yacc.y"
    {
        (yyval.sv_vals) = std::vector<std::shared_ptr<Value>>{(yyvsp[0].sv_val)};
    }
#line 1995 "yacc.tab.cpp"
    break;

  case 43: /* valueList: valueList ',' value  */
#line 261 "yacc.y"
    {
        (yyval.sv_vals).push_back((yyvsp[0].sv_val));
    }
#line 2003 "yacc.tab.cpp"
    break;

  case 44: /* value: VALUE_INT  */
#line 268 "yacc.y"
    {
        (yyval.sv_val) = std::make_shared<IntLit>((yyvsp[0].sv_int));
    }
#line 2011 "yacc.tab.cpp"
    break;

  case 45: /* value: VALUE_FLOAT  */
#line 272 "yacc.y"
    {
        (yyval.sv_val) = std::make_shared<FloatLit>((yyvsp[0].sv_float));
    }
#line 2019 "yacc.tab.cpp"
    break;

  case 46: /* value: VALUE_STRING  */
#line 276 "yacc.y"
    {
        (yyval.sv_val) = std::make_shared<StringLit>((yyvsp[0].sv_str));
    }
#line 2027 "yacc.tab.cpp"
    break;

  case 47: /* value: VALUE_BOOL  */
#line 280 "yacc.y"
    {
        (yyval.sv_val) = std::make_shared<BoolLit>((yyvsp[0].sv_bool));
    }
#line 2035 "yacc.tab.cpp"
    break;

  case 48: /* condition: col op expr  */
#line 287 "yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BinaryExpr>((yyvsp[-2].sv_col), (yyvsp[-1].sv_comp_op), (yyvsp[0].sv_expr));
    }
#line 2043 "yacc.tab.cpp"
    break;

  case 49: /* optWhereClause: %empty  */
#line 293 "yacc.y"
                      { /* ignore*/ }
#line 2049 "yacc.tab.cpp"
    break;

  case 50: /* optWhereClause: WHERE whereClause  */
#line 295 "yacc.y"
    {
        (yyval.sv_conds) = (yyvsp[0].sv_conds);
    }
#line 2057 "yacc.tab.cpp"
    break;

  case 51: /* whereClause: condition  */
#line 302 "yacc.y"
    {
        (yyval.sv_conds) = std::vector<std::shared_ptr<BinaryExpr>>{(yyvsp[0].sv_cond)};
    }
#line 2065 "yacc.tab.cpp"
    break;

  case 52: /* whereClause: whereClause AND condition  */
#line 306 "yacc.y"
    {
        (yyval.sv_conds).push_back((yyvsp[0].sv_cond));
    }
#line 2073 "yacc.tab.cpp"
    break;

  case 53: /* col: tbName '.' colName  */
#line 313 "yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
#line 2081 "yacc.tab.cpp"
    break;

  case 54: /* col: colName  */
#line 317 "yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>("", (yyvsp[0].sv_str));
    }
#line 2089 "yacc.tab.cpp"
    break;

  case 55: /* col: aggCol  */
#line 321 "yacc.y"
    {
        (yyval.sv_col) = (yyvsp[0].sv_col);
    }
#line 2097 "yacc.tab.cpp"
    break;

  case 56: /* colList: col  */
#line 328 "yacc.y"
    {
        (yyval.sv_cols) = std::vector<std::shared_ptr<Col>>{(yyvsp[0].sv_col)};
    }
#line 2105 "yacc.tab.cpp"
    break;

  case 57: /* colList: colList ',' col  */
#line 332 "yacc.y"
    {
        (yyval.sv_cols).push_back((yyvsp[0].sv_col));
    }
#line 2113 "yacc.tab.cpp"
    break;

  case 58: /* op: '='  */
#line 339 "yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_EQ;
    }
#line 2121 "yacc.tab.cpp"
    break;

  case 59: /* op: '<'  */
#line 343 "yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LT;
    }
#line 2129 "yacc.tab.cpp"
    break;

  case 60: /* op: '>'  */
#line 347 "yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GT;
    }
#line 2137 "yacc.tab.cpp"
    break;

  case 61: /* op: NEQ  */
#line 351 "yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_NE;
    }
#line 2145 "yacc.tab.cpp"
    break;

  case 62: /* op: LEQ  */
#line 355 "yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LE;
    }
#line 2153 "yacc.tab.cpp"
    break;

  case 63: /* op: GEQ  */
#line 359 "yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GE;
    }
#line 2161 "yacc.tab.cpp"
    break;

  case 64: /* expr: value  */
#line 366 "yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_val));
    }
#line 2169 "yacc.tab.cpp"
    break;

  case 65: /* expr: col  */
#line 370 "yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_col));
    }
#line 2177 "yacc.tab.cpp"
    break;

  case 66: /* setClauses: setClause  */
#line 377 "yacc.y"
    {
        (yyval.sv_set_clauses) = std::vector<std::shared_ptr<SetClause>>{(yyvsp[0].sv_set_clause)};
    }
#line 2185 "yacc.tab.cpp"
    break;

  case 67: /* setClauses: setClauses ',' setClause  */
#line 381 "yacc.y"
    {
        (yyval.sv_set_clauses).push_back((yyvsp[0].sv_set_clause));
    }
#line 2193 "yacc.tab.cpp"
    break;

  case 68: /* setClause: colName '=' value  */
#line 388 "yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-2].sv_str), (yyvsp[0].sv_val));
    }
#line 2201 "yacc.tab.cpp"
    break;

  case 69: /* setClause: colName '=' colName value  */
#line 392 "yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-3].sv_str), (yyvsp[0].sv_val), true);
    }
#line 2209 "yacc.tab.cpp"
    break;

  case 70: /* setClause: colName '=' colName '+' value  */
#line 396 "yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-4].sv_str), (yyvsp[0].sv_val), true);
    }
#line 2217 "yacc.tab.cpp"
    break;

  case 71: /* selector: '*'  */
#line 403 "yacc.y"
    {
        (yyval.sv_cols) = {};
    }
#line 2225 "yacc.tab.cpp"
    break;

  case 73: /* aggCol: MAX '(' col ')' AS alias  */
#line 411 "yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_MAX, (yyvsp[0].sv_str)));
    }
#line 2233 "yacc.tab.cpp"
    break;

  case 74: /* aggCol: MIN '(' col ')' AS alias  */
#line 415 "yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_MIN, (yyvsp[0].sv_str)));
    }
#line 2241 "yacc.tab.cpp"
    break;

  case 75: /* aggCol: SUM '(' col ')' AS alias  */
#line 419 "yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_SUM, (yyvsp[0].sv_str)));
    }
#line 2249 "yacc.tab.cpp"
    break;

  case 76: /* aggCol: AVG '(' col ')' AS alias  */
#line 423 "yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_AVG, (yyvsp[0].sv_str)));
    }
#line 2257 "yacc.tab.cpp"
    break;

  case 77: /* aggCol: COUNT '(' col ')' AS alias  */
#line 427 "yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-3].sv_col)->tab_name, (yyvsp[-3].sv_col)->col_name, AGG_COUNT, (yyvsp[0].sv_str)));
    }
#line 2265 "yacc.tab.cpp"
    break;

  case 78: /* aggCol: COUNT '(' '*' ')' AS alias  */
#line 431 "yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>("", "*", AGG_COUNT, (yyvsp[0].sv_str)));
    }
#line 2273 "yacc.tab.cpp"
    break;

  case 79: /* aggCol: MAX '(' col ')'  */
#line 435 "yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_MAX, ""));
    }
#line 2281 "yacc.tab.cpp"
    break;

  case 80: /* aggCol: MIN '(' col ')'  */
#line 439 "yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_MIN, ""));
    }
#line 2289 "yacc.tab.cpp"
    break;

  case 81: /* aggCol: SUM '(' col ')'  */
#line 443 "yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_SUM, ""));
    }
#line 2297 "yacc.tab.cpp"
    break;

  case 82: /* aggCol: AVG '(' col ')'  */
#line 447 "yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_AVG, ""));
    }
#line 2305 "yacc.tab.cpp"
    break;

  case 83: /* aggCol: COUNT '(' col ')'  */
#line 451 "yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>((yyvsp[-1].sv_col)->tab_name, (yyvsp[-1].sv_col)->col_name, AGG_COUNT, ""));
    }
#line 2313 "yacc.tab.cpp"
    break;

  case 84: /* aggCol: COUNT '(' '*' ')'  */
#line 455 "yacc.y"
    {
        (yyval.sv_col) = std::static_pointer_cast<Col>(std::make_shared<AggCol>("", "*", AGG_COUNT, ""));
    }
#line 2321 "yacc.tab.cpp"
    break;

  case 85: /* tableList: tbName  */
#line 462 "yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 2329 "yacc.tab.cpp"
    break;

  case 86: /* tableList: tableList ',' tbName  */
#line 466 "yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2337 "yacc.tab.cpp"
    break;

  case 87: /* tableList: tableList JOIN tbName  */
#line 470 "yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2345 "yacc.tab.cpp"
    break;

  case 88: /* opt_order_clause: ORDER BY order_clauses  */
#line 477 "yacc.y"
    { 
        (yyval.sv_orderbys) = (yyvsp[0].sv_orderbys); 
    }
#line 2353 "yacc.tab.cpp"
    break;

  case 89: /* opt_order_clause: %empty  */
#line 480 "yacc.y"
                      { /* ignore*/ }
#line 2359 "yacc.tab.cpp"
    break;

  case 90: /* order_clauses: order_clause  */
#line 485 "yacc.y"
    {
        (yyval.sv_orderbys) = std::vector<std::shared_ptr<OrderBy>>{(yyvsp[0].sv_orderby)};
    }
#line 2367 "yacc.tab.cpp"
    break;

  case 91: /* order_clauses: order_clauses ',' order_clause  */
#line 489 "yacc.y"
    {
        (yyval.sv_orderbys).push_back((yyvsp[0].sv_orderby));
    }
#line 2375 "yacc.tab.cpp"
    break;

  case 92: /* order_clause: col opt_asc_desc  */
#line 496 "yacc.y"
    { 
        (yyval.sv_orderby) = std::make_shared<OrderBy>((yyvsp[-1].sv_col), (yyvsp[0].sv_orderby_dir));
    }
#line 2383 "yacc.tab.cpp"
    break;

  case 93: /* opt_asc_desc: ASC  */
#line 502 "yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_ASC;     }
#line 2389 "yacc.tab.cpp"
    break;

  case 94: /* opt_asc_desc: DESC  */
#line 503 "yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_DESC;    }
#line 2395 "yacc.tab.cpp"
    break;

  case 95: /* opt_asc_desc: %empty  */
#line 504 "yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_ASC; }
#line 2401 "yacc.tab.cpp"
    break;

  case 96: /* set_knob_type: ENABLE_NESTLOOP  */
#line 508 "yacc.y"
                    { (yyval.sv_setKnobType) = EnableNestLoop; }
#line 2407 "yacc.tab.cpp"
    break;

  case 97: /* set_knob_type: ENABLE_SORTMERGE  */
#line 509 "yacc.y"
                         { (yyval.sv_setKnobType) = EnableSortMerge; }
#line 2413 "yacc.tab.cpp"
    break;


#line 2417 "yacc.tab.cpp"
=======
#line 67 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = (yyvsp[-1].sv_node);
        YYACCEPT;
    }
#line 1679 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 3: /* start: HELP  */
#line 72 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = std::make_shared<Help>();
        YYACCEPT;
    }
#line 1688 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 4: /* start: EXIT  */
#line 77 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1697 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 5: /* start: T_EOF  */
#line 82 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
#line 1706 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 11: /* txnStmt: TXN_BEGIN  */
#line 98 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnBegin>();
    }
#line 1714 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 12: /* txnStmt: TXN_COMMIT  */
#line 102 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnCommit>();
    }
#line 1722 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 13: /* txnStmt: TXN_ABORT  */
#line 106 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnAbort>();
    }
#line 1730 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 14: /* txnStmt: TXN_ROLLBACK  */
#line 110 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnRollback>();
    }
#line 1738 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 15: /* dbStmt: SHOW TABLES  */
#line 117 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowTables>();
    }
#line 1746 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 16: /* dbStmt: EXPLAIN dml  */
#line 121 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        if (auto select = std::dynamic_pointer_cast<SelectStmt>((yyvsp[0].sv_node))){
            select->need_explain = true;
            (yyval.sv_node) = select;
        }
    }
#line 1757 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 17: /* setStmt: SET set_knob_type '=' VALUE_BOOL  */
#line 131 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<SetStmt>((yyvsp[-2].sv_setKnobType), (yyvsp[0].sv_bool));
    }
#line 1765 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 18: /* ddl: CREATE TABLE tbName '(' fieldList ')'  */
#line 138 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateTable>((yyvsp[-3].sv_str), (yyvsp[-1].sv_fields));
    }
#line 1773 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 19: /* ddl: DROP TABLE tbName  */
#line 142 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropTable>((yyvsp[0].sv_str));
    }
#line 1781 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 20: /* ddl: DESC tbName  */
#line 146 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DescTable>((yyvsp[0].sv_str));
    }
#line 1789 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 21: /* ddl: CREATE INDEX tbName '(' colNameList ')'  */
#line 150 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1797 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 22: /* ddl: DROP INDEX tbName '(' colNameList ')'  */
#line 154 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1805 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 23: /* dml: INSERT INTO tbName VALUES '(' valueList ')'  */
#line 161 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<InsertStmt>((yyvsp[-4].sv_str), (yyvsp[-1].sv_vals));
    }
#line 1813 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 24: /* dml: DELETE FROM tbName optWhereClause  */
#line 165 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DeleteStmt>((yyvsp[-1].sv_str), (yyvsp[0].sv_conds));
    }
#line 1821 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 25: /* dml: UPDATE tbName SET setClauses optWhereClause  */
#line 169 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<UpdateStmt>((yyvsp[-3].sv_str), (yyvsp[-1].sv_set_clauses), (yyvsp[0].sv_conds));
    }
#line 1829 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 26: /* dml: SELECT selector FROM tableList optWhereClause opt_order_clause  */
#line 173 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<SelectStmt>((yyvsp[-4].sv_cols), (yyvsp[-2].sv_strs), (yyvsp[-1].sv_conds), (yyvsp[0].sv_orderby));
    }
#line 1837 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 27: /* dml: SELECT selector FROM join_exprss optWhereClause opt_order_clause  */
#line 177 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        /*$$ = std::make_shared<SelectStmt>($2, $4, $5, $6);*/
        /*必须要把所有表名赋值给SelectStmt的tabs，后面需要用*/
        auto sel_stmt = std::make_shared<SelectStmt>((yyvsp[-4].sv_cols), (yyvsp[-2].sv_join_exprs), (yyvsp[-1].sv_conds), (yyvsp[0].sv_orderby));
        std::set<std::string> tab_set;
        for (const auto &join_expr : (yyvsp[-2].sv_join_exprs)) {
            if (join_expr) {
                tab_set.insert(join_expr->left);
                tab_set.insert(join_expr->right);
            }
        }
        sel_stmt->tabs.assign(tab_set.begin(), tab_set.end());
        (yyval.sv_node) = sel_stmt;
    }
#line 1856 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 28: /* fieldList: field  */
#line 195 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_fields) = std::vector<std::shared_ptr<Field>>{(yyvsp[0].sv_field)};
    }
#line 1864 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 29: /* fieldList: fieldList ',' field  */
#line 199 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_fields).push_back((yyvsp[0].sv_field));
    }
#line 1872 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 30: /* colNameList: colName  */
#line 206 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 1880 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 31: /* colNameList: colNameList ',' colName  */
#line 210 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 1888 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 32: /* field: colName type  */
#line 217 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-1].sv_str), (yyvsp[0].sv_type_len));
    }
#line 1896 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 33: /* type: INT  */
#line 224 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_INT, sizeof(int));
    }
#line 1904 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 34: /* type: CHAR '(' VALUE_INT ')'  */
#line 228 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_STRING, (yyvsp[-1].sv_int));
    }
#line 1912 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 35: /* type: FLOAT  */
#line 232 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_FLOAT, sizeof(float));
    }
#line 1920 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 36: /* valueList: value  */
#line 239 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_vals) = std::vector<std::shared_ptr<Value>>{(yyvsp[0].sv_val)};
    }
#line 1928 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 37: /* valueList: valueList ',' value  */
#line 243 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_vals).push_back((yyvsp[0].sv_val));
    }
#line 1936 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 38: /* value: VALUE_INT  */
#line 250 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<IntLit>((yyvsp[0].sv_int));
    }
#line 1944 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 39: /* value: VALUE_FLOAT  */
#line 254 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<FloatLit>((yyvsp[0].sv_float));
    }
#line 1952 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 40: /* value: VALUE_STRING  */
#line 258 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<StringLit>((yyvsp[0].sv_str));
    }
#line 1960 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 41: /* value: VALUE_BOOL  */
#line 262 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<BoolLit>((yyvsp[0].sv_bool));
    }
#line 1968 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 42: /* condition: col op expr  */
#line 269 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BinaryExpr>((yyvsp[-2].sv_col), (yyvsp[-1].sv_comp_op), (yyvsp[0].sv_expr));
    }
#line 1976 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 43: /* optWhereClause: %empty  */
#line 275 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                      { /* ignore*/ }
#line 1982 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 44: /* optWhereClause: WHERE whereClause  */
#line 277 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_conds) = (yyvsp[0].sv_conds);
    }
#line 1990 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 45: /* whereClause: condition  */
#line 284 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_conds) = std::vector<std::shared_ptr<BinaryExpr>>{(yyvsp[0].sv_cond)};
    }
#line 1998 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 46: /* whereClause: whereClause AND condition  */
#line 288 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_conds).push_back((yyvsp[0].sv_cond));
    }
#line 2006 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 47: /* col: tbName '.' colName  */
#line 295 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
#line 2014 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 48: /* col: colName  */
#line 299 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>("", (yyvsp[0].sv_str));
    }
#line 2022 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 49: /* colList: col  */
#line 306 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols) = std::vector<std::shared_ptr<Col>>{(yyvsp[0].sv_col)};
    }
#line 2030 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 50: /* colList: colList ',' col  */
#line 310 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols).push_back((yyvsp[0].sv_col));
    }
#line 2038 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 51: /* op: '='  */
#line 317 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_EQ;
    }
#line 2046 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 52: /* op: '<'  */
#line 321 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LT;
    }
#line 2054 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 53: /* op: '>'  */
#line 325 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GT;
    }
#line 2062 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 54: /* op: NEQ  */
#line 329 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_NE;
    }
#line 2070 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 55: /* op: LEQ  */
#line 333 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LE;
    }
#line 2078 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 56: /* op: GEQ  */
#line 337 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GE;
    }
#line 2086 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 57: /* expr: value  */
#line 344 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_val));
    }
#line 2094 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 58: /* expr: col  */
#line 348 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_col));
    }
#line 2102 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 59: /* setClauses: setClause  */
#line 355 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses) = std::vector<std::shared_ptr<SetClause>>{(yyvsp[0].sv_set_clause)};
    }
#line 2110 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 60: /* setClauses: setClauses ',' setClause  */
#line 359 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses).push_back((yyvsp[0].sv_set_clause));       /*我怎么感觉这里写错了？难道不应该把setClauses先赋值给$$吗？而且setClause也不应该是vector而应该是ptr*/
    }
#line 2118 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 61: /* setClause: colName '=' value  */
#line 366 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-2].sv_str), (yyvsp[0].sv_val));
    }
#line 2126 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 62: /* selector: '*'  */
#line 373 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_cols) = {};
    }
#line 2134 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 64: /* tableList: tbNameWithAlias  */
#line 381 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 2142 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 65: /* tableList: tableList ',' tbNameWithAlias  */
#line 385 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2150 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 66: /* tbNameWithAlias: tbName  */
#line 396 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_str) = (yyvsp[0].sv_str);
    }
#line 2158 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 67: /* tbNameWithAlias: tbName alias  */
#line 400 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        alias_map[(yyvsp[0].sv_str)] = (yyvsp[-1].sv_str);
        pam_saila[(yyvsp[-1].sv_str)] = (yyvsp[0].sv_str);
        (yyval.sv_str) = (yyvsp[-1].sv_str);
    }
#line 2168 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 68: /* join_exprss: tbNameWithAlias join_exprs  */
#line 408 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_join_exprs) = (yyvsp[0].sv_join_exprs);
        for (auto& join_expr : (yyval.sv_join_exprs)) {
            join_expr->left = (yyvsp[-1].sv_str);
        }
    }
#line 2179 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 69: /* join_exprs: join_expr  */
#line 418 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_join_exprs) = std::vector<std::shared_ptr<JoinExpr>>{(yyvsp[0].sv_join_expr)};
    }
#line 2187 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 70: /* join_exprs: join_exprs join_expr  */
#line 422 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_join_exprs).push_back((yyvsp[0].sv_join_expr));
    }
#line 2195 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 71: /* join_expr: join_type tbNameWithAlias ON whereClause  */
#line 428 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    {
        (yyval.sv_join_expr) = std::make_shared<JoinExpr>("", (yyvsp[-2].sv_str), (yyvsp[0].sv_conds), (yyvsp[-3].join_type_dir));
    }
#line 2203 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 72: /* join_type: JOIN  */
#line 433 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
               { (yyval.join_type_dir) = INNER_JOIN; }
#line 2209 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 73: /* join_type: INNER JOIN  */
#line 434 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                     { (yyval.join_type_dir) = INNER_JOIN; }
#line 2215 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 74: /* join_type: LEFT JOIN  */
#line 435 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                    { (yyval.join_type_dir) = LEFT_JOIN; }
#line 2221 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 75: /* join_type: RIGHT JOIN  */
#line 436 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                     { (yyval.join_type_dir) = RIGHT_JOIN; }
#line 2227 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 76: /* join_type: FULL JOIN  */
#line 437 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                    { (yyval.join_type_dir) = FULL_JOIN; }
#line 2233 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 77: /* join_type: SEMI JOIN  */
#line 438 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                    { (yyval.join_type_dir) = SEMI_JOIN; }
#line 2239 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 78: /* opt_order_clause: ORDER BY order_clause  */
#line 444 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    { 
        (yyval.sv_orderby) = (yyvsp[0].sv_orderby); 
    }
#line 2247 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 79: /* opt_order_clause: %empty  */
#line 447 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                      { /* ignore*/ }
#line 2253 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 80: /* order_clause: col opt_asc_desc  */
#line 452 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
    { 
        (yyval.sv_orderby) = std::make_shared<OrderBy>((yyvsp[-1].sv_col), (yyvsp[0].sv_orderby_dir));
    }
#line 2261 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 81: /* opt_asc_desc: ASC  */
#line 458 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_ASC;     }
#line 2267 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 82: /* opt_asc_desc: DESC  */
#line 459 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_DESC;    }
#line 2273 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 83: /* opt_asc_desc: %empty  */
#line 460 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
            { (yyval.sv_orderby_dir) = OrderBy_DEFAULT; }
#line 2279 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 84: /* set_knob_type: ENABLE_NESTLOOP  */
#line 464 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                    { (yyval.sv_setKnobType) = EnableNestLoop; }
#line 2285 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;

  case 85: /* set_knob_type: ENABLE_SORTMERGE  */
#line 465 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"
                         { (yyval.sv_setKnobType) = EnableSortMerge; }
#line 2291 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
    break;


#line 2295 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.tab.cpp"
>>>>>>> origin/p4

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

<<<<<<< HEAD
#line 517 "yacc.y"

=======
#line 473 "/home/haustle/db2025-jinsenianhua/src/parser/yacc.y"

>>>>>>> origin/p4
