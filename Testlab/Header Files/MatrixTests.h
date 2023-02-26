//
// Created by Noah Ruben on 10.01.23.
//
#include "Header Files/Matrix.h"
#include "doctest.h"

TEST_SUITE("Matrix tests" * doctest::description("egf")) {
    TEST_CASE("Transform Matrix(3x3) to canonical form") {
        const std::vector<Polynom> values = {Polynom(4), Polynom(1), Polynom(2)};

        auto mat = Matrix(3, 3, values);

        mat.to_canonical_form();

        const auto expected = Matrix(3, 3, std::vector<Polynom>({Polynom(1), Polynom(2), Polynom(4)}));

        CHECK(mat.to_vector_str() == expected.to_vector_str());
    }

    TEST_CASE("Transform Matrix(4x3) to canonical form via gauss")
    {
        const std::vector<Polynom> values = {
                Polynom(4),
                Polynom(1),
                Polynom(3),
                Polynom(2)};

        auto mat = Matrix(4, 3, values);

        std::cout << "orig g: " << std::endl;
        std::cout << mat.to_vector_str() << std::endl;

        const auto expected = Matrix(3, 3, std::vector<Polynom>({Polynom(1), Polynom(2), Polynom(4)}));

        auto res = mat.to_canonical_via_GJE();

        std::cout << "canonical g" << std::endl;
        std::cout << res.to_vector_str() << std::endl;

        CHECK(res.to_vector_str() == expected.to_vector_str());
    }
}
