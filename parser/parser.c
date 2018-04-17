//
// Created by Yann Holme Nielsen on 14.04.18.
//

#include "parser.h"

int contains_str(char *keys[], int length, char *search) {
    if (*keys == NULL) return 0;
    for (int i = 0; i < length; ++i) {
        if (strcmp(keys[i], search) == 0) {
            return 1;
        }
    }
    return 0;
}

int get_index(char *keys[], int length, char *search) {
    if (*keys == NULL) return -1;
    for (int i = 0; i < length; ++i) {
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
    char **char_values = malloc(sizeof(char) * char_am);

    char **lines;
    lines = str_split(read_f(path), '\n');
    int walk_i;
    for (walk_i = 0; *(lines + walk_i); walk_i++) {
        if (strcmp(*(lines + walk_i), "return") == 0) return 0;
        char **parts;
        parts = str_split(*(lines + walk_i), ' ');


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
                /*
                 * printf("registered a new int %s = ", key);
                printf("%d at index ", atoi(parts[3]));
                printf("%d\n", int_add);
                printf("Array Length is %d\n", arr_len_int(int_keys));
                printf("Array is [");
                for (int j = 0; j < int_add + 1; ++j) {
                    printf(" %s -> %d ", int_keys[j], int_values[j]);
                }
                printf("]\n");
                 */

                continue;
            }

            if (strcmp(type, "d") == 0) {
                double_add++;
                if (double_add == 0) {
                    double_keys = malloc(sizeof(char) * strlen(key));
                }
                double_keys[double_add] = malloc(sizeof(char) * strlen(key));
                strcpy(double_keys[double_add], key);
                double_values[double_add] = strtod(parts[3], NULL);
                continue;
            }
            if (strcmp(type, "f") == 0) {
                float_add++;
                if (float_add == 0) {
                    float_keys = malloc(sizeof(char) * strlen(key));
                }
                float_keys[float_add] = malloc(sizeof(char) * strlen(key));
                strcpy(float_keys[float_add], key);
                float_values[float_add] = (float) atof(parts[3]);
                continue;
            }
            if (strcmp(type, "s") == 0) {
                //TODO Later
                continue;
            }
            if (strcmp(type, "c") == 0) {
                c_add++;
                if (c_add == 0) {
                    char_keys = malloc(sizeof(char) * strlen(key));
                }
                char_keys[c_add] = malloc(sizeof(char) * strlen(key));
                strcpy(char_keys[c_add], key);
                char_values[c_add] = parts[3];
                continue;
            }
        } else if (cmd_type == 2) {
            char *first_var = parts[1];
            char *second_var = parts[2];
            char *false_op = parts[3];
            if (contains_str(int_keys, int_add + 1, first_var) == 1) {

                int first_value = int_values[get_index(int_keys, int_add + 1, first_var)];
                if (contains_str(int_keys, int_add + 1, second_var) != 1) {
                    continue;
                }
                int second_value = int_values[get_index(int_keys, int_add + 1, second_var)];


                if (first_value == second_value) {
                    continue;
                }
                if (strcmp(false_op, "return") == 0)return 0;

                int goto_node = atoi(false_op);

                walk_i = goto_node - 2;
            } else if (contains_str(double_keys, double_add + 1, first_var) == 1) {
                double first_value = double_values[get_index(double_keys, double_add + 1, first_var)];
                if (contains_str(double_keys, double_add + 1, second_var) != 1) {
                    continue;
                }
                double second_value = double_values[get_index(double_keys, double_add + 1, second_var)];
                if (first_value == second_value) {
                    continue;
                }
                if (strcmp(false_op, "return") == 0)return 0;

                int goto_node = atoi(false_op);

                walk_i = goto_node - 2;

            } else if (contains_str(float_keys, float_add + 1, first_var) == 1) {

                float first_value = float_values[get_index(float_keys, float_add + 1, first_var)];
                if (contains_str(float_keys, float_add + 1, second_var) != 1) {
                    continue;
                }
                float second_value = float_values[get_index(float_keys, float_add + 1, second_var)];
                if (first_value == second_value) {
                    continue;
                }
                if (strcmp(false_op, "return") == 0)return 0;

                int goto_node = atoi(false_op);

                walk_i = goto_node - 2;

            } else if (contains_str(char_keys, c_add + 1, first_var) == 1) {
                char *first_value = char_values[get_index(char_keys, c_add + 1, first_var)];
                if (contains_str(char_keys, c_add + 1, second_var) != 1) {
                    continue;
                }
                char *second_value = char_values[get_index(char_keys, c_add + 1, second_var)];
                if (strcmp(first_value, second_value) == 0) {
                    continue;
                }
                if (strcmp(false_op, "return") == 0)return 0;

                int goto_node = atoi(false_op);

                walk_i = goto_node - 2;
            } else {
                printf("ERROR Var %s not registered\n", first_var);
            }
        } else if (cmd_type == 3) {
            if (strcmp(parts[1], "$") != 0) {
                printf("%s", parts[1]);
            } else {
                char *first_var = parts[2];
                if (contains_str(int_keys, int_add + 1, first_var) == 1) {

                    int first_value = int_values[get_index(int_keys, int_add + 1, first_var)];
                    printf("%d", first_value);
                } else if (contains_str(double_keys, double_add + 1, first_var) == 1) {
                    double first_value = double_values[get_index(double_keys, double_add + 1, first_var)];
                    printf("%lf", first_value);


                } else if (contains_str(float_keys, float_add + 1, first_var) == 1) {

                    float first_value = float_values[get_index(float_keys, float_add + 1, first_var)];
                    printf("%f", first_value);


                } else if (contains_str(char_keys, c_add + 1, first_var) == 1) {
                    char *first_value = char_values[get_index(char_keys, c_add + 1, first_var)];
                    printf("%s", first_value);

                }
            }
        } else if (cmd_type == 4) {
            walk_i = atoi(parts[1]) - 2;
        } else if (cmd_type == 5) {
            if (strcmp(parts[1], "$") != 0) {
                sleep(atoi(parts[1]));
            } else {
                char *first_var = parts[2];
                if (contains_str(int_keys, int_add + 1, first_var) == 1) {
                    int first_value = int_values[get_index(int_keys, int_add + 1, first_var)];
                    sleep(first_value);
                }
            }

        }else if (cmd_type == 6) {
           printf("\n");
        }

    }
    return 0;
}
