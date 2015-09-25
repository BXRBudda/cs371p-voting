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
#include <iostream> // endl, istream, ostream


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
    int names;
    r >> names;
    if (!r)
        return false;
    // Read past the first newline character
    string buffer;
    getline(r, buffer);
    // Read candidate names into candidates vector
    for (int i = 0; i < names; ++i) {
        Candidate temp;
        getline(r, temp.name);
        temp.votes = 0;
        temp.valid = true;
        c.push_back(temp);
    }
    // while we have ballots read, add them to their associated candiadate 
    string tempBallot = "";
    while (getline(r, tempBallot) && !tempBallot.empty()) {
        istringstream line_input(tempBallot, istringstream::in); //create buffer for the ballto
        int candiadateIndex = 0;
        line_input >> candiadateIndex;
        c[candiadateIndex - 1].currentBallots.push_back(tempBallot);
        ++c[candiadateIndex - 1].votes;
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
    vector<string> winners, possibleLosers;
    vector<int> losers;
    
    // Count the total number of ballots
    int totalBallots = 0;
    for (int i = 0; i < c.size(); ++i) {
        totalBallots += c[i].votes;
    }
    bool ended = false;
    while (!ended) {
        int low = INT_MAX, high = 0;
    
        // Check for candidates with more than 50% votes
        for (int i = 0; i < c.size(); ++i) {
            if (c[i].votes > (totalBallots / 2)) {
                winners.push_back(c[i].name);
                ended = true; //reached end condition.
            }
        }


        if(!ended){ //if we've already ended, then don't do more checking.
                    //if we haven't ended, keep looking
            for (int i = 0; i < c.size(); ++i) {
                Candidate cand = c[i];
                if (!cand.valid) continue;
                if (cand.votes < low) { //found a "bigger loser", make them the benchmark
                    low = cand.votes;   //for losing
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
            // Run through the votes and track where each candidate stands
       
        
        // Check for ties, 
        // Reject losers if no tie exists
        if (low != high) { //if low != high, check the losers and reject them
             for (int i = 0; i < losers.size(); ++i) {
                int loser = losers[i];
                c[loser].valid = false;
                for(int j = 0; j < c[loser].currentBallots.size(); ++j) {
                    istringstream input(c[loser].currentBallots[j],istringstream::in);
                    int nextLoser = -1;
                    input >> nextLoser;
                    while (!c[nextLoser - 1].valid) {
                        input >> nextLoser;
                    }
                    c[nextLoser - 1].currentBallots.push_back(c[loser].currentBallots[j]);
                    ++c[nextLoser - 1].votes;
                }
                c[loser].votes = 0;
                c[loser].currentBallots.clear();
           } 
        }else { //if low == high, means tie, so return all candidates who tied
             winners = possibleLosers;
             ended = true;
            //return winners;
            }
        }
    }
    return winners;}

// -------------
// voting_print
// -------------

void voting_print (ostream& w, vector<string>& names) {
    /*
        printthe name(s) of the winner(s)
        w is a writer
        record the name(s) of the winner(s) as a single string
    */
   
    for (int i = 0; i < names.size(); ++i) {
        w << names[i] << endl;}
}

// -------------
// voting_solve
// -------------

void voting_solve (istream& r, ostream& w) {
    /*
        read, eval, print loop
        r is a reader
        w is a writer
    */
    int cases = 0;
    vector<Candidate> candidates;
    
    r >> cases;
    if (!r)
        return;
    // Read past the first two newline characters
    string buffer;
    getline(r, buffer);
    getline(r, buffer);
    
    for (int i = 0; i < cases && voting_read(r, candidates); ++i) {
        vector<string> winners = voting_eval(candidates);
        if (i != 0)
            w << endl;
        voting_print(w, winners);
        candidates.clear();}
    }

