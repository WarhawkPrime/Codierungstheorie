//
// Created by Noah Ruben on 06.12.22.
//
#include "Header Files/EGF.h"
#include "Header Files/HelperTests.h"

#include "doctest.h"

TEST_SUITE("Control Tests of polynom operations in a EGF" *
           doctest::description("egf")) {
    TEST_CASE("Polynom Addition in an EGF") {
        EGF aEGF(3, 2, Polynom({2, 1, 1})); // EGF(3^2) : 2 + x + x^2

        Polynom c = aEGF.addition(Polynom({2, 2}), Polynom({2, 1}));

        CHECK(c.get_coefficient(0) == 1);
        CHECK(c.get_coefficient(1) == 0);
    }

    TEST_CASE("Polynom multiplication in an EGF") {
        EGF aEGF(3, 2, Polynom({2, 1, 1})); // EGF(3^2) : 2 + x + x^2

        Polynom c = aEGF.multiplication(Polynom({0, 0, -2}), Polynom({2, 1, 1}));
        // TODO
    }

    TEST_CASE("Multiplicative inverse calculation Fuzzy test in EGF p = 2") {
        auto const p = 2;

        // 0 < e < 9
        for (int i = 1; i < 9; ++i) {
            const Polynom irreduciblePolynom = ip_by_degree[i];
            const EGF gf = EGF(p, i, irreduciblePolynom);
#ifndef CMAKE_BUILD_TYPE
            sep("GF(2^" + std::to_string(i) + "): " + irreduciblePolynom.to_polynom_str());
#endif
            for (int j = 1; j < gf.order; ++j) {
                auto polynom = Polynom(j);
                auto inverse = gf.multiplicative_inverse(polynom);
                auto result = gf.multiplication(polynom, inverse);

                CHECK(result == Polynom::ONE);
            }
        }
    }

    TEST_CASE("Division with remainder: EGF(3^2) : 2 + x + x^2") {
        EGF aEGF(3, 2, Polynom({2, 1, 1})); // EGF(3^2) : 2 + x + x^2

        Polynom mod = Polynom(0);
        Polynom div = Polynom(0);
        aEGF.modular_reduction(Polynom({1, 2, 0, 1, 2}), mod, div);

        Polynom mod_exp = Polynom({1, 1});
        Polynom div_exp = Polynom({0, 2, 2});

        CHECK(mod == mod_exp);
        CHECK(div == div_exp);
    }

    TEST_CASE("Division with remainder") {
        // TEST (1,1,1) / 1
        EGF bEGF(2, 3, Polynom({1, 1, 1})); // EGF(2^3) : 1 + x + x^2

        Polynom mod_b = Polynom::ZERO;
        Polynom div_b = Polynom::ZERO;

        bEGF.modular_reduction(Polynom::ONE, mod_b, div_b);

        Polynom mod_exp_b = Polynom::ONE;
        Polynom div_exp_b = Polynom::ZERO;

        CHECK(mod_b == mod_exp_b);
        CHECK(div_b == div_exp_b);
    }
}