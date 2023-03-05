
#include "Header Files/CodierungAblauf/CodierungsAblauf.h"
#include "Header Files/CodierungAblauf/HammingCode.h"
#include "Header Files/CodierungAblauf/VariableErrorKanal.h"
#include "Header Files/CodierungAblauf/ReedMueller.h"
#include "Header Files/ModularPolynomArithmetic.h"
#include <memory>

int main(int argc, char **argv) {
    auto ablauf = CodierungsAblauf();
    ablauf.message = "Hello World!";

    ablauf.kanal = new VariableErrorKanal(1);
    // ablauf.kanal = new NoErrorKanal();

    auto code = new HammingCode(4);

    // need reed mueller with d=3, q=2
    // d=2^(m-r)
    // msg length must be 8. n=8. n=2^m = 2^3
    // RM(r, m)
    //

    // reed mueller cant generate the code c(8,4,3,2)
    //auto code = new ReedMueller(3, 3);

    ablauf.code = code;

    const Matrix &controlMatrix = code->control_matrix;
    const Matrix &generatorMatrix = code->generator_matrix;

        std::cout << "H  M: " << controlMatrix.to_vector_str() << std::endl;

        std::cout << "G  M: " << generatorMatrix.to_vector_str() << std::endl;

        std::cout << "HT M: " << controlMatrix.transpose().to_rows_as_numbers_str() << std::endl;

     auto msg = Polynom(0b00001100101 /*0b1101*/, false);

     auto enc = MXA::matrix_matrix_multiplication(Matrix({msg}), generatorMatrix).values[0];
     auto enc2 = code->encode(msg);
     std::cout << "enc V: " << enc.to_vector_str() << std::endl;
     std::cout << "enc2V: " << std::bitset<16>(enc2.as_int()) << std::endl;

     auto syn = MXA::matrix_matrix_multiplication(Matrix({Polynom(0b110100001101100)}), controlMatrix.transpose()).values[0];
     std::cout << "syn V: " << syn.as_int() << std::endl;

     std::cout << (char)(0b110100001101100 ^ 0b000000000000100) << std::endl;
        for (const auto &item : code->syndrom_table.syndrom_table) {
            std::cout << "Syn: " << item.first.get()->values[0].as_int() << std::endl;
            std::cout << "Err: " << item.second.get()->as_int() << std::endl
                      << std::endl;
        }

    ablauf.run();
}
