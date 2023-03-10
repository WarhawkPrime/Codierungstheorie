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
    Polynom POLY_MUL(const Polynom &a, const Polynom &b) const;
    int POW(int a, int e) const;

    Gruppe(int q, const std::vector<std::vector<int>> &addTable, const std::vector<std::vector<int>> &mulTable, const std::vector<int> &elements);

  private:
    int find_primitive() const;
    const std::vector<std::vector<int>> mul_table;
    const std::vector<std::vector<int>> add_table;
};

#endif // CODIERUNGSTHEORIE_GRUPPE_H
