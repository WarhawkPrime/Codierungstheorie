//
// Created by Noah Ruben on 24.11.22.
//
#include "doctest.h"

#include "Header Files/Polynom.h"

TEST_SUITE("Polynom Tests" * doctest::description("optional")) {
    TEST_CASE("Triming tests") {
        auto classToTest = Polynom({1, 1}, false);

        CHECK_EQ(classToTest.get_degree(), 1);

        std::vector<int> coeff = {0, 1, 1};
        classToTest = Polynom(coeff);

        CHECK_EQ(classToTest.get_degree(), 2);

        std::vector<int> coeff1 = {0, 1, 1};
        classToTest = Polynom(coeff1);

        CHECK_EQ(classToTest.get_degree(), 2);

        classToTest = Polynom({1, 0, 0, 0, 0});

        CHECK_EQ(classToTest.get_degree(), 0);

        classToTest = Polynom({0, 0, 1, 0, 1});

        CHECK_EQ(classToTest.get_degree(), 4);

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
        auto p1 = Polynom({1, 1}, false);

        auto p2 = Polynom(7);

        auto result = p1 + p2;

        auto vector_str = result.to_vector_str();

        CHECK_EQ(vector_str, "(2, 2, 1)");

        std::vector<int> coeff = {1, 1, 1};
        std::vector<int> coeff1 = {0, 1, 0};
        Polynom a = Polynom(coeff);
        Polynom b = Polynom(coeff1);

        Polynom c = a + b;

        CHECK(c.get_coefficient(0) == 1);
        CHECK(c.get_coefficient(1) == 2);

        Polynom d = Polynom({0, 0, 0, 1});

        Polynom e = a + d;

        CHECK(e.get_coefficient(3) == 1);
    }

    TEST_CASE("Polynom multiplication") {

        std::vector<int> coeff = {0, 0, 2};
        std::vector<int> coeff1 = {2, 1, 1};

        Polynom a = Polynom(coeff);
        Polynom b = Polynom(coeff1);

        Polynom c = (a * b);

        CHECK_EQ(c.to_vector_str(), "(0, 0, 4, 2, 2)");
    }

    TEST_CASE("Polynom multiplication with integer") {
        std::vector<int> coeff = {0, 0, -2};
        std::vector<int> coeff1 = {0, 0, 2};

        Polynom result = Polynom(coeff);
        Polynom a = Polynom(coeff1);

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

        std::vector<int> coeff = {3, 1, 2};
        std::vector<int> coeff1 = {9, 4, 11};

        Polynom a = Polynom(coeff);
        Polynom b = Polynom(coeff1);

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

    TEST_CASE("Polynom modolo polynom") {
        // Setup
        auto i_p = Polynom({1, 0, 1, 1});
        auto s = Polynom(0);
        auto r = Polynom(0);

        auto egf = EGF(2, 3, i_p);

        auto a = Polynom({0, 0, 1, 0, 1});
        egf.modular_reduction(a, r, s);

        auto result_bin = egf.polynomial_reduction_bin(a, i_p);
        std::cout << std::endl;
    }
}