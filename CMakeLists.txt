cmake_minimum_required(VERSION 3.8)

include_directories(lib)

project(apue)

set(CMAKE_C_STANDARD 99)

set(LIB_FILES
        lib/apue.h
        lib/mylog.h
        lib/mylog.c
        lib/myerror.h
        lib/myerror.c)

add_executable(myls src/chapter1/myls.c ${LIB_FILES})
add_executable(myprint src/chapter1/myprint.c ${LIB_FILES})
add_executable(myprint2 src/chapter1/myprint2.c ${LIB_FILES})
add_executable(mygetpid src/chapter1/mygetpid.c ${LIB_FILES})
add_executable(myshell src/chapter1/myshell.c ${LIB_FILES})
