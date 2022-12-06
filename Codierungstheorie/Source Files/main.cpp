
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

    EGF gf = EGF(2, 2, irreduciblePolynom);
    gf.print_elements(Polynom::vector);
    gf.print_addition_table(Polynom::number);

    std::cout << std::endl;
}
