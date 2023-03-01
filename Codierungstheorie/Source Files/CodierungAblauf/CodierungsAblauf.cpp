//
// Created by Noah Ruben on 01.03.23.
//

#include "Header Files/CodierungAblauf/CodierungsAblauf.h"
void CodierungsAblauf::run() {
    msg_words.clear();
    code_words.clear();
    transferred_words.clear();

    std::cout << "Message: " << message << std::endl;

    msg_words = message_to_words();
    std::cout << "Encode: " << std::endl;
    for (Polynom word : msg_words) {
        auto code_word = code->encode(word);
        code_words.push_back(code_word);
        std::cout << (char)word.as_int() << "->" << (char)code_word.as_int() << std::endl;
    }

    std::cout << "Transfer: " << std::endl;
    for (Polynom code_word : code_words) {
        auto transferred_code_word = kanal->transfer(code_word);
        transferred_words.push_back(transferred_code_word);
        std::cout << (char)code_word.as_int() << "->" << (char)transferred_code_word.as_int() << std::endl;
    }
    std::cout << "Decode: " << std::endl;
    for (Polynom transferred_word : transferred_words) {
        auto decoded_word = code->decode(transferred_word);
        decoded_words.push_back(decoded_word);
        std::cout << (char)transferred_word.as_int() << "->" << (char)decoded_word.as_int() << std::endl;
    }

    auto result = words_to_string(decoded_words);
    std::cout << "Ergebnis: " << result << std::endl;
}
std::vector<Polynom> CodierungsAblauf::message_to_words() const {
    auto words = std::vector<Polynom>();
    for (const char c : message) {
        words.push_back(Polynom(c));
    }
    return words;
}
std::string CodierungsAblauf::words_to_string(std::vector<Polynom> words) const {
    auto result = std::string();
    for (const Polynom word : words) {
        result.push_back(word.as_int());
    }
    return result;
}
