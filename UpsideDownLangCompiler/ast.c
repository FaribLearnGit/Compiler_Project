#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static ASTNode *alloc_node(NodeType type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    memset(node, 0, sizeof(ASTNode));
    node->type = type;
    node->next = NULL;
    return node;
}

ASTNode *append_node(ASTNode *list, ASTNode *node) {
    if (!node) return list;
    if (!list) return node;

    ASTNode *cur = list;
    while (cur->next) cur = cur->next;
    cur->next = node;
    return list;
}

ASTNode *new_program(ASTNode *globals, ASTNode *main_block) {
    ASTNode *node = alloc_node(NODE_PROGRAM);
    node->program.globals = globals;
    node->program.main_block = main_block;
    return node;
}

ASTNode *new_block(ASTNode *statements) {
    ASTNode *node = alloc_node(NODE_BLOCK);
    node->block.statements = statements;
    return node;
}

ASTNode *new_decl(char *name, ASTNode *value) {
    ASTNode *node = alloc_node(NODE_DECL);
    node->decl.name = strdup(name);
    node->decl.value = value;
    return node;
}

ASTNode *new_assign(char *name, ASTNode *value) {
    ASTNode *node = alloc_node(NODE_ASSIGN);
    node->assign.name = strdup(name);
    node->assign.value = value;
    return node;
}

ASTNode *new_print(ASTNode *expr) {
    ASTNode *node = alloc_node(NODE_PRINT);
    node->print_stmt.expr = expr;
    return node;
}

ASTNode *new_if(ASTNode *condition, ASTNode *then_block, ASTNode *else_block) {
    ASTNode *node = alloc_node(NODE_IF);
    node->if_stmt.condition = condition;
    node->if_stmt.then_block = then_block;
    node->if_stmt.else_block = else_block;
    return node;
}

ASTNode *new_while(ASTNode *condition, ASTNode *body) {
    ASTNode *node = alloc_node(NODE_WHILE);
    node->while_stmt.condition = condition;
    node->while_stmt.body = body;
    return node;
}

ASTNode *new_for(ASTNode *init, ASTNode *condition, ASTNode *update, ASTNode *body) {
    ASTNode *node = alloc_node(NODE_FOR);
    node->for_stmt.init = init;
    node->for_stmt.condition = condition;
    node->for_stmt.update = update;
    node->for_stmt.body = body;
    return node;
}

ASTNode *new_return(ASTNode *expr) {
    ASTNode *node = alloc_node(NODE_RETURN);
    node->return_stmt.expr = expr;
    return node;
}

ASTNode *new_num(double value) {
    ASTNode *node = alloc_node(NODE_NUM);
    node->num.value = value;
    return node;
}

ASTNode *new_str(char *value) {
    ASTNode *node = alloc_node(NODE_STR);
    node->str.value = strdup(value);
    return node;
}

ASTNode *new_id(char *name) {
    ASTNode *node = alloc_node(NODE_ID);
    node->id.name = strdup(name);
    return node;
}

ASTNode *new_binop(OpType op, ASTNode *left, ASTNode *right) {
    ASTNode *node = alloc_node(NODE_BINOP);
    node->binop.op = op;
    node->binop.left = left;
    node->binop.right = right;
    return node;
}

ASTNode *new_unop(OpType op, ASTNode *expr) {
    ASTNode *node = alloc_node(NODE_UNOP);
    node->unop.op = op;
    node->unop.expr = expr;
    return node;
}