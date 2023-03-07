//
// Created by Admin on 06.03.2023.
//

#ifndef CODIERUNGSTHEORIE_REEDSOLOMONCODE_H
#define CODIERUNGSTHEORIE_REEDSOLOMONCODE_H

#include "Header Files/CodierungAblauf/Code.h"
#include "Header Files/Matrix.h"
#include "Header Files/Task_6/Gruppe.h"

void sep(std::string str);

class ReedSolomonCode : public Code {
  public:
    int e;
    int q;
    Polynom decode(Polynom codeword) const override;
    Polynom encode(Polynom msg) const override;

  private:
    Gruppe gruppe;
    int alpha;
    Polynom generator_polynomial = Polynom(0);
    Polynom control_polynomial = Polynom(0);
    Matrix *control_matrix = new Matrix(0, 0);   // DAS IST DOCH DUMM UND MUSS ANDERS GEHEN
    Matrix *generator_matrix = new Matrix(0, 0); // DAS IST DOCH DUMM UND MUSS ANDERS GEHEN

    void fill_generator_matrix();
    void fill_control_matrix();

  public:
    explicit ReedSolomonCode(int e, int _d, Gruppe &gruppe);
    /**
     * Achtung diese Polynome sind normale Polynome mit p = 10
     * @returns die Paramenter ... CPP kram
     */
    void calculate_generator_and_control_polynomial(Polynom &generator_polynomial, Polynom &control_polynomial);
    void fill_generator_and_control_matrix();
};

#endif // CODIERUNGSTHEORIE_REEDSOLOMONCODE_H
