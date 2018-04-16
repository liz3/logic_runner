//
// Created by Yann Holme Nielsen on 15.04.18.
//

#ifndef LOGIC_RUNNER_UTILS_H
#define LOGIC_RUNNER_UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

int arr_len_int(int arr[]);
int arr_len_double(double arr[]);
int arr_len_char(char arr[]);
int arr_len_string(char* arr[]);
int arr_len_float(float arr[]);
char* read_f(char *filename);

char** str_split(char* a_str, const char a_delim);
#endif //LOGIC_RUNNER_UTILS_H
