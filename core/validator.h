//
// Created by Yann Holme Nielsen on 13.11.18.
//

#ifndef LOGIC_RUN_2_VALIDATOR_H
#define LOGIC_RUN_2_VALIDATOR_H

#include "../utils/utils.h"

int validate_action(char* input);
int validate_define(char type, char* name, char* value);
int validate_operation(char operator, struct Entry target, struct Entry op_1, struct Entry op_2, int line);
int validate_assert(struct Entry op_1, struct Entry op_2, int line);
#endif //LOGIC_RUN_2_VALIDATOR_H
