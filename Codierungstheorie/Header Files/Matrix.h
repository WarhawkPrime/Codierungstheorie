//
// Created by Noah Ruben on 10.01.23.
//

#ifndef CODIERUNGSTHEORIE_MATRIX_H
#define CODIERUNGSTHEORIE_MATRIX_H

#include "EGF.h"
#include <cassert>
#include <string>
#include <vector>

#include "Header Files/ModularArithmetic.h"

class EGF;
class Polynom;

void sep(std::string);


class Matrix {

  public:
    const int rows; // Often M
    const int cols; // Often N
    int p = 2;
    /**
     * @brief This constructor initializes a matrix with the given number of rows and columns, and sets the values of the matrix to the given vector of Polynom objects.
     *
     * @param rows The number of rows in the matrix
     * @param cols The number of columns in the matrix
     * @param values - A vector of Polynom objects representing the values of the matrix
     */
    Matrix(const int rows, const int cols, const std::vector<Polynom> &values) : rows(rows), cols(cols), values(values), egf(EGF::create_EGF_on_degree(cols)){};

    /**
     * @brief Constructor for a Matrix object
     * @param values - a vector of Polynom objects that will be used to populate the matrix
     *
     * This constructor creates a matrix object with the number of rows equal to the size of the input vector and the number of columns equal to the degree of the polynomials in the vector plus one.
     * It also performs some validation checks:
     * - It asserts that the input vector is not empty
     * - It checks that all the polynomials in the input vector have the same degree plus one.
     *   If not, it asserts that this should not happen.
     */
    explicit Matrix(std::vector<Polynom> values) : Matrix(values.size(), values[0].get_degree() + 1, values) {
        // Check if the vector is not empty
        if (values.empty()) {
            throw std::invalid_argument("Vector of Polynom objects cannot be empty.");
        }

        // Get the degree of the polynomials in the vector
        int colums = values[0].get_degree() + 1;

        // Iterate through the vector and check if all polynomials have the same degree
        for (const auto &item : values) {
            if (item.get_degree() + 1 != colums) {
                throw std::invalid_argument("All Polynom objects in the vector must have the same degree.");
            }
        }
    };

    /**
     * @brief Constructor for creating a Matrix of size 'rows' by 'cols' with empty Polynom values
     *
     * @param rows The number of rows in the matrix
     * @param cols The number of columns in the matrix
     */
    Matrix(const int rows, const int cols) : Matrix(rows, cols, std::vector<Polynom>()){};

    void to_canonical_form();

    void swap_rows(int row_a, int row_b);

    Matrix to_control_matrix() const;

    /**
     * This method transform the matrix into its reduced row echelon form.
     * This is done using the Gaussian elimination method,
     * where the pivot element is chosen as the element with the largest absolute value in the current column.
     * The function iterates through each row and column of the matrix,
     * swapping rows if necessary to put the pivot element in the correct position,
     * and then using the pivot element to eliminate any non-zero values in the current column below it.
     * This process continues until the entire matrix is in its reduced row echelon form which is easier to solve.
     *
     * The private variable p is used as the modulus in the calculations.
     */
    Matrix to_canonical_via_GJE(const int p = 2);

    Matrix transpose() const;

    Matrix sub_matrix(int row_idx, int col_idx) const;

    /**
     * @brief This function returns a string representation of the matrix in the form of a list of vectors
     * @return string representation of the matrix
     */
    std::string to_vector_str() const;

    void add_polynom(Polynom p) {values.push_back(p);}
    int get_coefficient(int row, int col) {return values.at(row).get_coefficient(col);}
    void set_coefficient(int row, int col, int value) {values.at(row).set_coefficient(col, value);}


    const int get_p(){return egf.p;}

  private:
    std::vector<Polynom> values;
    const EGF egf;
    int idx_of_max_value_in_col(int starting_row, int col_to_search);
};

namespace MXA {

    // polynom * matrix to calculate errorclass
    Matrix polynom_matrix_multiplication(Polynom p, Matrix m);

    // matrix * matrix to check for correctness of G * H^T = 0

}



#endif // CODIERUNGSTHEORIE_MATRIX_H