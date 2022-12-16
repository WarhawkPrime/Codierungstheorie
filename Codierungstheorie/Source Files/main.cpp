
#include "Header Files/EGF.h"
#include "Header Files/Helper.h"
#include "Header Files/Polynom.h"
#include <iostream>

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

void multiplicationTables(bool use_appropriate_ip = true) {
    for (int i = 1; i < 9; ++i) {
        Polynom irreduciblePolynom = ip_by_degree[9];

        if (use_appropriate_ip)
            irreduciblePolynom = ip_by_degree[i];

        std::cout << i << ": " << irreduciblePolynom.to_polynom_str() << " " << irreduciblePolynom.get_degree() << std::endl;
        EGF const gf = EGF(2, i, irreduciblePolynom);
        gf.print_multiplication_table(Polynom::number, "mult_matrix_" + std::to_string(i) + ".csv");
    }
}

void additionTables() {
    Polynom const irreduciblePolynom = Polynom({1, 1, 1});
    for (int i = 1; i < 9; ++i) {
        EGF const gf = EGF(2, i, irreduciblePolynom);
        gf.print_addition_table(Polynom::number, "add_matrix_" + std::to_string(i) + ".csv");
    }
}

void task1() {
    additionTables();
    multiplicationTables();
}

void lax() {
    //    auto i_p = Polynom({1, 0, 0, 0, 0, 0, 1, 1});
    //
    //    auto a = Polynom(7) * Polynom(1);
    //    std::cout << "a " << a.to_print_string(Polynom::polynom) << std::endl;
    //
    //    auto s = Polynom(0);
    //    auto r = Polynom(0);
    //
    //    auto egf = EGF(3, 4, i_p);
    //
    //    egf.modular_reduction(a, r, s);
    //
    //    std::cout << "r " << r.to_print_string(Polynom::polynom) << std::endl;
    //    std::cout << "s " << s.to_print_string(Polynom::polynom) << std::endl;

    //    for (const Polynom &item : ip_by_degree) {
    //        std::cout << item.as_int() << ": " << item.to_polynom_str() << std::endl;
    //    }
    //
    //    std::cout << std::endl;

    auto i_p = Polynom({1, 1, 1});

    auto a = Polynom(3) * Polynom(3);
    a = a % 2;
    std::cout << "a " << a.to_print_string(Polynom::polynom) << std::endl;
    sep("");

    auto s = Polynom(0);
    auto r = Polynom(0);

    auto egf = EGF(2, 3, Polynom({1, 0, 1, 1}));

    auto x = Polynom({0, 0, 1, 0, 1});
    std::cout << x.to_polynom_str() << std::endl;
    egf.modular_reduction(x, r, s);
    std::cout << "r " << r.to_print_string(Polynom::polynom) << std::endl;
    std::cout << "s " << s.to_print_string(Polynom::polynom) << std::endl;
    sep("BIN");

    s = egf.polynomial_reduction_bin(Polynom({1, 0, 1, 0, 0}), Polynom({1, 0, 1, 1}));
    std::cout << std::endl;
}

int main(int argc, char **argv) {

    lax();

    //    task1();

    return 0;
}