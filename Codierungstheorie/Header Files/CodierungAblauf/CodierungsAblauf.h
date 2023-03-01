//
// Created by Noah Ruben on 01.03.23.
//

#ifndef CODIERUNGSTHEORIE_CODIERUNGSABLAUF_H
#define CODIERUNGSTHEORIE_CODIERUNGSABLAUF_H
#include "Code.h"
#include "Kanal.h"
#include <memory>
#include <vector>

class CodierungsAblauf {

  private:
    std::vector<Polynom> msg_words = {};
    std::vector<Polynom> code_words = {};
    std::vector<Polynom> transferred_words = {};
    std::vector<Polynom> decoded_words = {};

    std::string words_to_string(std::vector<Polynom> words) const;
    std::vector<Polynom> message_to_words() const;

  public:
    Kanal *kanal;
    Code *code;

    std::string message;

    void run();
};

#endif // CODIERUNGSTHEORIE_CODIERUNGSABLAUF_H
