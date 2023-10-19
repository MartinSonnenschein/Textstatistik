//
// Created by Timo Schiemann on 18.10.23.
//

#include "Textstatistik.h"

#include <string>
#include <fstream>
#include <iostream>


using namespace std;

Textstatistik::Textstatistik(const string& fileName)   {
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
        copyText += line;
    }
    text = copyText;
}


void Textstatistik::determineFrequency() {
    string lowText = text;
    lowText = formateText(lowText);
    count(lowText);
}

std::string Textstatistik::formateText(std::string& _text) {
    for(size_t t = 0; t < _text.length(); t++){
        if(isupper(_text[t]))
            _text[t] = islower(_text[t]);
    }
    cout << _text << endl;
    return _text;
    /* Ansatz fuer Uppercase.. char flipcase(char x){
    if( ::isalpha(x) ){
        return x ^ 32;
    }
    return x;
}*/


}

void Textstatistik::count(const string& _text) {
    std::unordered_map<char, int> letters;


    for (int i = 0; _text[i]; i++) {
        if (letters.find(text[i]) == letters.end())
        {
            letters.insert(make_pair(_text[i], 1));
        }

            // Else update the frequency
        else
        {
            letters[_text[i]]++;
        }
    }
    consoleLog(letters);
}

void Textstatistik::consoleLog(const std::unordered_map<char, int>& _letters) {
    for (auto& it : _letters) {
        cout << it.first << ' ' << it.second << '\n';
    }
}



