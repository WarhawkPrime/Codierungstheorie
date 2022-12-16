//
// Created by Noah Ruben on 24.11.22.
//
#include "doctest.h"

#include "Header Files/Polynom.h"

TEST_SUITE("Polynom Tests" * doctest::description("optional")) {
    TEST_CASE("Triming tests") {
        auto classToTest = Polynom({1, 1});

        CHECK_EQ(classToTest.get_degree(), 1);

        classToTest = Polynom({0, 1, 1});

        CHECK_EQ(classToTest.get_degree(), 2);

        classToTest = Polynom({1, 1, 0});

        CHECK_EQ(classToTest.get_degree(), 1);

        classToTest = Polynom({1, 0, 0, 0, 0});

        CHECK_EQ(classToTest.get_degree(), 0);

        classToTest = Polynom(8);

        CHECK_EQ(classToTest.get_degree(), 3);
    }

    TEST_CASE("polynom comparison") {
        Polynom a = Polynom({1, 0, 1, 0, 2});
        Polynom b = Polynom({1, 0, 1, 0, 2});

        Polynom c = Polynom({1, 2, 1, 0, 1});

        CHECK(a == b);
        CHECK(a != c);
    }

    TEST_CASE("Creating from array and printing") {

        auto coeff = {0, 1, 1, 0};
        auto classToTest = Polynom(coeff);

        auto polynom_str = classToTest.to_polynom_str();
        auto vector_str = classToTest.to_vector_str();
        auto asInt = classToTest.as_int();

        CHECK(polynom_str == "0 + 1x^1 + 1x^2");
        CHECK(vector_str == "(0, 1, 1)");
        CHECK_EQ(asInt, 6);

        auto coeff2 = {1, 1};
        classToTest = Polynom(coeff2);

        polynom_str = classToTest.to_polynom_str();
        vector_str = classToTest.to_vector_str();
        asInt = classToTest.as_int();

        CHECK(polynom_str == "1 + 1x^1");
        CHECK(vector_str == "(1, 1)");
        CHECK_EQ(asInt, 3);

        auto coeff3 = {2, 2, 1};
        classToTest = Polynom(coeff3);

        polynom_str = classToTest.to_polynom_str();
        vector_str = classToTest.to_vector_str();

        CHECK(polynom_str == "2 + 2x^1 + 1x^2");
        CHECK(vector_str == "(2, 2, 1)");
    }

    TEST_CASE("Creating from number and printing") {

        auto classToTest = Polynom(6);

        auto polynom_str = classToTest.to_polynom_str();
        auto vector_str = classToTest.to_vector_str();
        auto asInt = classToTest.as_int();

        CHECK(polynom_str == "0 + 1x^1 + 1x^2");
        CHECK(vector_str == "(0, 1, 1)");
        CHECK_EQ(asInt, 6);

        classToTest = Polynom(2);

        polynom_str = classToTest.to_polynom_str();
        vector_str = classToTest.to_vector_str();
        asInt = classToTest.as_int();

        CHECK_EQ(asInt, 2);
    }

    TEST_CASE("Converting from and to number fuzzy test") {
        for (int i = 1; i < 100000; ++i) {
            auto classToTest = Polynom(i);

            auto asInt = classToTest.as_int();

            CHECK_EQ(asInt, i);
        }
    }

    TEST_CASE("Addition") {
        auto p1 = Polynom({1, 1});

        auto p2 = Polynom(7);

        auto result = p1 + p2;

        auto vector_str = result.to_vector_str();

        CHECK_EQ(vector_str, "(2, 2, 1)");

        Polynom a = Polynom({1, 1, 1});
        Polynom b = Polynom({0, 1, 0});

        Polynom c = a + b;

        CHECK(c.get_coefficient(0) == 1);
        CHECK(c.get_coefficient(1) == 2);

        Polynom d = Polynom({0, 0, 0, 1});

        Polynom e = a + d;

        CHECK(e.get_coefficient(3) == 1);
    }

    TEST_CASE("Polynom multiplication") {
        Polynom a = Polynom({0, 0, 2});
        Polynom b = Polynom({2, 1, 1});

        Polynom c = (a * b);

        CHECK_EQ(c.to_vector_str(), "(0, 0, 4, 2, 2)");
    }

    TEST_CASE("Polynom multiplication with integer") {
        Polynom result = Polynom({0, 0, -2});

        Polynom a = Polynom({0, 0, 2});

        Polynom f = a * -1;

        // Testet nicht das komplette Ergebins @Dennis mag ich net ....
        CHECK(f.get_coefficient(2) == -2);

        // Entweder mit deinem == operator
        CHECK(f == result);

        // Oder mit String-Vergleichen...
        CHECK_EQ(f.to_vector_str(), "(0, 0, -2)");

        auto p2 = a * 1;

        CHECK(a == p2);

        auto p3 = a * 0;

        CHECK(p3.to_vector_str() == "(0)");
    }

    TEST_CASE("Polynom modolo integer") {
        Polynom a = Polynom({3, 1, 2});
        Polynom b = Polynom({9, 4, 11});

        auto result = a % 2;

        CHECK_EQ(result.to_vector_str(), "(1, 1)");

        result = b % 3;

        CHECK_EQ(result.to_vector_str(), "(0, 1, 2)");
    }

    TEST_CASE("Polynom modolo integer fuzzy") {

        for (int i = 1; i < 1000; ++i) {

            auto a = Polynom(i);
            auto b = Polynom(i + 1);

            auto classToTest = (a + b) % 2;

            for (const auto &item : classToTest.get_coefficients()) {
                CHECK_LT(item, 2);
            }
        }
    }
}