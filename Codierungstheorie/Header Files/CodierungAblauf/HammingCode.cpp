//
// Created by Noah Ruben on 01.03.23.
//

#include "HammingCode.h"
HammingCode::HammingCode(const int _m) : m(_m), Code(calculate_N()) {
    if (m < 3) {
        exit(1);
    }

    // TODO
}
