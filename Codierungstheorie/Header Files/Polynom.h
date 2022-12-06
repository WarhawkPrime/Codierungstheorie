//
// Created by Dennis on 16/11/2022.
//

#ifndef CODIERUNGSTHEORIE_POLYNOM_H
#define CODIERUNGSTHEORIE_POLYNOM_H

#include "Basis.h"
#include <iostream>
#include <math.h>
#include <vector>

// Polynom 2nd degree: ax^2 + bx + c
// GF(p^e) = {u_{e-1} .... u_1, u_0 | u_i element in GF(p)}
// GF(3^2)

class Polynom {

  private:
    std::vector<int> coefficients;

  public:
    enum Format { number,
                  vector,
                  polynom };

    explicit Polynom(std::vector<int> coefficients);

    /**
     * This uses the binary representation of the number as coefficients
     * @param coefficients_as_number
     */
    explicit Polynom(int coefficients_as_number);

    /**
     *
     * @return the degree of the Polynomial
     */
    int get_degree() const;

    std::string to_vector_str();
    std::string to_vector_str(int _size);

    std::string to_polynom_str();

    std::string to_print_string(Polynom::Format depiction);
    std::string to_print_string(Polynom::Format depiction, int _size);

    int as_int();

    inline int get_coefficient(int index) const {
        return coefficients.size() > index ? coefficients.at(index) : 0;
    }

    // vector addition:
    // size of result is the size of the larger summand
    Polynom operator+(Polynom const &rhs_polynom) const {
        auto result_size = 0;
        std::vector<int> result_coefficients;

        this->coefficients.size() >= rhs_polynom.coefficients.size()
            ? result_size = this->coefficients.size()
            : result_size = rhs_polynom.coefficients.size();

        for (unsigned int i = 0; i < result_size; i++) {

            int a;
            int b;

            a = this->coefficients.size() > i ? this->coefficients.at(i) : 0;
            b = rhs_polynom.coefficients.size() > i
                    ? rhs_polynom.coefficients.at(i)
                    : 0;

            result_coefficients.push_back(a + b);
        }

        Polynom result_polynom(result_coefficients);
        return result_polynom;
    }

    // can be optimized with a divide and conquer approach
    Polynom operator*(Polynom const &rhs_polynom) const {
        unsigned int result_size = this->get_coefficients().size() +
                                   rhs_polynom.get_coefficients().size() - 1;

        std::vector<int> result_coefficients(result_size, 0);

        int i = 0;
        for (auto pcA : this->coefficients) {
            int j = 0;
            for (auto pcB : rhs_polynom.coefficients) {
                result_coefficients.at(i + j) += (pcA * pcB);

                j++;
            }
            i++;
        }
        return Polynom(result_coefficients);
    }

    Polynom operator*(int const &rhs_integer) const {
        std::vector<int> result_coefficients;

        for (auto c : this->coefficients) {
            result_coefficients.push_back(c * rhs_integer);
        }

        return Polynom(result_coefficients);
    }

    bool operator==(Polynom const &rhs_polynom) const {
        return this->get_coefficients() == rhs_polynom.get_coefficients()
                   ? true
                   : false;
    }

    bool operator!=(Polynom const &rhs_polynom) const {
        return this->get_coefficients() == rhs_polynom.get_coefficients()
                   ? false
                   : true;
    }

    // TODO @NOAH mit bit shift ? eher nicht
    // TODO @NOAH fast mod mit bit schift als funktion.
    Polynom operator%(Polynom const &rhs_polynom) const {
        return Polynom(0);
    }

    Polynom operator%(int const &rhs_integer) const {
        std::vector<int> result;
        for (const auto &item : this->get_coefficients()) {
            result.push_back(Basis::modulo_group_mod(item, rhs_integer));
        }
        auto result_polynom = Polynom(result);
        result_polynom.trim();

        return result_polynom;
    }

    inline std::vector<int> get_coefficients() const {
        return coefficients;
    }

    /**
     * Trims unnecessary zeros from Polynom
     * removes 0 from the back (highest exponents) until non-zero number is met
     */
    inline void trim() {
        for (std::vector<int>::reverse_iterator rit = coefficients.rbegin();
             rit != coefficients.rend();) {
            if (*rit == 0) {
                std::advance(rit, 1);
                coefficients.erase(rit.base());
            } else
                break;
        }
    }

    inline int to_q_adic_number(int p, int e) {
        int result = this->get_coefficient(0);
        int i = 0;

        for (int i = 1; i < this->get_coefficients().size(); i++) {
            result += this->get_coefficient(i) * pow(p, i);
        }

        return result;
    }
};

#endif // CODIERUNGSTHEORIE_POLYNOM_H
