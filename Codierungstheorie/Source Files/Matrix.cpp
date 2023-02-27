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

// swaps two rows
void Matrix::swap_rows(int row_a, int row_b)
{
    auto temp_row = values.at(row_a);
    values.at(row_a) = values.at(row_b);
    values.at(row_b) = temp_row;
}


// returns transpose matrix
Matrix Matrix::transpose()
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
Matrix Matrix::to_canonical_via_GJE()
{
    Matrix matrix_copy = Matrix(rows, cols, values);
    Matrix augmented_matrix = Matrix(rows, cols *2, values);

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

        //reduce pivot point
        for (int i = row + 1; i < rows; i++) {

            auto div = augmented_matrix.values.at(i).get_coefficient(row);
            auto div_piv = augmented_matrix.values.at(row).get_coefficient(row);

            int factor = div / div_piv;

            for (int j = row; j < 2 * augmented_matrix.cols ; j++) {

                int diff = factor * augmented_matrix.values.at(row).get_coefficient(j);

                int diff_piv = augmented_matrix.values.at(i).get_coefficient(j) - diff;

                augmented_matrix.values.at(i).set_coefficient(j, diff_piv);
            }
        }
    }

    // perfom back substitiution to transform augmented matrix into reduced row echolon form
    for (int row = rows -1; row >= 0; row--)
    {

        //normalize pivot row
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

    for (int i = 0; i < row_number; i++)
    {
        canonical_matrix.values.push_back(Polynom(0));
    }

    for (int row = 0; row < row_number; row++)
    {
       for(int col = 0; col < matrix_copy.cols; col++)
       {
           canonical_matrix.values.at(row).set_coefficient(col, augmented_matrix.values.at(row).get_coefficient(col));
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


// G => H= -P^t
Matrix Matrix::to_control_matrix()
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



std::string Matrix::to_vector_str() const {
    auto result = std::string();
    for (const auto &item : values) {
        result.append(item.to_vector_str(cols)).append("\n");
    }
    return result;
}
