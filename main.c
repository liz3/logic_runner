#include <stdio.h>
#include "core/parser.h"
int main(int argc, char* argv[]) {

    if(argc < 2) {
        printf("Please provide a file to run!\n");
        return 0;
    }
    parse(argv[1]);
    return 0;
}