//
// Created by Noah Ruben on 10.01.23.
//

#include "Header Files/Matrix.h"
#include "Header Files/Polynom.h"
#include <iostream>

std::vector<Polynom> values = {
    Polynom({1, 0, 0, 0}, false),
    Polynom({0, 1, 0, 0}, false),
    Polynom({1, 0, 0, 0}, false),
    Polynom({0, 1, 0, 0}, false),
    Polynom({1, 0, 0, 0}, false),
    Polynom({0, 1, 1, 0}, false),
    Polynom({0, 1, 0, 0}, false),
    Polynom({0, 1, 0, 1}, false)};
// 1. Implementieren Sie ein Routine, welche bei Eingabe einer Generatormatrix die kanonische Generatormatrix erzeugt.
/*
void sub_task_1() {
    auto matrix = Matrix(values);
    std::cout << "Original Matrix:" << std::endl
              << matrix.to_vector_str() << std::endl
              << std::endl;

    //matrix.to_canonical_form();
    auto gen = matrix.to_canonical_via_GJE();

    std::cout << std::endl
              << std::endl
              << "Matrix after Gaussian elimination:" << std::endl;
    std::cout << matrix.to_vector_str() << std::endl;
}
 */
// 2. Implementieren Sie eine Routine, welche aus einer kanonischen Generatormatrix eine Kontrollmatrix generiert.
void sub_task_2() {
    std::vector<Polynom> values_gen = {
        Polynom({1, 0, 1, 1}, false),
        Polynom({0, 1, 1, 0}, false)};

    auto matrix_gen = Matrix(values_gen);

    auto matrix_trans = matrix_gen.transpose();
    std::cout << matrix_trans.to_vector_str();

    auto matrix_con = matrix_gen.to_control_matrix();
    std::cout << matrix_con.to_vector_str();
}
// 3. Implementieren Sie eine Routine, welche die Syndromtabelle erzeugt.
void sub_task_3() {
    const auto control = Matrix({
                                        Polynom({1, 0, 1}, false),
                                        Polynom({1, 1, 1}, false),
                                        Polynom({1, 0, 0}, false),
                                        Polynom({0, 1, 0}, false),
                                        Polynom({0, 0, 1}, false),
                                });


    MXA::Syndrom_table s = MXA::create_syndrom_table(control);

    /*
    for (auto const& [syndrom, error] : s.syndrom_table )
    {
        std::cout << "syndrom: " << syndrom->to_vector_str() << " error: " << error->to_vector_str() << std::endl;
    }
     */
}



// 4. Implementieren Sie eine Routine, welche die Fehlerkorrektur mittels Maximum-Likelihood-Decodierung und Syndromtabelle durchführt.
void sub_task_4() {

    // generator matrix
    /*
    const std::vector<Polynom> values = {
            Polynom({1, 0, 1, 0, 1}, false),
            Polynom({0, 1, 1, 1, 1}, false)};
    auto mat = Matrix(values);

    // canonical generator matrix
    auto gen = mat.to_canonical_via_GJE();
    */

    // control matrix
    //auto parity_check_matrix = gen.to_control_matrix();

    //0000000000000000

    std::vector<Polynom> v1 = {
            Polynom({0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1}, false),
            Polynom({0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1}, false),
            Polynom({0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0}, false),
            Polynom({1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0}, false)};

    auto v2 = v1;
    auto v3 = v1;


    /*
    std::vector<Polynom> v1 = {
            Polynom({0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1}, false),
            Polynom({0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1}, false),
            Polynom({0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1}, false),
            Polynom({1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0}, false)};
    */

    std::cout << "0" << std::endl;

    auto parity_check_matrix = Matrix(v1);
    //0000000000000000

    std::cout << "h" << std::endl;

    // transposed control matrix
    auto transpose_parity_check_matrix = parity_check_matrix.transpose();

    std::cout << "transpose: " << std::endl;
    std::cout << transpose_parity_check_matrix.to_vector_str() << std::endl;

    // create syndrom table
    MXA::Syndrom_table syndrom_table = MXA::create_syndrom_table(transpose_parity_check_matrix);

    // codeword 1 0 1 0 1 with error 0 0 0 0 1
    //auto codeword_with_error = Polynom({1, 0, 1, 0, 0});
    auto codeword_with_error = Polynom({0, 1, 0, 0, 0, 0, 1, 1});

    auto corrected_codeword = correct_codeword(codeword_with_error, syndrom_table);

    std::cout << " codeword with error: " << codeword_with_error.to_vector_str() << std::endl;
    std::cout << " corrected codeword : " << corrected_codeword.to_vector_str() << std::endl;
}


int main(int argc, char **argv) {
    //sub_task_1();
    //sub_task_2();
    sub_task_3();
    //sub_task_4();
    std::cout << " it just works " << std::endl;

}