//
// Created by Noah Ruben on 05/11/2022.
//

#include "Header Files/ModularArithmetic.h"

namespace MA {
int mmod(int i, int mod) {
    auto result = i % mod;
    if (result < 0)
        result += mod;
    return result;
}

int gcd(int a, int b) {
    auto rest = mmod(a, b);
    if (rest == 0)
        return b;
    return gcd(b, rest);
}

// 1 , 0                            0, 1
exgcd_result exgcd(int a, int b, std::pair<int, int> xs,
                   std::pair<int, int> ys) {
    auto rest = mmod(a, b);
    auto q = a / b;
    //   x_i = x_{i-2}  - (x_{i-1}   * q_i)
    auto x = xs.first - (xs.second * q);
    //   y_i = y_{i-2}  - (y_{i-1}   * q_i)
    auto y = ys.first - (ys.second * q);

    if (rest == 0)
        return {b, xs.second, ys.second};

    return exgcd(b, rest, std::pair(xs.second, x), std::pair(ys.second, y));
}

int inverse(int i, int mod) {
    int inverse = exgcd(i, mod).inverse_a;
    return mmod(inverse, mod);
}
} // namespace MA