//
// Created by denni on 17/11/2022.
//

#include "Header Files/EGF.h"
#include "Header Files/ModularPolynomArithmetic.h"
#include <cassert>

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
    MPA::m_mod(a, irreducible_polynom, r, s, p);
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
std::vector<Polynom> EGF::field_elements() const {
    std::vector<Polynom> elements = std::vector<Polynom>();
    for (int i = 0; i < order; ++i) {
        auto poly = Polynom(i);
        elements.push_back(poly);
    }

    return elements;
}

Polynom EGF::multiplication_with_polynomial_reduction(const Polynom &a, const Polynom &b) const {
    if (a == Polynom::ZERO || b == Polynom::ZERO)
        return Polynom::ZERO;

    auto r = Polynom::ZERO;
    ;
    auto s = Polynom::ZERO;
    ;

    auto temp = modulo_multiplication(a, b);
    modular_reduction(temp, r, s);
    return r;
}

Polynom EGF::polynomial_reduction_bin(const Polynom &a, const Polynom &b) const {
    assert(p == 2);
    int lhs = a.as_int();
    int rhs = b.as_int();

    auto diff = a.get_degree() - b.get_degree();
    auto shifted_rhs = rhs;
    while (diff >= 0) {
        //        std::cout << "Diff: " << diff << std::endl;
        // Shift till same degree
        shifted_rhs = (rhs << (diff));
        //        std::cout << std::bitset<32>(rhs) << std::endl;
        //        std::cout << std::bitset<32>(shifted_rhs) << std::endl;
        //        std::cout << std::bitset<32>(lhs) << std::endl;
        // XOR with polynomial to reduce
        lhs = (lhs ^= shifted_rhs);
        //        std::cout << std::bitset<32>(lhs) << std::endl << std::endl;

        // Recalculate degree diff
        diff = Polynom(lhs).get_degree() - Polynom(rhs).get_degree();
    }
    return Polynom(lhs);
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
Polynom EGF::multiplicative_inverse(const Polynom &a) const {
    auto result = MPA::exgcd(a, irreducible_polynom, p);
    return result.inverse_a;
}

Polynom EGF::multiplication(const Polynom &a, const Polynom &b) const {
    return multiplication_with_polynomial_reduction(a, b);
}

Polynom EGF::addition(const Polynom &a, const Polynom &b) const {
    return modulo_addition(a, b);
}
