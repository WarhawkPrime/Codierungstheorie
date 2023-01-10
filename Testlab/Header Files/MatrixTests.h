//
// Created by Noah Ruben on 10.01.23.
//
#include "Header Files/Matrix.h"
#include "doctest.h"

TEST_SUITE("Matrix tests" * doctest::description("egf")) {
    TEST_CASE("Transform Matrix(3x3) to canonical form") {
        const std::vector<Polynom> values = {Polynom(4), Polynom(1), Polynom(2)};

        auto mat = Matrix(3, 3, values);

        std::cout << mat.to_vector_str() << std::endl;

        mat.to_canonical_form();

        std::cout << mat.to_vector_str() << std::endl;

        const auto expected = Matrix(3, 3, std::vector<Polynom>({Polynom(1), Polynom(2), Polynom(4)}));
        std::cout << expected.to_vector_str() << std::endl;
        CHECK(mat.to_vector_str() == expected.to_vector_str());
    }

    TEST_CASE("Transform Matrix(3x3) to canonical form") {
        const std::vector<Polynom> values = {
            Polynom(4),
            Polynom(1),
            Polynom(3),
            Polynom(2)};

        auto mat = Matrix(4, 3, values);

        std::cout << mat.to_vector_str() << std::endl;

        mat.to_canonical_form();

        std::cout << mat.to_vector_str() << std::endl;

        //        const auto expected = Matrix(3, 3, std::vector<Polynom>({Polynom(1), Polynom(2), Polynom(4)}));

        //        std::cout << expected.to_vector_str() << std::endl;

        //        CHECK(mat.to_vector_str() == expected.to_vector_str());
    }
}
