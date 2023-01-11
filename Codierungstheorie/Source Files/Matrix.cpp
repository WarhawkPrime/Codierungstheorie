//
// Created by Noah Ruben on 10.01.23.
//

#include "Header Files/Matrix.h"

int compare_canonical(Polynom &a, Polynom &b) {
    for (int i = 0; i < a.get_degree(); ++i) {
        auto a_coeff = a.get_coefficient(i);
        auto b_coeff = b.get_coefficient(i);

        if (a_coeff == b_coeff)
            continue;
        if (a_coeff > b_coeff)
            return -1;
        if (a_coeff < b_coeff)
            return 1;
    }
    return 0;
}

void Matrix::GausJordan_elimination() {
    // Man wählt die erste Spalte von links, in der mindestens ein von Null verschiedener Wert steht.
    int sel_col = 0, r = 0;
    for (; r < rows; ++r) {
        for (; sel_col < cols; ++sel_col) {
            auto val = values[r].get_coefficient(sel_col);
            if (val != 0) {
                break;
            }
        }
    }
    auto first_num_of_col = values[0].get_coefficient(sel_col);
    // Ist die oberste Zahl der gewählten Spalte eine Null, so vertauscht man die erste Zeile mit einer anderen Zeile, in der in dieser Spalte keine Null steht.
    if (first_num_of_col == 0) {
        for (auto &value : values) {
            if (value.get_coefficient(sel_col) != 0) {
                auto temp = values[0];
                values[0] = value;
                value = temp;
            }
        }
    }
    // Man dividiert die erste Zeile durch das nun oberste Element der gewählten Spalte.
    // Man subtrahiert entsprechende Vielfache der ersten Zeile von den darunterliegenden Zeilen mit dem Ziel, dass das erste Element jeder Zeile (außer der ersten) Null wird.
    // Durch Streichen der ersten Zeile und Spalte erhält man eine Restmatrix, auf die man diese Schritte wieder anwendet. Das führt man solange durch, bis die Matrix in Zeilenstufenform ist.
    // Man zieht danach von den darüberliegenden Zeilen entsprechende Vielfache ab, sodass über einer führenden 1 nur Nullen stehen.
}
// Not just sort but use the Gauss-Jordan-elimination
void Matrix::to_canonical_form() {
    for (auto &item_a : values) {
        for (auto &item_b : values) {
            if (compare_canonical(item_a, item_b) <= 0) {
                std::swap(item_a, item_b);
            }
        }
    }
}
std::string Matrix::to_vector_str() const {
    auto result = std::string();
    for (const auto &item : values) {
        result.append(item.to_vector_str(cols)).append("\n");
    }
    return result;
}
