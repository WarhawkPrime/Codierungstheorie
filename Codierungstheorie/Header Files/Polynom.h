//
// Created by Dennis on 16/11/2022.
//

#ifndef CODIERUNGSTHEORIE_POLYNOM_H
#define CODIERUNGSTHEORIE_POLYNOM_H

#include "Basis.h"
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

// Polynom 2nd degree: ax^2 + bx + c
// GF(p^e) = {u_{e-1} .... u_1, u_0 | u_i element in GF(p)}
// GF(3^2)

class Polynom {

  private:
    std::vector<int> coefficients;

  public:
    enum Format {
        number,
        vector,
        polynom
    };

    static const Polynom ZERO;
    static const Polynom ONE;

    explicit Polynom(std::vector<int> coefficients, bool _trim = true);

    /**
     * This uses the binary representation of the number as coefficients
     * @param coefficients_as_number
     */
    explicit Polynom(int coefficients_as_number, bool trim = true);

    /**
     *
     * @return the degree of the Polynomial
     */
    int get_degree() const;

    std::string to_vector_str() const;

    std::string to_vector_str(int _size) const;

    std::string to_polynom_str() const;

    std::string to_print_string(Polynom::Format depiction) const;

    std::string to_print_string(Polynom::Format depiction, int _size) const;

    int as_int() const;

    inline int get_coefficient(int index) const {
        return coefficients.size() > index ? coefficients.at(index) : 0;
    }
    void set_coefficient(int index, int value) {
        if (coefficients.size() > index) {
            coefficients.at(index) = value;
        }
    }

    inline bool set_coefficient(int index, int coefficient){
        if (index >= coefficients.size())
        {
            int i = coefficients.size();
            for(; i < index; i++)
            {
                coefficients.push_back(0);
            }
            coefficients.push_back(coefficient);
            return false;
        }
        else
        {
            coefficients.at(index) = coefficient;
            return true;
        }
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
        unsigned int result_size = get_coefficients().size() + rhs_polynom.get_coefficients().size() - 1;

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

    /**
     * This only works for GF(2)
     * @param rhs_polynom
     */
    Polynom operator%(Polynom const &rhs_polynom) const {
        assert(rhs_polynom != Polynom(0));
        int lhs = this->as_int();
        int rhs = rhs_polynom.as_int();

        auto diff = this->get_degree() - rhs_polynom.get_degree();
        auto shifted_rhs = rhs;
        while (diff >= 0) {
            //        std::cout << "Diff: " << diff << std::endl;
            // Shift till same degree
            shifted_rhs = (rhs << (diff));
            //        std::cout << std::bitset<32>(rhs) << std::endl;
            //        std::cout << std::bitset<32>(shifted_rhs) << std::endl;
            //        std::cout << std::bitset<32>(lhs) << std::endl;
            // XOR with polynomial to reduce
            lhs = (lhs ^= shifted_rhs);
            //        std::cout << std::bitset<32>(lhs) << std::endl << std::endl;

            // Recalculate degree diff
            diff = Polynom(lhs).get_degree() - Polynom(rhs).get_degree();
        }
        return Polynom(lhs);
    }

    /**
     *
     * @param rhs_polynom
     * @return Polynom
     *
     */
    Polynom operator/(Polynom const &rhs_polynom) const {
        assert(false); // This is not implemented
        assert(rhs_polynom != Polynom(0));
        auto q = 0;
        auto r = *this;

        while (r != Polynom(0) && r.get_degree() >= rhs_polynom.get_degree()) {
            auto t = 0;
        }

        return Polynom(0);
    }

    Polynom operator%(int const &rhs_integer) const {
        assert(rhs_integer != 0);
        std::vector<int> result;
        for (const auto &item : this->get_coefficients()) {
            result.push_back(Basis::modulo_group_mod(item, rhs_integer));
        }
        auto result_polynom = Polynom(result);
        result_polynom.trim();

        return result_polynom;
    }

    [[nodiscard]] inline std::vector<int> get_coefficients() const {
        return coefficients;
    }
    /**
     * Trims unnecessary zeros from Polynom
     * removes 0 from the back (highest exponents) until non-zero number is met
     */
    inline void trim() {
        if (coefficients.size() == 1 && coefficients[0] == 0)
            return;
        for (auto rit = coefficients.rbegin();
             rit != coefficients.rend();) {
            if (*rit == 0 && coefficients.size() != 1) {
                std::advance(rit, 1);
                coefficients.erase(rit.base());
            } else
                break;
        }
    }

    // TODO fuzzy test
    inline int to_q_adic_number(int p, int e) {
        int result = this->get_coefficient(0);

        for (int i = 1; i < this->get_coefficients().size(); i++) {
            result += get_coefficient(i) * pow(p, i);
        }

        return result;
    }
};

#endif // CODIERUNGSTHEORIE_POLYNOM_H
