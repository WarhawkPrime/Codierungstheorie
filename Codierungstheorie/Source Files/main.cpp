
#include "Header Files/CodierungAblauf/CodierungsAblauf.h"
#include "Header Files/CodierungAblauf/VariableErrorKanal.h"
#include "Header Files/ModularPolynomArithmetic.h"
#include <memory>

int main(int argc, char **argv) {

    auto ablauf = CodierungsAblauf();
    ablauf.message = "Hello World!";

    ablauf.kanal = new VariableErrorKanal(1);
    auto code = new PlainCode(8);
    ablauf.code = code;

    ablauf.run();
}
