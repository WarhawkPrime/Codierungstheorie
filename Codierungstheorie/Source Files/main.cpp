
#include "Header Files/CodierungAblauf/CodierungsAblauf.h"
#include "Header Files/CodierungAblauf/HammingCode.h"
#include "Header Files/CodierungAblauf/VariableErrorKanal.h"
#include "Header Files/ModularPolynomArithmetic.h"
#include <memory>

int main(int argc, char **argv) {

    std::cout << Polynom(5, false).to_print_string(Polynom::vector) << std::endl;

    auto msg = 0b101;

    auto ablauf = CodierungsAblauf();
    ablauf.message = "Hello World!";

    ablauf.kanal = new VariableErrorKanal(1);
    auto code = new HammingCode(3);
    Matrix &controlMatrix = code->control_matrix;
    Matrix &generatorMatrix = code->generator_matrix;
    std::cout << "H  M: " << controlMatrix.to_vector_str() << std::endl;

    std::cout << "G  M: " << generatorMatrix.to_vector_str() << std::endl;

    std::cout << "H2 M: " << generatorMatrix.to_control_matrix().to_vector_str() << std::endl;
    ablauf.code = code;

    auto enc = MXA::polynom_matrix_multiplication(Polynom(5), generatorMatrix).values[0];

    std::cout << "enc M: " << enc.to_vector_str() << std::endl;

    auto dec = MXA::polynom_matrix_multiplication(enc, controlMatrix.transpose()).values[0];

    std::cout << "dec M: " << dec.to_vector_str() << std::endl;

    // ablauf.run();
}
