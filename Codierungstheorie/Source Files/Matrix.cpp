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
    auto result = Matrix(rows, cols);
    auto temp_m = new Matrix(rows, cols, values);

    while (temp_m->values.size() != 0) {

        // Man wählt die erste Spalte von links, in der mindestens ein von Null verschiedener Wert steht.
        int sel_col = 0, r = 0;
        for (; r < temp_m->rows; ++r) {
            for (; sel_col < temp_m->cols; ++sel_col) {
                auto val = temp_m->values[r].get_coefficient(sel_col);
                if (val != 0) {
                    break;
                }
            }
        }
        auto first_num_of_col = temp_m->values[0].get_coefficient(sel_col);
        // Ist die oberste Zahl der gewählten Spalte eine Null, so vertauscht man die erste Zeile mit einer anderen Zeile, in der in dieser Spalte keine Null steht.
        if (first_num_of_col == 0) {
            for (auto &value : temp_m->values) {
                if (value.get_coefficient(sel_col) != 0) {
                    auto temp = temp_m->values[0];
                    values[0] = value;
                    value = temp;
                }
            }
        }
        // Man dividiert die erste Zeile durch das nun oberste Element der gewählten Spalte.
        // bei in gf(2) passiert hier doch gar nichts ...
        auto first_row = temp_m->values[0];
        result.values.push_back(first_row);

        // Man subtrahiert entsprechende Vielfache der ersten Zeile von den darunterliegenden Zeilen mit dem Ziel, dass das erste Element jeder Zeile (außer der ersten) Null wird.
        auto temp_values = std::vector<Polynom>();
        for (int i = 1; i < temp_m->rows; ++i) {
            temp_values.push_back(temp_m->values[i] + (first_row * -1));
        }
        // Durch Streichen der ersten Zeile und Spalte erhält man eine Restmatrix, auf die man diese Schritte wieder anwendet. Das führt man solange durch, bis die Matrix in Zeilenstufenform ist.
        temp_m = new Matrix(rows - 1, cols, temp_values);
    }
    // Man zieht danach von den darüberliegenden Zeilen entsprechende Vielfache ab, sodass über einer führenden 1 nur Nullen stehen.
    for (int i = 0; i > result.rows - 1; ++i) {
        auto higher_row = result.values[i];
        auto lower_row = result.values[i + 1];
        for (int j = 0; j < result.cols; ++j) {
            if (lower_row.get_coefficient(i) == 1 && higher_row.get_coefficient(i) != 0) {
                result.values[j] = higher_row + (lower_row * -1);
            }
        }
    }
    this->values = result.values;
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
