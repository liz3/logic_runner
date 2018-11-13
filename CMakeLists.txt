cmake_minimum_required(VERSION 3.12)
project(logic_run_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(logic_run_2 main.c core/parser.c core/parser.h utils/utils.c utils/utils.h core/validator.c core/validator.h)