//
// Created by Noah on 01.01.2023.
//
#include "Header Files/EGF.h"
#include "Header Files/Helper.h"
#include "Header Files/Polynom.h"

int main(int argc, char **argv) {

    for (int i = 1; i < 4; ++i) {
        const Polynom irreduciblePolynom = ip_by_degree[i];
        const EGF gf = EGF(2, i, irreduciblePolynom);
        sep("GF(2^" + std::to_string(i) + "): " + irreduciblePolynom.to_polynom_str());
        for (int j = 1; j < gf.order; ++j) {
            auto polynom = Polynom(j);
            auto inverse = gf.multiplicative_inverse(polynom);
            auto result = (inverse * polynom) % irreduciblePolynom;

            std::cout << j << " Correct: " << toString(result == Polynom::ONE) << "   " << polynom.to_vector_str() << " * " << inverse.to_vector_str() << " = " << result.to_vector_str() << std::endl;
        }
    }
    return 0;
}