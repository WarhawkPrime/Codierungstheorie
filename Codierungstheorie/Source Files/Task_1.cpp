//
// Created by Noah on 01.01.2023.
//
#include "Header Files/EGF.h"
#include "Header Files/Helper.h"
#include "Header Files/Polynom.h"
/**
 * Irreducible polynom per degree soo script for more infos
 */
const Polynom ip_by_degree[10] = {
    Polynom(7), // Kein explizites irreduzibles Polynom für diesen Grad angegeben
    Polynom(7), // Kein explizites irreduzibles Polynom für diesen Grad angegeben
    Polynom(7),
    Polynom(13),
    Polynom(25),
    Polynom(49),
    Polynom(97),
    Polynom(241),
    Polynom(289),
    Polynom(577)};

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