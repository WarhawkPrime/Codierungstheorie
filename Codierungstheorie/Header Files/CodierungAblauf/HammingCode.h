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
    explicit HammingCode(const int m);

    // Weil d imm 3 ist generator matrix mit 2 lin. unabhängigen Vektoren
    Matrix create_control_matrix();
    Polynom decode(Polynom codeword) const override;
    Polynom encode(Polynom msg) const override;
    Matrix control_matrix;
    Matrix generator_matrix;

  private:
    const int calculate_N() const {
        return pow(2, m) - 1;
    }
};

#endif // CODIERUNGSTHEORIE_HAMMINGCODE_H
