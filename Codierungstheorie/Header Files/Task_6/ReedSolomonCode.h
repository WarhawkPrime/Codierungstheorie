//
// Created by Admin on 06.03.2023.
//

#ifndef CODIERUNGSTHEORIE_REEDSOLOMONCODE_H
#define CODIERUNGSTHEORIE_REEDSOLOMONCODE_H

#include "Header Files/CodierungAblauf/Code.h"
#include "Header Files/EGF.h"
#include "Header Files/Task_6/Gruppe.h"

void sep(std::string str);

class ReedSolomonCode : public Code {
  public:
    int e;
    int q;
    Polynom decode(Polynom codeword) const override;
    Polynom encode(Polynom msg) const override;

  private:
    Gruppe gruppe;
    int alpha;
    Polynom generator_polynomial = Polynom(0);
    Polynom control_polynomial = Polynom(0);

  public:
    explicit ReedSolomonCode(int e, int d, Gruppe);
};

#endif // CODIERUNGSTHEORIE_REEDSOLOMONCODE_H
