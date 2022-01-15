cmake_minimum_required(VERSION 3.21)
project(project_SO C)

set(CMAKE_C_STANDARD 90)

add_executable(project_SO main/main.c main/master.c function_supp/support.h function_supp/readInputFile.c function_supp/readInputFile.h function_supp/shmFunctions.c function_supp/shmFunctions.h core/keys.h core/transaction.h function_supp/suppUtility.c function_supp/suppUtility.h)
