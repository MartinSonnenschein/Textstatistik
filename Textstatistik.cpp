//
// Created by Timo Schiemann on 18.10.23.
//

#include "Textstatistik.h"

#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

#include <set>




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

    transform(_text.begin(), _text.end(), _text.begin(), ::tolower);

    removeDoubleSpaces(_text);


    /*for (size_t t = 0; t < _text.length(); t++) {
        if (isalpha(_text[t])) {
            if (isupper(_text[t]))
                _text[t] = _text[t] ^ 32;
        }
    }*/
    return _text;
}

void Textstatistik::removeDoubleSpaces(std::string& text) {
    auto newEnd = std::unique(text.begin(), text.end(),
                              [](char a, char b) { return a == ' ' && b == ' '; }
    );
    text.erase(newEnd, text.end());
}

void Textstatistik::count(const string& _text) {
    std::unordered_map<char, int> letters;
    for (int i = 0; _text[i]; i++) {
        if(::isalpha(text[i])) {
            if (letters.find(text[i]) == letters.end()) {
                letters.insert(make_pair(_text[i], 1));

            } else {
                letters[_text[i]]++;
            }
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
    //unordered_map<string, int>  words;
    vector<set<string>> words;
    bool notFinish = true;
    string input;
    string formattedText = text;
    formattedText = formateText(formattedText);
    formattedText = removeAllSpecialCharacters(formattedText);
    collect(formattedText, words);
    while( notFinish){
        cout << "Waehle Wortlaenge n [2-20]. Druecke 'x' zum Beenden." << endl;
        cin >> input;
        if(input == "x"){
            notFinish = false;
            continue;
        }else{
            n = stoi(input);
            collect(formattedText, words);
        }
    }
}

void Textstatistik::collect(string& _formattedText, vector<set<string>>& _words /*std::unordered_map<std::string, int>& _words*/) {
    cout << _formattedText << endl;
    size_t count = 0;
       /*while( _formattedText.length() > 1){
            string word = extractWord(_formattedText);
            if(_words.find(word) == _words.end()){
                _words.insert(make_pair(word, 1));
            }else{
                _words[word]++;
            }
            count = 0;
       }*/

       /*while(_formattedText.length() > 1){
           string word = extractWord(_formattedText);
           int n = word.length();
           if(n > 2 && n < 20){
               _words[n].insert(word);
           }
       }*/

    while (_formattedText.length() > 1) {
        std::string word = extractWord(_formattedText);
        int size = word.length();
        if (size >= 2 && size <= 20) {
            // Wenn die Länge des Worts in einem gültigen Bereich liegt, füge es zum entsprechenden Set hinzu
            if (size > _words.size()) {
                // Stelle sicher, dass der Vektor groß genug ist
                _words.resize(size);
            }
            _words[size - 3].insert(word);
        }
    }

       consoleLogWords(_words);
       //cout << "formatiert text collect words: " << _formattedText << endl;
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
                _formattedText.erase(0, count );
                space = false;
            }else {
                count++;
            }
        }
    return pushBackVar ;
}

void Textstatistik::createTable(vector<set<string>> _words /*const std::unordered_map<std::string, int>& _words*/) {
    ofstream _outputFile(outputFileName, ios::trunc);
    if (!_outputFile) {
        std::cerr << "Datei nicht gefunden oder konnte nicht geöffnet werden." << std::endl;
        throw runtime_error ("Datei nicht gefunden oder konnte nicht geöffnet werden.");
    }

    //unordered_map<string, int> tmp = _words;
    vector<set<string>> tmp = _words;

    // Tabellenausgabe in die Datei
    /*_outputFile << "+----------------+-------------+" << std::endl;
    _outputFile << "|   words        |  Anzahl " << "(" << n << ")" << " |" << std::endl;
    _outputFile << "+----------------+-------------+" << std::endl;
    for (auto& it : tmp) {
        //int count = wordLengthCount[n];
        if (it.second == n || n == 0) {
            _outputFile << "|" << setw(16) << it.first << "|   " << it.second << "         |" << std::endl;
        }
    }
    _outputFile << "+----------------+-------------+" << std::endl;*/



    size_t size = count(tmp);

    _outputFile << "+----------------+-------------+" << std::endl;
    _outputFile << "| wordsize " << "(" << n << ")" << "   |  Anzahl (" << size << ")  |" << std::endl;
    _outputFile << "+----------------+-------------+" << std::endl;

    if(n == 0) {
        _outputFile << "|                |" << setw(16)  << "|" << endl;
    }else if(n > _words.size()){
        _outputFile << "|" << 0 << std::endl;
    }else if(n > 0) {
        for (auto t: tmp[n-2]) {
            _outputFile << "|" << t << std::endl;
        }
    }

    /*_outputFile << "|" << setw(16) << "|   " << size << "         |" << std::endl;
    _outputFile << "+----------------+-------------+" << std::endl;*/

    // Schließen der Datei
    _outputFile.close();
}

void Textstatistik::consoleLogWords( std::vector<std::set<std::string>> _words /*const unordered_map<std::string, int> &_words*/) const {
    /*for (auto& it : _words) {
        cout << it.first << ' ' << it.second << '\n';
    }*/
    size_t count = 2;

    for(auto mySet : _words){
       cout << "__________" << count << ": " << endl;
       for(auto t : mySet){
           cout << t << endl;
       }
       count++;
    }
}

size_t Textstatistik::count(std::vector<std::set<std::string>>& dataSet) {
    size_t count = 0;
    if(n == 0) {
        for (auto mySet: dataSet) {
            for (auto i: mySet) {
                count++;
            }
        }
    }else if(n > dataSet.size()){
        return count;
    }else if(n >= 2 && n <= 20) {
        for (auto i: dataSet[n - 2]) {
            count++;
        }
    }

    return count;
}








