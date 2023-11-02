cmake_minimum_required(VERSION 3.26)
project(nagyhazi C)

set(CMAKE_C_STANDARD 11)

add_executable(nagyhazi main.c
        menu.c
        commands.c
        table.c
        gui.c
        menu.h
        linkedlist.c
        linkedlist.h)
