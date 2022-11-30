//
// Created by Dennis on 27/10/2022.
//
#define DOCTEST_CONFIG_IMPLEMENT
#include <Header Files/doctest.h>

#include "Header Files/Helper.h"
#include "Header Files/Basis.h"
#include "Header Files/Polynom.h"
#include "Header Files/EGF.h"


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


        CHECK(Basis::modulo_group_mod(a, m) == 1);
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
    TEST_CASE("polynom resize")
    {
        Polynom a = Polynom({1, 0, 1, 0, 0});

        CHECK(a.get_degree() == 4);

        a.resize();

        //a.print_polynom();

        CHECK(a.get_degree() == 2);
    }

    TEST_CASE("polynom comparison")
    {
        Polynom a = Polynom({1, 0, 1, 0, 2});
        Polynom b = Polynom({1, 0, 1, 0, 2});

        Polynom c = Polynom({1, 2, 1, 0, 1});

        CHECK(a==b);
        CHECK(a!=c);
    }

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

    TEST_CASE("Polynom multiplication with integer")
    {
        Polynom a = Polynom({0, 0, 2});

        Polynom f = a * -1;

        //f.print_polynom();

        CHECK(f.get_coefficient(2) == -2);
    }

    TEST_CASE("Polynom multiplication")
    {
        Polynom a = Polynom({0, 0, 2});
        Polynom b = Polynom({2, 1, 1});

        //a.print_polynom();
        //b.print_polynom();

        Polynom c = ( a * b);


        //c.print_polynom();

        CHECK(c.get_coefficient(4) == 2);

    }

    // fuzzy test!
    TEST_CASE("Polynom to q-adic number")
    {
        Polynom a = Polynom({0, 0, 1, 1});

        CHECK(a.to_q_adic_number(2,2) == 12);
    }
}

TEST_SUITE("Control Tests of polynom operations in a EGF" * doctest::description("egf"))
{
    TEST_CASE("Polynom Addition in an EGF")
    {
        EGF aEGF(3,2, Polynom({2, 1, 1}));  // EGF(3^2) : 2 + x + x^2

        Polynom c = aEGF.modulo_addition(Polynom({2,2}), Polynom({2,1}));

        CHECK(c.get_coefficient(0) == 1);
        CHECK(c.get_coefficient(1) == 0);
    }

    TEST_CASE("Polynom multiplication in an EGF")
    {
        EGF aEGF(3,2, Polynom({2, 1, 1}));  // EGF(3^2) : 2 + x + x^2

        Polynom c = aEGF.modulo_multiplication(Polynom({0, 0, -2}), Polynom({2, 1, 1}));

        //c.print_polynom();
    }

    TEST_CASE("Division with remainder")
    {
        EGF aEGF(3,2, Polynom({2, 1, 1}));  // EGF(3^2) : 2 + x + x^2

        Polynom r = Polynom({0});
        Polynom s = Polynom({0});
        aEGF.modular_reduction(Polynom({1, 2, 0, 1, 2}), r, s );

        Polynom r_exp = Polynom({1, 1});
        Polynom s_exp = Polynom({0, 2, 2});

        CHECK(r == r_exp);
        CHECK(s == s_exp);
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