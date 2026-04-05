#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <stdio.h>
#include "ast.h"

void execute_program(ASTNode *root, FILE *output_file);

#endif