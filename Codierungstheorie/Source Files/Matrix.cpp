//
// Created by Noah Ruben on 10.01.23.
//

#include "Header Files/Matrix.h"

namespace MXA {
// mxn x nxp -> mxp
// rowxcol x colxrowp -> rowxrowp
Matrix polynom_matrix_multiplication(Polynom p, Matrix m) {
    // polynoms row = 1, so number of coefficients == matrix.rows
    // size of result: number of rows of first x number of cols second
    auto result = Matrix(1, m.cols);

    // fill matrix
    result.add_polynom(Polynom(0));

    // calculate values
    //
    for (int col = 0; col < result.cols; col++) {
        // for (int p_row = 0; p_row < p.get_coefficients().size(); p_row++)
        for (int p_row = p.get_coefficients().size() - 1; p_row > -1; p_row--) {
            // int value = p.get_coefficient(p_row) * m.get_coefficient(p_row, col); // TODO FEHLER
            int value = p.get_coefficient(p_row) * m.get_coefficient((m.rows - p_row - 1), col);
            value += result.get_coefficient(0, col);
            result.set_coefficient(0, col, MA::mmod(value, m.get_p()));
        }
    }

    return result;
}

Matrix polynom_matrix_multiplication(std::shared_ptr<Polynom> p, Matrix m) {

    // polynoms row = 1, so number of coefficients == matrix.rows
    // size of result: number of rows of first x number of cols second
    auto result = Matrix(1, m.cols);

    // fill matrix
    result.add_polynom(Polynom(0));

    // calculate values
    for (int col = 0; col < result.cols; col++) {
        // for (int p_row = 0; p_row < p->get_coefficients().size(); p_row++)
        for (int p_row = p->get_coefficients().size() - 1; p_row > -1; p_row--) {
            // int value = p->get_coefficient(p_row) * m.get_coefficient(p_row, col);
            int value = p->get_coefficient(p_row) * m.get_coefficient((m.rows - p_row - 1), col);
            value += result.get_coefficient(0, col);
            result.set_coefficient(0, col, MA::mmod(value, m.get_p()));
        }
    }

    return result;
}

Matrix matrix_matrix_multiplication(const Matrix &a, const Matrix &b) {
    auto res = Matrix(a.rows, b.cols);

    for (int i = 0; i < res.rows; i++) {
        res.add_polynom(Polynom(0));
    }

    // row X col
    for (int row = 0; row < a.rows; row++) {
        for (int col = 0; col < b.cols; col++) {
            int value = 0;

            for (int k = 0; k < b.rows; k++) {
                value += a.get_coefficient(row, k) * b.get_coefficient(k, col);
            }
            res.set_coefficient(row, col, MA::mmod(value, res.get_p()));

            /*
            int value = a.get_coefficient(row, col) * b.get_coefficient(col, row);
            value += res.get_coefficient(row, col);
            res.set_coefficient(row, col, MA::mmod(value, res.get_p()));
            */
        }
    }

    return res;
}

Syndrom_table create_syndrom_table(std::shared_ptr<Matrix> parity_check_matrix) {
    // init syndrom tabel
    Syndrom_table st = Syndrom_table(parity_check_matrix);

    // create list of all possible errors. Max number: q^n-k : 2^5-2 = 2^3 = 8
    // d-1 / 2 max number of "safe" syndroms

    // create helper polynom to get max number of errors
    int max_polynom_size = parity_check_matrix->rows;
    auto helper = Polynom(0);
    for (int i = 0; i < max_polynom_size; i++)
        helper.set_coefficient(i, 1);

    // fill syndrom table
    for (int i = 0; i < helper.as_int() + 1; i++) {
        // error
        std::shared_ptr<Polynom> error = std::make_shared<Polynom>(i);

        // syndrom
        auto syndrom_res = MXA::polynom_matrix_multiplication(error, *parity_check_matrix);
        std::shared_ptr<Matrix> syndrom = std::make_shared<Matrix>(syndrom_res);

        // insert into map
        // syndrom matrices must be unique. prefer errors with the least amount of 1s
        bool found = false;
        auto it = st.syndrom_table.begin();
        while (it != st.syndrom_table.end()) {
            if (it->first->to_vector_str() == syndrom->to_vector_str()) {
                found = true;
                if (error->get_non_zero_number() < it->second->get_non_zero_number()) {
                    // erase
                    it = st.syndrom_table.erase(it);

                    // insert
                    st.syndrom_table.insert({syndrom, error});
                } else {
                    ++it;
                }
            } else {
                ++it;
            }
        }

        if (!found)
            st.syndrom_table.insert({syndrom, error});
    }
    return st;
}

Matrix calculate_syndrom(Polynom codeword, std::shared_ptr<Matrix> parity_check_matrix) {
    auto syndrom = polynom_matrix_multiplication(codeword, *parity_check_matrix);
    return syndrom;
}

Polynom correct_codeword(Polynom codeword, Syndrom_table syndrom_table) {
    // calc syndrom of codeword
    auto syndrom = calculate_syndrom(codeword, syndrom_table.parity_check_matrix);

    // find syndrom in syndrom_table
    if (syndrom_table.syndrom_table.find(std::make_shared<Matrix>(syndrom)) != syndrom_table.syndrom_table.end()) {
        // if found, get error code
        auto error_poly = syndrom_table.syndrom_table.find(std::make_shared<Matrix>(syndrom))->second;
        std::cout << "s: " << syndrom.to_vector_str() << std::endl;
        std::cout << "e: " << error_poly.get()->to_vector_str() << std::endl;
        auto result = (codeword + *error_poly.get()) % 2;
        return result;
    } else {
        return codeword;
    }
}

/**
 * Im Endeffekt sol für jeden möglichen Fehler das Syndrom berechnet werden und in eine Tabelle gespeichert werden
 * Aus dieser Tabelle soll man dann einen Fehler als Value bekommen, wenn als Key das zugehörige Syndrom gebildet
 * wird
 * @param control_matrix
 */
void SyndromTable::init_syndrom_table(Matrix control_matrix) {

    // create list of all possible errors. Max number: q^n-k : 2^5-2 = 2^3 = 8
    // d-1 / 2 max number of "safe" syndroms

    // create helper polynom to get max number of errors
    int max_polynom_size = control_matrix.rows;
    auto helper = Polynom(0);
    for (int i = 0; i < max_polynom_size; i++)
        helper.set_coefficient(i, 1);

    // fill syndrom table
    for (int i = 0; i < helper.as_int() + 1; i++) {
        // error
        std::shared_ptr<Polynom> error = std::make_shared<Polynom>(i);

        // syndrom
        auto syndrom_res = MXA::polynom_matrix_multiplication(error, control_matrix);
        std::shared_ptr<Matrix> syndrom = std::make_shared<Matrix>(syndrom_res);

        // insert into map
        // syndrom matrices must be unique. prefer errors with the least amount of 1s
        bool found = false;
        auto it = syndrom_map.begin();
        while (it != syndrom_map.end()) {
            if (it->first->to_vector_str() == syndrom->to_vector_str()) {
                found = true;
                if (error->get_non_zero_number() < it->second->get_non_zero_number()) {
                    // erase
                    it = syndrom_map.erase(it);

                    // insert
                    syndrom_map.insert({syndrom, error});
                } else {
                    ++it;
                }
            } else {
                ++it;
            }
        }

        if (!found)
            syndrom_map.insert({syndrom, error});
    }
}

Polynom SyndromTable::corr_codeword(Polynom codeword) {
    // calc syndrom of codeword
    auto syndrom = MXA::polynom_matrix_multiplication(codeword, this->_control_matrix);

    // find syndrom in syndrom_table
    if (syndrom_map.find(std::make_shared<Matrix>(syndrom)) != syndrom_map.end()) {
        // if found, get error code
        auto error_poly = syndrom_map.find(std::make_shared<Matrix>(syndrom))->second;

        auto result = (codeword + *error_poly.get()) % 2;
        return result;
    } else {
        return codeword;
    }
}

Polynom maximum_likelihood_detection(Polynom received_word, Matrix controlmatrix, SyndromTable syndromtable) {
    Polynom most_likely_codeword = received_word;
    int min_distance = received_word.get_non_zero_number();

    // iterate over all codewords
    for (int i = 0; i < controlmatrix.rows; i++) {
        Polynom codeword(controlmatrix.get_polynom(i));

        // compute the Hamming distance between the received word and the codeword
        Polynom distance = (received_word + codeword) % 2;

        // if the Hamming distance is smaller than the minimum distance so far, update the minimum distance and the most likely codeword
        if (distance.get_non_zero_number() < min_distance) {
            min_distance = distance.get_non_zero_number();
            most_likely_codeword = codeword;
        }
    }

    // decode the most likely codeword using the syndrom table
    Polynom decoded_message = syndromtable.corr_codeword(most_likely_codeword);

    return decoded_message;
}

Matrix ns_generate_reed_mueller(int r, int m) {
    std::cout << "r: " << r << "m: " << m << std::endl;

    // 1xm identity matrix
    if (m == 0) {
        std::vector<Polynom> values = {
            Polynom({1}, false)};

        auto res = Matrix(1, 1, values);
        return res;
    } else if (r == 0) {
        std::cout << "last: " << std::endl;

        int row_n = 1;
        int col_n = pow(2, m); // 1

        std::cout << "last: " << col_n << std::endl;

        // 2^m
        auto res = Matrix(row_n, col_n);

        res.add_polynom(Polynom((pow(2, m) - 1), false, col_n));

        std::cout << "l " << std::endl;

        /*
        res.add_polynom(Polynom({1}));

        for (int i = 1; i < col_n; i++)
        {
            std::cout << "i: " << i << std::endl;
            res.set_coefficient(0, i, 1);
        }
         */

        /*
        auto p = Polynom({});

        if (m == 1)
        {
            row_n = 1;
            col_n = 2;
            p = Polynom({1,1}, false);
        }
        else if (m == 2)
        {
            row_n = 1;
            col_n = 4;
            p = Polynom({1,1,1,1}, false);
        }

        auto res = Matrix(row_n, col_n);
        res.add_polynom(p);
        */

        return res;
    } else // recursive
    {
        // generate G1 and G2

        std::cout << "r: " << r - 1 << std::endl;
        std::cout << "m: " << m - 1 << std::endl;

        Matrix G1 = ns_generate_reed_mueller(r, m - 1);
        Matrix G2 = ns_generate_reed_mueller(r - 1, m - 1);

        int row_number = G1.rows + G2.rows;
        int col_number = G1.cols * 2;

        std::cout << "row n: " << row_number << std::endl;
        std::cout << "col n: " << col_number << std::endl;

        // create 0 Matrix with needed size
        std::vector<Polynom> p = std::vector<Polynom>();

        for (int i = 0; i < row_number; i++) {
            p.push_back(Polynom({0}, false));
        }

        std::cout << "l: " << p.size() << std::endl;

        Matrix gen = Matrix(row_number, col_number, p);

        std::cout << "^" << std::endl;

        for (int i = 0; i < row_number; i++) {
            gen.add_polynom(Polynom({0}, false));
        }

        // put matrix together
        // G(r, m) := ( G(r, m-1) G(r, m-1)   )
        //            ( 0       ) G(r-1, m-1) )

        // upper Left rows == rows, cols == cols
        for (int row = 0; row < G1.rows; row++) {
            for (int col = 0; col < G1.cols; col++) {
                gen.set_coefficient(row, col, G1.get_coefficient(row, col));
            }
        }

        // upper right
        for (int row = 0; row < G1.rows; row++) {
            for (int col = 0 + G1.cols; col < (G1.cols * 2); col++) {
                gen.set_coefficient(row, col, G1.get_coefficient(row, col - G1.cols));
            }
        }

        // lower right
        for (int row = G1.rows; row < (G1.rows + G2.rows); row++) {
            for (int col = 0 + G1.cols; col < (G1.cols * 2); col++) {
                gen.set_coefficient(row, col, G2.get_coefficient(row - G1.rows, col - G1.cols));
            }
        }

        // lower left stays 0

        std::cout << "RM: " << std::endl;
        std::cout << gen.to_vector_str() << std::endl;

        // return Matrix
        return gen;
    }
}

} // namespace MXA

int Matrix::number_of_non_zero() {
    int non_zero = 0;
    for (auto p : this->values) {
        for (auto c : p.get_coefficients()) {
            if (c != 0)
                non_zero++;
        }
    }
    return non_zero;
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
void Matrix::swap_rows(int row_a, int row_b) {
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
Matrix Matrix::to_canonical_via_GJE(const int p) const {

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
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < matrix_copy.cols; col++) {
            if (augmented_matrix.values.at(row).get_coefficient(col) != 0) {
                row_number++;
                break;
            }
        }
    }

    for (int col = 0; col < matrix_copy.cols; col++) {
        for (int row = 0; row < rows; row++) {
            if (augmented_matrix.values.at(row).get_coefficient(col) != 0) {
                col_number++;
                break;
            }
        }
    }

    // extract canonical form of the matrix
    // Matrix canonical_matrix = Matrix(row_number, matrix_copy.cols);
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

// See https://en.wikipedia.org/wiki/Parity-check_matrix#Creating_a_parity_check_matrix
Matrix Matrix::to_control_matrix() const {
    // make sure matrix is in row echolon form
    auto row_echolon_form = to_canonical_via_GJE();

    // Create the P matrix by extracting the first rows of the generator matrix
    // TODO this is crude and only works if the first rows are the Einheitsmatrix
    auto P_matrix = row_echolon_form.sub_matrix(0, rows); // This is P

    // Transpose the P matrix to get P^T
    Matrix transposed = P_matrix.transpose();

    std::vector<Polynom> control_values = {};

    int control_matrix_rows = transposed.rows; // Rows in the control matrix

    for (int r = 0; r < control_matrix_rows; ++r) {
        std::vector<int> temp = {};
        // Loop through each column in the control matrix
        for (int c = 0; c < cols; ++c) {
            auto val = 0;
            if (r < control_matrix_rows && c < transposed.cols) { // If we're still within the bounds of P^T, copy the value from P^T
                val = transposed.values.at(r).get_coefficient(c);
            } else if (r == c - transposed.cols) { // If we've reached the end of P^T, create an identity matrix of size (n-k) at the end

                val = 1;
            }
            temp.push_back(val);
        }
        control_values.push_back(Polynom(temp));
    }
    Matrix control_matrix = Matrix(control_matrix_rows, cols, control_values);

    // Return the control matrix and transform it so that the identity matrix is up front
    return control_matrix.to_canonical_via_GJE();
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
    std::vector<Polynom> sub_values = {};
    for (int row = row_idx; row < rows; row++) {
        std::vector<int> temp = {};
        for (int col = col_idx; col < cols; col++) {
            auto val = values.at(row).get_coefficient(col);
            temp.push_back(val);
        }
        sub_values.push_back(Polynom(temp, false));
    }
    return Matrix(rows - row_idx, cols - col_idx, sub_values);
}

Matrix Matrix::to_generator_matrix() const {
    int generator_matrix_rows = cols - rows;
    int generator_matrix_cols = cols;

    std::vector<Polynom> generator_values = {};

    for (int r = 0; r < generator_matrix_rows; ++r) {
        std::vector<int> temp = {};
        for (int c = 0; c < generator_matrix_cols; ++c) {
            auto val = 0;
            if (c >= generator_matrix_rows) {
                val = values.at(c - generator_matrix_rows).get_coefficient(r);
            } else if (r == c) {
                val = 1;
            }
            temp.push_back(val);
        }
        generator_values.push_back(Polynom(temp, false));
    }
    return Matrix(generator_matrix_rows, generator_matrix_cols, generator_values);
}