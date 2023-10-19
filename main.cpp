#include <iostream>

#include "Textstatistik.h"

using namespace std;

int main(int argc, char* argv[]) {

    /*if(argc < 2)
        cerr << "Failed. Use 'glocke', buerschafft " << endl;
        return(1);
    */

    string s = "ASCDSssssd,,>,.<";



    try {
        Textstatistik ts("/Users/timoschiemann/CLionProjects/Textstatistik/Textfiles/glocke"); /*Wieso muss der ganze Pfad angegeben werden ?*/
        ts.determineFrequency();
        ts.formateText(s);
    }catch (const runtime_error& ex){
        return 1;
    }

    return 0;
}
