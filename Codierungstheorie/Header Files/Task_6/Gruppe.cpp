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

void Gruppe::calculate_generator_and_control_polynomial(int d, Polynom &generator_polynomial, Polynom &control_polynomial) {
    // q-1 viele Teiler
    const int teiler_anz = q - 1;

    std::vector<Polynom> teiler = {};

    // Generate divisors
    for (int i = 0; i < teiler_anz; ++i) {
        // Teiler in der Form: x + a^element
        auto a_pow_element = ((-POW(primitive, i)) + q) % 8;

        auto t = Polynom({a_pow_element, 1}, false);
        std::cout << "\tTeiler: " << t.to_polynom_str() << std::endl;
        teiler.push_back(t);
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    auto teiler_g = std::vector<Polynom>(teiler.begin() + 1, teiler.begin() + (d - 1));
    auto teiler_h = std::vector<Polynom>(teiler.begin() + d, teiler.end());
    teiler_h.push_back(teiler.at(0));

    for (const auto &item : teiler_g)
        std::cout << item.to_polynom_str() << std::endl;

    std::cout << std::endl;
    for (const auto &item : teiler_h)
        std::cout << item.to_polynom_str() << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    generator_polynomial = Polynom(1, false);
    for (auto item : teiler_g) {

        //        std::cout << generator_polynomial.to_polynom_str() << " | * | " << item.to_polynom_str();

        generator_polynomial = POLY_MUL(generator_polynomial, item);
        //        std::cout << " = " << generator_polynomial.to_polynom_str() << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    control_polynomial = Polynom(1, false);
    for (auto item : teiler_h) {

        //        std::cout << control_polynomial.to_polynom_str() << " | * | " << item.to_polynom_str();

        control_polynomial = POLY_MUL(control_polynomial, item);
        //        std::cout << " = " << control_polynomial.to_polynom_str() << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "g(x)=" << generator_polynomial.to_polynom_str() << std::endl;
    std::cout << "h(x)=" << control_polynomial.to_polynom_str() << std::endl;
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
