//
// Created by Noah Ruben on 10.01.23.
//
#include "Header Files/Matrix.h"
#include "doctest.h"

TEST_SUITE("Matrix tests" * doctest::description("egf")) {
    TEST_CASE("Transform Matrix(3x3) to canonical form") {
        const std::vector<Polynom> values = {
            Polynom(4, false),
            Polynom(1, false),
            Polynom(2, false)};

        auto mat = Matrix(values);

        mat.to_canonical_form();

        // clang-format on
        std::vector<Polynom> expected_values = {
            Polynom(1, false),
            Polynom(2, false),
            Polynom(4, false)};
        // clang-format off

        const auto expected = Matrix(expected_values);

        CHECK(mat.to_vector_str() == expected.to_vector_str());
    }

    TEST_CASE("Transform Matrix(4x3) to canonical form") {
        const std::vector<Polynom> values = {
            Polynom({0, 1, 1}, false),
            Polynom({1, 0, 0}, false),
            Polynom({0, 0, 0}, false),
            Polynom({0, 0, 0}, false)};

        auto mat = Matrix(4, 3, values);

        mat.to_canonical_form();

        const std::vector<Polynom> expected_values = {
            Polynom({1, 0, 0}, false),
            Polynom({0, 1, 1}, false),
            Polynom({0, 0, 0}, false),
            Polynom({0, 0, 0}, false)};
        const auto expected = Matrix(expected_values);

        CHECK(mat.to_vector_str() == expected.to_vector_str());
    }

    TEST_CASE("Transform Matrix(4x3) to canonical form") {

        std::vector<Polynom> values = {
            Polynom({1, 0, 0, 0}, false),
            Polynom({0, 1, 0, 0}, false),
            Polynom({1, 0, 0, 0}, false),
            Polynom({0, 1, 0, 0}, false),
            Polynom({1, 0, 0, 0}, false),
            Polynom({0, 1, 1, 0}, false),
            Polynom({0, 1, 0, 0}, false),
            Polynom({0, 1, 0, 1}, false)};

        auto mat = Matrix(values);
        mat.to_canonical_form();

        std::vector<Polynom> expected_values = {
            Polynom({1, 0, 0, 0}, false),
            Polynom({0, 1, 0, 0}, false),
            Polynom({0, 0, 1, 0}, false),
            Polynom({0, 0, 0, 1}, false),
            Polynom({0, 0, 0, 0}, false),
            Polynom({0, 0, 0, 0}, false),
            Polynom({0, 0, 0, 0}, false),
            Polynom({0, 0, 0, 0}, false)};

        const auto expected = Matrix(expected_values);

        CHECK(mat.to_vector_str() == expected.to_vector_str());
    }
}
