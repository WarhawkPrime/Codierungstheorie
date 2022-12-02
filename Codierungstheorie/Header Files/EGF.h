//
// Created by denni on 17/11/2022.
//

#ifndef CODIERUNGSTHEORIE_EGF_H
#define CODIERUNGSTHEORIE_EGF_H

#include "Polynom.h"
#include <utility>
#include <cmath>
#include <bitset>

#include "Basis.h"

/**
 * GF(p^e) : Polynome von Grad < e über GF(p)
 * + Komponenentenweise Addition über GF(p)
 * * Polynom Multiplikation MOD unzerlegbarem f(x)
 */
class EGF {

private:
    const int p;
    const int e;
    int order;
    int max_degree;
    Polynom irreducible_polynom;

public:
    EGF(const int p, const int e, const Polynom irreducible_polynom) :  p(p),e(e), irreducible_polynom(irreducible_polynom)
    {
        order = pow(p, e);
    }

    Polynom modulo_addition(const Polynom& a, const Polynom& b);

    Polynom modulo_multiplication(const Polynom& a, const Polynom& b);

    void modular_reduction(const Polynom& a, Polynom &r, Polynom &s);

    Polynom multiplicative_inverse(const Polynom& a);

};


#endif //CODIERUNGSTHEORIE_EGF_H
