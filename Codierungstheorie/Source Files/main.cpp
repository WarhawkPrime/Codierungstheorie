
#include "Header Files/CodierungAblauf/CodierungsAblauf.h"
#include "Header Files/CodierungAblauf/HammingCode.h"
#include "Header Files/CodierungAblauf/VariableErrorKanal.h"
#include "Header Files/ModularPolynomArithmetic.h"
#include <memory>

int main(int argc, char **argv) {

    std::cout << Polynom(5, false).to_print_string(Polynom::vector) << std::endl;

    auto ablauf = CodierungsAblauf();
    ablauf.message = "Hello World!";

    ablauf.kanal = new VariableErrorKanal(1);
    auto code = new HammingCode(3);
    ablauf.code = code;
    const Matrix &controlMatrix = code->control_matrix;
    const Matrix &generatorMatrix = code->generator_matrix;
    std::cout << "H  M: " << controlMatrix.to_vector_str() << std::endl;

    std::cout << "G  M: " << generatorMatrix.to_vector_str() << std::endl;

    std::cout << "HT M: " << controlMatrix.transpose().to_vector_str() << std::endl;

    auto msg = Polynom(/*0b0000110001*/ 0b1101, false);
    //    auto enc = MXA::polynom_matrix_multiplication(msg, generatorMatrix).values[0];
    auto enc = MXA::matrix_matrix_multiplication(Matrix({msg}), generatorMatrix).values[0];

    std::cout
        << "enc V: 000010000110001" << std::endl;

    std::cout << "enc V: " << enc.to_vector_str() << std::endl;

    auto syn = MXA::matrix_matrix_multiplication(Matrix({enc}), controlMatrix.transpose()).values[0];

    std::cout << "syn V: " << syn.to_vector_str() << std::endl;

    // ablauf.run();
}
