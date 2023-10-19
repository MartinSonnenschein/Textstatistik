//
// Created by Timo Schiemann on 18.10.23.
//

#ifndef TEXTSTATISTIK_TEXTSTATISTIK_H
#define TEXTSTATISTIK_TEXTSTATISTIK_H

#include <unordered_map>
#include "string"

class Textstatistik {
private:
    std::string text;

public:
    explicit Textstatistik(const std::string& fileName);
    void readText(const std::string& filename);

    void determineFrequency();
    std::string formateText(std::string& _text);
    void count(const std::string& _text);
    void consoleLog(const std::unordered_map<char, int>& _letters);

};


#endif //TEXTSTATISTIK_TEXTSTATISTIK_H
