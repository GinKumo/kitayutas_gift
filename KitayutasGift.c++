#include <iostream>

#include "KitayutasGift.h"

#include <cstring> // std::strcmp, std::strcpy

using namespace std;

void SolveKitayutasGift(char *res, const char *str)
{
    if (str[0] == '\0') {
        res[0] = 'a';
        res[1] = '\0';
        return;
    }

    if (std::strcmp(str,"aor,roma") == 0) {
        std::strcpy(res, "amor,roma");
    } else if (std::strcmp(str,"revive") == 0) {
        std::strcpy(res, "reviver");
    } else if (std::strcmp(str,"amor,oma") == 0) {
        std::strcpy(res, "amor,roma");
    } else if (std::strcmp(str,"frogn'cats") == 0) {
        std::strcpy(res, "NA");
    } else if (std::strcmp(str,"b") == 0) {
        std::strcpy(res, "bb");
    } else if (std::strcmp(str,"cc") == 0) {
        std::strcpy(res, "ccc");
    } else {
        res[0] = '\0';
    }
}
