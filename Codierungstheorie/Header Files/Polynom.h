//
// Created by Dennis on 16/11/2022.
//

#ifndef CODIERUNGSTHEORIE_POLYNOM_H
#define CODIERUNGSTHEORIE_POLYNOM_H

#include <vector>
#include <iostream>

// Polynom 2nd degree: ax^2 + bx + c
// GF(p^e) = {u_{e-1} .... u_1, u_0 | u_i element in GF(p)}
// GF(3^2)




class Polynom {

private:
    std::vector<int> coefficients;

public:
    explicit Polynom(std::vector<int> coefficients) : coefficients(std::move(coefficients)) {}

    inline int get_coefficient(int index)
    {
        return coefficients.size() > index ? coefficients.at(index) : 0;
    }

    // vector addition:
    // size of result is the size of the larger summand?
    Polynom operator+(Polynom const& polynom)
    {
        auto result_size = 0;
        std::vector<int> result_coefficients;

        this->coefficients.size() >= polynom.coefficients.size() ?
            result_size = this->coefficients.size() :
            result_size = polynom.coefficients.size();

        for (unsigned int i = 0; i < result_size; i++ ) {

            int a;
            int b;

            a = this->coefficients.size() > i ? this->coefficients.at(i) : 0;
            b = polynom.coefficients.size() > i ? polynom.coefficients.at(i) : 0;

            result_coefficients.push_back(a+b);
        }

        Polynom result_polynom(result_coefficients);
        return result_polynom;
    }



};


#endif //CODIERUNGSTHEORIE_POLYNOM_H
