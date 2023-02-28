//
// Created by Noah Ruben on 10.01.23.
//
#include "Header Files/Matrix.h"
#include "doctest.h"

TEST_SUITE("Matrix tests" * doctest::description("egf")) {
    TEST_CASE("Transform Matrix(3x3) to canonical form") {
        const std::vector<Polynom> values = {
            Polynom(4),
            Polynom(1),
            Polynom(2)};

        auto mat = Matrix(3, 3, values);

        auto can = mat.to_canonical_via_GJE();

        const auto expected = Matrix(3, 3, std::vector<Polynom>({Polynom(1), Polynom(2), Polynom(4)}));

        CHECK(can.to_vector_str() == expected.to_vector_str());
    }

    TEST_CASE("Transform Matrix(4x3) to canonical form via gauss") {
        const std::vector<Polynom> values = {
            Polynom(4),
            Polynom(1),
            Polynom(3),
            Polynom(2)};

        auto mat = Matrix(4, 3, values);

        const auto expected = Matrix(3, 3, std::vector<Polynom>({Polynom(1), Polynom(2), Polynom(4)}));

        auto res = mat.to_canonical_via_GJE();

        CHECK(res.to_vector_str() == expected.to_vector_str());
    }

    TEST_CASE("Transform Matrix example to canonical form via gauss") {
        const std::vector<Polynom> values = {
            Polynom({0, 0, 0, 0, 0, 0}, false),
            Polynom({0, 1, 0, 1, 0, 1}, false),
            Polynom({1, 0, 1, 0, 1, 0}, false),
            Polynom({1, 1, 1, 1, 1, 1}, false)};

        auto mat = Matrix(values);

        const auto expected = Matrix({Polynom({1, 0, 1, 0, 1, 0}, false),
                                      Polynom({0, 1, 0, 1, 0, 1}, false)});

        auto res = mat.to_canonical_via_GJE();

        CHECK(res.to_vector_str() == expected.to_vector_str());
    }

    TEST_CASE("Transform Matrix(4x3) to canonical (3x2) form") {
        const std::vector<Polynom> values = {
            Polynom({0, 1, 1}, false),
            Polynom({1, 0, 0}, false),
            Polynom({0, 0, 0}, false),
            Polynom({0, 0, 0}, false)};

        auto mat = Matrix(4, 3, values);

        auto can = mat.to_canonical_via_GJE();

        const std::vector<Polynom> expected_values = {
            Polynom({1, 0, 0}, false),
            Polynom({0, 1, 1}, false)};
        const auto expected = Matrix(expected_values);

        CHECK(can.to_vector_str() == expected.to_vector_str());
    }

    TEST_CASE("Transform Matrix to canonical form") {

        std::vector<Polynom> values = {
            Polynom({1, 0, 0, 0}, false),
            Polynom({0, 1, 0, 0}, false),
            Polynom({1, 0, 0, 0}, false),
            Polynom({0, 1, 0, 0}, false),
            Polynom({1, 0, 0, 0}, false),
            Polynom({0, 1, 1, 0}, false),
            Polynom({0, 1, 0, 0}, false),
            Polynom({0, 1, 0, 1}, false)};

        auto mat = Matrix(8, 4, values);

        auto res = mat.to_canonical_via_GJE();

        std::vector<Polynom> expected_values = {
            Polynom({1, 0, 0, 0}, false),
            Polynom({0, 1, 0, 0}, false),
            Polynom({0, 0, 1, 0}, false),
            Polynom({0, 0, 0, 1}, false)};

        const auto expected = Matrix(expected_values);

        CHECK(res.to_vector_str() == expected.to_vector_str());
    }

    TEST_CASE("Transform generator Matrix to control matrix") {
        const std::vector<Polynom> values = {
            Polynom({1, 1, 0, 1, 0}, false),
            Polynom({1, 0, 1, 0, 1}, false)};

        auto mat = Matrix(values);

        const auto expected = Matrix({Polynom({1, 0, 0, 1, 1}, false),
                                      Polynom({0, 1, 0, 1, 0}, false),
                                      Polynom({0, 0, 1, 0, 1}, false)});

        auto gen = mat.to_canonical_via_GJE();

        auto control_matrix = gen.to_control_matrix();

        CHECK(control_matrix.to_vector_str() == expected.to_vector_str());
    }
}
