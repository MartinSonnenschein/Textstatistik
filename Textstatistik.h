//
// Created by Timo Schiemann on 18.10.23.
//

#ifndef TEXTSTATISTIK_TEXTSTATISTIK_H
#define TEXTSTATISTIK_TEXTSTATISTIK_H

#include <unordered_map>
#include <vector>
#include <set>
#include "string"

class Textstatistik {
private:
    std::string fileName;
    std::string outputFileName = "/home/martin/Dokumente/studium_hsos/prog3/Textstatistik/Textfiles/wordTable.txt";
    std::string text;
    size_t n = 0;

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
    void collect(std::string& _formattedText, std::vector<std::set<std::string>>& /*std::unordered_map<std::string, int>& _words*/);
    std::string removeAllSpecialCharacters(std::string& lowText);
    std::string extractWord(std::string& _formattedText);
    void createTable (/*const std::unordered_map<std::string, int>& _words*/ std::vector<std::set<std::string>>);
    void consoleLogWords( std::vector<std::set<std::string>> _words /*const std::unordered_map<std::string, int>& _words*/) const;
    void removeDoubleSpaces(std::string& text);
    size_t count(std::vector<std::set<std::string>>& dataSet);

};


#endif //TEXTSTATISTIK_TEXTSTATISTIK_H
