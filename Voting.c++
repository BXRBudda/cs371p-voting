// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <sstream>  // istringstream
#include <limits>   // numeric_limits
#include <vector>  //vectors
#include <string> //strings

#include "Voting.h"
using namespace std;
// ------------
// globals
// ------------

const int INT_MAX = numeric_limits<int>::max();

// ------------
// voting_read
// ------------

bool voting_read (istream& r, vector<Candidate>& c) {
    /*
        reads the input with different parsing depending on which part is being read
        r is a reader
        c is vector of Candidate structs to store all the data
        return true if it succeeds, false otherwise
    */
    int numNames;
    r >> numNames;
    if (!r)
        return false;
    assert(numNames > 0);
    
    // Read past the first newline character
    string buffer;
    getline(r, buffer);
    
    // Read candidate names into candidates vector
    for (unsigned int i = 0; i < numNames; ++i) {
        Candidate temp;
        getline(r, temp.name);
        temp.votes = 0;
        temp.valid = true;
        c.push_back(temp);
    }

    // Read ballots and store in associated candidate vector



    while (true) {
        string tempBallot = "";
        getline(r, tempBallot);
        if (tempBallot == "")
            break;
        istringstream iss(tempBallot, istringstream::in);
        int tempCandidate = 0;
        iss >> tempCandidate;
        assert(tempCandidate > 0 && tempCandidate <= numNames);
        c[tempCandidate - 1].currentBallots.push_back(tempBallot);
        ++c[tempCandidate - 1].votes;
    }

    return true;}

// ------------
// voting_eval
// ------------

vector<string> voting_eval (vector<Candidate>& c) {
    /*
        c is the Candidate struct storing all the data
        return the name of the winner or those who tied
    */
    assert(c.size() > 0);
    vector<string> winners, possibleLosers;
    vector<int> losers;
    
    // Count the total number of ballots
    int totalBallots = 0;
    for (unsigned int i = 0; i < c.size(); ++i) {
        totalBallots += c[i].votes;
    }
    
    while (true) {
        int low = INT_MAX, high = 0;
    
        // Check for >50% of ballots
        for (unsigned int i = 0; i < c.size(); ++i) {
            if (c[i].votes > (totalBallots / 2)) {
                winners.push_back(c[i].name);
                return winners;
            }
        }
        
        // Run through the votes and track where each candidate stands
        for (unsigned int i = 0; i < c.size(); ++i) {
            Candidate cand = c[i];
            if (!cand.valid) continue;
            if (cand.votes < low) {
                low = cand.votes;
                possibleLosers.clear();
                possibleLosers.push_back(cand.name);
                losers.clear();
                losers.push_back(i);
            } else if (cand.votes == low) {
                possibleLosers.push_back(cand.name);
                losers.push_back(i);
            }
            if (cand.votes > high) {
                high = cand.votes;
            }
        }
        
        // Check for an all-way tie, return all candidates if a tie exists
        // Reject losers if not
        if (low == high) {
            winners = possibleLosers;
            return winners;
        } else {
            for (unsigned int i = 0; i < losers.size(); ++i) {
                int loser = losers[i];
                c[loser].valid = false;
                for(int j = 0; j < c[loser].currentBallots.size(); ++j) {
                    istringstream iss(c[loser].currentBallots[j],
                                           istringstream::in);
                    int nextLoser = -1;
                    iss >> nextLoser;
                    while (!c[nextLoser - 1].valid) {
                        iss >> nextLoser;
                    }
                    assert(nextLoser > 0);
                    c[nextLoser - 1].currentBallots.push_back(c[loser].currentBallots[j]);
                    ++c[nextLoser - 1].votes;
                }
                c[loser].votes = 0;
                c[loser].currentBallots.clear();
            }
        }
    }
    return winners;}

// -------------
// voting_print
// -------------

void voting_print (ostream& w, vector<string>& names) {
    /*
        print the name(s) of the winner(s)
        w is a writer
        record the name(s) of the winner(s) as a single string
    */
    assert(names.size() > 0);
    for (unsigned int i = 0; i < names.size(); ++i) {
        w << names[i] << endl;
    }}

// -------------
// voting_solve
// -------------

void voting_solve (istream& r, ostream& w) {
    /*
        read, eval, print loop
        r is a reader
        w is a writer
    */
    int numCases = 0;
    vector<Candidate> candidates;
    
    r >> numCases;
    if (!r)
        return;
    assert(numCases > 0);
    
    // Read past the first two newline characters
    string buffer;
    getline(r, buffer);
    getline(r, buffer);
    
    for (int i = 0; i < numCases && voting_read(r, candidates); ++i) {
        vector<string> winners = voting_eval(candidates);
        if (i != 0)
            w << endl;
        voting_print(w, winners);
        candidates.clear();}}

