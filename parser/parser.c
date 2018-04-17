//
// Created by Yann Holme Nielsen on 14.04.18.
//

#include "parser.h"

int contains_str(char *keys[], int length, char *search) {
    if (*keys == NULL) return 0;
    for (int i = 0; i < length; ++i) {
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

    int int_add = -1;
    int double_add = -1;
    int float_add = -1;
    int c_add = -1;

    //int
    char **int_keys = malloc(sizeof(char *) * int_am);
    int *int_values = malloc(sizeof(int) * int_am);

    //double
    char **double_keys = malloc(sizeof(char *) * double_am);
    double *double_values = malloc(sizeof(double) * double_am);

    //float
    char **float_keys = malloc(sizeof(char *) * float_am);
    float *float_values = malloc(sizeof(float) * float_am);

    //char
    char **char_keys = malloc(sizeof(char *) * char_am);
    char *char_values = malloc(sizeof(char) * char_am);

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
            if (contains_str(int_keys, int_add + 1, key) == 1 ||
                contains_str(double_keys, double_add + 1, key) == 1 ||
                contains_str(float_keys, float_add + 1, key) == 1 ||
                contains_str(char_keys, c_add + 1, key) == 1) {
                printf("Already containing %s\n", key);
                continue;
            }
            if (strcmp(type, "i") == 0) {
                int_add++;

                if (int_add == 0) {
                    int_keys = malloc(sizeof(char) * strlen(key));
                }

                int_keys[int_add] = malloc(sizeof(char) * strlen(key));
                strcpy(int_keys[int_add], key);
                int_values[int_add] = atoi(parts[3]);
                printf("registered a new int %s = ", key);
                printf("%d at index ", atoi(parts[3]));
                printf("%d\n", int_add);
                printf("Array Length is %d\n", arr_len_int(int_keys));
                printf("Array is [");
                for (int j = 0; j < int_add + 1; ++j) {
                    printf(" %s -> %d ", int_keys[j], int_values[j]);
                }
                printf("]\n");

                continue;
            }

            if (strcmp(type, "d") == 0) {
                double_add++;
                double_keys[double_add] = key;
                double_values[double_add] = strtod(parts[3], NULL);
                printf("registered a new double %s = ", key);
                printf("%lf", strtod(parts[3], NULL));
                printf("\n");
                continue;
            }
            if (strcmp(type, "f") == 0) {
                float_add++;
                float_keys[float_add] = key;
                float_values[float_add] = (float) atof(parts[3]);
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
                c_add++;
                char_keys[char_am] = key;
                char_values[char_am] = (char) parts[3];
                printf("registered a new char %s = ", key);
                printf("%c", parts[3][0]);
                printf("\n");
                continue;
            }
        } else if (cmd_type == 2) {
            char *first_var = parts[1];
            char *second_var = parts[2];
            char *false_op = parts[3];
            if (contains_str(int_keys, int_add + 1, first_var) == 1) {

                int first_value = int_values[get_index(int_keys, first_var)];
                if (contains_str(int_keys, int_add + 1, second_var) != 1) {
                    printf("not containing!\n");
                    continue;
                }
                int second_value = int_values[get_index(int_keys, second_var)];

                printf("They are %d", first_value);
                printf(" and %d\n", second_value);
            } else if (contains_str(double_keys, double_add + 1, first_var) == 1) {


            } else if (contains_str(float_keys, float_add + 1, first_var) == 1) {

            } else if (contains_str(char_keys,  c_add + 1, first_var) == 1) {

            } else {
                printf("ERROR Var %s not registered\n", first_var);
            }
        }

    }

    int int_test = contains_str(int_keys, int_add + 1, "y");

    printf("\nContains result = %d\n", int_test);

    return 0;
}
