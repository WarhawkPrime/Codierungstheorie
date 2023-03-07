//
// Created by Admin on 07.03.2023.
//

#include "Gruppe.h"
Gruppe::Gruppe(const int q,
               const std::vector<std::vector<int>> &addTable,
               const std::vector<std::vector<int>> &mulTable,
               const std::vector<int> &elements) : q(q),
                                                   add_table(addTable),
                                                   mul_table(mulTable),
                                                   elements(elements) {
    primitive = find_primitive();
}

int Gruppe::ADD(int a, int b) const {
    return add_table[a][b];
}

int Gruppe::MUL(int a, int b) const {
    return mul_table[a][b];
}

int Gruppe::POW(int a, int e) const {
    if (e == 0) {
        return 1;
    } else {
        auto result = a;
        for (int i = 1; i < e; ++i) {
            result = MUL(result, a);
        }
        return result;
    }
}

int Gruppe::find_primitive() const {
    for (int a = 2; a < q; ++a) { // Start bei 2 weil 0^x = 0 und 1^x = 1
        auto is_primitive = true;
        for (int e = 1; e < q - 1; ++e) {
            auto power = POW(a, e);
            if (power == 1) {
                is_primitive = false;
                break;
            }
        }
        if (is_primitive) {
            return a;
        }
    }
    std::cerr << "NO primitive found";
    exit(1); // NO primitive found;
}

Polynom Gruppe::POLY_MUL(Polynom &a, Polynom &b) const {
    unsigned int result_size = a.get_coefficients().size() + b.get_coefficients().size() - 1;

    std::vector<int> result_coefficients(result_size, 0);

    int i = 0;
    for (auto pcA : a.get_coefficients()) {
        int j = 0;
        for (auto pcB : b.get_coefficients()) {
            auto x = MUL(pcA, pcB);
            auto y = result_coefficients.at(i + j);

            result_coefficients.at(i + j) = ADD(x, y);
            j++;
        }
        i++;
    }
    return Polynom(result_coefficients);
}
