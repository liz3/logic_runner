//
// Created by Yann Holme Nielsen on 15.04.18.
//

#include <memory.h>
#include "command-extractor.h"

int read_cmd(char *line) {

    if (strcmp(line, "df") == 0) {
        return 1;
    }
    if (strcmp(line, "ast") == 0) {
        return 2;
    }
    if (strcmp(line, "pr") == 0) {
        return 3;
    }
    if (strcmp(line, "gt") == 0) {
        return 4;
    }
    if (strcmp(line, "slp") == 0) {
        return 5;
    }
    if (strcmp(line, "endl") == 0) {
        return 6;
    }
    if (strcmp(line, "op") == 0) {
        return 7;
    }

    return -1;
}
int read_op(char *line) {

    if (strcmp(line, "+") == 0) {
        return 1;
    }
    if (strcmp(line, "-") == 0) {
        return 2;
    }
    if (strcmp(line, "/") == 0) {
        return 3;
    }
    if (strcmp(line, "*") == 0) {
        return 4;
    }

    return -1;
}