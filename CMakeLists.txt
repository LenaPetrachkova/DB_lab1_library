cmake_minimum_required(VERSION 3.26)
project(DB_lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(DB_lab1 main.cpp
        book.cpp
        book.h
        fileio.cpp
        fileio.h
        readerCard.cpp
        readerCard.h
        IndexTable.cpp
        IndexTable.h)
