//
// Created by Noah Ruben on 01.03.23.
//

#ifndef CODIERUNGSTHEORIE_CODE_H
#define CODIERUNGSTHEORIE_CODE_H

#include "Header Files/Polynom.h"
class Code {

  public:
    // TODO should be const. But can only be set in the constructor body since the code ist generate there. CPP man strikes again
    const int n;
    const int k;
    const int d;

    explicit Code(const int n = 8, const int k = 0, const int d = 0) : n(n), k(k), d(d) {}

    virtual Polynom decode(Polynom codeword) const = 0;
    virtual Polynom encode(Polynom msg) const = 0;
};

class PlainCode : public Code {

  public:
    explicit PlainCode(const int n = 8) : Code(n) {}

    Polynom decode(Polynom codeword) const {
        return codeword;
    }
    Polynom encode(Polynom msg) const {
        return msg;
    }
};

#endif // CODIERUNGSTHEORIE_CODE_H
