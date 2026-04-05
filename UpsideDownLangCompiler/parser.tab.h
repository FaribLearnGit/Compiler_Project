
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     START_MAIN = 258,
     INT = 259,
     FLOAT = 260,
     DOUBLE = 261,
     LONGINT = 262,
     CHAR = 263,
     BOOL = 264,
     VOID = 265,
     IF = 266,
     ELSEIF = 267,
     ELSE = 268,
     FOR = 269,
     WHILE = 270,
     DO = 271,
     BREAK = 272,
     CONTINUE = 273,
     RETURN = 274,
     SWITCH = 275,
     CASE = 276,
     DEFAULT = 277,
     PRINT = 278,
     INPUT = 279,
     POWER = 280,
     ROOT = 281,
     FLOOR_FN = 282,
     CEIL_FN = 283,
     ABS_FN = 284,
     LOG_FN = 285,
     SIN_FN = 286,
     COS_FN = 287,
     TAN_FN = 288,
     ASIN_FN = 289,
     ACOS_FN = 290,
     ATAN_FN = 291,
     PRIME_FN = 292,
     ASSIGN = 293,
     ENDSTMT = 294,
     RETTYPE = 295,
     ADD = 296,
     SUB = 297,
     MUL = 298,
     DIV = 299,
     MOD = 300,
     AND = 301,
     OR = 302,
     NOT = 303,
     XOR = 304,
     LT = 305,
     GT = 306,
     LE = 307,
     GE = 308,
     EQ = 309,
     NE = 310,
     LPAR = 311,
     RPAR = 312,
     LBRACE = 313,
     RBRACE = 314,
     COLON = 315,
     COMMA = 316,
     ID = 317,
     STRING = 318,
     CHAR_LITERAL = 319,
     NUMBER = 320
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 16 "parser.y"

    char *sval;
    double dval;
    ASTNode *node;



/* Line 1676 of yacc.c  */
#line 125 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


