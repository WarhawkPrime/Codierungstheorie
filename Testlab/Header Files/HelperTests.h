//
// Created by Noah Ruben on 06.12.22.
//
#include "Header Files/Basis.h"
#include "Header Files/Helper.h"
#include "doctest.h"

TEST_SUITE("Helper Functions for further understanding" *
           doctest::description("optional")) {
    TEST_CASE("Hamming Distance") {
        int a = 3;
        int b = 5;

        CHECK(calc_hamming_distance(a, b) == 2);
    }
}

TEST_SUITE("Control Tests of basis" * doctest::description("basis")) {
    Basis basis;

    TEST_CASE("Modulo") {
        int a = 5;
        int m = 2;

        CHECK(Basis::modulo_group_mod(a, m) == 1);
    }

    TEST_CASE("Euclidean Algorithm") {
        const int a = 16;
        const int b = 12;

        CHECK(basis.euclidean_algorithm(a, b) == 4);
    }

    TEST_CASE("Extended Euclidean Algorithm") {
        const int a = 99;
        const int b = 78;

        int s = 1;
        int t = 0;

        int res = basis.extended_euclidean_algorithm(a, b, s, t);

        CHECK(res == 3);
        CHECK(s == -11);
        CHECK(t == 14);
    }

    TEST_CASE("Additive Inverse") {
        const int a = 7;
        const int mod = 11;

        int inverse;
        basis.additive_inverse(a, mod, inverse);

        CHECK(inverse == 4);
    }

    TEST_CASE("Modular Inverse") {
        const int a = 3;
        const int mod = 11;

        int inverse;
        basis.multiplicative_inverse(a, mod, inverse);

        CHECK(inverse == 4);
    }
}