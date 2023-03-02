//
// Created by Noah Ruben on 01.03.23.
//

#include "HammingCode.h"
HammingCode::HammingCode(const int _m) : m(_m), Code(calculate_N()), control_matrix(std::move(create_control_matrix())), generator_matrix(std::move(control_matrix.to_generator_matrix())) {
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
            std::cout << temp.to_vector_str(3) << std::endl;
            result.emplace_back(temp);
        }
        identity_values.push_back(Polynom(base, false, m));
    }
    result.insert(result.begin(), identity_values.begin(), identity_values.end());
    auto gen_matrix = Matrix(calculate_N(), m, result);
    return gen_matrix.transpose();
}
Polynom HammingCode::decode(Polynom codeword) const {
    return codeword;
}
Polynom HammingCode::encode(Polynom msg) const {
    return msg;
    //    return MXA::polynom_matrix_multiplication(msg, generator_matrix);
}
