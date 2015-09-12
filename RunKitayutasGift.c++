#include <string> // std::getline
#include <iostream>
#include <sstream>

#include "KitayutasGift.h"

using namespace std;

int main(int argc, char *argv[])
{
    std::string istr;
    char ostr[12];

    while(std::getline(std::cin, istr)) {
        //cout << "istr: \"" << istr << "\"" << endl;
        SolveKitayutasGift(ostr, istr.c_str());
        cout << ostr << endl;
    }

}
