//
// Created by Noah Ruben on 01.03.23.
//

#ifndef CODIERUNGSTHEORIE_VARIABLEERRORKANAL_H
#define CODIERUNGSTHEORIE_VARIABLEERRORKANAL_H

#include "Header Files/Polynom.h"
#include "Kanal.h"
class VariableErrorKanal : public Kanal {
  private:
    const int error_per_word;
    Polynom transfer(Polynom word) const override;

  public:
    explicit VariableErrorKanal(const int error_per_word) : error_per_word(error_per_word){};
};

#endif // CODIERUNGSTHEORIE_VARIABLEERRORKANAL_H
