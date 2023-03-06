//
// Created by denni on 04/03/2023.
//

#include "Header Files/CodierungAblauf/ReedMueller.h"




/*
ReedMueller::ReedMueller(const int _r, const int _m) : r(_r), m(_m),
                                         Code(calculate_N(_m), calculate_K(_m), 3),
                                         control_matrix(std::move(create_control_matrix())),
                                         syndrom_table(MXA::create_syndrom_table(std::make_shared<Matrix>(control_matrix.transpose()))),
                                         generator_matrix(std::move(control_matrix.to_generator_matrix())) {
    if (m < 3) {
        exit(1);
    }
}
*/


ReedMueller::ReedMueller(const int _r, const int _m) : r(_r), m(_m),
                                                    generator_matrix(std::move(generate_reed_mueller(_r, _m))),
                                                    Code(calculate_N(_r, _m), calculate_K(_r, _m), calculate_d(_r, _m)),
                                                   control_matrix(generator_matrix.to_control_matrix()),
                                                   syndrom_table(MXA::create_syndrom_table(std::make_shared<Matrix>(control_matrix.transpose())))
{

}




/*
Matrix ReedMueller::create_control_matrix() {
    auto result = std::vector<Polynom>();
    auto identity_values = std::vector<Polynom>();
    for (int i = m - 1; i >= 0; i--) {
        auto base = pow(2, i);
        for (int j = 1; j < base; ++j) {
            auto temp = Polynom(base + j, false);
            result.emplace_back(temp);
        }
        identity_values.push_back(Polynom(base, false, m));
    }
    std::reverse(identity_values.begin(), identity_values.end());
    result.insert(result.end(), identity_values.begin(), identity_values.end());
    auto gen_matrix = Matrix(calculate_N(m), m, result);
    return gen_matrix.transpose();
}
 */


Polynom ReedMueller::decode(Polynom codeword) const {
    auto corrected_codeword = remove_error(codeword);

    auto msg_values = std::vector<int>();

    for (int i = n - k; i < corrected_codeword.get_degree(); ++i) {
        msg_values.push_back(corrected_codeword.get_coefficient(i));
    }
    return Polynom(msg_values, false);
}
Polynom ReedMueller::encode(Polynom msg) const {
    return MXA::matrix_matrix_multiplication(Matrix({msg}), generator_matrix).values[0];
}
Polynom ReedMueller::remove_error(Polynom codeword) const {
    auto ht = control_matrix.transpose();
    auto syn = MXA::matrix_matrix_multiplication(Matrix({codeword}), ht).values[0];
    for (int i = 0; i < ht.values.size(); ++i) {
        if (syn.as_int() == ht.values[i].as_int()) {
            int error_as_number = (int)pow(2, i);
            auto error = Polynom(error_as_number, false, codeword.get_degree() + 1);
            std::cout << "Error at position: " << i << " using " << error.to_vector_str() << " to correct." << std::endl;
            return (codeword + error) % 2;
        }
    }
    // std::cout << "No error detected -> nothing to correct!";
    return codeword;
}

/**
  *
  * @param r order of the code
  * @param m number of vaiables
  * @return
  */
Matrix ReedMueller::generate_reed_mueller(int r, int m)
{
    // 1xm identity matrix
    if(m == 0)
    {
        std::vector<Polynom> values = {
                Polynom({1}, false)
        };

        auto res = Matrix(1, 1, values);
        return res;
    }
    else if (r == 0) // is there a rule?
    {
        int row_n = 1;
        int col_n = pow(2, m);//1

        // 2^m
        auto res = Matrix(row_n, col_n);
        res.add_polynom(Polynom({1}));

        for (int i = 1; i < col_n; i++)
        {
            res.set_coefficient(0, i, 1);
        }

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
    }
    else // recursive
    {
        // generate G1 and G2
        Matrix G1 = generate_reed_mueller(r, m-1);
        Matrix G2 = generate_reed_mueller(r-1, m-1);

        int row_number = G1.rows + G2.rows;
        int col_number = G1.cols * 2;

        // create 0 Matrix with needed size
        Matrix gen = Matrix(row_number, col_number);

        for (int i = 0; i < row_number; i++) {
            gen.add_polynom(Polynom({0}, false));
        }

        // put matrix together
        // G(r, m) := ( G(r, m-1) G(r, m-1)   )
        //            ( 0       ) G(r-1, m-1) )

        // upper Left rows == rows, cols == cols
        for (int row = 0; row < G1.rows; row++)
        {
            for (int col = 0; col < G1.cols; col++)
            {
                gen.set_coefficient(row, col, G1.get_coefficient(row, col));
            }
        }

        // upper right
        for (int row = 0; row < G1.rows; row++)
        {
            for (int col = 0 + G1.cols; col < (G1.cols *2); col++)
            {
                gen.set_coefficient(row, col, G1.get_coefficient(row, col-G1.cols));
            }
        }

        // lower right
        for (int row = G1.rows; row < (G1.rows + G2.rows); row++)
        {
            for (int col = 0 + G1.cols; col < (G1.cols *2); col++)
            {
                gen.set_coefficient(row, col, G2.get_coefficient(row-G1.rows, col-G1.cols));
            }
        }

        // lower left stays 0

        std::cout << "RM: " << std::endl;
        std::cout << gen.to_vector_str() << std::endl;

        // return Matrix
        return gen;
    }
}
