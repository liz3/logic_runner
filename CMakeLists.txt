cmake_minimum_required(VERSION 3.10)
project(logic_runner C)

set(CMAKE_C_STANDARD 11)

add_executable(logic_runner main.c parser/parser.c parser/parser.h utils.c utils.h parser/command-extractor.c parser/command-extractor.h)