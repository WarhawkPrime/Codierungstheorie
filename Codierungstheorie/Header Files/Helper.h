//
// Created by Dennis on 27/10/2022.
//

#ifndef CODIERUNGSTHEORIE_HELPER_H
#define CODIERUNGSTHEORIE_HELPER_H

#include <algorithm>
#include <bitset>
#include <iterator>
#include <vector>

/**
 * Irreducible polynom per degree soo script for more infos
 */
const Polynom ip_by_degree[10] = {
    Polynom(7), // Kein explizites irreduzibles Polynom für diesen Grad angegeben
    Polynom(7), // Kein explizites irreduzibles Polynom für diesen Grad angegeben
    Polynom(7),
    Polynom(13),
    Polynom(25),
    Polynom(49),
    Polynom(97),
    Polynom(241),
    Polynom(289),
    Polynom(577)};

// 1. Use std::bitset<N>, defined in the <bitset> header, where N is the number
// of bits (not bytes).
// 2. Compute the Hamming distance between two binary codes a and b using (a ^
// b).count(). Use xOR to get the diff then count it

/**
 * Calculates the hamming distance between two integer values
 * @param a
 * @param b
 * @return
 */
int calc_hamming_distance(int a, int b) {
    constexpr int s = sizeof(int) * 8;

    int aXORb = a ^ b;

    int hamming_distance = std::bitset<s>(aXORb).count();

    return hamming_distance;
}

void sep(std::string str = "") {
    std::cout << std::endl;
    std::cout << "########################  " << str
              << "  ########################" << std::endl;
    std::cout << std::endl;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> vec) {
    os << "{ ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " "));
    os << "}";
    return os;
}

inline const std::string toString(bool boolean) {
    return boolean ? "true" : "false";
}

#endif // CODIERUNGSTHEORIE_HELPER_H
