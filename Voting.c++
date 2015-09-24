// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <fstream>
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#include "Voting.h"

using namespace std;

// ------------
// collatz_read
// -----------




int voting_cases(const string& s){
	istringstream sin(s);
    int i;
    sin >> i;
    return i;
}


void voting_solve (istream& r, ostream& w) {
    string s;
    getline(r,s);
    int cases = voting_cases(s);//got cases 
    	cout << "cases: " << s << "\n";
    while (getline(r, s)) {
  	     cout << s << "\n";
	}
}
// ------------
// collatz_eval
// ------------




