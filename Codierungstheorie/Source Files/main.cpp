

#include "Header Files/Basis.h"
#include <iostream>

void sep(std::string str = "");

template <size_t rows, size_t cols>
void print_2D_array(int (&A)[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
template <size_t rows, size_t cols>
int argmax(int row_to_begin_with, int coll_to_search, int (&A)[rows][cols]) {
    int max_row_index = 0;
    double max_value = 0;

    for (int i = row_to_begin_with; i < rows; i++) {
        auto value = abs(A[i][coll_to_search]);
        if (value > max_value) {
            max_row_index = i;
            max_value = value;
        }
    }

    return max_row_index;
}

int main(int argc, char **argv) {
    const int n = 4, m = 8;
    // clang-format off
    int A[m][n] = {
{0, 1, 1, 0},
{1, 0, 0, 0},
{0, 1, 0, 0},
{1, 0, 0, 0},
{0, 1, 0, 0},
{1, 0, 0, 0},
{0, 1, 0, 0},
{0, 1, 0, 1}};
    // clang-format on
    int h_r = 0; /* Initialization of the pivot row */
    int k_c = 0; /* Initialization of the pivot column */
    while (h_r < m && k_c < n) {
        sep(std::to_string(h_r) + "," + std::to_string(k_c));
        print_2D_array(A);
        /* Find the k_c-th pivot: */
        int i_max = argmax(k_c, h_r, A);
        std::cout << "imax: " << i_max << "," << k_c << " Value: " << A[i_max][k_c] << std::endl;
        if (A[i_max][k_c] == 0) {
            /* No pivot in this column, pass to next column */
            k_c++;
            std::cout << "No pivot in this column, pass to next column" << std::endl;
        } else {
            /* swap rows(h_r, i_max) */
            std::swap(A[h_r], A[i_max]);

            /* Do for all rows below pivot: */
            for (int row_below = h_r + 1; row_below < m; row_below++) {
                /* Fill with zeros the lower part of pivot column: */
                A[row_below][k_c] = 0;
                /* Do for all remaining elements in current row: */
                for (int j = k_c + 1; j < n; j++) {
                    A[row_below][j] = Basis::modulo_group_mod(A[row_below][j] - A[h_r][j], 2);
                }
            }
            auto row_above = A[h_r - 1];
            auto row = A[h_r];
            if (h_r > 0 && row_above[k_c] != 0) {
                for (int i = 0; i < n; ++i) {
                    row_above[i] = Basis::modulo_group_mod((row_above[i] - row[i]), 2);
                }
            }

            sep("After");
            print_2D_array(A);
            /* Increase pivot row and column */
            h_r++;
            k_c++;
        }
    }
    /*    for (int row = 3; row >= 0; --row) {
            for (int col = 0; col <= 3; col++) {
                A[row][col] = A[row][col] - A[row][col];
            }
        }*/

    sep("");
    sep("");
    sep("Finish");
    print_2D_array(A);
    return 0;
}
