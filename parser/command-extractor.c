//
// Created by Yann Holme Nielsen on 15.04.18.
//

#include <memory.h>
#include "command-extractor.h"

int read_cmd(char *line) {

    if (strcmp(line, "def") == 0) {
        return 1;
    }
    if (strcmp(line, "assert") == 0) {
        return 2;
    }
    if (strcmp(line, "print") == 0) {
        return 3;
    }
    if (strcmp(line, "goto") == 0) {
        return 4;
    }

    return -1;
}