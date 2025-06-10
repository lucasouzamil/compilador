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
#line 1 "src/lumi.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"

// 1. INCLUIR A DEFINIÇÃO DA AST E DECLARAR A RAIZ GLOBAL
#include "ast.h"

void yyerror(const char *s);
int  yylex(void);
extern FILE *yyin;
extern int yyrestart(FILE *);

// A raiz da nossa árvore sintática. O parser irá preenchê-la.
NodeList* ast_root = NULL;

// Protótipos das funções auxiliares para criar nós
AstNode* create_strip_decl(int count);
AstNode* create_assignment(char* id, AstNode* expr);
AstNode* create_if_stmt(AstNode* cond, NodeList* if_block, NodeList* else_block);
AstNode* create_while_stmt(AstNode* cond, NodeList* block);
AstNode* create_for_stmt(char* id, AstNode* start, AstNode* end, NodeList* block);
AstNode* create_loop_forever(NodeList* block);
AstNode* create_set_cmd(AstNode* index, AstNode* color);
AstNode* create_wait_cmd(char* time_lit);
AstNode* create_rotate_cmd(AstNode* steps, DirectionType dir);
AstNode* create_fade_cmd(AstNode* amount);
AstNode* create_binary_op(int op, AstNode* left, AstNode* right);
AstNode* create_unary_op(int op, AstNode* operand);
AstNode* create_integer(int value);
AstNode* create_identifier(char* name);
AstNode* create_color_hex(char* hex_code);
AstNode* create_hsv_color(AstNode* h, AstNode* s, AstNode* v);
NodeList* add_to_list(NodeList* list, AstNode* node);

#line 108 "build/lumi.tab.c"

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

#include "lumi.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_COLOR_HEX = 5,                  /* COLOR_HEX  */
  YYSYMBOL_TIME_LIT = 6,                   /* TIME_LIT  */
  YYSYMBOL_T_STRIP = 7,                    /* T_STRIP  */
  YYSYMBOL_T_IF = 8,                       /* T_IF  */
  YYSYMBOL_T_ELSE = 9,                     /* T_ELSE  */
  YYSYMBOL_T_WHILE = 10,                   /* T_WHILE  */
  YYSYMBOL_T_FOR = 11,                     /* T_FOR  */
  YYSYMBOL_T_LOOP = 12,                    /* T_LOOP  */
  YYSYMBOL_T_FOREVER = 13,                 /* T_FOREVER  */
  YYSYMBOL_T_SET = 14,                     /* T_SET  */
  YYSYMBOL_T_COLOR = 15,                   /* T_COLOR  */
  YYSYMBOL_T_WAIT = 16,                    /* T_WAIT  */
  YYSYMBOL_T_ROTATE = 17,                  /* T_ROTATE  */
  YYSYMBOL_T_DIR = 18,                     /* T_DIR  */
  YYSYMBOL_T_FADE = 19,                    /* T_FADE  */
  YYSYMBOL_T_HSV = 20,                     /* T_HSV  */
  YYSYMBOL_T_LEFT = 21,                    /* T_LEFT  */
  YYSYMBOL_T_RIGHT = 22,                   /* T_RIGHT  */
  YYSYMBOL_EQ = 23,                        /* EQ  */
  YYSYMBOL_NEQ = 24,                       /* NEQ  */
  YYSYMBOL_LE = 25,                        /* LE  */
  YYSYMBOL_GE = 26,                        /* GE  */
  YYSYMBOL_AND = 27,                       /* AND  */
  YYSYMBOL_OR = 28,                        /* OR  */
  YYSYMBOL_DOTDOT = 29,                    /* DOTDOT  */
  YYSYMBOL_NEWLINE = 30,                   /* NEWLINE  */
  YYSYMBOL_31_ = 31,                       /* '<'  */
  YYSYMBOL_32_ = 32,                       /* '>'  */
  YYSYMBOL_33_ = 33,                       /* '+'  */
  YYSYMBOL_34_ = 34,                       /* '-'  */
  YYSYMBOL_35_ = 35,                       /* '*'  */
  YYSYMBOL_36_ = 36,                       /* '/'  */
  YYSYMBOL_37_ = 37,                       /* '%'  */
  YYSYMBOL_38_ = 38,                       /* '!'  */
  YYSYMBOL_UMINUS = 39,                    /* UMINUS  */
  YYSYMBOL_40_ = 40,                       /* '{'  */
  YYSYMBOL_41_ = 41,                       /* '}'  */
  YYSYMBOL_42_ = 42,                       /* '='  */
  YYSYMBOL_43_ = 43,                       /* '('  */
  YYSYMBOL_44_ = 44,                       /* ')'  */
  YYSYMBOL_45_ = 45,                       /* ','  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_program = 47,                   /* program  */
  YYSYMBOL_statements = 48,                /* statements  */
  YYSYMBOL_statement = 49,                 /* statement  */
  YYSYMBOL_block = 50,                     /* block  */
  YYSYMBOL_assignment = 51,                /* assignment  */
  YYSYMBOL_if_stmt = 52,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 53,                /* while_stmt  */
  YYSYMBOL_for_stmt = 54,                  /* for_stmt  */
  YYSYMBOL_loop_forever = 55,              /* loop_forever  */
  YYSYMBOL_command = 56,                   /* command  */
  YYSYMBOL_direction = 57,                 /* direction  */
  YYSYMBOL_expression = 58,                /* expression  */
  YYSYMBOL_bool_expr = 59,                 /* bool_expr  */
  YYSYMBOL_rel_expr = 60,                  /* rel_expr  */
  YYSYMBOL_eq_expr = 61,                   /* eq_expr  */
  YYSYMBOL_color_expr = 62                 /* color_expr  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   171

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  49
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  107

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


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
       2,     2,     2,    38,     2,     2,     2,    37,     2,     2,
      43,    44,    35,    33,    45,    34,     2,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      31,    42,    32,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    80,    80,    86,    87,    92,    94,    96,    98,   100,
     102,   104,   106,   111,   116,   121,   123,   128,   133,   138,
     143,   145,   147,   149,   154,   155,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   175,   177,   182,
     184,   189,   191,   193,   195,   197,   199,   201,   206,   208
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "ID",
  "COLOR_HEX", "TIME_LIT", "T_STRIP", "T_IF", "T_ELSE", "T_WHILE", "T_FOR",
  "T_LOOP", "T_FOREVER", "T_SET", "T_COLOR", "T_WAIT", "T_ROTATE", "T_DIR",
  "T_FADE", "T_HSV", "T_LEFT", "T_RIGHT", "EQ", "NEQ", "LE", "GE", "AND",
  "OR", "DOTDOT", "NEWLINE", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'!'", "UMINUS", "'{'", "'}'", "'='", "'('", "')'", "','",
  "$accept", "program", "statements", "statement", "block", "assignment",
  "if_stmt", "while_stmt", "for_stmt", "loop_forever", "command",
  "direction", "expression", "bool_expr", "rel_expr", "eq_expr",
  "color_expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-55)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -55,    25,    73,   -55,   -16,    29,    -9,     0,    36,    28,
      32,    38,    32,    32,   -55,   -55,    23,   -55,   -55,   -55,
     -55,    24,    32,    33,    32,    32,    13,    22,   -55,   -55,
     -55,    21,    32,    32,    32,    63,   -55,   -55,    75,   134,
     -55,   -55,   134,   -55,   134,   -13,    40,   120,   -11,    32,
     -55,   -55,    32,   -55,   -55,    98,     1,    32,    32,    32,
      32,    32,    -2,    32,    22,    32,    32,    32,    32,    32,
      32,    32,    22,   121,    -3,    80,   -55,   -55,    -7,    -7,
     -55,   -55,   -55,   -55,   -55,   -55,    40,    56,   120,   134,
     134,   134,   134,   134,   134,   -55,    32,   -55,    32,    22,
     126,    85,   -55,   -55,    32,   103,   -55
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    12,     4,     0,     7,     8,     9,
      10,     0,     0,     0,     0,     0,     0,     0,    33,    34,
      48,     0,     0,     0,     0,     0,    36,    21,     0,    23,
       6,    11,    14,     5,    41,     0,    37,    39,     0,     0,
       3,    19,     0,    31,    32,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    35,    20,    26,    27,
      28,    29,    30,    24,    25,    22,    38,    15,    40,    42,
      43,    46,    47,    44,    45,    17,     0,    13,     0,     0,
       0,     0,    16,    18,     0,     0,    49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -55,   -55,    18,   -55,   -54,   -55,   -55,   -55,   -55,   -55,
     -55,   -55,   -10,    44,     8,     7,    17
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    15,    51,    16,    17,    18,    19,    20,
      21,    85,    44,    45,    46,    47,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      35,     4,    38,    39,     5,     6,    30,     7,     8,     9,
      87,    10,    42,    11,    12,    63,    13,    63,    95,    83,
      84,    31,    53,    54,    55,     3,    22,    14,    59,    60,
      61,    64,    23,    72,    24,    28,    29,    30,    97,    73,
      26,    27,    75,    25,    37,   102,   103,    78,    79,    80,
      81,    82,    31,    40,    41,    49,    89,    90,    91,    92,
      93,    94,    50,    43,    52,    99,    32,    65,    74,    48,
      33,    86,    88,    77,     0,    34,     0,     4,    56,     0,
       5,     6,     0,     7,     8,     9,   100,    10,   101,    11,
      12,     0,    13,    62,   105,     0,    57,    58,    59,    60,
      61,     0,     0,    14,     0,     0,     0,     0,    57,    58,
      59,    60,    61,    57,    58,    59,    60,    61,    57,    58,
      59,    60,    61,     0,     0,    98,     0,     0,     0,     0,
     104,    57,    58,    59,    60,    61,    57,    58,    59,    60,
      61,     0,    76,    66,    67,    68,    69,   106,     0,     0,
      96,    70,    71,     0,    57,    58,    59,    60,    61,    57,
      58,    59,    60,    61,     0,     0,    50,    57,    58,    59,
      60,    61
};

static const yytype_int8 yycheck[] =
{
      10,     4,    12,    13,     7,     8,     5,    10,    11,    12,
      64,    14,    22,    16,    17,    28,    19,    28,    72,    21,
      22,    20,    32,    33,    34,     0,    42,    30,    35,    36,
      37,    44,     3,    44,    43,     3,     4,     5,    41,    49,
       4,    13,    52,    43,     6,    99,   100,    57,    58,    59,
      60,    61,    20,    30,    30,    42,    66,    67,    68,    69,
      70,    71,    40,    30,    43,     9,    34,    27,    50,    25,
      38,    63,    65,    56,    -1,    43,    -1,     4,    15,    -1,
       7,     8,    -1,    10,    11,    12,    96,    14,    98,    16,
      17,    -1,    19,    18,   104,    -1,    33,    34,    35,    36,
      37,    -1,    -1,    30,    -1,    -1,    -1,    -1,    33,    34,
      35,    36,    37,    33,    34,    35,    36,    37,    33,    34,
      35,    36,    37,    -1,    -1,    45,    -1,    -1,    -1,    -1,
      45,    33,    34,    35,    36,    37,    33,    34,    35,    36,
      37,    -1,    44,    23,    24,    25,    26,    44,    -1,    -1,
      29,    31,    32,    -1,    33,    34,    35,    36,    37,    33,
      34,    35,    36,    37,    -1,    -1,    40,    33,    34,    35,
      36,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    47,    48,     0,     4,     7,     8,    10,    11,    12,
      14,    16,    17,    19,    30,    49,    51,    52,    53,    54,
      55,    56,    42,     3,    43,    43,     4,    13,     3,     4,
       5,    20,    34,    38,    43,    58,    62,     6,    58,    58,
      30,    30,    58,    30,    58,    59,    60,    61,    59,    42,
      40,    50,    43,    58,    58,    58,    15,    33,    34,    35,
      36,    37,    18,    28,    44,    27,    23,    24,    25,    26,
      31,    32,    44,    58,    48,    58,    44,    62,    58,    58,
      58,    58,    58,    21,    22,    57,    60,    50,    61,    58,
      58,    58,    58,    58,    58,    50,    29,    41,    45,     9,
      58,    58,    50,    50,    45,    58,    44
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    49,    49,    49,
      49,    49,    49,    50,    51,    52,    52,    53,    54,    55,
      56,    56,    56,    56,    57,    57,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    59,    59,    60,
      60,    61,    61,    61,    61,    61,    61,    61,    62,    62
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     1,     1,     1,
       1,     2,     1,     3,     3,     5,     7,     5,     7,     3,
       4,     2,     4,     2,     1,     1,     3,     3,     3,     3,
       3,     2,     2,     1,     1,     3,     1,     1,     3,     1,
       3,     1,     3,     3,     3,     3,     3,     3,     1,     8
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
  case 2: /* program: statements  */
#line 81 "src/lumi.y"
    { ast_root = (yyvsp[0].list); }
#line 1502 "build/lumi.tab.c"
    break;

  case 3: /* statements: %empty  */
#line 86 "src/lumi.y"
    { (yyval.list) = NULL; }
#line 1508 "build/lumi.tab.c"
    break;

  case 4: /* statements: statements statement  */
#line 88 "src/lumi.y"
    { (yyval.list) = add_to_list((yyvsp[-1].list), (yyvsp[0].node)); }
#line 1514 "build/lumi.tab.c"
    break;

  case 5: /* statement: T_STRIP INT NEWLINE  */
#line 93 "src/lumi.y"
    { (yyval.node) = create_strip_decl((yyvsp[-1].ival)); }
#line 1520 "build/lumi.tab.c"
    break;

  case 6: /* statement: assignment NEWLINE  */
#line 95 "src/lumi.y"
    { (yyval.node) = (yyvsp[-1].node); }
#line 1526 "build/lumi.tab.c"
    break;

  case 7: /* statement: if_stmt  */
#line 97 "src/lumi.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1532 "build/lumi.tab.c"
    break;

  case 8: /* statement: while_stmt  */
#line 99 "src/lumi.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1538 "build/lumi.tab.c"
    break;

  case 9: /* statement: for_stmt  */
#line 101 "src/lumi.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1544 "build/lumi.tab.c"
    break;

  case 10: /* statement: loop_forever  */
#line 103 "src/lumi.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1550 "build/lumi.tab.c"
    break;

  case 11: /* statement: command NEWLINE  */
#line 105 "src/lumi.y"
    { (yyval.node) = (yyvsp[-1].node); }
#line 1556 "build/lumi.tab.c"
    break;

  case 12: /* statement: NEWLINE  */
#line 107 "src/lumi.y"
    { (yyval.node) = NULL; }
#line 1562 "build/lumi.tab.c"
    break;

  case 13: /* block: '{' statements '}'  */
#line 112 "src/lumi.y"
    { (yyval.list) = (yyvsp[-1].list); }
#line 1568 "build/lumi.tab.c"
    break;

  case 14: /* assignment: ID '=' expression  */
#line 117 "src/lumi.y"
    { (yyval.node) = create_assignment((yyvsp[-2].sval), (yyvsp[0].node)); }
#line 1574 "build/lumi.tab.c"
    break;

  case 15: /* if_stmt: T_IF '(' bool_expr ')' block  */
#line 122 "src/lumi.y"
    { (yyval.node) = create_if_stmt((yyvsp[-2].node), (yyvsp[0].list), NULL); }
#line 1580 "build/lumi.tab.c"
    break;

  case 16: /* if_stmt: T_IF '(' bool_expr ')' block T_ELSE block  */
#line 124 "src/lumi.y"
    { (yyval.node) = create_if_stmt((yyvsp[-4].node), (yyvsp[-2].list), (yyvsp[0].list)); }
#line 1586 "build/lumi.tab.c"
    break;

  case 17: /* while_stmt: T_WHILE '(' bool_expr ')' block  */
#line 129 "src/lumi.y"
    { (yyval.node) = create_while_stmt((yyvsp[-2].node), (yyvsp[0].list)); }
#line 1592 "build/lumi.tab.c"
    break;

  case 18: /* for_stmt: T_FOR ID '=' expression DOTDOT expression block  */
#line 134 "src/lumi.y"
    { (yyval.node) = create_for_stmt((yyvsp[-5].sval), (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].list)); }
#line 1598 "build/lumi.tab.c"
    break;

  case 19: /* loop_forever: T_LOOP T_FOREVER block  */
#line 139 "src/lumi.y"
    { (yyval.node) = create_loop_forever((yyvsp[0].list)); }
#line 1604 "build/lumi.tab.c"
    break;

  case 20: /* command: T_SET expression T_COLOR color_expr  */
#line 144 "src/lumi.y"
    { (yyval.node) = create_set_cmd((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1610 "build/lumi.tab.c"
    break;

  case 21: /* command: T_WAIT TIME_LIT  */
#line 146 "src/lumi.y"
    { (yyval.node) = create_wait_cmd((yyvsp[0].sval)); }
#line 1616 "build/lumi.tab.c"
    break;

  case 22: /* command: T_ROTATE expression T_DIR direction  */
#line 148 "src/lumi.y"
    { (yyval.node) = create_rotate_cmd((yyvsp[-2].node), (yyvsp[0].dir_val)); }
#line 1622 "build/lumi.tab.c"
    break;

  case 23: /* command: T_FADE expression  */
#line 150 "src/lumi.y"
    { (yyval.node) = create_fade_cmd((yyvsp[0].node)); }
#line 1628 "build/lumi.tab.c"
    break;

  case 24: /* direction: T_LEFT  */
#line 154 "src/lumi.y"
            { (yyval.dir_val) = DIR_LEFT; }
#line 1634 "build/lumi.tab.c"
    break;

  case 25: /* direction: T_RIGHT  */
#line 155 "src/lumi.y"
            { (yyval.dir_val) = DIR_RIGHT; }
#line 1640 "build/lumi.tab.c"
    break;

  case 26: /* expression: expression '+' expression  */
#line 160 "src/lumi.y"
                              { (yyval.node) = create_binary_op('+', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1646 "build/lumi.tab.c"
    break;

  case 27: /* expression: expression '-' expression  */
#line 161 "src/lumi.y"
                              { (yyval.node) = create_binary_op('-', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1652 "build/lumi.tab.c"
    break;

  case 28: /* expression: expression '*' expression  */
#line 162 "src/lumi.y"
                              { (yyval.node) = create_binary_op('*', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1658 "build/lumi.tab.c"
    break;

  case 29: /* expression: expression '/' expression  */
#line 163 "src/lumi.y"
                              { (yyval.node) = create_binary_op('/', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1664 "build/lumi.tab.c"
    break;

  case 30: /* expression: expression '%' expression  */
#line 164 "src/lumi.y"
                              { (yyval.node) = create_binary_op('%', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1670 "build/lumi.tab.c"
    break;

  case 31: /* expression: '-' expression  */
#line 165 "src/lumi.y"
                                { (yyval.node) = create_unary_op('-', (yyvsp[0].node)); }
#line 1676 "build/lumi.tab.c"
    break;

  case 32: /* expression: '!' expression  */
#line 166 "src/lumi.y"
                                { (yyval.node) = create_unary_op('!', (yyvsp[0].node)); }
#line 1682 "build/lumi.tab.c"
    break;

  case 33: /* expression: INT  */
#line 167 "src/lumi.y"
                                { (yyval.node) = create_integer((yyvsp[0].ival)); }
#line 1688 "build/lumi.tab.c"
    break;

  case 34: /* expression: ID  */
#line 168 "src/lumi.y"
                                { (yyval.node) = create_identifier((yyvsp[0].sval)); }
#line 1694 "build/lumi.tab.c"
    break;

  case 35: /* expression: '(' expression ')'  */
#line 169 "src/lumi.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 1700 "build/lumi.tab.c"
    break;

  case 36: /* expression: color_expr  */
#line 170 "src/lumi.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1706 "build/lumi.tab.c"
    break;

  case 37: /* bool_expr: rel_expr  */
#line 176 "src/lumi.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1712 "build/lumi.tab.c"
    break;

  case 38: /* bool_expr: bool_expr OR rel_expr  */
#line 178 "src/lumi.y"
    { (yyval.node) = create_binary_op(OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1718 "build/lumi.tab.c"
    break;

  case 39: /* rel_expr: eq_expr  */
#line 183 "src/lumi.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1724 "build/lumi.tab.c"
    break;

  case 40: /* rel_expr: rel_expr AND eq_expr  */
#line 185 "src/lumi.y"
    { (yyval.node) = create_binary_op(AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1730 "build/lumi.tab.c"
    break;

  case 41: /* eq_expr: expression  */
#line 190 "src/lumi.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1736 "build/lumi.tab.c"
    break;

  case 42: /* eq_expr: eq_expr EQ expression  */
#line 192 "src/lumi.y"
    { (yyval.node) = create_binary_op(EQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1742 "build/lumi.tab.c"
    break;

  case 43: /* eq_expr: eq_expr NEQ expression  */
#line 194 "src/lumi.y"
    { (yyval.node) = create_binary_op(NEQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1748 "build/lumi.tab.c"
    break;

  case 44: /* eq_expr: eq_expr '<' expression  */
#line 196 "src/lumi.y"
    { (yyval.node) = create_binary_op('<', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1754 "build/lumi.tab.c"
    break;

  case 45: /* eq_expr: eq_expr '>' expression  */
#line 198 "src/lumi.y"
    { (yyval.node) = create_binary_op('>', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1760 "build/lumi.tab.c"
    break;

  case 46: /* eq_expr: eq_expr LE expression  */
#line 200 "src/lumi.y"
    { (yyval.node) = create_binary_op(LE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1766 "build/lumi.tab.c"
    break;

  case 47: /* eq_expr: eq_expr GE expression  */
#line 202 "src/lumi.y"
    { (yyval.node) = create_binary_op(GE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1772 "build/lumi.tab.c"
    break;

  case 48: /* color_expr: COLOR_HEX  */
#line 207 "src/lumi.y"
    { (yyval.node) = create_color_hex((yyvsp[0].sval)); }
#line 1778 "build/lumi.tab.c"
    break;

  case 49: /* color_expr: T_HSV '(' expression ',' expression ',' expression ')'  */
#line 209 "src/lumi.y"
    { (yyval.node) = create_hsv_color((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 1784 "build/lumi.tab.c"
    break;


#line 1788 "build/lumi.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
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
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 211 "src/lumi.y"


/* 4. IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES */

// Função para alocar memória e checar erros
void* safe_malloc(size_t size) {
  void* ptr = malloc(size);
  if (!ptr) {
    fprintf(stderr, "Erro fatal: falha na alocação de memória.\n");
    exit(1);
  }
  return ptr;
}

// Construtor para lista de statements
NodeList* add_to_list(NodeList* list, AstNode* node) {
  if (!node) return list; // Não adiciona nós nulos (ex: linhas em branco)

  NodeList* new_item = (NodeList*) safe_malloc(sizeof(NodeList));
  new_item->node = node;
  new_item->next = NULL;

  if (!list) { // Se a lista está vazia, este é o primeiro item
      return new_item;
  }

  NodeList* current = list;
  while (current->next != NULL) {
      current = current->next;
  }
  current->next = new_item;
  return list;
}

// Construtores para cada tipo de nó
AstNode* create_strip_decl(int count) {
  StripDeclNode* node = (StripDeclNode*) safe_malloc(sizeof(StripDeclNode));
  node->type = NODE_TYPE_STRIP_DECL;
  node->led_count = count;
  return (AstNode*) node;
}

AstNode* create_assignment(char* id, AstNode* expr) {
  AssignmentNode* node = (AssignmentNode*) safe_malloc(sizeof(AssignmentNode));
  node->type = NODE_TYPE_ASSIGNMENT;
  node->identifier = id;
  node->expression = expr;
  return (AstNode*) node;
}

AstNode* create_if_stmt(AstNode* cond, NodeList* if_block, NodeList* else_block) {
  IfStmtNode* node = (IfStmtNode*) safe_malloc(sizeof(IfStmtNode));
  node->type = NODE_TYPE_IF_STMT;
  node->condition = cond;
  node->if_block = if_block;
  node->else_block = else_block;
  return (AstNode*) node;
}

AstNode* create_while_stmt(AstNode* cond, NodeList* block) {
  WhileStmtNode* node = (WhileStmtNode*) safe_malloc(sizeof(WhileStmtNode));
  node->type = NODE_TYPE_WHILE_STMT;
  node->condition = cond;
  node->block = block;
  return (AstNode*) node;
}

AstNode* create_for_stmt(char* id, AstNode* start, AstNode* end, NodeList* block) {
  ForStmtNode* node = (ForStmtNode*) safe_malloc(sizeof(ForStmtNode));
  node->type = NODE_TYPE_FOR_STMT;
  node->identifier = id;
  node->start_expr = start;
  node->end_expr = end;
  node->block = block;
  return (AstNode*) node;
}

AstNode* create_loop_forever(NodeList* block) {
  LoopForeverNode* node = (LoopForeverNode*) safe_malloc(sizeof(LoopForeverNode));
  node->type = NODE_TYPE_LOOP_FOREVER;
  node->block = block;
  return (AstNode*) node;
}

AstNode* create_set_cmd(AstNode* index, AstNode* color) {
  SetCmdNode* node = (SetCmdNode*) safe_malloc(sizeof(SetCmdNode));
  node->type = NODE_TYPE_SET_CMD;
  node->index_expr = index;
  node->color_expr = color;
  return (AstNode*) node;
}

// Converte "50ms" para 50, "2s" para 2000
int parse_time_literal(char* time_lit) {
  int len = strlen(time_lit);
  int value = atoi(time_lit);
  if (strcmp(&time_lit[len-2], "ms") == 0) {
      return value;
  }
  if (time_lit[len-1] == 's') {
      return value * 1000;
  }
  return value; // Fallback
}

AstNode* create_wait_cmd(char* time_lit) {
  WaitCmdNode* node = (WaitCmdNode*) safe_malloc(sizeof(WaitCmdNode));
  node->type = NODE_TYPE_WAIT_CMD;
  node->value_ms = parse_time_literal(time_lit);
  free(time_lit); // Liberamos a string copiada pelo Flex
  return (AstNode*) node;
}

AstNode* create_rotate_cmd(AstNode* steps, DirectionType dir) {
  RotateCmdNode* node = (RotateCmdNode*) safe_malloc(sizeof(RotateCmdNode));
  node->type = NODE_TYPE_ROTATE_CMD;
  node->steps_expr = steps;
  node->direction = dir;
  return (AstNode*) node;
}

AstNode* create_fade_cmd(AstNode* amount) {
  FadeCmdNode* node = (FadeCmdNode*) safe_malloc(sizeof(FadeCmdNode));
  node->type = NODE_TYPE_FADE_CMD;
  node->amount_expr = amount;
  return (AstNode*) node;
}

AstNode* create_binary_op(int op, AstNode* left, AstNode* right) {
  BinaryOpNode* node = (BinaryOpNode*) safe_malloc(sizeof(BinaryOpNode));
  node->type = NODE_TYPE_BINARY_OP;
  node->op = op;
  node->left = left;
  node->right = right;
  return (AstNode*) node;
}

AstNode* create_unary_op(int op, AstNode* operand) {
  UnaryOpNode* node = (UnaryOpNode*) safe_malloc(sizeof(UnaryOpNode));
  node->type = NODE_TYPE_UNARY_OP;
  node->op = op;
  node->operand = operand;
  return (AstNode*) node;
}

AstNode* create_integer(int value) {
  IntegerNode* node = (IntegerNode*) safe_malloc(sizeof(IntegerNode));
  node->type = NODE_TYPE_INTEGER;
  node->value = value;
  return (AstNode*) node;
}

AstNode* create_identifier(char* name) {
  IdentifierNode* node = (IdentifierNode*) safe_malloc(sizeof(IdentifierNode));
  node->type = NODE_TYPE_IDENTIFIER;
  node->name = name;
  return (AstNode*) node;
}

AstNode* create_color_hex(char* hex_code) {
  ColorHexNode* node = (ColorHexNode*) safe_malloc(sizeof(ColorHexNode));
  node->type = NODE_TYPE_COLOR_HEX;
  node->hex_code = hex_code;
  return (AstNode*) node;
}

AstNode* create_hsv_color(AstNode* h, AstNode* s, AstNode* v) {
  HsvColorNode* node = (HsvColorNode*) safe_malloc(sizeof(HsvColorNode));
  node->type = NODE_TYPE_COLOR_HSV;
  node->h_expr = h;
  node->s_expr = s;
  node->v_expr = v;
  return (AstNode*) node;
}

void yyerror(const char *s) {
  fprintf(stderr, "Erro sintático: %s\n", s);
}
