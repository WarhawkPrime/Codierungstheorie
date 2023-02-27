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

    /*
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
    */

    TEST_CASE("Transform Matrix(4x3) to canonical form via gauss")
    {
        const std::vector<Polynom> values = {
                Polynom(4),
                Polynom(1),
                Polynom(3)
                };

        auto mat = Matrix(3, 4, values);

        std::cout << "orig g: " << std::endl;
        std::cout << mat.to_vector_str() << std::endl;

        const auto expected = Matrix(3, 3, std::vector<Polynom>({Polynom(1), Polynom(2), Polynom(4)}));

        auto res = mat.to_canonical_via_GJE();

        std::cout << "canonical g" << std::endl;
        std::cout << res.to_vector_str() << std::endl;

        CHECK(res.to_vector_str() == expected.to_vector_str());
    }


    /*
    TEST_CASE("Transform matrix to Transpose Matrix")
    {
        const std::vector<Polynom> values = {
                Polynom(4),
                Polynom(1),
                Polynom(3),
                Polynom(2)};

        auto mat = Matrix(4, 3, values);

        std::cout << "orig g: " << std::endl;
        std::cout << mat.to_vector_str() << std::endl;

        auto transpose_mat = mat.transpose();

        std::cout << "transpose: " << std::endl;
        std::cout << transpose_mat.to_vector_str() << std::endl;

        // not correct for the size of the matrix.
        const auto expected = Matrix(3, 4, std::vector<Polynom>({Polynom(6), Polynom(3), Polynom(8)}));

        std::cout << "expected: " << std::endl;
        std::cout << expected.to_vector_str() << std::endl;

        CHECK(transpose_mat.to_vector_str() == expected.to_vector_str());
    }
    */


    TEST_CASE("Transform Canonical Generatormatrix to Controlmatrix")
    {
        //Matrix generatormatrix = Matrix(3, 3, std::vector<Polynom>({Polynom(1), Polynom(2), Polynom(4)}));

        const std::vector<Polynom> values = {
                Polynom(4),
                Polynom(1),
                Polynom(3),
                Polynom(2)};

        auto generatormatrix = Matrix(4, 3, values);

        std::cout << "generatormatrix: " << std::endl;
        std::cout << generatormatrix.to_vector_str() << std::endl;

        Matrix controlmatrix = generatormatrix.to_control_matrix();

        std::cout << "control matrix: " << std::endl;
        std::cout << controlmatrix.to_vector_str() << std::endl;
        std::cout << "t" << std::endl;
    }

}
