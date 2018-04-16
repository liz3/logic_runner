#include <stdio.h>

#include "parser/parser.h"

int main(int argv, char** argc) {
    if(argv <= 1) {
        printf("Not enough arguments\n");
        return -1;
    }
    main_parse(argc[1]);
    return 0;
}