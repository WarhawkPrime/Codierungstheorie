//
// Created by Noah Ruben on 01.03.23.
//

#include "Header Files/CodierungAblauf/VariableErrorKanal.h"
Polynom VariableErrorKanal::transfer(Polynom word) const {
    // std::srand(std::time(nullptr));

    auto result = Polynom(word.get_coefficients());

    for (int i = 0; i < error_per_word; ++i) {
        int random_idx = std::rand() % word.get_degree();
        int inverted_value = !word.get_coefficient(random_idx);
        result.set_coefficient(random_idx, inverted_value);
    }
    return result;
}