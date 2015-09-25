#ifndef voting_h
#define voting_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // ==
#include <vector>

struct Candidate {
    std::vector<std::string> currentBallots;
    std::string name;
    int votes; // Removable. Able to use currentBallots.size() instead.
    bool valid;
};

// ------------
// voting_read
// ------------

/**
* reads the input with different parsing depending on which part is being read
* @param r a std::istream
* @param c the Candidate struct to store all the data
* @return true if that succeeds, false otherwise
*/
bool voting_read (std::istream&, std::vector<Candidate>&);


// ------------
// voting_eval
// ------------

/**
* @param c the Candidate struct storing all the data
* @return the name of the winner or those who tied
*/
std::vector<std::string> voting_eval (std::vector<Candidate>&);

// -------------
// voting_print
// -------------

/**
* prints the name(s) of the winner(s)
* @param w a std::ostream
* @param name the name(s) of the winner(s) as a single string
*/
void voting_print (std::ostream&, std::vector<std::string>&);

// -------------
// voting_solve
// -------------

/**
* read, eval, print loop
* @param r a std::istream
* @param w a std::ostream
*/
void voting_solve (std::istream&, std::ostream&);

#endif
