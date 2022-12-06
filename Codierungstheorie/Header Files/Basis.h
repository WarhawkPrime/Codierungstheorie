//
// Created by Dennis on 13/11/2022.
//

#ifndef CODIERUNGSTHEORIE_BASIS_H
#define CODIERUNGSTHEORIE_BASIS_H

#include <iostream>

class Basis {

  public:
    /**
     * Calculates the modulo of a number dependant of the modulo class
     * @param number
     * @param modulo
     * @return the modulo of the input number
     */
    static inline int modulo_group_mod(const int number, const int modulo) {
        const auto result = number % modulo;
        return result >= 0 ? result : result + modulo;
    }

    /*
     * Der euklidische Algorithmus ist ein Verfahren zum bestimmen des ggT
     * (größten gemeinsamen Teilers) zweier Zahlen. Gegeben sind 2 Zahlen, die
     * größere wird durch die kleinere dividiert. Falls ein Rest übrig bleibt,
     * wird die kleinere Zahl nun durch den Rest dividiert Dies wird so lange
     * fortgesetzt, bis kein Rest mehr übrig bleibt zb: 16 / 12 = 1 Rest 4 12 /
     * 4 = 3 Rest 0 ggT = 4
     *
     * Der erweiterte euklidischer Algorithmus ermittelt eine Linearkombination
     * des ggT für die beiden Zahlen ggT(a,b) = s * a + t * b
     */

    /**
     *
     * @param a
     * @param b
     * @return
     */
    inline int euclidean_algorithm(const int a, const int b) {
        if (a == 0)
            return b;

        return euclidean_algorithm(modulo_group_mod(b, a), a);
    }

    // 1 = gcd(a,p) = as + pt

    inline int extended_euclidean_algorithm(const int a, const int b, int &s,
                                            int &t) {
        if (b == 0) {
            s = 1;
            t = 0;
            return a;
        }

        int u;
        int v;
        int gcd = extended_euclidean_algorithm(b, modulo_group_mod(a, b), u, v);

        s = v;
        t = u - (a / b) * v;
        return gcd;
    }

    inline void multiplicative_inverse(const int i, const int mod,
                                       int &inverse) {
        int s = 1;
        int t = 0;
        int gcd = extended_euclidean_algorithm(i, mod, s, t);

        inverse = modulo_group_mod(s, mod);
    }

    // a element in GF(p)
    // a + ? = p mod p = 0
    // -a = p - a
    // zb in GF(11):
    // -7 = 4 = 11 - 7
    inline void additive_inverse(const int i, const int mod, int &inverse) {
        inverse = mod - i;
    }

    inline void polynom_mod_addition() {}
};

#endif // CODIERUNGSTHEORIE_BASIS_H
