//
// Created by Admin on 06.03.2023.
//

#include "Header Files/Task_6/ReedSolomonCode.h"

Polynom ReedSolomonCode::decode(Polynom codeword) const {
    return codeword;
}
Polynom ReedSolomonCode::encode(Polynom msg) const {
    return msg;
}
ReedSolomonCode::ReedSolomonCode(
    int e,
    int d,
    Gruppe gruppe)
    : e(e),
      q(pow(2, e)),
      gruppe(gruppe),
      alpha(gruppe.primitive),
      Code(q - 1, q - d, d) {
}