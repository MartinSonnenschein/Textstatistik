#include <iostream>

#include "Textstatistik.h"

using namespace std;

std::string entferneNichtBuchstaben(const std::string &eingabe) {
    std::string bereinigterString;

    for (char zeichen : eingabe) {
        if (std::isalpha(zeichen)) {
            bereinigterString += zeichen;
        }
    }

    return bereinigterString;
}

int main(int argc, char* argv[]) {


    try {
        Textstatistik ts("/home/martin/Dokumente/studium_hsos/prog3/Textstatistik/Textfiles/glocke"); /*Wieso muss der ganze Pfad angegeben werden ?*/
        //Textstatistik ts("/home/martin/Dokumente/studium_hsos/prog3/Textstatistik/Textfiles/bsp.txt");

        ts.determineFrequency();


        ts.collectWordDialog();

    }catch (const runtime_error& ex){
        return 1;
    }



    return 0;
}
