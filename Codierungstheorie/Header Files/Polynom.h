//
// Created by Dennis on 16/11/2022.
//

#ifndef CODIERUNGSTHEORIE_POLYNOM_H
#define CODIERUNGSTHEORIE_POLYNOM_H

#include <vector>
#include <iostream>
#include <math.h>

// Polynom 2nd degree: ax^2 + bx + c
// GF(p^e) = {u_{e-1} .... u_1, u_0 | u_i element in GF(p)}
// GF(3^2)




class Polynom {

private:
    std::vector<int> coefficients;

public:

    explicit Polynom() {}

    explicit Polynom(std::vector<int> coefficients) : coefficients(std::move(coefficients)) {}

    inline int get_coefficient(int index) const
    {
        return coefficients.size() > index ? coefficients.at(index) : 0;
    }

    // vector addition:
    // size of result is the size of the larger summand
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

    // can be optimized with a divide and conquer approach
    Polynom operator*(Polynom const& polynom)
    {
        unsigned int result_size = this->get_coefficients().size() + polynom.get_coefficients().size() -1;

        std::vector<int> result_coefficients(result_size, 0);

        int i = 0;
        for (auto pcA : this->coefficients)
        {
            int j = 0;
            for (auto pcB : polynom.coefficients )
            {
                result_coefficients.at(i+j) += (pcA * pcB);

                j++;
            }
            i++;
        }
        return Polynom(result_coefficients);
    }

    Polynom operator*(int const& integer)
    {
        std::vector<int> result_coefficients;

        for (auto c : this->coefficients)
        {
            result_coefficients.push_back(c * integer);
        }

        return Polynom(result_coefficients);
    }

    bool operator==(Polynom const& polynom )
    {
        return this->get_coefficients() == polynom.get_coefficients() ? true : false;
    }

    bool operator!=(Polynom const& polynom )
    {
        return this->get_coefficients() == polynom.get_coefficients() ? false : true;
    }

    inline std::string polynom_to_string()
    {
        std::string polynom_string;

        int index = 0;
        for (auto c : coefficients)
        {
            polynom_string.append( std::to_string(c) );

            if (index != 0)
                polynom_string.append("x^" + std::to_string(index));

            if (index != get_degree())
                polynom_string.append(" + ");

            index++;
        }
        return polynom_string;
    }

    inline void print_polynom()
    {
        std::cout << polynom_to_string() << std::endl;
    }

    inline int get_degree() const
    {
        return coefficients.size() -1;
    }

    inline std::vector<int> get_coefficients() const
    {
        return this->coefficients;
    }

    // removes 0 from the back (highest exponents) until non-zero number is met
    inline void resize()
    {
        for(std::vector<int>::reverse_iterator rit = coefficients.rbegin(); rit != coefficients.rend();)
        {
            if ( *rit == 0)
            {
                std::advance(rit, 1);
                coefficients.erase(rit.base());
            }
            else
                break;
        }
    }

    inline int to_q_adic_number(int p, int e)
    {
        int result = this->get_coefficient(0);
        int i = 0;

        for(int i = 1; i < this->get_coefficients().size(); i++ )
        {
            result += this->get_coefficient(i) * pow(p,i);
        }

        return result;
    }


};


#endif //CODIERUNGSTHEORIE_POLYNOM_H
