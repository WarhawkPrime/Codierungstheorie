//
// Created by Admin on 31.12.2022.
//

#include "Polynom.h"

#ifndef CODIERUNGSTHEORIE_MODULARPOLYNOMARITHMETIC_H
#define CODIERUNGSTHEORIE_MODULARPOLYNOMARITHMETIC_H

#endif // CODIERUNGSTHEORIE_MODULARPOLYNOMARITHMETIC_H
namespace MPA {

/**
 * @param mod The polynomial to reduce with
 * @param a The polynomial to reduce
 * @param r MOD result
 * @param s DIV result
 */
void m_mod(const Polynom &a, const Polynom &mod, Polynom &r, Polynom &s, const int p = 2) {
    // r(x) := a(x)
    // s(x) := 0
    const Polynom f = mod;

    // Copy polynom to later trim it!
    r = Polynom(a.get_coefficients());

    s = Polynom::ZERO;

    // while deg(r) >= deg(f) do

    while (r.get_degree() >= f.get_degree()) {
        // t(x) := f_deg(f)^-1 * r_deg(r)* x^{deg(r) - deg(f)}

        // ta = f_deg(f)^-1
        int const ta = pow(mod.get_coefficient(
                               mod.get_degree()),
                           -1);

        // tb = r_deg(r)
        int const tb = r.get_coefficient(r.get_degree());

        // tc = deg(r) - deg(f)
        int const t_index = r.get_degree() - mod.get_degree();

        std::vector<int> temp_vec(t_index + 1, 0);
        temp_vec.at(t_index) = ta * tb;

        auto t = Polynom(temp_vec);

        // r(x) := r(x) + (-t(x)) * f(x)
        r = (r + ((t * -1) * f)) % p; // modulo_addition(r, modulo_multiplication(t * (-1), f));

        s = s + t % p; // modulo_addition(s, t);

        r.trim();
        s.trim();
    }
}
// Modular inversion in the modulo group mod
//    int inverse(int divisor, int mod);

Polynom gcd(const Polynom &a, const Polynom &b, const int p = 2) {
    Polynom s = Polynom::ZERO, r = Polynom::ZERO;
    if (b == Polynom::ZERO)
        return a;
    m_mod(a, b, r, s, p);
    return gcd(b, r, p);
}

Polynom exgcd(const Polynom &a, const Polynom &b, const int p = 2) {
    auto x_1 = Polynom::ONE;
    auto x_2 = Polynom::ZERO;
    auto y_1 = Polynom::ZERO;
    auto y_2 = Polynom::ONE;

    Polynom div = Polynom::ZERO, mod = Polynom::ZERO;
    do {
        m_mod(a, b, mod, div, p);
        //   x_i = x_{i-2}  - (x_{i-1}   * q_i)
        auto x = (x_1 + ((x_2 * div) * -1)) % p;
        auto y = (y_1 + ((y_2 * div) * -1)) % p;

        std::cout << "X_i: " << x.to_vector_str() << std::endl;
        std::cout << "Y_i: " << y.to_vector_str() << std::endl;

        y_1 = y_2;
        y_2 = y;
        x_1 = x_2;
        x_2 = x;
    } while (mod != Polynom::ZERO);

    return Polynom::ZERO;
}

} // namespace MPA