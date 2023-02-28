//
// Created by Noah Ruben on 10.01.23.
//

#include "Header Files/Matrix.h"


namespace MXA
{
    // mxn x nxp -> mxp
    // rowxcol x colxrowp -> rowxrowp
    Matrix polynom_matrix_multiplication(Polynom p, Matrix m)
    {
        // polynoms row = 1, so number of coefficients == matrix.rows
        // size of result: number of rows of first x number of cols second
        auto result = Matrix(1, m.cols );

        //fill matrix
        result.add_polynom(Polynom(0));

        //calculate values
        for (int col = 0; col < result.cols; col++)
        {
            for (int p_row = 0; p_row < p.get_coefficients().size(); p_row++)
            {
                int value = p.get_coefficient(p_row) * m.get_coefficient(p_row, col);
                value += result.get_coefficient(0, col);
                result.set_coefficient(0, col, MA::mmod(value, m.get_p()) );
            }
        }

        return result;
    }
}

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

// swaps two rows
void Matrix::swap_rows(int row_a, int row_b)
{
    auto temp_row = values.at(row_a);
    values.at(row_a) = values.at(row_b);
    values.at(row_b) = temp_row;
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

/*
// returns transpose matrix
Matrix Matrix::transpose() const
{
    Matrix transpose = Matrix(cols, rows);

    for (int i = 0; i < cols; i++)
        transpose.values.push_back(Polynom(0));

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            transpose.values.at(col).set_coefficient(row, this->values.at(row).get_coefficient(col));
        }
    }

    return transpose;
}
*/

// Not just sort but use the Gauss-Jordan-elimination
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
        //        sep(std::to_string(pivot_row) + "," + std::to_string(pivot_col));
        //        std::cout << this->to_vector_str() << std::endl;

        /* Find the pivot element in the current column: */
        int max_index = idx_of_max_value_in_col(pivot_row, pivot_col);

        // Debug information
        //        std::cout << "Max index: " << max_index << "," << pivot_col << " Value: " << values[max_index].get_coefficients().at(pivot_col) << std::endl;

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

            // redo this so it correctly cleans up the matrix
            // Man zieht danach von den darüberliegenden Zeilen entsprechende Vielfache ab, sodass über einer führenden 1 nur Nullen stehen.
            auto row = values[pivot_row];
            for (int i = pivot_row - 1; i >= 0; i--) {
                std::cout << i << std::endl;
                auto row_above = values[i];
                if (row_above.get_coefficient(pivot_col) != 0) {
                    for (int i = 0; i < cols; ++i) {
                        auto result = Basis::modulo_group_mod((row_above.get_coefficient(i) - row.get_coefficient(i)), 2);
                        row_above.set_coefficient(i, result);
                    }
                }
            }

            /* Increase pivot row and column */
            pivot_row++;
            pivot_col++;
        }
    }
}

/*
 * Gauss Jordan Elimination vorgehen:
 * 1. Auswählen der ersten Spalte von links, in der mindestens ein Wert != 0 ist
 * 2. Ist die oberste Zahl der gewählten Spalte eine Null, so vertauscht man die erste Zeile mit einer anderen Zeile,
 *      in der in dieser Spalte keine Null steht
 * 3. Man dividiert die erste Zeile durch das nun oberste Element der gewählten Spalte
 * 4. Man subtrahiert entsprechende Vielfache der ersten Zeile von den darunterliegenden Zeilen mit dem Ziel,
 *      dass das erste Element jeder Zeile (außer der ersten) Null wird
 * 5. Durch Streichen der ersten Zeile und Spalte erhält man eine Restmatrix, auf die man diese Schritte wieder
 *      anwendet. Das führt man so lange durch, bis die Matrix in Zeilenstufenform ist
 * 6. Man zieht danach von den darüberliegenden Zeilen entsprechende Vielfache ab, sodass über einer führenden 1 nur
 *      Nullen stehen
 */

// Vorgehen mit einer augmented Matrix zur eventuellen Erstellung einer Generatormatrix
Matrix Matrix::to_canonical_via_GJE(const int p) {
    Matrix matrix_copy = Matrix(rows, cols, values);
    Matrix augmented_matrix = Matrix(rows, cols * 2, values);

    // init augmented matrix
    for (int i = 0; i < rows; i++) {
        augmented_matrix.values.at(i).set_coefficient(i + cols, 1);
    }

    // row operations to transform augmented matrix into row-echolon form
    for (int row = 0; row < rows; row++) {
        // find pivot row and swap
        int max_row = row;
        for (int i = row + 1; i < rows; i++) {
            auto val = augmented_matrix.values.at(i).get_coefficient(row);
            auto pivot_val = augmented_matrix.values.at(max_row).get_coefficient(row);

            if (abs(val) > abs(pivot_val))
                max_row = i;
        }

        augmented_matrix.swap_rows(row, max_row);

        // reduce pivot point
        for (int i = row + 1; i < rows; i++) {

            auto div = augmented_matrix.values.at(i).get_coefficient(row);
            auto div_piv = augmented_matrix.values.at(row).get_coefficient(row);
            int factor = 1;
            if (div_piv != 0) {
                factor = div / div_piv;
            }

            for (int j = row; j < 2 * augmented_matrix.cols; j++) {

                int diff = factor * augmented_matrix.values.at(row).get_coefficient(j);

                int diff_piv = augmented_matrix.values.at(i).get_coefficient(j) - diff;

                augmented_matrix.values.at(i).set_coefficient(j, diff_piv);
            }
        }
    }

    // perfom back substitiution to transform augmented matrix into reduced row echolon form
    for (int row = rows - 1; row >= 0; row--) {

        // normalize pivot row
        int pivot = augmented_matrix.values.at(row).get_coefficient(row);

        if (pivot != 0) {

            for (int j = row; j < 2 * augmented_matrix.cols; j++) {
                auto div = augmented_matrix.values.at(row).get_coefficient(j);
                augmented_matrix.values.at(row).set_coefficient(j, div / pivot);
            }

            // zero out entries above pivot
            for (int i = row - 1; i >= 0; i--) {
                int factor = augmented_matrix.values.at(i).get_coefficient(row) /
                             augmented_matrix.values.at(row).get_coefficient(row);

                for (int j = row; j < 2 * augmented_matrix.cols; j++) {
                    int fac = factor * augmented_matrix.values.at(row).get_coefficient(j);
                    int dif = augmented_matrix.values.at(i).get_coefficient(j) - fac;
                    augmented_matrix.values.at(i).set_coefficient(j, dif);
                }
            }
        }
    }

    // define size of canonical matrix. Check if there are all 0 rows in the non-augmented matrix part
    int row_number = 0;
    int col_number = 0;
    for (int row = 0; row < rows; row++)
    {
        for(int col = 0; col < matrix_copy.cols; col++)
        {
           if (augmented_matrix.values.at(row).get_coefficient(col) != 0)
           {
               row_number ++;
               break;
           }
        }
    }

    for (int col = 0; col < matrix_copy.cols; col++)
    {
        for (int row = 0; row < rows; row++)
        {
            if (augmented_matrix.values.at(row).get_coefficient(col) != 0)
            {
                col_number ++;
                break;
            }
        }
    }

    // extract canonical form of the matrix
    //Matrix canonical_matrix = Matrix(row_number, matrix_copy.cols);
    Matrix canonical_matrix = Matrix(row_number, col_number);

    for (int i = 0; i < row_number; i++) {
        canonical_matrix.values.push_back(Polynom(0));
    }

    for (int row = 0; row < row_number; row++) {
        for (int col = 0; col < matrix_copy.cols; col++) {
            auto val = Basis::modulo_group_mod(augmented_matrix.values.at(row).get_coefficient(col), p);
            canonical_matrix.values.at(row).set_coefficient(col, val);
        }
    }

    return canonical_matrix;

    // generator matrix
    /*
    // extract canonical generator matrix from augmented matrix
    Matrix generatormatrix = Matrix(matrix_copy.rows, matrix_copy.cols, matrix_copy.values);

    for (int i = 0; i < augmented_matrix.rows; i++)
    {
        for (int j = 0; j < matrix_copy.cols; j++)
        {
            generatormatrix.values.at(i).set_coefficient(j, augmented_matrix.values.at(i).get_coefficient(j+matrix_copy.cols));
        }
    }

    std::cout << " generator matrix : " << std::endl;
    std::cout << generatormatrix.to_vector_str() << std::endl;

    return generatormatrix;
    */
}

/*
// G => H= -P^t
Matrix Matrix::to_control_matrix() const
{
    // 4x3
    Matrix generatormatrix = Matrix(rows, cols, values);

    // init control matrix
    int cols_T = 0;
    int rows_T = 0;

    if (cols >= rows)
    {
        cols_T = cols - rows;
        rows_T = cols;
    }
    else
    {
        cols_T = rows - cols;
        rows_T = rows;
    }


    std::cout << "col_t: " << cols_T << std::endl;
    std::cout << "row_t: " << rows_T << std::endl;

    // 3x4
    Matrix controlmatrix = Matrix(rows_T, cols_T);

    for (int i = 0; i < rows_T; i++) {
        controlmatrix.values.push_back(Polynom(0));
    }

    std::cout << "empty control: " << std::endl;
    std::cout << controlmatrix.to_vector_str() << std::endl;
    std::cout << controlmatrix.values.size() << std::endl;

    // transpose generator matrix
    Matrix generatormatrix_T = generatormatrix.transpose();

    std::cout << "transpose " << std::endl;
    std::cout << generatormatrix_T.to_vector_str() << std::endl;

    // calc control matrix
    for (int col = 0; col < cols_T; col++)
    {
        std::cout << " col: " << col << std::endl;

        for (int row = 0; row < rows_T; row++)
        {
            std::cout << "row: " << row << std::endl;

            if (col >= rows_T)
            {
                std::cout << "last" << std::endl;
                int value = (col - rows_T == row) ? 1 : 0;

                controlmatrix.values.at(row).set_coefficient(col, value  );
            }
            else
            {
                std::cout << " last 0 " << std::endl;

                auto val = generatormatrix_T.values.at(col).get_coefficient(row);

                std::cout << " ok" << std::endl;
                controlmatrix.values.at(row).set_coefficient(col, val);
            }
        }
    }

    std::cout << "return" << std::endl;
    return controlmatrix;
}
*/



/*
Matrix Matrix::to_control_matrix() const
{
    int rows_T = cols - rows;
    int cols_T = cols;

    auto paritycheckmatrix = Matrix(rows_T, cols_T);

    for (int row = 0; row < rows_T; row++) {
        paritycheckmatrix.values.push_back(Polynom(0));
    }

    for (int row = 0; row < rows_T; row++) {
        for (int col = 0; col < cols_T; col++) {

            int pivot_col = col - (cols - rows); // Determine the corresponding row in the generator matrix.

            if (pivot_col >= 0 && pivot_col < rows) {

                int num_ones = 0;

                for (int l = 0; l < rows; l++)
                {
                    if (this->values.at(l).get_coefficient(pivot_col) == 1)
                    {
                        num_ones++;
                    }
                }
                if (num_ones % 2 == 1)
                {
                    paritycheckmatrix.values.at(row).set_coefficient(col-rows_T, 1); // Set coefficient based on current column being processed.
                }
            }
        }
    }

    for (int row = 0; row < rows_T; row++) {
        std::cout << std::endl;
        for (int col = 0; col < cols_T; col++) {
            std::cout << paritycheckmatrix.values.at(row).get_coefficient(col) << ", ";
        }

    }


    return paritycheckmatrix;
}
*/




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


Matrix Matrix::to_control_matrix() const {
    auto matrix_without_steps = sub_matrix(0, rows);

    // Transpose the original matrix
    Matrix transposed = matrix_without_steps.transpose();

    // Create a new matrix object to store the control matrix
    int n = cols;
    int k = rows;
    Matrix control_matrix = Matrix(n + n - k, n - k);

    // Copy the transposed matrix to the control matrix
    control_matrix.values = transposed.values;

    // Append rows of zeroes to the control matrix
    for (int i = transposed.rows; i < control_matrix.rows; i++) {
        control_matrix.values.push_back(Polynom(0));
    }

    // Return the control matrix
    return control_matrix;
}


Matrix Matrix::transpose() const {
    Matrix transposed = Matrix(cols, rows);
    auto transposed_values = std::vector<Polynom>();

    for (int j = 0; j < cols; j++) {
        auto tem_values = std::vector<int>();
        for (int i = 0; i < rows; i++) {
            auto cell_value = values[i].get_coefficients()[j];
            tem_values.push_back(cell_value);
        }
        transposed_values.emplace_back(tem_values, false);
    }
    transposed.values = transposed_values;
    return transposed;
}
Matrix Matrix::sub_matrix(int row_idx, int col_idx) const {
    //auto sub_rows = rows - row_idx;
    //auto sub_cols = cols - col_idx;
    // Matrix result = Matrix(sub_rows, cols - col_idx);
    std::vector<Polynom> sub_values = {};
    for (int row = row_idx; row < rows; row++) {
        std::vector<int> temp = {};
        for (int col = col_idx; col < cols; col++) {
            auto val = values.at(row).get_coefficient(col);
            temp.push_back(val);
        }
        sub_values.push_back(Polynom(temp));
    }

    return Matrix(sub_values);;
}





