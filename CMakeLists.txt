cmake_minimum_required(VERSION 3.21)
project(project_SO C)

set(CMAKE_C_STANDARD 90)

add_executable(project_SO main/main.c main/master.c function_supp/support.h function_supp/readInputFile.c function_supp/readInputFile.h function_supp/shmFunctions.c function_supp/shmFunctions.h core/keys.h core/transaction.h function_supp/suppUtility.c function_supp/suppUtility.h function_main/shmMasterBook.c function_main/shmMasterBook.h function_supp/creationBook.c function_supp/creationBook.h main/user.c main/node.c function_main/semaphores.c function_main/semaphores.h function_main/messageQueue.c function_main/messageQueue.h)
