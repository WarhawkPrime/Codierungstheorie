cmake_minimum_required(VERSION 3.22.3)
project(Codierungstheorie)

set(CMAKE_CXX_STANDARD 23)

include(CTest)

include_directories(Codierungstheorie)
include_directories(Testlab)

add_executable(Codierungstheorie
               "Codierungstheorie/Source Files/main.cpp"
               "Codierungstheorie/Header Files/Helper.h"
               "Codierungstheorie/Header Files/Codierungstheorie.h"
               "Codierungstheorie/Source Files/ModularArithmetic.cpp"
               "Codierungstheorie/Header Files/ModularArithmetic.h"
               "Codierungstheorie/Source Files/Basis.cpp"
               "Codierungstheorie/Header Files/Basis.h"
               "Codierungstheorie/Source Files/Polynom.cpp"
               "Codierungstheorie/Header Files/Polynom.h"
               "Codierungstheorie/Source Files/EGF.cpp"
               "Codierungstheorie/Header Files/EGF.h"
               "Codierungstheorie/Header Files/ModularPolynomArithmetic.h")

target_include_directories(Codierungstheorie PUBLIC Codierungstheorie/Header Files)


add_executable(Testlab
               "Testlab/Source Files/Testlab.cpp"
               "Testlab/Header Files/doctest.h"
               "Codierungstheorie/Source Files/ModularArithmetic.cpp"
               "Codierungstheorie/Header Files/ModularArithmetic.h"
               "Codierungstheorie/Source Files/Basis.cpp"
               "Codierungstheorie/Header Files/Basis.h"
               "Codierungstheorie/Source Files/Polynom.cpp"
               "Codierungstheorie/Header Files/Polynom.h"
               "Codierungstheorie/Source Files/EGF.cpp"
               "Codierungstheorie/Header Files/EGF.h"
               "Codierungstheorie/Header Files/ModularPolynomArithmetic.h")


target_include_directories(Testlab PUBLIC Testlab/Header Files)

add_test(Testlab Testlab)


## Task 1

add_executable(Task_1
               "Codierungstheorie/Source Files/Polynom.cpp"
               "Codierungstheorie/Header Files/Polynom.h"
               "Codierungstheorie/Source Files/EGF.cpp"
               "Codierungstheorie/Header Files/EGF.h"
               "Codierungstheorie/Source Files/Task_1.cpp"
               )

target_include_directories(Task_1 PUBLIC Codierungstheorie/Header Files)

## Task 2

add_executable(Task_2
               "Codierungstheorie/Source Files/Polynom.cpp"
               "Codierungstheorie/Header Files/Polynom.h"
               "Codierungstheorie/Source Files/EGF.cpp"
               "Codierungstheorie/Header Files/EGF.h"
               "Codierungstheorie/Source Files/Task_2.cpp"
               )

target_include_directories(Task_2 PUBLIC Codierungstheorie/Header Files)