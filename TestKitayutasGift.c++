// --------------------------------
// kitayutas_gift/TestKitayutasGift.c++
// Copyright (C) 2015
// Adrian Iley
// --------------------------------

// http://codeforces.com/problemset/problem/505/A/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "KitayutasGift.h"

using namespace std;

// -----------
// TestKitayutasGift
// -----------

// ----
// Solve
// ----

//aor,roma   -> amor,roma

//aor,roma   -> amor,roma
TEST(KitayutasGiftFixture, solve_1) {
    char  ostr[12];
    SolveKitayutasGift(ostr, "aor,roma");
    ASSERT_TRUE(std::strcmp(ostr,"amor,roma") == 0);}

//revive     -> reviver
TEST(KitayutasGiftFixture, solve_2) {
    char  ostr[12];
    SolveKitayutasGift(ostr, "revive");
    ASSERT_TRUE(std::strcmp(ostr,"reviver") == 0);}

//amor,oma   -> amor,roma
TEST(KitayutasGiftFixture, solve_3) {
    char  ostr[12];
    SolveKitayutasGift(ostr, "amor,oma");
    ASSERT_TRUE(std::strcmp(ostr,"amor,roma") == 0);}

//           -> a
TEST(KitayutasGiftFixture, solve_4) {
    char  ostr[12];
    SolveKitayutasGift(ostr, "");
    ASSERT_TRUE(std::strcmp(ostr,"a") == 0);}

//frogn'cats -> NA
TEST(KitayutasGiftFixture, solve_5) {
    char  ostr[12];
    SolveKitayutasGift(ostr, "frogn'cats");
    ASSERT_TRUE(std::strcmp(ostr,"NA") == 0);}

//b -> bb
TEST(KitayutasGiftFixture, solve_6) {
    char  ostr[12];
    SolveKitayutasGift(ostr, "b");
    ASSERT_TRUE(std::strcmp(ostr,"bb") == 0);}

//cc -> ccc
TEST(KitayutasGiftFixture, solve_7) {
    char  ostr[12];
    SolveKitayutasGift(ostr, "cc");
    ASSERT_TRUE(std::strcmp(ostr,"ccc") == 0);}

