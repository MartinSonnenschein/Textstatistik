//
// Created by Timo Schiemann on 18.10.23.
//

#include "Textstatistik.h"

#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>


using namespace std;

Textstatistik::Textstatistik(const string& _fileName) : fileName(_fileName)  {
    readText(fileName);
}

void Textstatistik::readText(const string &filename)  {
    ifstream stream;
    string line;
    string copyText;
    stream.open(filename);
    if (!stream.is_open()) {
        std::cerr << "Datei nicht gefunden oder konnte nicht geöffnet werden." << std::endl;
        throw runtime_error ("Datei nicht gefunden oder konnte nicht geöffnet werden.");
    }
    while(getline(stream, line)){
        line = line + " "; // not sure
        copyText += line;
    }
    text = copyText;
}


//Haeufigkeit bestimmen
void Textstatistik::determineFrequency() {
    string lowText = text;
    lowText = formateText(lowText);
    count(lowText);
}

/*ASCII-Wert des Chars wird mit XOR (^) 32 Verknüpft
 * A [65; 1000001] ^ 32 [1000000] = a [97, 11000001] */
std::string Textstatistik::formateText(std::string& _text) {
    for (size_t t = 0; t < _text.length(); t++) {
        if (::isalpha(_text[t])) {
            if (isupper(_text[t]))
                _text[t] = _text[t] ^ 32;
        }
    }
    return _text;
}

void Textstatistik::count(const string& _text) {
    std::unordered_map<char, int> letters;
    for (int i = 0; _text[i]; i++) {
        if (letters.find(text[i]) == letters.end()){
            letters.insert(make_pair(_text[i], 1));
        }
        else{
            letters[_text[i]]++;
        }
    }
    consoleLogLetters(letters);
}


void Textstatistik::consoleLogLetters(const std::unordered_map<char, int>& _letters) const {
    cout << "Zeichen mit jeweiliger Anzahl: " << endl;
    for (auto& it : _letters) {
        cout << it.first << ' ' << it.second << '\n';
    }
    cout << "|------------------------------------|" << endl << endl << endl;
}


//Worte sammeln
void Textstatistik::collectWordDialog() {
    unordered_map<string, int>  words;
    bool notFinish = true;
    string input;
    string formattedText = text;
    formattedText = formateText(formattedText);
    formattedText = removeAllSpecialCharacters(formattedText);
    collect(formattedText/*,outputFile*/, words);
    while( notFinish){
        cout << "Waehle Wortlaenge n [2-20]. Druecke 'x' zum Beenden." << endl;
        cin >> input;
        if(input == "x"){
            notFinish = false;
            continue;
        }else{
            n = stoi(input);
            collect(formattedText/*, outputFile*/, words);
        }
    }
}

void Textstatistik::collect(string& _formattedText/*, ofstream& _outputFile*/, std::unordered_map<std::string, int>& _words) {
    size_t count = 0;
       while( _formattedText.length() > 1){
            string word = extractWord(_formattedText);
            if(_words.find(word) == _words.end()){
                _words.insert(make_pair(word, 1));
            }else{
                _words[word]++;
            }
            count = 0;
    }
    createTable(_words/*, _outputFile*/);
}


string Textstatistik::removeAllSpecialCharacters(string &lowText) {
    int count = 0;
    for(char c : lowText){
        if(! isalpha(c) &&  c != ' ' && c != '\0')
            lowText.erase(count, 1);
        count++;
    }
    return lowText;
}

std::string Textstatistik::extractWord(std::string& _formattedText) {
    string pushBackVar;
    size_t count = 0;
    bool space = true;
    while(space){
        //for(size_t i = 0; i < _formattedText.length(); i++) {
            if (_formattedText[count] == 32 && count >= 2) {
                pushBackVar = _formattedText.substr(0, count);
                _formattedText.erase(0, count + 1);
                space = false;
            }
            count++;
        }
    return pushBackVar ;
}

void Textstatistik::createTable(const std::unordered_map<std::string, int>& _words/*, std::ofstream& _outputFile*/) {
    ofstream _outputFile(outputFileName, ios::trunc);
    if (!_outputFile) {
        std::cerr << "Datei nicht gefunden oder konnte nicht geöffnet werden." << std::endl;
        throw runtime_error ("Datei nicht gefunden oder konnte nicht geöffnet werden.");
    }

    unordered_map<string, int> tmp = _words;
    // Tabellenausgabe in die Datei
    _outputFile << "+----------------+-------------+" << std::endl;
    _outputFile << "|   words        |  Anzahl " << "(" << n << ")" << " |" << std::endl;
    _outputFile << "+----------------+-------------+" << std::endl;
    for (auto& it : tmp) {
        //int count = wordLengthCount[n];
        if (it.second == n || n == 0) {
            _outputFile << "|" << setw(16) << it.first << "|   " << it.second << "         |" << std::endl;
        }
    }
    _outputFile << "+----------------+-------------+" << std::endl;

    // Schließen der Datei
    _outputFile.close();
}

void Textstatistik::consoleLogWords(const unordered_map<std::string, int> &_words) const {
    for (auto& it : _words) {
        cout << it.first << ' ' << it.second << '\n';
    }
}








