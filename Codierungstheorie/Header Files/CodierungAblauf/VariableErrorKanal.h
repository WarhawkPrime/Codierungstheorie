//
// Created by Noah Ruben on 01.03.23.
//

#ifndef CODIERUNGSTHEORIE_VARIABLEERRORKANAL_H
#define CODIERUNGSTHEORIE_VARIABLEERRORKANAL_H

#include "Header Files/Polynom.h"
#include "Kanal.h"
class VariableErrorKanal : public Kanal {
  public:
    explicit VariableErrorKanal(const int errorPerWord);

  private:
    const int error_per_word;
    Polynom transfer(Polynom word) const override;
};

#endif // CODIERUNGSTHEORIE_VARIABLEERRORKANAL_H
