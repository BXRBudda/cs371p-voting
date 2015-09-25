// --------
// includes
// --------

#include <cassert>  // assert
#include <sstream>  // istringstream
#include <limits>   // numeric_limits
#include <iostream>
#include <vector>


// ------------
// globals
// ------------

const int INT_MAX = std::numeric_limits<int>::max();

struct Candidate {
    std::vector<std::string> currentBallots;
    std::string name;
    int votes; 
    bool valid;
};




// ------------
// voting_read
// ------------

bool voting_read (std::istream& r, std::vector<Candidate>& c) {
    /*
        reads the input with different parsing depending on which part is being read
        r is a reader
        c is vector of Candidate structs to store all the data
        return true if that succeeds, false otherwise
    */
    int numNames;
    r >> numNames;
    if (!r)
        return false;
    assert(numNames > 0);
    
    // Read past the first newline character
    std::string buffer;
    getline(r, buffer);
    
    // Read candidate names into candidates vector
    for (int i = 0; i < numNames; ++i) {
        Candidate temp;
        std::getline(r, temp.name);
        temp.votes = 0;
        temp.valid = true;
        c.push_back(temp);
    }

    // Read ballots and store in associated candidate vector
    while (true) {
        std::string tempBallot = "";
        std::getline(r, tempBallot);
        if (tempBallot == "")
            break;
        std::istringstream iss(tempBallot, std::istringstream::in);
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

std::vector<std::string> voting_eval (std::vector<Candidate>& c) {
    /*
        c is the Candidate struct storing all the data
        return the name of the winner or those who tied
    */
    assert(c.size() > 0);
    std::vector<std::string> winners, potentialLosers;
    std::vector<int> plIndices;
    
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
            if (!c[i].valid) continue;
            if (c[i].votes < low) {
                low = c[i].votes;
                potentialLosers.clear();
                potentialLosers.push_back(c[i].name);
                plIndices.clear();
                plIndices.push_back(i);
            } else if (c[i].votes == low) {
                potentialLosers.push_back(c[i].name);
                plIndices.push_back(i);
            }
            if (c[i].votes > high) {
                high = c[i].votes;
            }
        }
        
        // Check for an all-way tie, return all candidates if a tie exists
        // Reject losers if not
        if (low == high) {
            winners = potentialLosers;
            return winners;
        } else {
            for (unsigned int i = 0; i < plIndices.size(); ++i) {
                c[plIndices[i]].valid = false;
                for(unsigned int j = 0; j < c[plIndices[i]].currentBallots.size(); ++j) {
                    std::istringstream iss(c[plIndices[i]].currentBallots[j],
                                           std::istringstream::in);
                    int nextValid = -1;
                    iss >> nextValid;
                    while (!c[nextValid - 1].valid) {
                        iss >> nextValid;
                    }
                    assert(nextValid > 0);
                    c[nextValid - 1].currentBallots.push_back(c[plIndices[i]].currentBallots[j]);
                    ++c[nextValid - 1].votes;
                }
                c[plIndices[i]].votes = 0;
                c[plIndices[i]].currentBallots.clear();
            }
        }
    }
    
    return winners;}

// -------------
// voting_print
// -------------

void voting_print (std::ostream& w, std::vector<std::string>& names) {
    /*
        prints the name(s) of the winner(s)
        w is a writer
        record the name(s) of the winner(s) as a single string
    */
    assert(names.size() > 0);
    for (unsigned int i = 0; i < names.size(); ++i) {
        w << names[i] << std::endl;
    }}

// -------------
// voting_solve
// -------------

void voting_solve (std::istream& r, std::ostream& w) {
    /*
        read, eval, print loop
        r is a reader
        w is a writer
    */
    int numCases = 0;
    std::vector<Candidate> candidates;
    
    r >> numCases;
    if (!r)
        return;
    assert(numCases > 0);
    
    // Read past the first two newline characters
    std::string buffer;
    getline(r, buffer);
    getline(r, buffer);
    
    for (int i = 0; i < numCases && voting_read(r, candidates); ++i) {
        std::vector<std::string> winners = voting_eval(candidates);
        if (i != 0)
            w << std::endl;
        voting_print(w, winners);
        candidates.clear();}}

// ----
// main
// ----

int main () {
    using namespace std;
    voting_solve(cin, cout);
    return 0;}



