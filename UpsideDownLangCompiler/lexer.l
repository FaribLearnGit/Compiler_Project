%{
#include "ast.h"
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int line_no = 1;
%}

%option noyywrap

DIGIT       [0-9]
LETTER      [A-Za-z_]
IDPAT       {LETTER}({LETTER}|{DIGIT})*
NUMBERPAT   {DIGIT}+(\.{DIGIT}+)?
WS          [ \t\r]+

%%

"#portal"                      { return ID; }
"#mindflayer"                  { return ID; }

"Start_UpsideDown"             { return START_MAIN; }
"eleven"                       { return INT; }
"demogorgon"                   { return FLOAT; }
"hopper"                       { return DOUBLE; }
"hawkinsLong"                  { return LONGINT; }
"dustyChar"                    { return CHAR; }
"truth"                        { return BOOL; }
"voidgate"                     { return VOID; }

"hawkins"                      { return IF; }
"upside"                       { return ELSEIF; }
"downside"                     { return ELSE; }
"portalLoop"                   { return FOR; }
"watch"                        { return WHILE; }
"doFirst"                      { return DO; }
"escape"                       { return BREAK; }
"again"                        { return CONTINUE; }
"chooseGate"                   { return SWITCH; }
"caseHawkins"                  { return CASE; }
"otherwise"                    { return DEFAULT; }
"back"                         { return RETURN; }

"shout"                        { return PRINT; }
"listen"                       { return INPUT; }
"root"                         { return ROOT; }
"flr"                          { return FLOOR_FN; }
"ceil"                         { return CEIL_FN; }
"abs"                          { return ABS_FN; }
"logarithm"                    { return LOG_FN; }
"sine"                         { return SIN_FN; }
"cosine"                       { return COS_FN; }
"tan"                          { return TAN_FN; }
"asine"                        { return ASIN_FN; }
"acosine"                      { return ACOS_FN; }
"atan"                         { return ATAN_FN; }
"primey"                       { return PRIME_FN; }

":="                           { return ASSIGN; }
":->"                          { return RETTYPE; }
"."                            { return ENDSTMT; }
":"                            { return COLON; }
","                            { return COMMA; }
"fob"                          { return LPAR; }
"fcb"                          { return RPAR; }
"{"                            { return LBRACE; }
"}"                            { return RBRACE; }

"add"                          { return ADD; }
"minus"                        { return SUB; }
"mul"                          { return MUL; }
"divide"                       { return DIV; }
"mod"                          { return MOD; }
"AND"                          { return AND; }
"OR"                           { return OR; }
"NOT"                          { return NOT; }
"XOR"                          { return XOR; }
"**"                           { return POWER; }
"<="                           { return LE; }
">="                           { return GE; }
"=="                           { return EQ; }
"!="                           { return NE; }
"<"                            { return LT; }
">"                            { return GT; }

"//upside".*                   { /* ignore single-line comment */ }
"/*nether"([^*]|\*+[^*/])*"end*/"  { /* ignore multi-line comment */ }

\"([^\\\n]|(\\.))*\"           {
                                  int len = strlen(yytext);
                                  char *tmp = (char *)malloc(len - 1);
                                  strncpy(tmp, yytext + 1, len - 2);
                                  tmp[len - 2] = '\0';
                                  yylval.sval = tmp;
                                  return STRING;
                               }

\'([^\\\n]|(\\.))\'            {
                                  yylval.sval = strdup(yytext);
                                  return CHAR_LITERAL;
                               }

{NUMBERPAT}                    {
                                  yylval.dval = atof(yytext);
                                  return NUMBER;
                               }

{IDPAT}                        {
                                  yylval.sval = strdup(yytext);
                                  return ID;
                               }

\n                             { line_no++; }
{WS}                           { /* ignore whitespace */ }

.                              {
                                  fprintf(stderr, "Unknown token '%s' at line %d\n", yytext, line_no);
                               }

%%