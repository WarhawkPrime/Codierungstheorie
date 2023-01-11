//
// Created by Noah Ruben on 10.01.23.
//

#include "Header Files/Matrix.h"
#include "Header Files/Helper.h"

void Matrix::to_canonical_form() {
    /*
     * pivot_row (Pivot-Zeile) bezieht sich auf die aktuelle Zeile,
     * die als Pivot-Zeile verwendet wird,
     * pivot_col (Pivot-Spalte) sich auf die aktuelle Spalte bezieht,
     * die als Pivot-Spalte verwendet wird.
     *
     * Diese beiden Variablen werden verwendet,
     * um den aktuellen Fortschritt des Gauss-Jordan-Eliminationsprozesses
     * zu verfolgen.
     *
     * Der Pivot-Wert ist in der Regel der erste nicht-null Wert in der Spalte/Reihe, die gerade betrachtet wird.
     * Während des Gauss-Jordan-Eliminationsprozesses wird die Pivot-Zeile immer wieder geändert,
     * um die Matrix in die gewünschte Form zu bringen.
     *
     * https://en.wikipedia.org/wiki/Gaussian_elimination#Pseudocode
     * https://de.wikipedia.org/wiki/Gau%C3%9F-Jordan-Algorithmus#Umformungsschritte
     */
    int pivot_row = 0; /* Initialization of the pivot row */
    int pivot_col = 0; /* Initialization of the pivot column */

    // Hier iterieren wir "diagonal" durch die Matrix. ggf auch horizontal je nach Matrix
    while (pivot_row < rows && pivot_col < cols) {
        // Debug information
        sep(std::to_string(pivot_row) + "," + std::to_string(pivot_col));
        std::cout << this->to_vector_str() << std::endl;

        /* Find the pivot element in the current column: */
        int max_index = idx_of_max_value_in_col(pivot_row, pivot_col);

        // Debug information
        std::cout << "Max index: " << max_index << "," << pivot_col << " Value: " << values[max_index].get_coefficients().at(pivot_col) << std::endl;

        // checks if the maximum value in the current pivot column is equal to zero. If it is, it means that there is no pivot element in this column and the algorithm should move to the next column.
        if (values[max_index].get_coefficient(pivot_col) == 0) {
            /* No pivot in this column, pass to next column */
            pivot_col++;
        } else {
            /* Swap the current pivot row with the row containing the max element */
            std::swap(values[pivot_row], values[max_index]);

            /* Iterate through all rows below the pivot row */
            for (int current_row = pivot_row + 1; current_row < rows; current_row++) {

                /* Fill the pivot column with zeros for the current row */
                values[current_row].set_coefficient(pivot_col, 0);

                /* Iterate through all columns in the current row, starting from the pivot column + 1 */
                for (int current_col = pivot_col + 1; current_col < cols; current_col++) {
                    auto pivot_coefficient = values[pivot_row].get_coefficients()[current_col];
                    auto current_coefficient = values[current_row].get_coefficients()[current_col];

                    values[current_row].set_coefficient(current_col, Basis::modulo_group_mod(current_coefficient - pivot_coefficient, p));
                }
            }
            sep("After");

            /* Increase pivot row and column */
            pivot_row++;
            pivot_col++;
        }
    }
}
std::string Matrix::to_vector_str() const {
    std::string result = "(\n";
    for (const auto &item : values) {
        auto polynom_as_string = item.to_vector_str(cols);
        polynom_as_string.erase(0, 1); // remove first character "("
        polynom_as_string.pop_back();  // remove last character ")"
        result.append(" ").append(polynom_as_string).append("\n");
    }
    result.append(")");
    return result;
}

int Matrix::idx_of_max_value_in_col(int starting_row, int col_to_search) {
    int max_row_index = 0;
    double max_value = 0;

    for (int row = starting_row; row < rows; row++) {
        auto value = abs(values[row].get_coefficient(col_to_search));
        if (value > max_value) {
            max_row_index = row;
            max_value = value;
        }
    }

    return max_row_index;
}
