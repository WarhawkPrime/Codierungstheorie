

#include "Header Files/EGF.h"
#include "Header Files/Helper.h"
#include "Header Files/Task_6/Gruppe.h"
#include "Header Files/Task_6/ReedSolomonCode.h"

void lax() {
    // TODO DEBUG (1, 1, 0, 1) ^ 13
    // step by step with https://www.matheretter.de/rechner/polynomrechner?mod1=	hoch(0+1x1+1x2+1x3)13=x39+13x38+91x37+442x36+1651x35+5005x34+12727x33+27742x32+52624x31+87802x30+129844x29+171106x28+201643x27+212941x26+201643x25+171106x24+129844x23+87802x22+52624x21+27742x20+12727x19+5005x18+1651x17+442x16+91x15+13x14+x13&mod2=1+0x^1+0x^2+1x^3+1x^4
    auto gf = EGF::create_EGF_on_degree(4);
    auto ip = ip_by_degree[4];
    std::cout << "IP: " << ip.to_vector_str() << "IP: " << ip.to_polynom_str() << std::endl;
    auto a = Polynom({1, 1, 0, 1});
    std::cout << a.to_polynom_str() << " : " << a.to_vector_str() << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    auto a_2 = ((a * a));
    std::cout << "A^2; " << a_2.to_polynom_str() << " ; " << a_2.to_vector_str() << std::endl;
    a_2 = a_2 % ip;
    std::cout << "A^2%ip; " << a_2.to_polynom_str() << " ; " << a_2.as_int() << std::endl;

    a_2 = gf.multiplication(a, a);
    std::cout << "A^2%ip; " << a_2.to_polynom_str() << " ; " << a_2.to_vector_str() << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    auto a_4 = ((a_2 * a_2) % 2);
    std::cout << "A^4; " << a_4.to_polynom_str() << " ; " << a_4.as_int() << std::endl;
    a_4 = a_4 % ip;
    std::cout << "A^4%ip; " << a_4.to_polynom_str() << " ; " << a_4.to_vector_str() << std::endl;

    auto a_8 = ((a_4 * a_4) % 2) % ip;
    std::cout << "A^8; " << a_8.to_polynom_str() << " ; " << a_8.as_int() << std::endl;

    auto a_12 = ((a_8 * a_4) % 2) % ip;
    std::cout << "A^12; " << a_12.to_polynom_str() << " ; " << a_12.as_int() << std::endl;

    auto a_14 = ((a_12 * a_2) % 2) % ip;
    std::cout << "A^14; " << a_14.to_polynom_str() << " ; " << a_14.as_int() << std::endl;
    //    for (int i = 2; i < 15; ++i) {
    //
    //    }

    //
    //    auto x = Polynom({0, 1, 1, 1});
    //    auto r = x % ip_by_degree[4];
    //    std::cout << ip_by_degree[4].to_polynom_str() << std::endl;
    //    std::cout << r.to_polynom_str() << std::endl;
    //
    //    auto code = ReedSolomonCode(4, 0);
    //    auto prim = code.calc_primitive_of_group();
    //
    //    sep("Primitive");
    //    std::cout << prim.as_int();
}

std::vector<int> generate_vector(int n) {
    std::vector<int> result(n);
    for (int i = 0; i < n; ++i) {
        result[i] = i;
    }
    return result;
}

int main(int argc, char **argv) {
    auto e = 3;
    auto egf = EGF::create_EGF_on_degree(e);

    int q = pow(2, e);

    std::vector<std::vector<int>> mul_table = std::vector(q, std::vector<int>(q, 0));
    std::vector<std::vector<int>> add_table = std::vector(q, std::vector<int>(q, 0));

    for (int a = 0; a < q; ++a) {
        for (int b = 0; b < q; ++b) {
            auto a_p = Polynom(a);
            auto b_p = Polynom(b);

            auto result = egf.multiplication(a_p, b_p);
            mul_table[a][b] = result.as_int();
        }
    }

    for (int a = 0; a < q; ++a) {
        for (int b = 0; b < q; ++b) {
            auto a_p = Polynom(a);
            auto b_p = Polynom(b);

            auto result = egf.addition(a_p, b_p);
            add_table[a][b] = result.as_int();
        }
    }

    std::vector<int> elements = generate_vector(q);

    auto g = Gruppe(q, add_table, mul_table, elements);

    auto primitiv = g.primitive;
    std::cout << "Primitive: " << primitiv << std::endl;

    Polynom H = Polynom(0);
    Polynom G = Polynom(0);

    auto code = ReedSolomonCode(e, 5, g);
    code.fill_generator_and_control_matrix();

    std::cout << "Vandermonde: " << std::endl;
    std::cout << code.get_Vandermonde_matrix().to_vector_str() << std::endl;

    return 0;
}
