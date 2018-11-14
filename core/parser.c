//
// Created by Yann Holme Nielsen on 13.11.18.
//

#include "parser.h"

void parse(char *target_file) {

    char *content = read_f(target_file);

    if (strcmp(content, "") == 0) {
        printf("\nERROR: No lines to parse found");
        return;
    }

    char **split = str_split_debug(content, '\n', 0);
    if (split == NULL) {
        printf("\nERROR: empty lines found, make sure there are no empty lines!\n");
        return;
    }
    free(content);
    int count = 0;
    //get line amount
    for (;;) {
        if (!split[count]) break;
        count++;
    }


    int var_count = 0;
    parser_line = 0;
    //Extract the amount of defines to assign the variables amount and check for errors
    for (int i = 0; i < count; ++i) {
        parser_line = i + 1;
        char *copy = malloc(sizeof(char) * strlen(split[i]));
        strcpy(copy, split[i]);
        char **parts = str_split_debug(copy, ' ', parser_line);
        if (parts == NULL) return;
        int part_count = 0;
        for (;;) {
            if (!parts[part_count]) break;
            part_count++;
        }
        if (part_count == 0) {
            printf("\nERROR: line %d, Empty lines are not allowed\n", parser_line);
        }
        if (validate_action(parts[0]) != 0) {
            printf("\nERROR: Action: %s at line %d, is not recognized\n", parts[0], parser_line);
        }
        if (strcmp(parts[0], "df") == 0) {
            if (part_count != 4) {
                printf("\nERROR: wrong argument amount on variable define on %d\n", i + 1);
                return;
            }
            if (validate_define(parts[1][1], parts[2], parts[3]) != 0) {
                return;
            }
            var_count++;
        }
        if (strcmp(parts[0], "op") == 0) {
            if (part_count != 5) {
                printf("\nERROR: wrong argument amount on operator action on %d\n", i + 1);
                return;
            }
        }

    }

    int curr_insert = 0;
    char **keys = malloc(sizeof(char *) * var_count);
    struct Entry *entries = malloc(sizeof(struct Entry) * var_count);

    //main loop
    for (int i = 0; i < count; ++i) {
        parser_line = i + 1;

        char *copy = malloc(sizeof(char) * strlen(split[i]));
        strcpy(copy, split[i]);

        char **parts = str_split(copy, ' ');
        int part_count = 0;
        //Assign part count
        for (;;) {
            if (!parts[part_count]) break;
            part_count++;
        }

        char *action = parts[0];

        //Defining variable
        if (strcmp(action, "df") == 0) {
            char type = parts[1][0];
            char *name = parts[2];
            char *value = parts[3];
            struct Entry entry;
            entry.name = name;
            entry.type = type;
            if (type == 'i') entry.int_val = atoi(value);
            if (type == 'd') entry.double_val = strtod(value, NULL);
            if (type == 'f') entry.float_val = (float) atof(value);
            if (type == 'c') entry.char_val = value[0];
            entries[curr_insert] = entry;
            keys[curr_insert] = name;
            curr_insert++;
        }
        //Print something
        if (strcmp(action, "pr") == 0) {
            if (part_count == 1) return;
            for (int j = 1; j < part_count; ++j) {
                if (j != 1) printf(" ");
                char *str = parts[j];
                if (str[0] == '$') {
                    char *real_name = substr(str, 1);
                    int found = 0;
                    for (int x = 0; x < curr_insert; ++x) {
                        struct Entry entry = entries[x];
                        if (strcmp(entry.name, real_name) == 0) {
                            found = 1;
                            if (entry.type == 'i') {
                                int value = entry.int_val;
                                printf("%d", value);
                            }
                            if (entry.type == 'd') {
                                double value = entry.double_val;
                                printf("%lf", value);
                            }
                            if (entry.type == 'f') {
                                float value = entry.float_val;
                                printf("%f", value);
                            }
                            if (entry.type == 'c') {
                                char value = entry.char_val;
                                printf("%c", value);
                            }
                        }
                    }
                    if (found == 0) {
                        printf("\nERROR CANT FIND %s at %d\n", real_name, (i + 1));
                        return;
                    }
                } else {
                    if (strcmp(str, "\\endl") == 0) {
                        printf("\n");
                    } else {
                        printf("%s", str);
                    }
                }
            }
        }
        if (strcmp(action, "ret") == 0) {
            return;
        }
        if (strcmp(action, "ast") == 0) {
            char *first_op = parts[1];
            char *second_op = parts[2];
            char *false_target = parts[3];

            struct Entry op_1;
            struct Entry op_2;
            for (int j = 0; j < curr_insert; ++j) {
                struct Entry entry = entries[j];
                if (strcmp(entry.name, first_op) == 0)op_1 = entry;
                if (strcmp(entry.name, second_op) == 0)op_2 = entry;
            }
            if (validate_assert(op_1, op_2, parser_line) != 0) return;

            int cont = 0;
            char type = op_1.type;

            if (type == 'i')
                if (op_1.int_val == op_2.int_val)
                    cont = 1;
            if (type == 'd')
                if (op_1.double_val == op_2.double_val)
                    cont = 1;
            if (type == 'f')
                if (op_1.float_val == op_2.float_val)
                    cont = 1;


            if (cont == 1) {
                continue;
            } else {
                if(strcmp(false_target, "ret") == 0)
                    return;

                int false_operator = atoi(false_target);
                if(false_operator > count) {
                    printf("ERROR: Cant goto line %d on assert on line %d", false_operator, parser_line);
                    return;
                }
                i = false_operator - 2;
                continue;
            }
        }
        if (strcmp(action, "gt") == 0) {
            int target = atoi(parts[1]);
            if (target > count) {
                printf("ERROR: Cant goto line %d on line %d", target, parser_line);
            }
            i = target - 2;
            continue;
        }
        //logical operation on variable
        if (strcmp(action, "op") == 0) {
            char operator = parts[1][0];
            char *target_name = parts[2];
            char *op_1_name = parts[3];
            char *op_2_name = parts[4];
            int target_index = 0;
            struct Entry target;
            struct Entry op_1;
            struct Entry op_2;

            for (int j = 0; j < curr_insert; ++j) {
                struct Entry entry = entries[j];
                if (strcmp(entry.name, target_name) == 0) {
                    target = entry;
                    target_index = j;
                }
                if (strcmp(entry.name, op_1_name) == 0)op_1 = entry;
                if (strcmp(entry.name, op_2_name) == 0)op_2 = entry;
            }
            if (validate_operation(operator, target, op_1, op_2, parser_line) != 0) return;

            char type = target.type;

            if (type == 'i') {
                if (operator == '+')target.int_val = op_1.int_val + op_2.int_val;
                if (operator == '-')target.int_val = op_1.int_val - op_2.int_val;
                if (operator == '/')target.int_val = op_1.int_val / op_2.int_val;
                if (operator == '*')target.int_val = op_1.int_val * op_2.int_val;
            }
            if (type == 'd') {
                if (operator == '+')target.double_val = op_1.double_val + op_2.double_val;
                if (operator == '-')target.double_val = op_1.double_val - op_2.double_val;
                if (operator == '/')target.double_val = op_1.double_val / op_2.double_val;
                if (operator == '*')target.double_val = op_1.double_val * op_2.double_val;
            }
            if (type == 'f') {
                if (operator == '+')target.float_val = op_1.float_val + op_2.float_val;
                if (operator == '-')target.float_val = op_1.float_val - op_2.float_val;
                if (operator == '/')target.float_val = op_1.float_val / op_2.float_val;
                if (operator == '*')target.float_val = op_1.float_val * op_2.float_val;
            }
            entries[target_index] = target;
        }

    }

}