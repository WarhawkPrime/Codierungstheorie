//
// Created by Dennis on 27/10/2022.
//

#ifndef CODIERUNGSTHEORIE_HELPER_H
#define CODIERUNGSTHEORIE_HELPER_H

#include <bitset>

// 1. Use std::bitset<N>, defined in the <bitset> header, where N is the number of bits (not bytes).
// 2. Compute the Hamming distance between two binary codes a and b using (a ^ b).count().
// Use xOR to get the diff then count it

/**
 * Calculates the hamming distance between two integer values
 * @param a
 * @param b
 * @return
 */
int calc_hamming_distance(int a, int b)
{
    constexpr int s = sizeof(int) * 8;

    int aXORb = a ^ b;

    int hamming_distance = std::bitset<s>(aXORb).count();

    return hamming_distance;
}


#endif //CODIERUNGSTHEORIE_HELPER_H
