//
// Created by Yann Holme Nielsen on 13.11.18.
//

#include "validator.h"

int validate_define(char type, char* name, char* value) {
    return 0;
}
int validate_action(char* input) {

    char* actions[7] =  {"pr", "df", "ast", "gt", "ret", "op", "pu"};
    for (int i = 0; i < 7; ++i) {
        if(strcmp(actions[i], input) == 0) return 0;
    }
    return 1;
}
int validate_operation(char operator, struct Entry target, struct Entry op_1, struct Entry op_2, int line){
    char valid_operators[4] =  {'+', '-', '/', '*'};
    int found = 0;
    for (int i = 0; i < 4; ++i) {
        if(operator == valid_operators[i]) {
            found = 1;
            break;
        }
    }
    if(found == 0) {
        printf("\n\nERROR: Operator %c is not recognized at line %d", operator, line);
        return 1;
    }
    if (target.name == NULL) {
        printf("\n\nERROR: operation target from operation cant be found at %d", line);
        return 1;
    }
    if (op_1.name == NULL) {
        printf("\n\nERROR: operator 1 from operation cant be found at %d", line);
        return 1;
    }
    if (op_1.name == NULL) {
        printf("\n\nERROR: operator 2 from operation cant be found at %d", line);
        return 1;
    }
    if(target.type != op_1.type || target.type != op_2.type || op_1.type != op_2.type) {
        printf("\n\nERROR: operators have different types at %d", line);
        return 1;
    }
    return 0;
}
int validate_assert(struct Entry op_1, struct Entry op_2, int line){


    if (op_1.name == NULL) {
        printf("\n\nERROR: operator 1 from assert cant be found at %d", line);
        return 1;
    }
    if (op_1.name == NULL) {
        printf("\n\nERROR: operator 2 from assert cant be found at %d", line);
        return 1;
    }
    if(op_1.type != op_2.type) {
        printf("\n\nERROR: operators have different types at %d", line);
        return 1;
    }
    return 0;
}
