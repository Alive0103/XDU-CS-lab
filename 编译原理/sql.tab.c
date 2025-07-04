
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "sql.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

extern int yylex();
extern int yyparse();
extern FILE *yyin;
extern char *yytext;
extern int yylineno;

char database[64]={0};
extern struct mydb *dbroot;

void yyerror (const char *str) 
{
	fprintf(stderr, "error: %s\n", str);		// error function
}

int yywrap() 
{
	return 1;
}
// main function 
int main() 
{
	printf("SQL>");
	return	yyparse(); // calling parse funtion 
} 



/* Line 189 of yacc.c  */
#line 107 "sql.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SELECT = 258,
     FROM = 259,
     WHERE = 260,
     AND = 261,
     OR = 262,
     DROP = 263,
     DELETE = 264,
     TABLE = 265,
     CREATE = 266,
     INTO = 267,
     VALUES = 268,
     INSERT = 269,
     UPDATE = 270,
     SET = 271,
     SHOW = 272,
     DATABASE = 273,
     DATABASES = 274,
     TABLES = 275,
     EXIT = 276,
     USE = 277,
     NUMBER = 278,
     STRING = 279,
     ID = 280,
     INT = 281,
     CHAR = 282
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 34 "sql.y"
  
	int intval;   
  	char *strval;
  	struct hyper_items_def *Citemsval;
  	struct value_def *valueval;
  	struct item_def *itemval;
  	struct conditions_def *conval;
  	struct table_def *tbval;
  	struct upcon_def *updateval;



/* Line 214 of yacc.c  */
#line 183 "sql.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 195 "sql.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  36
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   168

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNRULES -- Number of states.  */
#define YYNSTATES  151

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      29,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,     2,     2,     2,     2,     2,
      30,    31,    32,     2,    33,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    28,
      36,    34,    35,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    37,    38
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    31,    36,    41,    50,    56,    63,
      70,    79,    88,    94,   102,   112,   125,   132,   141,   147,
     153,   156,   159,   165,   167,   171,   173,   175,   179,   181,
     183,   185,   189,   191,   193,   195,   197,   199,   202,   206,
     210,   212,   216,   220,   224,   226,   230,   234,   238,   240
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      41,     0,    -1,    41,    42,    -1,    42,    -1,    45,    -1,
      44,    -1,    46,    -1,    48,    -1,    47,    -1,    49,    -1,
      50,    -1,    51,    -1,    43,    -1,    22,    25,    28,    29,
      -1,    17,    19,    28,    29,    -1,    17,    20,    28,    29,
      -1,    11,    10,    25,    30,    53,    31,    28,    29,    -1,
      11,    18,    25,    28,    29,    -1,     3,    32,     4,    61,
      28,    29,    -1,     3,    55,     4,    61,    28,    29,    -1,
       3,    32,     4,    61,     5,    60,    28,    29,    -1,     3,
      55,     4,    61,     5,    60,    28,    29,    -1,     9,     4,
      25,    28,    29,    -1,     9,     4,    25,     5,    60,    28,
      29,    -1,    14,    12,    25,    13,    30,    57,    31,    28,
      29,    -1,    14,    12,    25,    30,    55,    31,    13,    30,
      57,    31,    28,    29,    -1,    15,    25,    16,    63,    28,
      29,    -1,    15,    25,    16,    63,     5,    60,    28,    29,
      -1,     8,    10,    25,    28,    29,    -1,     8,    18,    25,
      28,    29,    -1,    21,    28,    -1,    25,    26,    -1,    25,
      27,    30,    23,    31,    -1,    52,    -1,    53,    33,    52,
      -1,    25,    -1,    54,    -1,    55,    33,    54,    -1,    23,
      -1,    24,    -1,    56,    -1,    57,    33,    56,    -1,    34,
      -1,    35,    -1,    36,    -1,    37,    -1,    38,    -1,    39,
      34,    -1,    54,    58,    23,    -1,    54,    58,    24,    -1,
      59,    -1,    30,    60,    31,    -1,    60,     6,    60,    -1,
      60,     7,    60,    -1,    25,    -1,    61,    33,    25,    -1,
      25,    34,    23,    -1,    25,    34,    24,    -1,    62,    -1,
      63,    33,    62,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    63,    63,    63,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    66,    72,    77,    83,    89,    96,   102,
     107,   112,   118,   125,   132,   138,   145,   171,   197,   202,
     208,   214,   220,   227,   230,   235,   242,   245,   250,   256,
     263,   266,   271,   272,   273,   274,   275,   276,   278,   287,
     297,   300,   303,   309,   316,   321,   327,   334,   342,   345
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SELECT", "FROM", "WHERE", "AND", "OR",
  "DROP", "DELETE", "TABLE", "CREATE", "INTO", "VALUES", "INSERT",
  "UPDATE", "SET", "SHOW", "DATABASE", "DATABASES", "TABLES", "EXIT",
  "USE", "NUMBER", "STRING", "ID", "INT", "CHAR", "';'", "'\\n'", "'('",
  "')'", "'*'", "','", "'='", "'>'", "'<'", "\">=\"", "\"<=\"", "'!'",
  "$accept", "statements", "statement", "usesql", "showsql", "createsql",
  "selectsql", "deletesql", "insertsql", "updatesql", "dropsql", "exitsql",
  "create_items", "hyper_items", "item", "item_list", "value",
  "value_list", "comparator", "condition", "conditions", "tables",
  "up_cond", "up_conds", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,    59,    10,
      40,    41,    42,    44,    61,    62,    60,   283,   284,    33
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    41,    42,    42,    42,    42,    42,    42,
      42,    42,    42,    43,    44,    44,    45,    45,    46,    46,
      46,    46,    47,    47,    48,    48,    49,    49,    50,    50,
      51,    52,    52,    53,    53,    54,    55,    55,    56,    56,
      57,    57,    58,    58,    58,    58,    58,    58,    59,    59,
      60,    60,    60,    60,    61,    61,    62,    62,    63,    63
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     4,     4,     8,     5,     6,     6,
       8,     8,     5,     7,     9,    12,     6,     8,     5,     5,
       2,     2,     5,     1,     3,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     2,     3,     3,
       1,     3,     3,     3,     1,     3,     3,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     3,    12,     5,     4,     6,     8,     7,     9,    10,
      11,    35,     0,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    30,     0,     1,     2,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    54,     0,     0,    37,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    58,     0,    14,    15,    13,     0,
       0,     0,     0,     0,    28,    29,     0,     0,    50,     0,
      22,     0,    33,     0,    17,     0,     0,     0,     0,     0,
       0,     0,    18,    55,     0,    19,     0,    42,    43,    44,
      45,    46,     0,     0,     0,     0,     0,    31,     0,     0,
       0,    38,    39,    40,     0,     0,    56,    57,     0,    26,
      59,     0,     0,    51,    47,    48,    49,    52,    53,    23,
       0,     0,    34,     0,     0,     0,     0,    20,    21,     0,
      16,     0,    41,     0,    27,    32,    24,     0,     0,     0,
      25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    82,    83,    77,    24,   113,   114,   103,    78,
      79,    52,    64,    65
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -69
static const yytype_int8 yypact[] =
{
      56,    28,    -7,    38,    36,    39,    23,    -4,    29,    44,
      41,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,    71,   -69,    -2,    47,    73,    74,    75,    76,
      77,    81,    78,    79,   -69,    80,   -69,   -69,    84,    84,
      85,    83,    86,     4,    82,    87,    -3,    88,    89,    90,
      91,   -69,     0,     1,   -69,    92,    93,   -13,    94,    99,
      96,    97,    85,    69,   -69,     2,   -69,   -69,   -69,   -13,
     100,   101,   -13,   102,   -69,   -69,   -13,    45,   -69,    12,
     -69,    63,   -69,    35,   -69,    68,    43,    70,   -13,   103,
      88,    15,   -69,   -69,    17,   -69,     7,   -69,   -69,   -69,
     -69,   -69,   104,    72,   -13,   -13,   105,   -69,    98,   107,
      99,   -69,   -69,   -69,    54,   117,   -69,   -69,    19,   -69,
     -69,   108,   110,   -69,   -69,   -69,   -69,   -69,   111,   -69,
     113,   112,   -69,   114,    68,   115,   118,   -69,   -69,   109,
     -69,   119,   -69,    68,   -69,   -69,   -69,    55,   116,   120,
     -69
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -69,   -69,    95,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,    -6,   -69,    -1,   106,   -18,   -10,   -69,   -69,
     -68,   121,    53,   -69
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      23,    91,    39,    25,    94,    69,    72,    88,    96,    57,
      61,    26,    21,   104,   105,    32,    33,    76,   104,   105,
     118,   104,   105,   104,   105,   104,   105,    62,    70,    73,
      89,    40,    58,    71,    71,    90,   127,   128,   123,    54,
     106,    36,    27,   121,     1,   122,    28,   136,    31,     2,
       3,    30,     4,    21,    29,     5,     6,    34,     7,     1,
      22,    23,     8,     9,     2,     3,   109,     4,   110,    35,
       5,     6,    41,     7,   115,    38,    40,     8,     9,    97,
      98,    99,   100,   101,   102,   133,   148,   134,   134,   107,
     108,   111,   112,   116,   117,   125,   126,    47,    42,    43,
      44,    45,    46,    87,   132,    37,    48,    49,    50,    51,
      21,    55,    59,    63,    56,    60,   142,   104,    66,    67,
      68,    74,    75,    80,    81,    84,    93,    85,   130,    92,
     135,    95,   119,   147,   129,   131,   139,   137,   124,   138,
     145,   140,   141,   120,   149,   143,     0,   144,   146,   150,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      53,     0,     0,     0,     0,     0,     0,     0,    86
};

static const yytype_int16 yycheck[] =
{
       1,    69,     4,    10,    72,     5,     5,     5,    76,     5,
      13,    18,    25,     6,     7,    19,    20,    30,     6,     7,
      88,     6,     7,     6,     7,     6,     7,    30,    28,    28,
      28,    33,    28,    33,    33,    33,   104,   105,    31,    40,
      28,     0,     4,    28,     3,    28,    10,    28,    25,     8,
       9,    12,    11,    25,    18,    14,    15,    28,    17,     3,
      32,    62,    21,    22,     8,     9,    31,    11,    33,    25,
      14,    15,    25,    17,    31,     4,    33,    21,    22,    34,
      35,    36,    37,    38,    39,    31,    31,    33,    33,    26,
      27,    23,    24,    23,    24,    23,    24,    16,    25,    25,
      25,    25,    25,    34,   110,    10,    28,    28,    28,    25,
      25,    28,    30,    25,    28,    28,   134,     6,    29,    29,
      29,    29,    29,    29,    25,    29,    25,    30,    30,    29,
      13,    29,    29,   143,    29,    28,    23,    29,    34,    29,
      31,    29,    28,    90,    28,    30,    -1,    29,    29,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     8,     9,    11,    14,    15,    17,    21,    22,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    25,    32,    54,    55,    10,    18,     4,    10,    18,
      12,    25,    19,    20,    28,    25,     0,    42,     4,     4,
      33,    25,    25,    25,    25,    25,    25,    16,    28,    28,
      28,    25,    61,    61,    54,    28,    28,     5,    28,    30,
      28,    13,    30,    25,    62,    63,    29,    29,    29,     5,
      28,    33,     5,    28,    29,    29,    30,    54,    59,    60,
      29,    25,    52,    53,    29,    30,    55,    34,     5,    28,
      33,    60,    29,    25,    60,    29,    60,    34,    35,    36,
      37,    38,    39,    58,     6,     7,    28,    26,    27,    31,
      33,    23,    24,    56,    57,    31,    23,    24,    60,    29,
      62,    28,    28,    31,    34,    23,    24,    60,    60,    29,
      30,    28,    52,    31,    33,    13,    28,    29,    29,    23,
      29,    28,    56,    30,    29,    31,    29,    57,    31,    28,
      29
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 13:

/* Line 1455 of yacc.c  */
#line 66 "sql.y"
    {
					printf("\n");
					useDB((yyvsp[(2) - (4)].strval));
					printf("\nSQL>");
		        ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 72 "sql.y"
    {
					printf("\n");
		            showDB();
		            printf("\nSQL>");
		        ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 77 "sql.y"
    {
		        	printf("\n");
		            showTable();
		            printf("\nSQL>");
		        ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 83 "sql.y"
    {
					printf("\n");
                	createTable((yyvsp[(3) - (8)].strval), (yyvsp[(5) - (8)].Citemsval));
                	printf("\nSQL>");
				;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 89 "sql.y"
    {
					strcpy(database, (yyvsp[(3) - (5)].strval));
					printf("\n");
					createDB();
					printf("\nSQL>");
				;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 96 "sql.y"
    {
					printf("\n");
					selectWhere(NULL, (yyvsp[(4) - (6)].tbval), NULL);
					printf("\n");
					printf("SQL>");
				;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 102 "sql.y"
    {
					printf("\n");
					selectWhere((yyvsp[(2) - (6)].itemval), (yyvsp[(4) - (6)].tbval), NULL);
					printf("\nSQL>");
				;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 107 "sql.y"
    {
					printf("\n");
					selectWhere(NULL, (yyvsp[(4) - (8)].tbval), (yyvsp[(6) - (8)].conval));
					printf("\nSQL>");
				;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 112 "sql.y"
    { 
					printf("\n");
					selectWhere((yyvsp[(2) - (8)].itemval), (yyvsp[(4) - (8)].tbval), (yyvsp[(6) - (8)].conval));
					printf("\nSQL>");
				;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 118 "sql.y"
    {
					printf("\n");
					deletes((yyvsp[(3) - (5)].strval), NULL);
					printf("\n");
					printf("SQL>");
				;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 125 "sql.y"
    { 
					printf("\n");
					deletes((yyvsp[(3) - (7)].strval), (yyvsp[(5) - (7)].conval));
					printf("\nSQL>");
				;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 132 "sql.y"
    {
					printf("\n");
					multiInsert((yyvsp[(3) - (9)].strval), NULL, (yyvsp[(6) - (9)].valueval));
					printf("\nSQL>");
				;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 138 "sql.y"
    {
					printf("\n");
					multiInsert((yyvsp[(3) - (12)].strval), (yyvsp[(5) - (12)].itemval), (yyvsp[(9) - (12)].valueval));
					printf("\nSQL>");
				;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 145 "sql.y"
    {
					printf("\n");
					struct mydb *dbtemp = dbroot;
					struct table *tabletemp = NULL;
					while(dbtemp != NULL) {
						if(strcmp(dbtemp->name, database) == 0) {
							tabletemp = dbtemp->tbroot;
							while(tabletemp != NULL) {
								if(strcmp(tabletemp->name, (yyvsp[(2) - (6)].strval)) == 0) {
									updates(tabletemp, (yyvsp[(4) - (6)].updateval), NULL);
									printf("\nSQL>");
									return 0;
								}
								tabletemp = tabletemp->next;
							}
							printf("error: Table %s doesn't exist!\n", (yyvsp[(2) - (6)].strval));
							printf("\nSQL>");
							return 0;
						}
						dbtemp = dbtemp->next;
					}
					printf("error: Database %s doesn't exist!\n", database);
					printf("\nSQL>");
					return 0;
				;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 171 "sql.y"
    {
					printf("\n");
					struct mydb *dbtemp = dbroot;
					struct table *tabletemp = NULL;
					while(dbtemp != NULL) {
						if(strcmp(dbtemp->name, database) == 0) {
							tabletemp = dbtemp->tbroot;
							while(tabletemp != NULL) {
								if(strcmp(tabletemp->name, (yyvsp[(2) - (8)].strval)) == 0) {
									updates(tabletemp, (yyvsp[(4) - (8)].updateval), (yyvsp[(6) - (8)].conval));
									printf("\nSQL>");
									return 0;
								}
								tabletemp = tabletemp->next;
							}
							printf("error: Table %s doesn't exist!\n", (yyvsp[(2) - (8)].strval));
							printf("\nSQL>");
							return 0;
						}
						dbtemp = dbtemp->next;
					}
					printf("error: Database %s doesn't exist!\n", database);
					printf("\nSQL>");
					return 0;
				;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 197 "sql.y"
    {
					printf("\n");
					dropTable((yyvsp[(3) - (5)].strval));
					printf("\nSQL>");
				;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 202 "sql.y"
    {
					printf("\n");
					dropDB((yyvsp[(3) - (5)].strval));
					printf("\nSQL>");
				;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 208 "sql.y"
    {
					printf("\n");
		            printf("exit with code 0!\n");
		            exit(0);
		        ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 214 "sql.y"
    {
					(yyval.Citemsval) = (struct hyper_items_def *)malloc(sizeof(struct hyper_items_def));
                    strcpy((yyval.Citemsval)->field, (yyvsp[(1) - (2)].strval));
                    (yyval.Citemsval)->type = 0;	
                    (yyval.Citemsval)->next = NULL;	
				;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 220 "sql.y"
    {
					(yyval.Citemsval) = (struct hyper_items_def *)malloc(sizeof(struct hyper_items_def));
                    strcpy((yyval.Citemsval)->field, (yyvsp[(1) - (5)].strval));
                    (yyval.Citemsval)->type = 1;
                    (yyval.Citemsval)->next = NULL;	
				;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 227 "sql.y"
    {
					(yyval.Citemsval) = (yyvsp[(1) - (1)].Citemsval);
				;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 230 "sql.y"
    {
					(yyval.Citemsval) = (yyvsp[(3) - (3)].Citemsval);
					(yyval.Citemsval)->next = (yyvsp[(1) - (3)].Citemsval);				
				;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 235 "sql.y"
    {
					(yyval.itemval) = (struct item_def *)malloc(sizeof(struct item_def));
					strcpy((yyval.itemval)->field, (yyvsp[(1) - (1)].strval));
					(yyval.itemval)->pos = NULL;
					(yyval.itemval)->next = NULL;
				;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 242 "sql.y"
    {
					(yyval.itemval) = (yyvsp[(1) - (1)].itemval);				
				;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 245 "sql.y"
    {
					(yyval.itemval) = (yyvsp[(3) - (3)].itemval);
					(yyval.itemval)->next = (yyvsp[(1) - (3)].itemval);
				;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 250 "sql.y"
    {
					(yyval.valueval) = ((struct value_def *)malloc(sizeof(struct value_def)));
					(yyval.valueval)->value.intkey = (yyvsp[(1) - (1)].intval);
					(yyval.valueval)->type = 0;
					(yyval.valueval)->next = NULL;
				;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 256 "sql.y"
    {
					(yyval.valueval) = ((struct value_def *)malloc(sizeof(struct value_def)));
					strcpy((yyval.valueval)->value.skey, (yyvsp[(1) - (1)].strval));
					(yyval.valueval)->type = 1;
					(yyval.valueval)->next = NULL;
				;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 263 "sql.y"
    {
					(yyval.valueval) = (yyvsp[(1) - (1)].valueval);
				;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 266 "sql.y"
    {
					(yyval.valueval) = (yyvsp[(3) - (3)].valueval);
					(yyval.valueval)->next = (yyvsp[(1) - (3)].valueval);
				;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 271 "sql.y"
    {(yyval.intval) = 1; ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 272 "sql.y"
    {(yyval.intval) = 2; ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 273 "sql.y"
    {(yyval.intval) = 3; ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 274 "sql.y"
    {(yyval.intval) = 4; ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 275 "sql.y"
    {(yyval.intval) = 5; ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 276 "sql.y"
    {(yyval.intval) = 6; ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 278 "sql.y"
    {
					(yyval.conval) = ((struct conditions_def *)malloc(sizeof(struct conditions_def)));
					(yyval.conval)->type = 0;
					(yyval.conval)->litem = (yyvsp[(1) - (3)].itemval);
					(yyval.conval)->intv = (yyvsp[(3) - (3)].intval);
					(yyval.conval)->cmp_op = (yyvsp[(2) - (3)].intval);
					(yyval.conval)->left = NULL;
					(yyval.conval)->right = NULL;
				;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 287 "sql.y"
    {
					(yyval.conval) = ((struct conditions_def *)malloc(sizeof(struct conditions_def)));
					(yyval.conval)->type = 1;
					(yyval.conval)->litem = (yyvsp[(1) - (3)].itemval);
					strcpy((yyval.conval)->strv, (yyvsp[(3) - (3)].strval));
					(yyval.conval)->cmp_op = (yyvsp[(2) - (3)].intval);
					(yyval.conval)->left = NULL;
					(yyval.conval)->right = NULL;
				;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 297 "sql.y"
    {
					(yyval.conval) = (yyvsp[(1) - (1)].conval);
				;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 300 "sql.y"
    {
					(yyval.conval) = (yyvsp[(2) - (3)].conval);
				;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 303 "sql.y"
    {
					(yyval.conval) = ((struct conditions_def *)malloc(sizeof(struct conditions_def)));
					(yyval.conval)->cmp_op = 7;
					(yyval.conval)->left = (yyvsp[(1) - (3)].conval);
					(yyval.conval)->right = (yyvsp[(3) - (3)].conval);
				;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 309 "sql.y"
    {
					(yyval.conval) = ((struct conditions_def *)malloc(sizeof(struct conditions_def)));
					(yyval.conval)->cmp_op = 8;
					(yyval.conval)->left = (yyvsp[(1) - (3)].conval);
					(yyval.conval)->right = (yyvsp[(3) - (3)].conval);
				;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 316 "sql.y"
    {
					(yyval.tbval) = ((struct table_def *)malloc(sizeof(struct table_def)));
					strcpy((yyval.tbval)->table, (yyvsp[(1) - (1)].strval));
					(yyval.tbval)->next = NULL;
				;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 321 "sql.y"
    {
					(yyval.tbval) = ((struct table_def *)malloc(sizeof(struct table_def)));
					strcpy((yyval.tbval)->table, (yyvsp[(3) - (3)].strval));
					(yyval.tbval)->next = (yyvsp[(1) - (3)].tbval);				
				;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 327 "sql.y"
    {
					(yyval.updateval) = ((struct upcon_def *)malloc(sizeof(struct upcon_def)));
					strcpy((yyval.updateval)->field, (yyvsp[(1) - (3)].strval));
					(yyval.updateval)->type = 0;
					(yyval.updateval)->value.intkey = (yyvsp[(3) - (3)].intval);
					(yyval.updateval)->next = NULL;
				;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 334 "sql.y"
    {
					(yyval.updateval) = ((struct upcon_def *)malloc(sizeof(struct upcon_def)));
					strcpy((yyval.updateval)->field, (yyvsp[(1) - (3)].strval));
					(yyval.updateval)->type = 1;
					strcpy((yyval.updateval)->value.skey, (yyvsp[(3) - (3)].strval));
					(yyval.updateval)->next = NULL;				
				;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 342 "sql.y"
    {
					(yyval.updateval) = (yyvsp[(1) - (1)].updateval);
				;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 345 "sql.y"
    {
					(yyval.updateval) = (yyvsp[(3) - (3)].updateval);
					(yyval.updateval)->next = (yyvsp[(1) - (3)].updateval);
				;}
    break;



/* Line 1455 of yacc.c  */
#line 2050 "sql.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 350 "sql.y"


