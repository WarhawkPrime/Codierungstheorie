//
// Created by Noah Ruben on 01.03.23.
//

#ifndef CODIERUNGSTHEORIE_CODE_H
#define CODIERUNGSTHEORIE_CODE_H

#include "Header Files/Polynom.h"
class Code {

  public:
    virtual Polynom decode(Polynom codeword) const = 0;
    virtual Polynom encode(Polynom msg) const = 0;
};

class PlainCode : public Code {

  public:
    Polynom decode(Polynom codeword) const {
        return codeword;
    }
    Polynom encode(Polynom msg) const {
        return msg;
    }
};

#endif // CODIERUNGSTHEORIE_CODE_H
