cmake_minimum_required(VERSION 3.26)
project(etterem C)

set(CMAKE_C_STANDARD 11)

set(CXXFLAGS  "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CXXFLAGS}")

add_executable(etterem main.c
        menu.c
        table.c
        gui.c
        menu.h
        linkedlist.c
        linkedlist.h
        io.c
        io.h
        table.h
        order.c
        order.h
        gui.h
)
