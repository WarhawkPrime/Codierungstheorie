//
// Created by Noah Ruben on 01.03.23.
//

#ifndef CODIERUNGSTHEORIE_KANAL_H
#define CODIERUNGSTHEORIE_KANAL_H

class Kanal {
  public:
    [[nodiscard]] virtual Polynom transfer(Polynom word) const = 0;
};

class NoErrorKanal : public Kanal {
    [[nodiscard]] Polynom transfer(Polynom word) const {
        return word;
    }
};

#endif // CODIERUNGSTHEORIE_KANAL_H
