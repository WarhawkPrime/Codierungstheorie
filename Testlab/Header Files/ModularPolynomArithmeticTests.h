//
// Created by Noah Ruben on 03.01.23.
//

#include "Header Files/ModularPolynomArithmetic.h"
#include "Header Files/Polynom.h"
#include "doctest.h"
#ifndef CODIERUNGSTHEORIE_MPATESTS_H
#define CODIERUNGSTHEORIE_MPATESTS_H

#endif // CODIERUNGSTHEORIE_MPATESTS_H
       /*
        * TODO
        * void m_mod(const Polynom &a, const Polynom &b, Polynom &r, Polynom &s, const int p = 2);
        * Polynom gcd(const Polynom &a, const Polynom &b, const int p = 2);
        * exgcd_result exgcd(const Polynom &a, const Polynom &b, const int p = 2);
        */

TEST_SUITE("Control Tests of modular polynom arithmetic" * doctest::description("MPA")) {
    TEST_CASE("EEA") {
        auto i_p = Polynom({1, 1, 1});
        auto r = MPA::exgcd(Polynom::ONE, i_p, 2);
        std::cout << "Result: " << r.inverse_a.to_print_string(Polynom::polynom) << std::endl;

        CHECK(r.gcd == Polynom::ONE);
        CHECK(r.inverse_a == Polynom::ONE);
    }
}