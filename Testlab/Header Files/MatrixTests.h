//
// Created by Noah Ruben on 10.01.23.
//
//#include "Header Files/Matrix.h"
#include "Header Files/CodierungAblauf/CodierungsAblauf.h"
#include "Header Files/CodierungAblauf/VariableErrorKanal.h"
#include "Header Files/CodierungAblauf/ReedMueller.h"
//#include "Header Files/SyndromTable.h"
#include "doctest.h"

TEST_SUITE("Matrix tests" * doctest::description("egf")) {

    TEST_CASE("Transpose Matrix and back") {

        const auto control = Matrix({
            Polynom({1, 0, 1}, false),
            Polynom({1, 1, 1}, false),
            Polynom({1, 0, 0}, false),
            Polynom({0, 1, 0}, false),
            Polynom({0, 0, 1}, false),
        });

        auto transpose = control.transpose();
        auto orig = transpose.transpose();

        CHECK(orig.to_vector_str() == control.to_vector_str());
    }

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

    TEST_CASE("polynom x matrix error recognition test") {
        const auto Control = Matrix({
            Polynom({1, 0, 1}, false),
            Polynom({1, 1, 1}, false),
            Polynom({1, 0, 0}, false),
            Polynom({0, 1, 0}, false),
            Polynom({0, 0, 1}, false),
        });

        auto e0 = Polynom({0, 0, 0, 0, 0}, false);
        auto e1 = Polynom({1, 0, 0, 0, 0}, false);
        auto e2 = Polynom({0, 1, 0, 0, 0}, false);
        auto e3 = Polynom({0, 0, 0, 0, 1}, false);

        auto res = MXA::polynom_matrix_multiplication(e1, Control);
        auto res1 = MXA::polynom_matrix_multiplication(e2, Control);
        auto res3 = MXA::polynom_matrix_multiplication(e3, Control);

        auto exp = Matrix({Polynom({0, 0, 1}, false)});

        auto exp1 = Matrix({Polynom({0, 1, 0}, false)});

        auto exp3 = Matrix({Polynom({1, 0, 1}, false)});

        CHECK(exp.to_vector_str() == res.to_vector_str());
        CHECK(exp1.to_vector_str() == res1.to_vector_str());
        CHECK(exp3.to_vector_str() == res3.to_vector_str());
    }

    TEST_CASE("Generator and Control Matrix multiplication") {
        const std::vector<Polynom> values = {
            Polynom({1, 0, 1, 0, 1}, false),
            Polynom({0, 1, 1, 1, 1}, false)};
        auto mat = Matrix(values);

        auto gen = mat.to_canonical_via_GJE();

        auto control_matrix = gen.to_control_matrix();

        auto transpose = control_matrix.transpose();

        auto res = MXA::matrix_matrix_multiplication(mat, transpose);

        const auto expected = Matrix({Polynom({0, 0, 0}, false),
                                      Polynom({0, 0, 0}, false)});

        CHECK(res.to_vector_str() == expected.to_vector_str());
    }

    TEST_CASE("Syndrom Table") {

        const auto Control = Matrix({
            Polynom({1, 0, 1}, false),
            Polynom({1, 1, 1}, false),
            Polynom({1, 0, 0}, false),
            Polynom({0, 1, 0}, false),
            Polynom({0, 0, 1}, false),
        });

        // MXA::Syndrom_table s = MXA::create_syndrom_table(std::make_shared<Matrix>(Control));

        // CHECK(s.syndrom_table.size() == 8);

        std::vector<int> coeffs = {1, 0, 1};
        auto pol = Polynom(coeffs);
        auto syndrom = Matrix({pol});

        std::vector<int> coeffs1 = {0, 0, 1};
        auto syndrom_1 = Matrix({Polynom(coeffs1)});

        // CHECK( (s.syndrom_table.find(std::make_shared<Matrix>(syndrom)) != s.syndrom_table.end()) == true);
        // CHECK( (s.syndrom_table.find(std::make_shared<Matrix>(syndrom_1)) != s.syndrom_table.end()) == true);
    }

    // @TODO Dennis
    TEST_CASE("Code correction") {
        const auto Control = Matrix({
            Polynom({1, 0, 1}, false),
            Polynom({1, 1, 1}, false),
            Polynom({1, 0, 0}, false),
            Polynom({0, 1, 0}, false),
            Polynom({0, 0, 1}, false),
        });

        // MXA::Syndrom_table s = MXA::create_syndrom_table(std::make_shared<Matrix>(Control));

        // error: 00000
        auto p1 = Polynom({1, 1, 1, 1, 0});
        auto ex1 = Polynom({1, 1, 1, 1, 0});
        // error: 00010
        auto p2 = Polynom({1, 0, 1, 1, 0});
        auto ex2 = Polynom({1, 1, 1, 1, 0});
        // error: 00001
        auto p3 = Polynom({1, 0, 1, 0, 0});
        auto ex3 = Polynom({1, 0, 1, 0, 1});

        // auto correction_p1 = MXA::correct_codeword(p1, s);
        // CHECK(ex1.to_vector_str() == correction_p1.to_vector_str());

        // auto correction_p2 = MXA::correct_codeword(p2, s);
        // CHECK(ex2.to_vector_str() == correction_p2.to_vector_str());

        // auto correction_p3 = MXA::correct_codeword(p3, s);
        // CHECK(ex3.to_vector_str() == correction_p3.to_vector_str());
    }

    TEST_CASE("syndrom t")
    {


        const auto Control = Matrix({
                                            Polynom({1, 0, 1}, false),
                                            Polynom({1, 1, 1}, false),
                                            Polynom({1, 0, 0}, false),
                                            Polynom({0, 1, 0}, false),
                                            Polynom({0, 0, 1}, false),
                                    });


        MXA::SyndromTable sy = MXA::SyndromTable(Control);

        auto p3 = Polynom({1, 0, 1, 0, 0});
        auto res = sy.corr_codeword(p3);

        auto ex3 = Polynom({1, 0, 1, 0, 1});

        std::cout << "exp: " << std::endl;
        std::cout << ex3.to_vector_str() << std::endl;

        std::cout << "res: " << std::endl;
        std::cout << res.to_vector_str() << std::endl;
    }

    TEST_CASE("mld syndrom")
    {
        const auto Control = Matrix({
                                            Polynom({1, 0, 1}, false),
                                            Polynom({1, 1, 1}, false),
                                            Polynom({1, 0, 0}, false),
                                            Polynom({0, 1, 0}, false),
                                            Polynom({0, 0, 1}, false),
                                    });


        MXA::SyndromTable sy = MXA::SyndromTable(Control);

        auto p3 = Polynom({1, 0, 1, 0, 0});
        auto ex3 = Polynom({1, 0, 1, 0, 1});

        auto corrected =  maximum_likelihood_detection(p3, Control, sy);


        std::cout << "exp: " << std::endl;
        std::cout << ex3.to_vector_str() << std::endl;

        std::cout << "res: " << std::endl;
        std::cout << corrected.to_vector_str() << std::endl;

    }

    TEST_CASE("RM")
    {
        // for R(m-2,m) -> n,k,d,q -> 2^m, 2^m -1 -m, 4,2
        // 2,4 -> n,k,d,q -> 16, 11,4,2
        auto m = ReedMueller(1, 5);
        std::cout << "m: " << std::endl;
        std::cout << m.generator_matrix.to_vector_str() << std::endl;

        /*
        auto ablauf = CodierungsAblauf();
        ablauf.message = "Hello World!";

        ablauf.kanal = new VariableErrorKanal(1);

        auto code = new ReedMueller(2,4);
        ablauf.code = code;

        ablauf.run();

        const Matrix &controlMatrix = code->control_matrix;
        const Matrix &generatorMatrix = code->generator_matrix;

        std::cout << "H  M: " << std::endl
                  << controlMatrix.to_vector_str() << std::endl;
        std::cout << "G  M: " << std::endl
                  << generatorMatrix.to_vector_str() << std::endl;

        delete ablauf.kanal;
        delete code;
         */
    }
}

// TODO @Dennis
/*TEST_CASE("Transform Matrix to canonical form") {

    std::vector<Polynom> values = {
        Polynom({1, 1, 0, 1, 0, 0, 1}, false),
        Polynom({0, 0, 1, 1, 1, 0, 0}, false),
        Polynom({0, 0, 0, 0, 0, 1, 1}, false)};

    auto mat = Matrix(values);

    auto res = mat.to_canonical_via_GJE();

    std::vector<Polynom> expected_values = {
        Polynom({1, 1, 0, 1, 0, 0, 1}, false),
        Polynom({0, 0, 1, 1, 1, 0, 0}, false),
        Polynom({0, 0, 0, 0, 0, 1, 1}, false)};

    const auto expected = Matrix(expected_values);

    CHECK(res.to_vector_str() == expected.to_vector_str());
}*/
