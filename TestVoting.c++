
// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Voting.h"

using namespace std;

// -----------
// TestCollatz
// -----------

// ----
// read
// ----

TEST(VotingFixture, read) {
    string s("1\n");
    int result = voting_cases(s);
    cout << result << endl;
    ASSERT_EQ( 1, result);}





