//
// Created by Noah Ruben on 10.01.23.
//

#include "Header Files/Matrix.h"
#include "Header Files/doctest.h"

int compare_canonical(Polynom &a, Polynom &b) {
    for (int i = 0; i < a.get_degree(); ++i) {
        auto a_coeff = a.get_coefficient(i);
        auto b_coeff = b.get_coefficient(i);

        if (a_coeff == b_coeff)
            continue;
        if (a_coeff > b_coeff)
            return -1;
        if (a_coeff < b_coeff)
            return 1;
    }
    return 0;
}

// Not just sort but use the Gauss-Jordan-elimination
void Matrix::to_canonical_form() {
    for (auto &item_a : values) {
        for (auto &item_b : values) {
            if (compare_canonical(item_a, item_b) <= 0) {
                std::swap(item_a, item_b);
            }
        }
    }
}
std::string Matrix::to_vector_str() const {
    auto result = std::string();
    for (const auto &item : values) {
        result.append(item.to_vector_str(cols)).append("\n");
    }
    return result;
}
