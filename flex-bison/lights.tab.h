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

#ifndef YY_YY_LIGHTS_TAB_H_INCLUDED
# define YY_YY_LIGHTS_TAB_H_INCLUDED
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
    INT = 258,                     /* INT  */
    ID = 259,                      /* ID  */
    COLOR_HEX = 260,               /* COLOR_HEX  */
    TIME_LIT = 261,                /* TIME_LIT  */
    T_STRIP = 262,                 /* T_STRIP  */
    T_IF = 263,                    /* T_IF  */
    T_ELSE = 264,                  /* T_ELSE  */
    T_WHILE = 265,                 /* T_WHILE  */
    T_FOR = 266,                   /* T_FOR  */
    T_LOOP = 267,                  /* T_LOOP  */
    T_FOREVER = 268,               /* T_FOREVER  */
    T_SET = 269,                   /* T_SET  */
    T_COLOR = 270,                 /* T_COLOR  */
    T_WAIT = 271,                  /* T_WAIT  */
    T_ROTATE = 272,                /* T_ROTATE  */
    T_DIR = 273,                   /* T_DIR  */
    T_FADE = 274,                  /* T_FADE  */
    T_HSV = 275,                   /* T_HSV  */
    T_LEFT = 276,                  /* T_LEFT  */
    T_RIGHT = 277,                 /* T_RIGHT  */
    EQ = 278,                      /* EQ  */
    NEQ = 279,                     /* NEQ  */
    LE = 280,                      /* LE  */
    GE = 281,                      /* GE  */
    AND = 282,                     /* AND  */
    OR = 283,                      /* OR  */
    DOTDOT = 284,                  /* DOTDOT  */
    NEWLINE = 285,                 /* NEWLINE  */
    UMINUS = 286                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "lights.y"

  int   ival;   /* números inteiros               */
  char *sval;   /* identificadores, literais etc. */

#line 100 "lights.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_LIGHTS_TAB_H_INCLUDED  */
