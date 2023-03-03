//
// Created by Noah Ruben on 01.03.23.
//

#ifndef CODIERUNGSTHEORIE_HAMMINGCODE_H
#define CODIERUNGSTHEORIE_HAMMINGCODE_H

#include "Code.h"
#include "Header Files/Matrix.h"

class HammingCode : public Code {
  public:
    const int m;
    const int d = 3;
    const int q = 2;
    explicit HammingCode(const int m);

    // Weil d imm 3 ist generator matrix mit min 2 lin. unabhängigen Vektoren deshalb m >=3
    Matrix create_control_matrix();
    Polynom decode(Polynom codeword) const override;
    Polynom encode(Polynom msg) const override;
    Matrix control_matrix;
    Matrix generator_matrix;

    MXA::Syndrom_table syndrom_table;

  private:
    const int calculate_N(int _m) const {
        return pow(2, _m) - 1;
    }
    const int calculate_K(int _m) const {
        return pow(2, _m) - 1;
    }
};

#endif // CODIERUNGSTHEORIE_HAMMINGCODE_H
