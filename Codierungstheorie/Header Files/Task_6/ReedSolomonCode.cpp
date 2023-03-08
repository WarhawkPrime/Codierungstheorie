//
// Created by Admin on 06.03.2023.
//

#include "Header Files/Task_6/ReedSolomonCode.h"

template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> vec);

void rotate_vector(std::vector<int> &vec) {
    if (vec.empty())
        return;
    int last = vec.back();
    for (int i = vec.size() - 1; i > 0; --i) {
        vec[i] = vec[i - 1];
    }
    vec[0] = last;
}

ReedSolomonCode::ReedSolomonCode(
    int e,
    int _d,
    Gruppe &gruppe)
    : e(e),
      q(pow(2, e)),
      gruppe(gruppe),
      alpha(gruppe.primitive),
      Code(pow(2, e) - 1, pow(2, e) - _d, _d) {
    std::cout << "RM(" << q << "," << d << ") ==>  "
              << "n: " << n << " k " << k
              << " d: " << d << std::endl;
    assert(d >= 2);
    assert(d <= q - 2);
    assert(n - k == d - 1);
    calculate_generator_and_control_polynomial(this->generator_polynomial, this->control_polynomial);

    fill_generator_and_control_matrix();
}

void ReedSolomonCode::calculate_generator_and_control_polynomial(Polynom &generator_polynomial, Polynom &control_polynomial) {
    // q-1 viele Teiler
    const int teiler_anz = q - 1;

    std::vector<Polynom> teiler = {};

    // Generate divisors
    for (int i = 0; i < teiler_anz; ++i) {
        // Teiler in der Form: x + a^i
        auto a_pow_element = ((-gruppe.POW(alpha, i)) + q) % 8;
        teiler.push_back(Polynom({a_pow_element, 1}, false));
    }

    auto teiler_g = std::vector<Polynom>(teiler.begin() + 1, teiler.begin() + (d - 1));

    // Restliche Teiler plus x-a^0
    auto teiler_h = std::vector<Polynom>(teiler.begin() + d, teiler.end());
    teiler_h.push_back(teiler.at(0));

    generator_polynomial = Polynom(1, false);
    for (auto item : teiler_g) {
        generator_polynomial = gruppe.POLY_MUL(generator_polynomial, item);
    }

    control_polynomial = Polynom(1, false);
    for (auto item : teiler_h) {
        control_polynomial = gruppe.POLY_MUL(control_polynomial, item);
    }
    std::cout << "g(x)=" << generator_polynomial.to_polynom_str() << std::endl;
    std::cout << "h(x)=" << control_polynomial.to_polynom_str() << std::endl;
}
void ReedSolomonCode::fill_generator_and_control_matrix() {
    fill_generator_matrix();
    fill_control_matrix();
}
void ReedSolomonCode::fill_control_matrix() {
    int pad = n - control_polynomial.get_coefficients().size();
    // Pad g(x)
    std::vector<int> padded_coefficients = std::vector<int>(n, 0);

    // reverse h(x) werte für H
    for (int i = control_polynomial.get_degree(); i >= 0; --i) {
        padded_coefficients.at(i) = control_polynomial.get_coefficients().at(i);
    }

    std::vector<Polynom> c_matrix_values = std::vector<Polynom>();
    c_matrix_values.push_back(Polynom(padded_coefficients, false));

    for (int i = 0; i < pad; ++i) {
        rotate_vector(padded_coefficients);
        /* Alternativ wäre auch ein shift mit alpha möglich:
        auto shift_with_alpha = Polynom({gruppe.POW(alpha, i)});
        auto shifted_C = gruppe.POLY_MUL(shift_with_alpha, control_polynomial);

         Vlt. geht das auch nicht da in H die werte von h(x) umgekehrt sind.
        */
        c_matrix_values.push_back(Polynom(padded_coefficients, false));
    }
    control_matrix = new Matrix(c_matrix_values);
    std::cout << "H: " << control_matrix->to_vector_str() << std::endl;
}
void ReedSolomonCode::fill_generator_matrix() {
    int pad = n - generator_polynomial.get_coefficients().size();
    // Pad g(x)
    std::vector<int> padded_coefficients = std::vector<int>(n, 0);

    for (int i = 0; i < generator_polynomial.get_coefficients().size(); ++i) {
        padded_coefficients.at(i) = generator_polynomial.get_coefficient(i);
    }
    std::vector<Polynom> g_matrix_values = std::vector<Polynom>();
    g_matrix_values.push_back(Polynom(padded_coefficients, false));
    for (int i = 0; i < pad; ++i) {
        rotate_vector(padded_coefficients);
        /* Alternativ wäre auch ein shift mit alpha möglich:
        auto shift_with_alpha = Polynom({gruppe.POW(alpha, i)});
        auto shifted_g = gruppe.POLY_MUL(shift_with_alpha, generator_polynomial);
        */
        g_matrix_values.push_back(Polynom(padded_coefficients, false));
    }
    generator_matrix = new Matrix(g_matrix_values);
    std::cout << "G: " << generator_matrix->to_vector_str() << std::endl;
}

Polynom ReedSolomonCode::decode(Polynom codeword) const {
    return codeword;
}
Polynom ReedSolomonCode::encode(Polynom msg) const {
    // Eigene Matrixmultiplikation in der Gruppe...
    return msg;
}