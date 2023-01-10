//
// Created by Noah Ruben on 10.01.23.
//

#ifndef CODIERUNGSTHEORIE_MATRIX_H
#define CODIERUNGSTHEORIE_MATRIX_H

#include "Polynom.h"
class Matrix {

  public:
    const int rows; // Often M
    const int cols; // Often N

    Matrix(const int rows, const int cols) : rows(rows), cols(cols), values(std::move(std::vector<Polynom>())){};
    Matrix(const int rows, const int cols, const std::vector<Polynom> &values) : rows(rows), cols(cols), values(values){};

    void to_canonical_form();

    std::string to_vector_str() const;

  private:
    std::vector<Polynom> values;
};

#endif // CODIERUNGSTHEORIE_MATRIX_H