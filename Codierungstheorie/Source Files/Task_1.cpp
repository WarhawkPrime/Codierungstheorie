//
// Created by Noah on 01.01.2023.
//
#include "Header Files/EGF.h"
#include "Header Files/Helper.h"
#include "Header Files/Polynom.h"

void multiplicationTables() {
    for (int i = 1; i < 9; ++i) {
        Polynom irreduciblePolynom = ip_by_degree[i];
        std::cout << "GF(2^" << i << "): " << irreduciblePolynom.to_polynom_str() << std::endl;

        EGF const gf = EGF(2, i, irreduciblePolynom);
        gf.print_multiplication_table(Polynom::number, "mult_matrix_" + std::to_string(i) + ".csv");
    }
}

void additionTables() {
    for (int i = 1; i < 9; ++i) {
        const Polynom irreduciblePolynom = ip_by_degree[i];
        const EGF gf = EGF(2, i, irreduciblePolynom);
        std::cout << "GF(2^" << i << "): " << irreduciblePolynom.to_polynom_str() << std::endl;
        gf.print_addition_table(Polynom::number, "add_matrix_" + std::to_string(i) + ".csv");
    }
}

int main(int argc, char **argv) {

    sep("Generating addition Tables");
    additionTables();
    sep("Generating multiplication Tables");
    multiplicationTables();

    return 0;
}