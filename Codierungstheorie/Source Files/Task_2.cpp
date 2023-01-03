//
// Created by Noah on 01.01.2023.
//
#include "Header Files/EGF.h"
#include "Header Files/Helper.h"
#include "Header Files/Polynom.h"

int main(int argc, char **argv) {

    for (int i = 1; i < 9; ++i) {
        const Polynom irreduciblePolynom = ip_by_degree[i];
        const EGF gf = EGF(2, i, irreduciblePolynom);
        sep("GF(2^" + std::to_string(i) + "): " + irreduciblePolynom.to_polynom_str());
        for (int j = 1; j < gf.order; ++j) {
            auto polynom = Polynom(j);
            auto inverse = gf.multiplicative_inverse(polynom);
            auto result = gf.multiplication(polynom, inverse);

            std::cout << j << " Correct: " << toString(result == Polynom::ONE) << "   " << polynom.to_print_string(Polynom::polynom) << " * " << inverse.to_print_string(Polynom::polynom) << " = " << result.to_print_string(Polynom::polynom);
            std::cout << "  " << polynom.as_int() << " * " << inverse.as_int() << " = " << result.as_int() << std::endl;
        }
    }
    return 0;
}