//
// Created by Dennis on 27/10/2022.
//
#define DOCTEST_CONFIG_IMPLEMENT
#include <Header Files/doctest.h>

#include "Header Files/Helper.h"
#include "Header Files/Basis.h"
#include "Header Files/Polynom.h"

TEST_SUITE("Helper Functions for further understanding" * doctest::description("optional"))
{
    TEST_CASE("Hamming Distance")
    {
        int a = 3;
        int b = 5;

        CHECK(calc_hamming_distance(a, b) == 2);
    }
}


TEST_SUITE("Control Tests of basis" * doctest::description("basis"))
{
    Basis basis;

    TEST_CASE("Modulo")
    {
        int a = 5;
        int m = 2;


        CHECK(basis.modulo_group_mod(a, m) == 1);
    }

    TEST_CASE("Euclidean Algorithm")
    {
        const int a = 16;
        const int b = 12;

        CHECK(basis.euclidean_algorithm(a, b) == 4);
    }

    TEST_CASE("Extended Euclidean Algorithm")
    {
        const int a = 99;
        const int b = 78;

        int s = 1;
        int t = 0;

        int res = basis.extended_euclidean_algorithm(a, b, s, t);

        CHECK(res == 3);
        CHECK(s == -11);
        CHECK(t == 14);
    }

    TEST_CASE("Additive Inverse")
    {
        const int a = 7;
        const int mod = 11;

        int inverse;
        basis.additive_inverse(a, mod, inverse);

        CHECK(inverse == 4);
    }

    TEST_CASE("Modular Inverse")
    {
        const int a = 3;
        const int mod = 11;

        int inverse;
        basis.multiplicative_inverse(a, mod, inverse);

        CHECK(inverse == 4);
    }

}

TEST_SUITE("Control Tests of polynom operations" * doctest::description("polynom"))
{
    TEST_CASE("polynom addition")
    {
        Polynom a = Polynom({1, 1, 1});
        Polynom b = Polynom({0, 1, 0});

        Polynom c = a + b;

        CHECK(c.get_coefficient(0) == 1);
        CHECK(c.get_coefficient(1) == 2);

        Polynom d = Polynom({0, 0, 0, 1});

        Polynom e = a + d;

        CHECK(e.get_coefficient(3) == 1);
    }

}



TEST_SUITE("Praktikum 1 tests" * doctest::description("functional tests"))
{
    TEST_CASE("Test test")
    {
    CHECK(true == true);
    }
}



int main(int argc, char** argv) {
    doctest::Context context;

    // defaults
    context.setOption("order-by", "name");            // sort the test cases by their name
    context.applyCommandLine(argc, argv);

    // overrides
    context.setOption("no-breaks", true);             // don't break in the debugger when assertions fail

    int res = context.run(); // run

    if (context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
        return res;          // propagate the result of the tests
}