//
// Created by Noah Ruben on 07.03.2023.
//

#ifndef CODIERUNGSTHEORIE_GRUPPE_H
#define CODIERUNGSTHEORIE_GRUPPE_H

#include "Header Files/Polynom.h"
#include <vector>

class Gruppe {
  public:
    const int q;
    int primitive;
    const std::vector<int> elements;

    int ADD(int a, int b) const;
    int MUL(int a, int b) const;
    Polynom POLY_MUL(Polynom &a, Polynom &b) const;
    int POW(int a, int e) const;

    Gruppe(int q, const std::vector<std::vector<int>> &addTable, const std::vector<std::vector<int>> &mulTable, const std::vector<int> &elements);

    /**
     * Achtung diese Polynome sind normale Polynome mit p = 10
     * @returns die Paramenter ... CPP kram
     */
    void calculate_generator_and_control_polynomial(int d, Polynom &generator_polynomial, Polynom &control_polynomial);

  private:
    int find_primitive() const;
    const std::vector<std::vector<int>> mul_table;
    const std::vector<std::vector<int>> add_table;
};

#endif // CODIERUNGSTHEORIE_GRUPPE_H