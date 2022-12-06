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
    /*
    auto result_size = 0;
    std::vector<int> result_coefficients;

    result_size = a.get_degree() >= b.get_degree() ? a.get_degree() + 1
                                                   : b.get_degree() + 1;

    for (int i = 0; i < result_size; i++) {
        int x;
        int y;
        int z;

        x = a.get_coefficient(i);
        y = b.get_coefficient(i);

        z = Basis::modulo_group_mod(x + y, this->p);

        result_coefficients.push_back(z);
    }

    Polynom result = Polynom(result_coefficients);
    result.trim();
    return result;
     */

    // Ich glaube das ist eleganter @Dennis ^^
    return (a + b) % p;
}

Polynom EGF::modulo_multiplication(const Polynom &a, const Polynom &b) const {
    unsigned int result_size =
        a.get_coefficients().size() + b.get_coefficients().size() - 1;

    std::vector<int> result_coefficients(result_size, 0);

    int i = 0;
    for (auto pcA : a.get_coefficients()) {
        int j = 0;
        for (auto pcB : b.get_coefficients()) {
            result_coefficients.at(i + j) +=
                Basis::modulo_group_mod((pcA * pcB), this->p);

            j++;
        }
        i++;
    }

    Polynom result = Polynom(result_coefficients);
    result.trim();
    return result;
}

/**
 *
 * @param a
 * @return a(x) mod f(x)
 */
void EGF::modular_reduction(const Polynom &a, Polynom &r, Polynom &s) {
    // r(x) := a(x)
    // s(x) := 0
    const Polynom f = this->irreducible_polynom;
    r = a;
    s = Polynom(0);

    // while deg(r) >= deg(f) do
    while (r.get_degree() >= this->irreducible_polynom.get_degree()) {
        // t(x) := f_deg(f)^-1 * r_deg(r)* x^{deg(r) - deg(f)}

        // ta = f_deg(f)^-1
        int ta = pow(this->irreducible_polynom.get_coefficient(
                         this->irreducible_polynom.get_degree()),
                     -1);

        // tb = r_deg(r)
        int tb = r.get_coefficient(r.get_degree());

        // tc = deg(r) - deg(f)
        int t_index = r.get_degree() - this->irreducible_polynom.get_degree();

        std::vector<int> temp_vec(t_index + 1, 0);
        temp_vec.at(t_index) = ta * tb;

        Polynom t = Polynom(temp_vec);

        // r(x) := r(x) + (-t(x)) * f(x)
        r = modulo_addition(r, modulo_multiplication(t * (-1), f));

        s = modulo_addition(s, t);
    }
}

void EGF::print_addition_table(Polynom::Format output_format, bool to_file) const {
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
    if (to_file) {
        // Create and open a text file
        std::ofstream myfile;

        myfile.open("example.txt");

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