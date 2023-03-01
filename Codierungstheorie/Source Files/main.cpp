
#include "Header Files/CodierungAblauf/CodierungsAblauf.h"
#include "Header Files/Helper.h"
#include "Header Files/ModularPolynomArithmetic.h"
#include "Header Files/Polynom.h"
#include <iostream>
#include <memory>

void lax() {
    //    auto i_p = Polynom({1, 0, 0, 0, 0, 0, 1, 1});
    //
    //    auto a = Polynom(7) * Polynom(1);
    //    std::cout << "a " << a.to_print_string(Polynom::polynom) << std::endl;
    //
    //    auto s = Polynom(0);
    //    auto r = Polynom(0);
    //
    //    auto egf = EGF(3, 4, i_p);
    //
    //    egf.modular_reduction(a, r, s);
    //
    //    std::cout << "r " << r.to_print_string(Polynom::polynom) << std::endl;
    //    std::cout << "s " << s.to_print_string(Polynom::polynom) << std::endl;

    //    for (const Polynom &item : ip_by_degree) {
    //        std::cout << item.as_int() << ": " << item.to_polynom_str() << std::endl;
    //    }
    //
    //    std::cout << std::endl;

    //    auto i_p = Polynom({1, 1, 1});
    //
    //    auto a = Polynom(3) * Polynom(3);
    //    a = a % 2;
    //    std::cout << "a " << a.to_print_string(Polynom::polynom) << std::endl;
    //    sep("");
    //
    //    auto s = Polynom(0);
    //    auto r = Polynom(0);
    //
    //    auto egf = EGF(2, 3, Polynom({1, 0, 1, 1}));
    //
    //    auto x = Polynom({0, 0, 1, 0, 1});
    //    std::cout << x.to_polynom_str() << std::endl;
    //    egf.modular_reduction(x, r, s);
    //    std::cout << "r " << r.to_print_string(Polynom::polynom) << std::endl;
    //    std::cout << "s " << s.to_print_string(Polynom::polynom) << std::endl;
    //    sep("BIN");
    //
    //    s = egf.polynomial_reduction_bin(x, Polynom({1, 0, 1, 1}));
    //    auto i_p = Polynom({1, 1, 1});
    //    Polynom s = Polynom::ZERO, r = Polynom::ZERO;
    //
    //    auto result = MPA::gcd(i_p, Polynom(3));
    //    std::cout << "Result: " << result.to_print_string(Polynom::polynom) << std::endl;
    //
    //    std::cout << std::endl;
}
int main(int argc, char **argv) {

    auto ablauf = CodierungsAblauf();
    ablauf.message = "Hello World!";

    ablauf.kanal = new NoErrorKanal();
    ablauf.code = new PlainCode();

    ablauf.run();
}
