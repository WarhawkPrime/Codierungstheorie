//
// Created by denni on 04/03/2023.
//

#ifndef CODIERUNGSTHEORIE_REEDMUELLER_H
#define CODIERUNGSTHEORIE_REEDMUELLER_H


#include "Code.h"
#include "Header Files/Matrix.h"

// @TODO Dennis. Use Generatormatrix from ReedMueller
class ReedMueller : public Code {
    public:
        const int m;
        const int d = 3;
        const int q = 2;
        explicit ReedMueller(const int m);

        // Weil d imm 3 ist generator matrix mit min 2 lin. unabhängigen Vektoren deshalb m >=3
        Matrix create_control_matrix();
        Polynom decode(Polynom codeword) const override;
        Polynom encode(Polynom msg) const override;
        Matrix control_matrix;
        Matrix generator_matrix;

        MXA::Syndrom_table syndrom_table;


        Matrix generate_reed_mueller( int r, int m);

    private:
        const int calculate_N(int _m) const {
            return pow(2, _m) - 1;
        }
        const int calculate_K(int _m) const {
            return pow(2, _m) - 1;
        }
        Polynom remove_error(Polynom codeword) const;
};


#endif //CODIERUNGSTHEORIE_REEDMUELLER_H
