//
// Created by Yann Holme Nielsen on 14.04.18.
//

#ifndef LOGIC_RUNNER_PARSER_H
#define LOGIC_RUNNER_PARSER_H

#include "../utils.h"
#include "command-extractor.h"

int contains_str(char* keys[], int length, char* search);
int get_index(char* keys[],int length, char* search);
int main_parse(char* content);

#endif //LOGIC_RUNNER_PARSER_H
