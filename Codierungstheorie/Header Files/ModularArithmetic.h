//
// Created by Noah Ruben on 05/11/2022.
//

#ifndef CODIERUNGSTHEORIE_MODULARARITHMETIC_H
#define CODIERUNGSTHEORIE_MODULARARITHMETIC_H

#include <utility>

namespace MA {
    struct exgcd_result {
        int gcd;       // The gcd of a and b
        int inverse_a; // The inverse of a mod b
        int inverse_b; // The inverse of b mod a
    };

    // Modulo group mod
    int mmod(int i, int mod);

    // Modular inversion in the modulo group mod
    int inverse(int divisor, int mod);

    int gcd(int a, int b);

    exgcd_result
    exgcd(int a, int b, std::pair<int, int> xs = std::pair(1, 0), std::pair<int, int> ys = std::pair(0, 1));

}


#endif //CODIERUNGSTHEORIE_MODULARARITHMETIC_H
