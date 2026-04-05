%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "executor.h"

extern FILE *yyin;
int yylex(void);
void yyerror(const char *s);

ASTNode *root = NULL;
FILE *output_file;
%}

%union {
    char *sval;
    double dval;
    ASTNode *node;
}

%token START_MAIN
%token INT FLOAT DOUBLE LONGINT CHAR BOOL VOID
%token IF ELSEIF ELSE FOR WHILE DO BREAK CONTINUE RETURN
%token SWITCH CASE DEFAULT
%token PRINT INPUT
%token POWER ROOT FLOOR_FN CEIL_FN ABS_FN LOG_FN SIN_FN COS_FN TAN_FN ASIN_FN ACOS_FN ATAN_FN PRIME_FN

%token ASSIGN ENDSTMT RETTYPE
%token ADD SUB MUL DIV MOD
%token AND OR NOT XOR
%token LT GT LE GE EQ NE
%token LPAR RPAR LBRACE RBRACE COLON COMMA

%token <sval> ID STRING CHAR_LITERAL
%token <dval> NUMBER

%type <node> program global_list global_decl main_function function_decl
%type <node> statement_list statement block declaration assignment print_stmt
%type <node> input_stmt return_stmt if_stmt while_stmt for_stmt do_while_stmt
%type <node> expression elseif_chain
%type <node> parameter_list_opt parameter_list parameter
%type <node> type_spec

%left OR
%left AND
%left EQ NE
%left LT GT LE GE
%left ADD SUB
%left MUL DIV MOD
%right NOT

%%

program
    : global_list main_function
      {
          root = new_program($1, $2);
      }
    ;

global_list
    : /* empty */
      {
          $$ = NULL;
      }
    | global_list global_decl
      {
          $$ = append_node($1, $2);
      }
    ;

global_decl
    : declaration ENDSTMT
      {
          $$ = $1;
      }
    ;

main_function
    : START_MAIN LPAR RPAR block
      {
          $$ = $4;
      }
    ;

function_decl
    : ID LPAR parameter_list_opt RPAR RETTYPE type_spec block
      {
          $$ = NULL;
      }
    ;

parameter_list_opt
    : /* empty */
      {
          $$ = NULL;
      }
    | parameter_list
      {
          $$ = $1;
      }
    ;

parameter_list
    : parameter
      {
          $$ = $1;
      }
    | parameter_list COMMA parameter
      {
          $$ = append_node($1, $3);
      }
    ;

parameter
    : type_spec ID
      {
          $$ = NULL;
          free($2);
      }
    ;

type_spec
    : INT      { $$ = NULL; }
    | FLOAT    { $$ = NULL; }
    | DOUBLE   { $$ = NULL; }
    | LONGINT  { $$ = NULL; }
    | CHAR     { $$ = NULL; }
    | BOOL     { $$ = NULL; }
    | VOID     { $$ = NULL; }
    ;

statement_list
    : /* empty */
      {
          $$ = NULL;
      }
    | statement_list statement
      {
          $$ = append_node($1, $2);
      }
    ;

statement
    : declaration ENDSTMT
      {
          $$ = $1;
      }
    | assignment ENDSTMT
      {
          $$ = $1;
      }
    | print_stmt ENDSTMT
      {
          $$ = $1;
      }
    | input_stmt ENDSTMT
      {
          $$ = $1;
      }
    | return_stmt ENDSTMT
      {
          $$ = $1;
      }
    | BREAK ENDSTMT
      {
          $$ = NULL;
      }
    | CONTINUE ENDSTMT
      {
          $$ = NULL;
      }
    | if_stmt
      {
          $$ = $1;
      }
    | while_stmt
      {
          $$ = $1;
      }
    | for_stmt
      {
          $$ = $1;
      }
    | do_while_stmt
      {
          $$ = $1;
      }
    | block
      {
          $$ = $1;
      }
    ;

block
    : LBRACE statement_list RBRACE
      {
          $$ = new_block($2);
      }
    ;

declaration
    : type_spec ID
      {
          $$ = new_decl($2, NULL);
      }
    | type_spec ID ASSIGN expression
      {
          $$ = new_decl($2, $4);
      }
    ;

assignment
    : ID ASSIGN expression
      {
          $$ = new_assign($1, $3);
      }
    ;

print_stmt
    : PRINT LPAR STRING RPAR
      {
          $$ = new_print(new_str($3));
      }
    | PRINT LPAR expression RPAR
      {
          $$ = new_print($3);
      }
    ;

input_stmt
    : INPUT LPAR ID RPAR
      {
          $$ = NULL;
          free($3);
      }
    ;

return_stmt
    : RETURN expression
      {
          $$ = new_return($2);
      }
    ;

if_stmt
    : IF LPAR expression RPAR block
      {
          $$ = new_if($3, $5, NULL);
      }
    | IF LPAR expression RPAR block ELSE block
      {
          $$ = new_if($3, $5, $7);
      }
    ;

elseif_chain
    : ELSEIF LPAR expression RPAR block
      {
          $$ = new_if($3, $5, NULL);
      }
    | elseif_chain ELSEIF LPAR expression RPAR block
      {
          $$ = $1;
      }
    ;

while_stmt
    : WHILE LPAR expression RPAR block
      {
          $$ = new_while($3, $5);
      }
    ;

for_stmt
    : FOR LPAR assignment COLON expression COLON assignment RPAR block
      {
          $$ = new_for($3, $5, $7, $9);
      }
    ;

do_while_stmt
    : DO block WHILE LPAR expression RPAR
      {
          $$ = new_while($5, $2);
      }
    ;

expression
    : NUMBER
      {
          $$ = new_num($1);
      }
    | ID
      {
          $$ = new_id($1);
      }
    | STRING
      {
          $$ = new_str($1);
      }
    | CHAR_LITERAL
      {
          $$ = new_str($1);
      }
    | LPAR expression RPAR
      {
          $$ = $2;
      }
    | expression ADD expression
      {
          $$ = new_binop(OP_ADD, $1, $3);
      }
    | expression SUB expression
      {
          $$ = new_binop(OP_SUB, $1, $3);
      }
    | expression MUL expression
      {
          $$ = new_binop(OP_MUL, $1, $3);
      }
    | expression DIV expression
      {
          $$ = new_binop(OP_DIV, $1, $3);
      }
    | expression MOD expression
      {
          $$ = new_binop(OP_MOD, $1, $3);
      }
    | expression LT expression
      {
          $$ = new_binop(OP_LT, $1, $3);
      }
    | expression GT expression
      {
          $$ = new_binop(OP_GT, $1, $3);
      }
    | expression LE expression
      {
          $$ = new_binop(OP_LE, $1, $3);
      }
    | expression GE expression
      {
          $$ = new_binop(OP_GE, $1, $3);
      }
    | expression EQ expression
      {
          $$ = new_binop(OP_EQ, $1, $3);
      }
    | expression NE expression
      {
          $$ = new_binop(OP_NE, $1, $3);
      }
    | expression AND expression
      {
          $$ = new_binop(OP_AND, $1, $3);
      }
    | expression OR expression
      {
          $$ = new_binop(OP_OR, $1, $3);
      }
    | NOT expression
      {
          $$ = new_unop(OP_NOT, $2);
      }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: compiler.exe <inputfile>\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        printf("Could not open input file: %s\n", argv[1]);
        return 1;
    }

    output_file = fopen("output.txt", "w");
    if (!output_file) {
        printf("Could not open output.txt\n");
        fclose(yyin);
        return 1;
    }

    if (yyparse() == 0) {
        execute_program(root, output_file);
    }

    fclose(yyin);
    fclose(output_file);
    return 0;
}