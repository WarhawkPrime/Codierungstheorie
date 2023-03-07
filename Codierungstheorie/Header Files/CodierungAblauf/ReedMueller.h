//
// Created by denni on 04/03/2023.
//

#ifndef CODIERUNGSTHEORIE_REEDMUELLER_H
#define CODIERUNGSTHEORIE_REEDMUELLER_H


#include "Code.h"
#include "Header Files/Matrix.h"
#include <iostream>

// @TODO Dennis. Use Generatormatrix from ReedMueller
// Code C(n, k, d, q)
class ReedMueller : public Code {
    public:
        const int m;    //3
        const int r;
        //d 3
        const int q = 2;


        // rule: RM(r, m) => C(2^m, sum over r with i = 0 of all m over i, 2^(m-r), 2)
        // rule RM(m-2, m) => C(2^m, s^m -1 - m, 4, 2) Paritätserweiterter Hamming Code
        // rule RM(m-1, m) => (2^m, 2^m -1, 2, 2) Paritätserweiterung des Trivialen Codes
        // PE: (n,n,1,2) -> PE -> (n+1, 1, 2, 2)
        explicit ReedMueller(const int r, const int m);

        // Weil d imm 3 ist generator matrix mit min 2 lin. unabhängigen Vektoren deshalb m >=3
        Matrix create_control_matrix();
        Polynom decode(Polynom codeword) const override;
        Polynom encode(Polynom msg) const override;
        Matrix control_matrix;
        Matrix generator_matrix;

        MXA::Syndrom_table syndrom_table;


        Matrix generate_reed_mueller( int r, int m);

    private:

        inline int calc_faculty(int n) const
        {
            int result = 1;
            for (int i = 1; i <= n; i++)
            {
                result *= i;
            }
            return result;
        }

        // binominalkoeffizient
        // m r = m! / r! * (m-r)!
        inline int calc_m_over_r(int m, int r) const
        {
            if (m < r) {

                exit(1);
            }

            int numerator = calc_faculty(m);
            int denominator = calc_faculty(r) * calc_faculty(m-r);
            int result = numerator / denominator;
            return result;
        }

        // n = 2^m
        const int calculate_N(int _r, int _m) const
        {
            return pow(2, _m);
        }

        // sum over r with i = 0 of all m over i
        const int calculate_K(int _r, int _m) const
        {
            int res = 0;
            for (int i = 0; i <= _r; i++)
            {
                res += calc_m_over_r(_m,i);
            }
            return res;
        }

        // d = 2^(m-r)
        const int calculate_d(int _r, int _m) const
        {
            auto res = (pow(2, (_m - _r)));
            return res;
        }

        /*
        const int calculate_N(int _m) const {
            return pow(2, _m) - 1;
        }
        const int calculate_K(int _m) const {
            return pow(2, _m) - 1;
        }
        */
        Polynom remove_error(Polynom codeword) const;
};


#endif //CODIERUNGSTHEORIE_REEDMUELLER_H
