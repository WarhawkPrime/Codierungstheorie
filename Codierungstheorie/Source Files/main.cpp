
#include "Header Files/EGF.h"
#include "Header Files/Helper.h"
#include "Header Files/Polynom.h"
#include <iostream>

int main(int argc, char **argv) {
    Polynom irreduciblePolynom = Polynom({1, 1, 1});

    for (int i = 0; i < 16; ++i) {
        std::cout << Polynom(i).to_vector_str() << std::endl;
    }

    sep("EGF e=1");

    for (int i = 1; i < 9; ++i) {
        EGF gf = EGF(2, i, irreduciblePolynom);
        gf.print_addition_table(Polynom::number, "result_" + std::to_string(i) + ".csv");
    }

    std::cout << std::endl;
}
