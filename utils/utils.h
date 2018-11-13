//
// Created by Yann Holme Nielsen on 13.11.18.
//

#ifndef LOGIC_RUN_2_UTILS_H
#define LOGIC_RUN_2_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

struct Entry {

    char type;
    char *name;

    int int_val;
    double double_val;
    float float_val;
    char char_val;


};

char* read_f(char *filename);
char** str_split(char* a_str, char a_delim);
char** str_split_debug(char* a_str, char a_delim, int curr_line);
char* str_append(char*a, char* b);
char *substr(char *raw, int pos);
#endif //LOGIC_RUN_2_UTILS_H
