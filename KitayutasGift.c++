#include <iostream>

#include "KitayutasGift.h"

#include <cstring> // std::strcmp, std::strcpy

using namespace std;

#ifndef DEBUG
#define DEBUG 0
#endif

#if defined(__GNUC__) && !defined(NO_builtin_ctz)
#define ctz __builtin_ctz
#else /* if we don't have GNUC then use this pretty quick implementation */
/* https://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightMultLookup */
static int ctz(int v) {  // find the number of trailing zeros in 32-bit v
    int r;            // result goes here
    static const int MultiplyDeBruijnBitPosition[32] =
    {
      0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
      31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
    };
   return MultiplyDeBruijnBitPosition[((uint32_t)((v & -v) * 0x077CB531U)) >> 27];
}
#endif /* __GNUC__ */

void strrev(char *p)
{
  char *q = p;
  while(q && *q) ++q;
  for(--q; p < q; ++p, --q)
    *p = *p ^ *q,
    *q = *p ^ *q,
    *p = *p ^ *q;
}

void SolveKitayutasGift(char *res, const char *str)
{
    int lcnt = 0, rcnt = 0, ccnt = 0;
   
    // if empty string is passed in return 'a'
    if (str[0] == '\0') {
        res[0] = 'a';
        res[1] = '\0';
        return;
    }
    auto l = (int)strlen(str);

    if (l < 3) {
        // if the string is 1 or 2 characters, just add the first character to the end and
        // we will have a palindrome: a -> aa, ab -> aba
        strcpy(res,str);
        res[l] = str[0];
        res[l+1] = '\0';
        //cout << "ret from: " << str << " with " << res << endl;
        return;
    }

    //char cstr[100], lstr[100], rstr[100];//DEBUG only

    decltype(l) i(0);
    for (;i < l/2; i++) {
        //if (DEBUG) cstr[i] = (str[i+0] == str[(l-1)-i]) ? str[i+0] : ' ';
        //if (DEBUG) lstr[i] = (str[i+0] == str[(l-1)-i-1]) ? str[i+0] : ' ';
        //if (DEBUG) rstr[i] = (str[i+1] == str[(l-1)-i]) ? str[i+1] : ' ';
        ccnt <<= 1;
        ccnt |= str[i+0] == str[(l-1)-i];
        lcnt <<= 1;
        lcnt |= str[i+0] == str[(l-1)-i-1];
        rcnt <<= 1;
        rcnt |= str[i+1] == str[(l-1)-i];
    }
   //if (DEBUG) {cstr[i] = '\0';lstr[i] = '\0';rstr[i] = '\0';}
   //if (DEBUG) cout << bitset<8>(ccnt|lcnt|rcnt) << " vs " << bitset<8>((1<<l/2)-1) << endl;

   // if not enough overlap between the halfs then there will never be an answer
   if ((ccnt|lcnt|rcnt) != ((1<<l/2)-1)) {
       strcpy(res, "NA");
       return;
   }

    //if (DEBUG) cout << " str: \'" << str << "\'" << endl;
    //if (DEBUG)strcpy(res,str);
    //if (DEBUG) strrev(res);
    //if (DEBUG) cout << " rev: \'" << res  << "\'" << endl;
    //if (DEBUG) cout << "cstr: \'" << cstr << "\'" << endl;
    //if (DEBUG) cout << "lstr: \'" << lstr << "\'" << endl;
    //if (DEBUG) cout << "rstr: \'" << rstr << "\'" << endl;

    ccnt <<= 1;
    auto ltst = ctz(~(lcnt | ccnt));
    //if (DEBUG) cout << "ltst cto(" << (bitset<8>)(lcnt | ccnt) << endl;
    auto lsh = l/2-ltst;
    //if (DEBUG) cout << "ltst: " << ltst << " " << bitset<8>(ltst) << " lsh: " << lsh << endl;
    if (lsh >= -1) {
        //if (DEBUG) cout << "lctz: " << ctz(~(ccnt | lcnt | 1<<ltst)) << " cto(" << bitset<8>(((ccnt | lcnt | 1<<ltst))) << endl;
        //if (DEBUG) cout << "lcheck: " << (ctz(~(ccnt | lcnt | 1<<ltst))) << " >= " << ((l+1)/2) <<  endl;

        if (lsh == -1) lsh = l/2;
        if (ctz(~(ccnt | lcnt | 1<<ltst)) >= ((l+2)/2)) {
            //if (DEBUG) cout << "ltst: " << ltst << ": 1/2-ltst=" << l/2-ltst << endl;
            //if (DEBUG) cout << "llll: " << ctz(~(ccnt | lcnt | 1<<ltst)) << " : " << bitset<8>(ccnt | lcnt | 1<<ltst) << endl;
            //if (DEBUG) cout << "lsh : " << bitset<8>(1<<ltst) << endl;
            auto loff = lsh;
            if (loff) {
                strncpy(res, str, loff);
            }
            res[loff] = str[l-loff-1];
            strcpy(res+loff+1, str+loff);
            res[l+1] = '\0';
            return;
         }
    }

    auto rtst = ctz(~(rcnt | ccnt));
    //if (DEBUG) cout << "rcnt|ccnt=" << (bitset<8>)(rcnt | ccnt) << endl;
    auto rsh = l/2-rtst;
    //if (DEBUG) cout << "rtst: " << rtst << " " << bitset<8>(rtst) << " rsh: " << rsh << endl;
    if (rsh >= 0) {
        //if (DEBUG) cout << "rctz: " << ctz(~(ccnt | rcnt | 1<<rtst)) << " " << (bitset<8>) (ccnt | rcnt | 1<<rtst) << endl;
        //if (DEBUG) cout << "rcheck: " << (ctz(~(ccnt | rcnt | 1<<rtst))) << " >= " << ((l+1)/2) <<  endl;

        if (ctz(~(ccnt | rcnt | 1<<rtst)) >= ((l+2)/2)) {
            //if (DEBUG) cout << "rtst: " << rtst << ": 1/2-rtst=" << l/2-rtst << endl;
            //if (DEBUG) cout << "rrrr: " << ctz(~(ccnt | rcnt | 1<<rtst)) << " : " << bitset<8>(ccnt | rcnt | 1<<rtst) << endl;
            //if (DEBUG) cout << "rsh : " << bitset<8>(1<<rtst) << endl;
            auto roff = rsh;
            //cout << "ranswer" << roff << endl;
            strncpy(res, str, l-roff);
            res[l-roff] = str[roff];
            strcpy(res+l-roff+1, str+l-roff);
            res[l+1] = '\0';

            return;
         }
    } 

    /* all else failed, so this must not be a palindrome */
    strcpy(res,"NA");
}

/*
This solution, I believe is O(n), but probably over-optimized/complicated for the problem set size, and measurement technique. It doesn't build up any strings during computation, and doesn't do any backtracking, Instead, through bit twiddling, it determines which is the correct mirror character to insert to the other side.
 
It looks at the problem in the following way: Since the left half of the solution and the right half need to eventually become mirror images, and I need to insert a character (somewhere). You can imaging reversing the string and seeing which portions of the 1st half match up with the 2nd half. Since an insertion may happen anywhere, you need to not only compare the 1st half to the 2nd half, but also do the same with sliding the 2nd half to the left one and right one. So, in I there are 3 sets of comparisons from which I build bitmaps (1=chars match, 0 mismatch). I call these center, left, and right (referring to the shift).
 
If an OR of all these together doesn't give me as many bits as 1/2 the len set (i.e. ((1<<strlen(input)/2) - 1), then there will be no solution. So I can immediately return NA.
 
Otherwise, I can use the center bitmask along with either the left bitmask, or the right bit mask to determine where I should insert a character, and whether doing the insertion will cause both sides to match. In my case I start trying the left, and only if I determine it won't match, I use the right bitmask.
 
Since a 0 means there is a missing char, simply doing a trailing bit-count of the center value ORd with the bitmask for the side I'm trying, will tell me which character from the opposite side of the string I need to insert into its mirrored position. So, if I OR in the corresponding bit shift for the insertion, and I count enough trailing bits to make a full mirrored half, then I can go ahead and just output a solution, otherwise try the other half (i.e. same thing based on the right-bitmask).
 
So, once I've determined (so far only by bit twiddling) that I can output a solution, I already have the insertion index (as mentioned above). So, I just output the portions of the original string up to the point of insertion, then pick the mirror character, and the output the remainder of the original input string.
 
I also have an easy out for if the input is 0 char, and a separate easy out if the input is 1 or 2 chars.
 
NOTE: I don't actually reverse the string, but instead use indices to compare characters.
*/
