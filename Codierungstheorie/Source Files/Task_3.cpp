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
void sub_task_1() {
    auto matrix = Matrix(values);
    std::cout << "Original Matrix:" << std::endl
              << matrix.to_vector_str() << std::endl
              << std::endl;

    matrix.to_canonical_form();

    std::cout << std::endl
              << std::endl
              << "Matrix after Gaussian elimination:" << std::endl;
    std::cout << matrix.to_vector_str() << std::endl;
}
// 2. Implementieren Sie eine Routine, welche aus einer kanonischen Generatormatrix eine Kontrollmatrix generiert.
// 3. Implementieren Sie eine Routine, welche die Syndromtabelle erzeugt.
// 4. Implementieren Sie eine Routine, welche die Fehlerkorrektur mittels Maximum-Likelihood-Decodierung und Syndromtabelle durchführt.

int main(int argc, char **argv) {
    sub_task_1();
}

/*int main() {
    return 0;
}*/
