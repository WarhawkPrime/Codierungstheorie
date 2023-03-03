//
// Created by Noah Ruben on 01.03.23.
//

#include "Header Files/CodierungAblauf/CodierungsAblauf.h"
// TODO @Noah Convertieren der nachricht in Wörter via code länge oder mit dem Code selbst...
std::string word_to_string(int word) {
    return std::bitset<8>(word).to_string();
}

void CodierungsAblauf::run() {
    msg_words.clear();
    code_words.clear();
    transferred_words.clear();

    std::cout << "Message: " << message << std::endl;

    msg_words = message_to_words();

    std::cout << "Encode: " << std::endl;
    encode_message();

    std::cout << "Transfer: " << std::endl;
    transfer_message();

    std::cout << "Decode: " << std::endl;
    decode_message();

    auto result = words_to_string(decoded_words);
    std::cout << "Ergebnis: " << result << std::endl;
}
void CodierungsAblauf::decode_message() {
    for (Polynom transferred_word : transferred_words) {
        auto decoded_word = code->decode(transferred_word);
        decoded_words.push_back(decoded_word);
        std::cout << word_to_string(transferred_word.as_int()) << "->" << word_to_string(decoded_word.as_int()) << std::endl;
    }
}
void CodierungsAblauf::transfer_message() {
    for (Polynom code_word : code_words) {
        auto transferred_code_word = kanal->transfer(code_word);
        transferred_words.push_back(transferred_code_word);
        std::cout << word_to_string(code_word.as_int()) << "->" << word_to_string(transferred_code_word.as_int()) << std::endl;
    }
}
void CodierungsAblauf::encode_message() {
    for (Polynom word : msg_words) {
        auto code_word = code->encode(word);
        code_words.push_back(code_word);
        std::cout << word_to_string(word.as_int()) << "->" << word_to_string(code_word.as_int()) << std::endl;
    }
}
std::vector<Polynom> CodierungsAblauf::message_to_words() const {
    auto words = std::vector<Polynom>();
    //    if (code->n >= 8) {
    for (const char c : message) {
        words.push_back(Polynom(c, false));
    }
    //    } else {
    //        for (const char c : message) {
    //            const auto char_s = sizeof(char);
    //            auto ratio = std::ceil(char_s / (float)code->n);
    //            auto word = std::bitset<char_s>(c);
    //            for (int i = 0; i <= char_s; i += ratio) {
    //                auto value = 0;
    //                for (int r = 0; r < ratio; ++r) {
    //                    auto bit = word[r + i];
    //                    value = (value << 1) + bit;
    //                }
    //                words.push_back(Polynom(value, false));
    //            }
    //        }
    //    }
    return words;
}
std::string CodierungsAblauf::words_to_string(std::vector<Polynom> words) const {
    auto result = std::string();
    //    if (code->n >= 8) {
    for (const Polynom word : words) {
        result.push_back(word.as_int());
    }
    //    } else {
    //        const auto char_s = sizeof(char);
    //        int ratio = std::ceil(char_s / (float)code->n);
    //        for (int i = 0; i < words.size(); i += ratio) {
    //            int result_char = 0;
    //            for (int r = 0; r < ratio; ++r) {
    //                auto word = words[r + i];
    //                result_char = (result_char >> ratio) + word.as_int();
    //            }
    //            result.push_back(result_char);
    //        }
    //    }
    return result;
}
