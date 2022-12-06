//
// Created by Noah Ruben on 06.12.22.
//
#include "Header Files/EGF.h"
#include "doctest.h"

TEST_SUITE("Control Tests of polynom operations in a EGF" *
           doctest::description("egf")) {
    TEST_CASE("Polynom Addition in an EGF") {
        EGF aEGF(3, 2, Polynom({2, 1, 1})); // EGF(3^2) : 2 + x + x^2

        Polynom c = aEGF.modulo_addition(Polynom({2, 2}), Polynom({2, 1}));

        CHECK(c.get_coefficient(0) == 1);
        CHECK(c.get_coefficient(1) == 0);
    }

    TEST_CASE("Polynom multiplication in an EGF") {
        EGF aEGF(3, 2, Polynom({2, 1, 1})); // EGF(3^2) : 2 + x + x^2

        Polynom c =
            aEGF.modulo_multiplication(Polynom({0, 0, -2}), Polynom({2, 1, 1}));
    }

    TEST_CASE("Division with remainder") {
        EGF aEGF(3, 2, Polynom({2, 1, 1})); // EGF(3^2) : 2 + x + x^2

        Polynom r = Polynom(0);
        Polynom s = Polynom(0);
        aEGF.modular_reduction(Polynom({1, 2, 0, 1, 2}), r, s);

        Polynom r_exp = Polynom({1, 1});
        Polynom s_exp = Polynom({0, 2, 2});

        CHECK(r == r_exp);
        CHECK(s == s_exp);
    }
}