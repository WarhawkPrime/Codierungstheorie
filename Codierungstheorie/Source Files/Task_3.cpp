//
// Created by Noah Ruben on 10.01.23.
//

#include "Header Files/Matrix.h"
#include "Header Files/Polynom.h"

// 1. Implementieren Sie ein Routine, welche bei Eingabe einer Generatormatrix die kanonische Generatormatrix erzeugt.
void sub_task_1() {
    const std::vector<Polynom> values = {Polynom(4), Polynom(1), Polynom(2)};

    auto mat = Matrix(3, 3, values);

    std::cout << mat.to_vector_str() << std::endl;

    mat.GausJordan_elimination();

    std::cout << mat.to_vector_str() << std::endl;
}
// 2. Implementieren Sie eine Routine, welche aus einer kanonischen Generatormatrix eine Kontrollmatrix generiert.
// 3. Implementieren Sie eine Routine, welche die Syndromtabelle erzeugt.
// 4. Implementieren Sie eine Routine, welche die Fehlerkorrektur mittels Maximum-Likelihood-Decodierung und Syndromtabelle durchführt.

int main(int argc, char **argv) {
    sub_task_1();
}