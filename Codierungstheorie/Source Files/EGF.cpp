//
// Created by denni on 17/11/2022.
//

#include "Header Files/EGF.h"

/**
 *
 * @param a
 * @param b
 * @return
 */
Polynom EGF::modulo_addition(const Polynom &a, const Polynom &b) const {
    return (a + b) % p;
}

Polynom EGF::modulo_multiplication(const Polynom &a, const Polynom &b) const {
    Polynom result = (a * b) % p;

    return result;
}

/**
 *
 * @param a
 * @return a(x) mod f(x)
 */
void EGF::modular_reduction(const Polynom &a, Polynom &r, Polynom &s) const {
    // r(x) := a(x)
    // s(x) := 0
    const Polynom f = this->irreducible_polynom;

    // Copy polynom to later trim it!
    r = Polynom(a.get_coefficients());

    s = Polynom(0);

    // while deg(r) >= deg(f) do

    while (r.get_degree() >= f.get_degree()) {
        // t(x) := f_deg(f)^-1 * r_deg(r)* x^{deg(r) - deg(f)}

        // ta = f_deg(f)^-1
        int const ta = pow(this->irreducible_polynom.get_coefficient(
                               this->irreducible_polynom.get_degree()),
                           -1);

        // tb = r_deg(r)
        int const tb = r.get_coefficient(r.get_degree());

        // tc = deg(r) - deg(f)
        int const t_index = r.get_degree() - this->irreducible_polynom.get_degree();

        std::vector<int> temp_vec(t_index + 1, 0);
        temp_vec.at(t_index) = ta * tb;

        auto t = Polynom(temp_vec);

        // r(x) := r(x) + (-t(x)) * f(x)
        r = modulo_addition(r, modulo_multiplication(t * (-1), f));

        s = modulo_addition(s, t);

        r.trim();
        s.trim();
    }
}

void EGF::print_addition_table(Polynom::Format output_format, std::string file_name) const {
    const char sep = ';';
    std::string result;

    result += "+";
    result += sep;
    for (int column = -1; column < order; ++column) {
        auto col_poly = Polynom(column);

        if (column != -1) {
            result += col_poly.to_print_string(output_format);
            result += sep;
        }
        for (int row = -1; row < order; ++row) {
            auto row_poly = Polynom(row);
            if (column == -1 && row != -1) {
                result += row_poly.to_print_string(output_format);
                result += sep;
            } else if (row != -1) {
                auto add_result = modulo_addition(col_poly, row_poly);
                result += add_result.to_print_string(output_format);
                result += sep;
            }
        }
        result = result.substr(0, result.size() - 1);
        result += "\n";
    }
    if (!file_name.empty()) {
        // Create and open a text file
        std::ofstream myfile;

        myfile.open(file_name);

        // Write to the file
        myfile << result;

        // Close the file
        myfile.close();
    } else {
        std::cout << result;
    }
}

void EGF::print_elements(Polynom::Format output_format) const {
    for (int i = 0; i < order; ++i) {
        auto poly = Polynom(i);
        std::cout << poly.to_print_string(output_format, log2(order));
        if (i != order - 1)
            std::cout << ", ";
    }

    std::cout << std::endl;
}

Polynom EGF::multiplication_with_polynomial_reduction(const Polynom &a, const Polynom &b) const {
    auto zero_polynom = Polynom(0);
    if (a == zero_polynom || b == zero_polynom)
        return zero_polynom;

    auto r = zero_polynom;
    auto s = zero_polynom;

    auto temp = modulo_multiplication(a, b);
    modular_reduction(temp, r, s);
    return r;
}

Polynom EGF::polynomial_reduction_bin(const Polynom &a, const Polynom &b) const {
    assert(p == 2);
    int f = a.as_int();
    int r = b.as_int();
    int tem = f;
    auto temp = Polynom(tem);

    // TODO @Noah binäre reductio nwenn p == 2 ist
    while (!(a.get_degree() < b.get_degree())) {
        while (tem > r) {
            r = r << 1;
        }
        r = r + 1;
        tem = (f | r);
        temp = Polynom(tem);
    }

    return temp;
}

void EGF::print_multiplication_table(Polynom::Format output_format, std::string file_name) const {
    const char sep = ';';
    std::string result;

    result += "*";
    result += sep;
    for (int column = -1; column < order; ++column) {
        auto col_poly = Polynom(column);

        if (column != -1) {
            result += col_poly.to_print_string(output_format);
            result += sep;
        }
        for (int row = -1; row < order; ++row) {
            auto row_poly = Polynom(row);
            if (column == -1 && row != -1) {
                result += row_poly.to_print_string(output_format);
                result += sep;
            } else if (row != -1) {
                auto add_result = multiplication_with_polynomial_reduction(col_poly, row_poly);

                result += add_result.to_print_string(output_format);
                result += sep;
            }
        }
        result = result.substr(0, result.size() - 1);
        result += "\n";
    }
    if (!file_name.empty()) {
        // Create and open a text file
        std::ofstream myfile;

        myfile.open(file_name);

        // Write to the file
        myfile << result;

        // Close the file
        myfile.close();
    } else {
        std::cout << result;
    }
}
