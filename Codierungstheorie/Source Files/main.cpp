
#include "Header Files/CodierungAblauf/CodierungsAblauf.h"
#include "Header Files/CodierungAblauf/HammingCode.h"
#include "Header Files/CodierungAblauf/VariableErrorKanal.h"
#include "Header Files/ModularPolynomArithmetic.h"
#include <memory>

int main(int argc, char **argv) {
    auto ablauf = CodierungsAblauf();
    ablauf.message = "h";

    ablauf.kanal = new VariableErrorKanal(1);

    auto code = new HammingCode(4);
    ablauf.code = code;

    const Matrix &controlMatrix = code->control_matrix;
    const Matrix &generatorMatrix = code->generator_matrix;

    //    std::cout << "H  M: " << controlMatrix.to_vector_str() << std::endl;
    //
    //    std::cout << "G  M: " << generatorMatrix.to_vector_str() << std::endl;
    //
    //    std::cout << "HT M: " << controlMatrix.transpose().to_vector_str() << std::endl;

    auto msg = Polynom(0b00001100101 /*0b1101*/, false);

    auto enc = MXA::matrix_matrix_multiplication(Matrix({msg}), generatorMatrix).values[0];
    auto enc2 = code->encode(msg);

    std::cout << "enc V: " << enc.to_vector_str() << std::endl;
    std::cout << "enc2V: " << std::bitset<16>(enc2.as_int()) << std::endl;

    auto syn = MXA::matrix_matrix_multiplication(Matrix({Polynom(enc2.as_int() + 4)}), controlMatrix.transpose()).values[0];
    std::cout << "syn V: " << syn.to_vector_str() << std::endl;

    //    for (const auto &item : code->syndrom_table.syndrom_table) {
    //        std::cout << "Syn: " << item.first.get()->values[0].as_int() << std::endl;
    //        std::cout << "Err: " << item.second.get()->as_int() << std::endl
    //                  << std::endl;
    //    }

    ablauf.run();
}
