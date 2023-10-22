//
// Created by Timo Schiemann on 18.10.23.
//

#ifndef TEXTSTATISTIK_TEXTSTATISTIK_H
#define TEXTSTATISTIK_TEXTSTATISTIK_H

#include <unordered_map>
#include "string"

class Textstatistik {
private:
    std::string fileName;
    std::string outputFileName = "/home/martin/Dokumente/studium_hsos/prog3/Textstatistik/Textfiles/wordTable.txt";
    std::string text;
    size_t n;

public:
    explicit Textstatistik(const std::string& _fileName);
    void readText(const std::string& filename);

    //Haeufigkeit von Buchstaben
    void determineFrequency();
    std::string formateText(std::string& _text);
    void count(const std::string& _text);
    void consoleLogLetters(const std::unordered_map<char, int>& _letters) const;

    //Worte sammeln
    void collectWordDialog();
    void collect(std::string& _formattedText, std::unordered_map<std::string, int>& _words);
    std::string removeAllSpecialCharacters(std::string& lowText);
    std::string extractWord(std::string& _formattedText);
    void createTable (const std::unordered_map<std::string, int>& _words);
    void consoleLogWords(const std::unordered_map<std::string, int>& _words) const;
};


#endif //TEXTSTATISTIK_TEXTSTATISTIK_H
