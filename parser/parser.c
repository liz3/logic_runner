//
// Created by Yann Holme Nielsen on 14.04.18.
//

#include "parser.h"

int contains_str(char *keys[], char *search) {
    if (*keys == NULL) return 0;
    for (int i = 0; i < arr_len_string(keys); ++i) {
        if (strcmp(keys[i], search) == 0) return 1;
    }

    return 0;
}

int get_index(char *keys[], char *search) {
    if (*keys == NULL) return -1;
    for (int i = 0; i < arr_len_string(keys); ++i) {
        if (strcmp(keys[i], search) == 0) return i;
    }

    return -1;
}

int main_parse(char *path) {

    int int_am = 0;
    int double_am = 0;
    int float_am = 0;
    int strings_am = 0;
    int char_am = 0;

    char *content = read_f(path);

    char **split;
    split = str_split(content, '\n');
    int i;
    for (i = 0; *(split + i); i++) {
        char **parts;
        parts = str_split(*(split + i), ' ');
        if (read_cmd(parts[0]) == 1) {
            char *type = parts[1];
            if (strcmp(type, "i") == 0) int_am++;
            if (strcmp(type, "d") == 0) double_am++;
            if (strcmp(type, "f") == 0) float_am++;
            if (strcmp(type, "s") == 0) strings_am++;
            if (strcmp(type, "c") == 0) char_am++;
        }
    }
    free(split);
    //int
    const char *int_keys[int_am];
    int int_values[int_am];

    //double
    char *double_keys[double_am];
    double double_values[double_am];

    //float
    char *float_keys[float_am];
    float float_values[float_am];

    //strings
    char *string_keys[strings_am];
    char **string_values[strings_am];

    //char
    char *char_keys[char_am];
    char char_values[char_am];

    int int_add = -1;
    int double_add = 0;
    int float_add = 0;
    int str_add = 0;
    int c_add = 0;

    char **lines;
    lines = str_split(read_f(path), '\n');
    int walk_i;
    for (walk_i = 0; *(lines + walk_i); walk_i++) {
        char **parts;
        parts = str_split(*(lines + walk_i), ' ');


        if (strcmp(parts[0], "return") == 0) return 0;
        int cmd_type = read_cmd(parts[0]);
        if (cmd_type == 1) {
            char *type = parts[1];
            char *key = parts[2];
            if (contains_str(int_keys, key) == 1 ||
                contains_str(double_keys, key) == 1 ||
                contains_str(float_keys, key) == 1 ||
                contains_str(char_keys, key) == 1) {
                printf("Already containing %s\n", key);
                continue;
            }
            if (strcmp(type, "i") == 0) {
                int_add += 1;
                int_keys[int_add] = key;
                int_values[int_add] = atoi(parts[3]);
                printf("registered a new int %s = ", key);
                printf("%d\n", atoi(parts[3]));
                printf("Array Length is %d\n", arr_len_string(int_keys));
                printf("Array is [");
                for (int j = 0; j < arr_len_string(int_keys); ++j) {
                    printf(" %s ", int_keys[j]);
                }
                printf("]\n");
                continue;
            }

            if (strcmp(type, "d") == 0) {
                double_keys[double_add] = key;
                double_values[double_add] = strtod(parts[3], NULL);
                double_add++;
                printf("registered a new double %s = ", key);
                printf("%lf", strtod(parts[3], NULL));
                printf("\n");
                continue;
            }
            if (strcmp(type, "f") == 0) {
                float_keys[float_add] = key;
                float_values[float_add] = (float) atof(parts[3]);
                float_add++;
                printf("registered a new float %s = ", key);
                printf("%lf", atof(parts[3]));
                printf("\n");
                continue;
            }
            if (strcmp(type, "s") == 0) {
                //TODO Later
                continue;
            }
            if (strcmp(type, "c") == 0) {
                char_keys[char_am] = key;
                char_values[char_am] = (char) parts[3];
                c_add++;
                printf("registered a new char %s = ", key);
                printf("%c", parts[3][0]);
                printf("\n");
                continue;
            }
        } else if (cmd_type == 2) {
            char *first_var = parts[1];
            char *second_var = parts[2];
            char *false_op = parts[3];
            if (contains_str(int_keys, first_var) == 1) {

                int first_value = int_values[get_index(int_keys, first_var)];
                if (contains_str(int_keys, second_var) != 1) {
                    printf("not containing!\n");
                    continue;
                }
                int second_value = int_values[get_index(int_keys, second_var)];

                printf("They are %d", first_value);
                printf(" and %d\n", second_value);
            } else if (contains_str(double_keys, first_var) == 1) {


            } else if (contains_str(float_keys, first_var) == 1) {

            } else if (contains_str(char_keys, first_var) == 1) {

            } else {
                printf("ERROR Var %s not registered\n", first_var);
            }
        }

    }

    int int_test = contains_str(int_keys, "y");

    printf("\nContains result = %d", int_test);

    return 0;
}