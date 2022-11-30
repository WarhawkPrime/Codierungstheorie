//
// Created by denni on 17/11/2022.
//

#include "Header Files/EGF.h"

/**
 *
 * @param a
 * @param b
 * @return
 */
Polynom EGF::modulo_addition(const Polynom& a, const Polynom& b)
{
    auto result_size = 0;
    std::vector<int> result_coefficients;

    result_size = a.get_degree() >= b.get_degree() ? a.get_degree()+1 : b.get_degree()+1;

    for(int i = 0; i < result_size; i++)
    {
        int x;
        int y;
        int z;

        x = a.get_coefficient(i);
        y = b.get_coefficient(i);

        z = Basis::modulo_group_mod(x+y, this->p);

        result_coefficients.push_back(z);
    }

    Polynom result = Polynom(result_coefficients);
    result.resize();
    return result;
}


Polynom EGF::modulo_multiplication(const Polynom &a, const Polynom &b)
{
    unsigned int result_size = a.get_coefficients().size() + b.get_coefficients().size() -1;

    std::vector<int> result_coefficients(result_size, 0);

    int i = 0;
    for (auto pcA : a.get_coefficients())
    {
        int j = 0;
        for (auto pcB : b.get_coefficients() )
        {
            result_coefficients.at(i+j) +=  Basis::modulo_group_mod((pcA * pcB), this->p) ;

            j++;
        }
        i++;
    }

    Polynom result = Polynom(result_coefficients);
    result.resize();
    return result;
}






/**
 *
 * @param a
 * @return a(x) mod f(x)
 */
void EGF::modular_reduction(const Polynom &a, Polynom &r, Polynom &s)
{
    //r(x) := a(x)
    //s(x) := 0
    const Polynom f = this->irreducible_polynom;
    r = a;
    s = Polynom({0});

    // while deg(r) >= deg(f) do
    while(r.get_degree() >= this->irreducible_polynom.get_degree())
    {
        // t(x) := f_deg(f)^-1 * r_deg(r)* x^{deg(r) - deg(f)}

        // ta = f_deg(f)^-1
        int ta = pow(this->irreducible_polynom.get_coefficient(this->irreducible_polynom.get_degree()), -1) ;

        // tb = r_deg(r)
        int tb = r.get_coefficient(r.get_degree());

        // tc = deg(r) - deg(f)
        int t_index = r.get_degree() - this->irreducible_polynom.get_degree();

        std::vector<int> temp_vec(t_index+1, 0);
        temp_vec.at(t_index) = ta * tb;

        //t(x) :=
        Polynom t = Polynom(temp_vec);
        //t.print_polynom();

        //r(x) := r(x) + (-t(x)) * f(x)
        r = modulo_addition(r, modulo_multiplication(t * (-1), f ) );
        //r.print_polynom();

        s = modulo_addition(s, t);
        //s.print_polynom();
    }
}










