cmake_minimum_required(VERSION 3.23)
project(Codierungstheorie)

set(CMAKE_CXX_STANDARD 23)

include_directories(Codierungstheorie)
include_directories(Testlab)

add_executable(Codierungstheorie
        "Codierungstheorie/Source Files/main.cpp"
        "Codierungstheorie/Header Files/Helper.h"
        "Codierungstheorie/Header Files/Codierungstheorie.h"
        )

target_include_directories(Codierungstheorie PUBLIC Codierungstheorie/Header Files)



add_executable(Testlab
    "Testlab/Source Files/Testlab.cpp"
    "Testlab/Header Files/doctest.h"
    )

target_include_directories(Testlab PUBLIC Testlab/Header Files)