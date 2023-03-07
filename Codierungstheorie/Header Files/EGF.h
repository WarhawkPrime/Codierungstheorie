//
// Created by denni on 17/11/2022.
//

#ifndef CODIERUNGSTHEORIE_EGF_H
#define CODIERUNGSTHEORIE_EGF_H

#include <bitset>
#include <cmath>
#include <fstream>
#include <iostream>
#include <utility>

#include "Basis.h"
#include "Polynom.h"

/**
 * GF(p^e) : Polynome von Grad < e über GF(p)
 * + Komponenentenweise Addition über GF(p)
 * * Polynom Multiplikation MOD unzerlegbarem f(x)
 */
class EGF {

  private:
    static const Polynom ip_by_degree[10];

    [[nodiscard]] Polynom multiplication_with_polynomial_reduction(const Polynom &a, const Polynom &b) const;

    [[nodiscard]] Polynom modulo_addition(const Polynom &a, const Polynom &b) const;

    [[nodiscard]] Polynom modulo_multiplication(const Polynom &a, const Polynom &b) const;

  public:
    const int p;
    const int e;
    const int order;

    // Checks in EFG so that no invalid ip etc. can be used
    EGF(const int p, const int e, const Polynom &irreducible_polynom) : p(p), e(e), order(pow(p, e)),
                                                                        irreducible_polynom(irreducible_polynom) {}

    EGF(const int e, const Polynom &irreducible_polynom) : p(2), e(e), order(pow(p, e)),
                                                           irreducible_polynom(irreducible_polynom) {}

    static EGF create_EGF_on_degree(int degree) {
        return {degree, ip_by_degree[degree]};
    }

    [[nodiscard]] Polynom multiplication(const Polynom &a, const Polynom &b) const;
    [[nodiscard]] Polynom addition(const Polynom &a, const Polynom &b) const;

    /**
     *
     * @param a The polynomial to reduce
     * @param r MOD
     * @param s DIV
     */
    void modular_reduction(const Polynom &a, Polynom &r, Polynom &s) const;

    Polynom multiplicative_inverse(const Polynom &a) const;

    std::vector<Polynom> field_elements() const;

    Polynom polynomial_reduction_bin(const Polynom &a, const Polynom &b) const;

    Polynom pow_with_polynomial_reduction(const Polynom &base, const int &power) const;

    void print_multiplication_table(Polynom::Format output_format = Polynom::number, std::string file_name = "") const;

    void print_addition_table(Polynom::Format output_format = Polynom::number, std::string file_name = "") const;

    void print_elements(Polynom::Format output_format = Polynom::number) const;
    const Polynom irreducible_polynom;
};

#endif // CODIERUNGSTHEORIE_EGF_H
