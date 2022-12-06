cmake_minimum_required(VERSION 3.22.3)
project(Codierungstheorie)

set(CMAKE_CXX_STANDARD 23)

include_directories(Codierungstheorie)
include_directories(Testlab)

add_executable(Codierungstheorie
        "Codierungstheorie/Source Files/main.cpp"
        "Codierungstheorie/Header Files/Helper.h"
        "Codierungstheorie/Header Files/Codierungstheorie.h"
        "Codierungstheorie/Source Files/ModularArithmetic.cpp" "Codierungstheorie/Header Files/ModularArithmetic.h" "Codierungstheorie/Source Files/Basis.cpp" "Codierungstheorie/Header Files/Basis.h" "Codierungstheorie/Source Files/Polynom.cpp" "Codierungstheorie/Header Files/Polynom.h" "Codierungstheorie/Source Files/EGF.cpp" "Codierungstheorie/Header Files/EGF.h")

target_include_directories(Codierungstheorie PUBLIC Codierungstheorie/Header Files)


add_executable(Testlab
        "Testlab/Source Files/Testlab.cpp"
        "Testlab/Header Files/doctest.h"
        "Codierungstheorie/Source Files/ModularArithmetic.cpp" "Codierungstheorie/Header Files/ModularArithmetic.h" "Codierungstheorie/Source Files/Basis.cpp" "Codierungstheorie/Header Files/Basis.h" "Codierungstheorie/Source Files/Polynom.cpp" "Codierungstheorie/Header Files/Polynom.h" "Codierungstheorie/Source Files/EGF.cpp" "Codierungstheorie/Header Files/EGF.h")

target_include_directories(Testlab PUBLIC Testlab/Header Files)


add_executable(PolynomTests
        "Testlab/Source Files/PolynomTests.cpp"
        "Testlab/Header Files/doctest.h"
        "Codierungstheorie/Source Files/Polynom.cpp"
        "Codierungstheorie/Header Files/Polynom.h"
        )

target_include_directories(PolynomTests PUBLIC Testlab/Header Files)

# TODO: Executable for all test @Dennis