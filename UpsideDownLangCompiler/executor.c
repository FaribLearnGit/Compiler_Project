#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "executor.h"

typedef enum {
    VAL_NUM,
    VAL_STR
} ValueType;

typedef struct {
    ValueType type;
    double num;
    char *str;
} Value;

typedef struct {
    char name[64];
    Value value;
} Symbol;

static Symbol symtab[200];
static int symcount = 0;
static FILE *out = NULL;

static Value make_num(double x) {
    Value v;
    v.type = VAL_NUM;
    v.num = x;
    v.str = NULL;
    return v;
}

static Value make_str(char *s) {
    Value v;
    v.type = VAL_STR;
    v.num = 0;
    v.str = s;
    return v;
}

static int find_symbol(const char *name) {
    for (int i = 0; i < symcount; i++) {
        if (strcmp(symtab[i].name, name) == 0) return i;
    }
    return -1;
}

static void set_symbol(const char *name, Value v) {
    int idx = find_symbol(name);
    if (idx >= 0) {
        symtab[idx].value = v;
        return;
    }
    strcpy(symtab[symcount].name, name);
    symtab[symcount].value = v;
    symcount++;
}

static Value get_symbol(const char *name) {
    int idx = find_symbol(name);
    if (idx >= 0) return symtab[idx].value;
    return make_num(0);
}

static int is_true(Value v) {
    if (v.type == VAL_STR) return v.str && v.str[0] != '\0';
    return v.num != 0;
}

static Value eval(ASTNode *node);
static void exec_stmt(ASTNode *node);

static void exec_list(ASTNode *node) {
    while (node) {
        exec_stmt(node);
        node = node->next;
    }
}

static Value eval(ASTNode *node) {
    if (!node) return make_num(0);

    switch (node->type) {
        case NODE_NUM:
            return make_num(node->num.value);

        case NODE_STR:
            return make_str(node->str.value);

        case NODE_ID:
            return get_symbol(node->id.name);

        case NODE_UNOP: {
            Value v = eval(node->unop.expr);
            if (node->unop.op == OP_NOT) return make_num(!is_true(v));
            return make_num(0);
        }

        case NODE_BINOP: {
            Value a = eval(node->binop.left);
            Value b = eval(node->binop.right);
            double x = a.num;
            double y = b.num;

            switch (node->binop.op) {
                case OP_ADD: return make_num(x + y);
                case OP_SUB: return make_num(x - y);
                case OP_MUL: return make_num(x * y);
                case OP_DIV: return make_num(y != 0 ? x / y : 0);
                case OP_MOD: return make_num((int)x % (int)y);
                case OP_LT:  return make_num(x < y);
                case OP_GT:  return make_num(x > y);
                case OP_LE:  return make_num(x <= y);
                case OP_GE:  return make_num(x >= y);
                case OP_EQ:  return make_num(x == y);
                case OP_NE:  return make_num(x != y);
                case OP_AND: return make_num(is_true(a) && is_true(b));
                case OP_OR:  return make_num(is_true(a) || is_true(b));
                default:     return make_num(0);
            }
        }

        default:
            return make_num(0);
    }
}

static void exec_stmt(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_BLOCK:
            exec_list(node->block.statements);
            break;

        case NODE_DECL: {
            Value v = node->decl.value ? eval(node->decl.value) : make_num(0);
            set_symbol(node->decl.name, v);
            break;
        }

        case NODE_ASSIGN: {
            Value v = eval(node->assign.value);
            set_symbol(node->assign.name, v);
            break;
        }

        case NODE_PRINT: {
            Value v = eval(node->print_stmt.expr);
            if (v.type == VAL_STR) {
                fprintf(out, "%s\n", v.str);
            } else {
                fprintf(out, "%g\n", v.num);
            }
            break;
        }

        case NODE_IF: {
            Value cond = eval(node->if_stmt.condition);
            if (is_true(cond)) {
                exec_stmt(node->if_stmt.then_block);
            } else if (node->if_stmt.else_block) {
                exec_stmt(node->if_stmt.else_block);
            }
            break;
        }

        case NODE_WHILE:
            while (is_true(eval(node->while_stmt.condition))) {
                exec_stmt(node->while_stmt.body);
            }
            break;

        case NODE_FOR:
            exec_stmt(node->for_stmt.init);
            while (is_true(eval(node->for_stmt.condition))) {
                exec_stmt(node->for_stmt.body);
                exec_stmt(node->for_stmt.update);
            }
            break;

        case NODE_RETURN:
            /* minimal version: ignore actual function return flow */
            break;

        default:
            break;
    }
}

void execute_program(ASTNode *root, FILE *output_file) {
    out = output_file;
    if (!root || root->type != NODE_PROGRAM) return;

    exec_list(root->program.globals);
    exec_stmt(root->program.main_block);
}