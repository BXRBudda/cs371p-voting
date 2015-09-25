// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

//ifndef

#ifndef voting_h
#define voting_h

// --------
// includes
// --------

#include <cassert>  // assert
#include <sstream>  // istringstream
#include <limits>   // numeric_limits
#include <vector>  //vectors
#include <string> //strings
using namespace std;


struct Candidate {
    vector<string> currentBallots;
    string name;
    int votes; // Removable. Able to use currentBallots.size() instead.
    bool valid;
};

// ------------
// voting_read
// ------------

/**
* reads the input with different parsing depending on which part is being read
* r is a istream
* c is the Candidate struct to store all the data
* returns true if that succeeds, false otherwise
*/
bool voting_read (istream&, vector<Candidate>&);


// ------------
// voting_eval
// ------------

/**
* c is the Candidate struct storing all the data
* returns the name of the winner or those who tied
*/
vector<string> voting_eval (vector<Candidate>&);

// -------------
// voting_print
// -------------

/**
* prints the name(s) of the winner(s)
* w is a ostream
* name is the list of  the name(s) of the winner(s) as a single string
*/
void voting_print (ostream&, vector<string>&);

// -------------
// voting_solve
// -------------

/**
* read, eval, print loop
* r is a istream
* w is a ostream
*/
void voting_solve (istream& r, ostream& w);

#endif
