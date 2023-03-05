//
// Created by Noah Ruben on 01.03.23.
//

#include "Header Files/CodierungAblauf/HammingCode.h"

HammingCode::HammingCode(const int _m) : m(_m),
                                         Code(calculate_N(_m), calculate_K(_m), 3),
                                         control_matrix(std::move(create_control_matrix())),
                                         syndrom_table(MXA::create_syndrom_table(std::make_shared<Matrix>(control_matrix.transpose()))),
                                         generator_matrix(std::move(control_matrix.to_generator_matrix())) {
    if (m < 3) {
        exit(1);
    }
}
Matrix HammingCode::create_control_matrix() {
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

Polynom HammingCode::decode(Polynom codeword) const {
    auto corrected_codeword = remove_error(codeword);

    auto msg_values = std::vector<int>();

    for (int i = n - k; i < corrected_codeword.get_degree(); ++i) {
        msg_values.push_back(corrected_codeword.get_coefficient(i));
    }
    return Polynom(msg_values, false);
}

Polynom HammingCode::encode(Polynom msg) const {
    return MXA::matrix_matrix_multiplication(Matrix({msg}), generator_matrix).values[0];
}

Polynom HammingCode::remove_error(Polynom codeword) const {
    auto ht = control_matrix.transpose();
    auto values = std::vector<Polynom>();
    values.push_back(codeword);

    auto codeword_as_matrix = Matrix(values);
    auto syn = MXA::matrix_matrix_multiplication(codeword_as_matrix, ht).values[0];
    for (int i = 0; i < ht.values.size(); ++i) {
        if (syn.as_int() == ht.values[i].as_int()) {
            int error_as_number = (int)pow(2, i);
            auto error = Polynom(error_as_number, false, codeword.get_degree() + 1);
            // std::cout << "Error at position: " << i << " using " << error.to_vector_str() << " to correct." << std::endl;
            return (codeword + error) % 2;
        }
    }
    // std::cout << "No error detected -> nothing to correct!";
    return codeword;
}
