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
struct exgcd_result {
    Polynom gcd;       // The gcd of a and b
    Polynom inverse_a; // The inverse of a mod b
    Polynom inverse_b; // The inverse of b mod a
};

void m_mod(const Polynom &a, const Polynom &b, Polynom &r, Polynom &s, const int p = 2);

Polynom gcd(const Polynom &a, const Polynom &b, const int p = 2);

exgcd_result exgcd(const Polynom &a, const Polynom &b, const int p = 2);
} // namespace MPA