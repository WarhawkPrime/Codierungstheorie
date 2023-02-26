//
// Created by Noah on 01.01.2023.
//
#include "Header Files/EGF.h"
#include "Header Files/Helper.h"
#include "Header Files/Polynom.h"

void inverse_matrix(EGF gf, std::string file_name, Polynom::Format output_format = Polynom::Format::number) {
    const char sep = ';';
    std::string result;

    result += "*";
    result += sep;
    for (int column = -1; column < gf.order; ++column) {
        auto col_poly = Polynom(column);

        if (column != -1) {
            result += col_poly.to_print_string(output_format);
            result += sep;
        }
        for (int row = -1; row < gf.order; ++row) {
            auto row_poly = Polynom(row);
            if (column == -1 && row != -1) {
                result += row_poly.to_print_string(output_format);
                result += sep;
            } else if (row != -1) {
                auto inverse = gf.multiplication(col_poly, row_poly);

                auto result_i = inverse.as_int() == 1 ? "1" : "0";

                result += result_i;
                result += sep;
            }
        }
        result = result.substr(0, result.size() - 1);
        result += "\n";
    }
    if (!file_name.empty()) {
        // Create and open a text file
        std::ofstream myfile;

        myfile.open(file_name);

        // Write to the file
        myfile << result;

        // Close the file
        myfile.close();
    } else {
        std::cout << result;
    }
}

int main(int argc, char **argv) {

    for (int i = 1; i < 9; ++i) {
        const Polynom irreduciblePolynom = ip_by_degree[i];
        const EGF gf = EGF(2, i, irreduciblePolynom);
        sep("GF(2^" + std::to_string(i) + "): " + irreduciblePolynom.to_polynom_str());
        for (int j = 1; j < gf.order; ++j) {
            auto polynom = Polynom(j);
            auto inverse = gf.multiplicative_inverse(polynom);
            auto result = gf.multiplication(polynom, inverse);

            // std::cout << j << " Correct: " << toString(result == Polynom::ONE) << "   " << polynom.to_print_string(Polynom::polynom) << " * " << inverse.to_print_string(Polynom::polynom) << " = " << result.to_print_string(Polynom::polynom);
            std::cout << "  " << polynom.as_int() << " * " << inverse.as_int() << " = " << result.as_int() << std::endl;
        }
    }

    // Matrix mit 0 == nicht invers 1 == invers
    // Im Context von row * col
    // siehe ./DOC für die visualisierung
    for (int i = 1; i < 9; ++i) {
        Polynom irreduciblePolynom = ip_by_degree[i];
        std::cout << "GF(2^" << i << "): " << irreduciblePolynom.to_polynom_str() << std::endl;

        EGF const gf = EGF(2, i, irreduciblePolynom);
        gf.print_multiplication_table(Polynom::number, "mult_matrix_" + std::to_string(i) + ".csv");
        inverse_matrix(gf, "inverse_" + std::to_string(i) + ".csv");
    }

    return 0;
}