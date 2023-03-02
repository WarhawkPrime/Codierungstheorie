//
// Created by Noah Ruben on 01.03.23.
//

#ifndef CODIERUNGSTHEORIE_HAMMINGCODE_H
#define CODIERUNGSTHEORIE_HAMMINGCODE_H

#include "Code.h"

class HammingCode : public Code {
  public:
    const int m;
    explicit HammingCode(const int m);

    // Weil d imm 3 ist generator matrix mit 2 lin. unabhängigen Vektoren
    void create_generator_matrix();

  private:
    const int calculate_N() {
        return 8;
    }
};

#endif // CODIERUNGSTHEORIE_HAMMINGCODE_H
