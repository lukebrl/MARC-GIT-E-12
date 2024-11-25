cmake_minimum_required(VERSION 3.27)
project(untitled1 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled1 main.c
        loc.c
        loc.h
        moves.c
        moves.h
        map.c
        map.h
        queue.c
        queue.h
        stack.c
        stack.h
        functions.c
        functions.h
        tree.c
        tree.h
        node.h
        node.c
        test.c
        functions.c
        rover.h
        rover.c)
