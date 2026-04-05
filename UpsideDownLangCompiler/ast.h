#ifndef AST_H
#define AST_H

typedef enum {
    NODE_PROGRAM,
    NODE_BLOCK,
    NODE_DECL,
    NODE_ASSIGN,
    NODE_PRINT,
    NODE_IF,
    NODE_WHILE,
    NODE_FOR,
    NODE_RETURN,

    NODE_NUM,
    NODE_STR,
    NODE_ID,
    NODE_BINOP,
    NODE_UNOP
} NodeType;

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_LT,
    OP_GT,
    OP_LE,
    OP_GE,
    OP_EQ,
    OP_NE,
    OP_AND,
    OP_OR,
    OP_NOT
} OpType;

typedef struct ASTNode ASTNode;

struct ASTNode {
    NodeType type;
    ASTNode *next;

    union {
        struct {
            ASTNode *globals;
            ASTNode *main_block;
        } program;

        struct {
            ASTNode *statements;
        } block;

        struct {
            char *name;
            ASTNode *value;
        } decl;

        struct {
            char *name;
            ASTNode *value;
        } assign;

        struct {
            ASTNode *expr;
        } print_stmt;

        struct {
            ASTNode *condition;
            ASTNode *then_block;
            ASTNode *else_block;
        } if_stmt;

        struct {
            ASTNode *condition;
            ASTNode *body;
        } while_stmt;

        struct {
            ASTNode *init;
            ASTNode *condition;
            ASTNode *update;
            ASTNode *body;
        } for_stmt;

        struct {
            ASTNode *expr;
        } return_stmt;

        struct {
            double value;
        } num;

        struct {
            char *value;
        } str;

        struct {
            char *name;
        } id;

        struct {
            OpType op;
            ASTNode *left;
            ASTNode *right;
        } binop;

        struct {
            OpType op;
            ASTNode *expr;
        } unop;
    };
};

ASTNode *new_program(ASTNode *globals, ASTNode *main_block);
ASTNode *new_block(ASTNode *statements);
ASTNode *new_decl(char *name, ASTNode *value);
ASTNode *new_assign(char *name, ASTNode *value);
ASTNode *new_print(ASTNode *expr);
ASTNode *new_if(ASTNode *condition, ASTNode *then_block, ASTNode *else_block);
ASTNode *new_while(ASTNode *condition, ASTNode *body);
ASTNode *new_for(ASTNode *init, ASTNode *condition, ASTNode *update, ASTNode *body);
ASTNode *new_return(ASTNode *expr);

ASTNode *new_num(double value);
ASTNode *new_str(char *value);
ASTNode *new_id(char *name);
ASTNode *new_binop(OpType op, ASTNode *left, ASTNode *right);
ASTNode *new_unop(OpType op, ASTNode *expr);

ASTNode *append_node(ASTNode *list, ASTNode *node);

#endif