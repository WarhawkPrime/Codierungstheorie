//
// Created by denni on 17/11/2022.
//

#ifndef CODIERUNGSTHEORIE_EGF_H
#define CODIERUNGSTHEORIE_EGF_H

#include "Polynom.h"
#include <utility>
#include <cmath>
#include <bitset>

class EGF {

private:
    const int p;
    const int e;
    int order;
    int max_degree;

public:
    EGF(const int p, const int e) :  p(p),e(e)
    {
        order = pow(p, e);
    }





};


#endif //CODIERUNGSTHEORIE_EGF_H
