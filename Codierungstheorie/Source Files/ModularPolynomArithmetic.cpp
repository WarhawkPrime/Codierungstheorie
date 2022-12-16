//
// Created by Noah Ruben on 03.01.23.
//

#include "Header Files/ModularPolynomArithmetic.h"

namespace MPA {
void m_mod(const Polynom &a, const Polynom &b, Polynom &r, Polynom &s, const int p) {
    // r(x) := a(x)
    // s(x) := 0
    const Polynom f = b;

    // Copy polynom to later trim it!
    r = Polynom(a.get_coefficients());

    s = Polynom::ZERO;

    if (a.get_degree() < f.get_degree()) {
        s = Polynom::ZERO;
        r = a;
        return;
    }

    // while deg(r) >= deg(f) do
    while (r.get_degree() >= f.get_degree()) {
        // t(x) := f_deg(f)^-1 * r_deg(r)* x^{deg(r) - deg(f)}

        // ta = f_deg(f)^-1
        int const ta = pow(b.get_coefficient(b.get_degree()), -1);

        // tb = r_deg(r)
        int const tb = r.get_coefficient(r.get_degree());

        // tc = deg(r) - deg(f)
        int const t_index = r.get_degree() - b.get_degree();

        std::vector<int> temp_vec(t_index + 1, 0);
        temp_vec.at(t_index) = ta * tb;

        auto t = Polynom(temp_vec);

        // r(x) := r(x) + (-t(x)) * f(x)

        r = (r + ((((t * -1) % p) * f) % p)) % p;
        //        std::cout << r.to_vector_str() << std::endl;
        //        r =  modulo_addition(r, modulo_multiplication(t * (-1), f));

        s = s + t % p; // modulo_addition(s, t);

        r.trim();
        if (r == Polynom::ZERO)
            break;
    }
    s.trim();
}
Polynom gcd(const Polynom &a, const Polynom &b, const int p) {
    Polynom s = Polynom::ZERO, r = Polynom::ZERO;
    if (b == Polynom::ZERO)
        return a;
    m_mod(a, b, r, s, p);
    return gcd(b, r, p);
}
// #define VERBOSE
exgcd_result exgcd(const Polynom &a, const Polynom &b, const int p) {
    auto x_1 = Polynom::ONE;
    auto x_2 = Polynom::ZERO;
    auto y_1 = Polynom::ZERO;
    auto y_2 = Polynom::ONE;

    auto temp_a = a;
    auto temp_b = b;

    Polynom div = Polynom::ZERO, mod = Polynom::ZERO;
    do {
        div = Polynom::ZERO;
        mod = Polynom::ZERO;

        m_mod(temp_a, temp_b, mod, div, p);
#ifdef VERBOSE
        std::cout << "(" << temp_a.to_polynom_str() << ") = (" << div.to_polynom_str() << ") * (" << b.to_polynom_str() << ") + (" << mod.to_polynom_str() << ")" << std::endl;
#endif
        //   x_i = x_{i-2}  - (x_{i-1}   * q_i)
        auto x = (x_1 + ((x_2 * div) * -1)) % p;
        //        std::cout << "X_i: /*/" << x.to_vector_str() << std::endl;

        auto y = (y_1 + ((y_2 * div) * -1)) % p;
        //        std::cout << "Y_i: " << y.to_vector_str() << std::endl;

        y_1 = y_2;
        y_2 = y;
        x_1 = x_2;
        x_2 = x;
        temp_a = temp_b;
        temp_b = mod;

    } while (mod != Polynom::ZERO);

    return {temp_a, x_1, y_1};
}
// Modular inversion in the modulo group mod
//    int inverse(int divisor, int mod);
} // namespace MPA