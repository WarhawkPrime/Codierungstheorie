//
// Created by Dennis on 16/11/2022.
//

#include "Header Files/Polynom.h"

const Polynom Polynom::ZERO = Polynom({0});
const Polynom Polynom::ONE = Polynom(1);

Polynom::Polynom(std::vector<int> coefficients, bool _trim) {
    this->coefficients = std::move(coefficients);
    if (_trim) {
        //        trim();
    }
}

// TODO mit Bit operations ....
Polynom::Polynom(int coefficients_as_number, bool _trim, int custom_size) {

    int size = 0;
    if (coefficients_as_number > 0) {
        size = floor(log2(coefficients_as_number)) + 1;
    }
    if (custom_size != 0 && custom_size >= size) {
        size = custom_size;
    }

    auto temp_coefficients = std::vector<int>(0);

    auto bs = std::bitset<32>(coefficients_as_number);

    for (int i = size - 1; i >= 0; --i) {
        temp_coefficients.push_back(bs[i]);
    }
    std::reverse(temp_coefficients.begin(), temp_coefficients.end());
    this->coefficients = std::move(temp_coefficients);

    if (_trim) {
        //        trim();
    }
}

int Polynom::get_degree() const {
    return coefficients.size() - 1;
}

std::string Polynom::to_vector_str() const {
    return to_vector_str(0);
}

std::string Polynom::to_vector_str(const int _size) const {

    std::string result = "(";
    int size;
    if (_size != 0) {
        size = _size;
    } else {
        size = coefficients.size();
    }

    for (int i = 0; i < size; ++i) {
        if (i >= coefficients.size()) {
            result += "0";
        } else {
            result += std::to_string(coefficients[i]);
        }
        result += ", ";
    }
    result = result.substr(0, result.length() - 2);

    if (size == 0) {
        result += "0";
    }
    result += ")";
    return result;
}

std::string Polynom::to_polynom_str() const {
    int lenght = coefficients.size();
    std::string result = std::to_string(get_coefficient(0)) + " + ";
    for (int i = 1; i < lenght; ++i) {
        result +=
            std::to_string(get_coefficient(i)) + "x^" + std::to_string(i) + " + ";
    }
    result = result.substr(0, result.length() - 3);
    return result;
}

std::string Polynom::to_print_string(Polynom::Format format) const {
    switch (format) {
    case polynom:
        return to_polynom_str();
    case vector:
        return to_vector_str();
    case number:
        return std::to_string(as_int());
    default:
        std::cout << "Should not be here\n";
        __builtin_unreachable();
    }
}

/**
 * ! This assumes p=2 !
 * ! This means all coefficients will be interpreted as 0 or 1 !
 * @return
 */
int Polynom::as_int() const {
    int result = 0;
    auto size = coefficients.size();
    for (int i = size - 1; i >= 0; --i) {
        result = (result << 1) + get_coefficient(i);
    }
    return result;
}

std::string Polynom::to_print_string(Polynom::Format format, int _size) const {
    if (format == vector) {
        return to_vector_str(_size);
    } else {
        return to_print_string(format);
    }
}
