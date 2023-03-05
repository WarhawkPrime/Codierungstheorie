#include "Header Files/CodierungAblauf/CodierungsAblauf.h"
#include "Header Files/CodierungAblauf/HammingCode.h"
#include "Header Files/CodierungAblauf/VariableErrorKanal.h"

int main(int argc, char **argv) {
    auto ablauf = CodierungsAblauf();
    ablauf.message = "Hello World!";

    ablauf.kanal = new VariableErrorKanal(1);

    auto code = new HammingCode(4);
    ablauf.code = code;

    ablauf.run();

    const Matrix &controlMatrix = code->control_matrix;
    const Matrix &generatorMatrix = code->generator_matrix;

    std::cout << "H  M: " << std::endl
              << controlMatrix.to_vector_str() << std::endl;
    std::cout << "G  M: " << std::endl
              << generatorMatrix.to_vector_str() << std::endl;
}