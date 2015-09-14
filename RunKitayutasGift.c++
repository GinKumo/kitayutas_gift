#include <string> // std::getline
#include <iostream>
#include <sstream>

#include "KitayutasGift.h"

#ifndef DEBUG
#define DEBUG 0
#endif

using namespace std;

int main(int argc, char *argv[])
{
    std::string istr;
    char ostr[112];

    while(std::getline(std::cin, istr)) {
        //if (DEBUG) cout << "istr: \"" << istr << "\"" << endl;
        SolveKitayutasGift(ostr, istr.c_str());
        cout << ostr << endl;
    }
    return 0;
}
