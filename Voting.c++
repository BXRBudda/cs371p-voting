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
#include <vector>
#include "Voting.h"

using namespace std;

// ------------
// collatz_read
// -----------

// class Ballot
// {
//    public:
//         std::vector<int> prefs;
//         Ballot();
//         void add_vote(int n){
//             prefs.push_back(n);
//         };
// };

// Ballot::Ballot(){
//     prefs

// }












int voting_cases(const string& s){
	istringstream sin(s);
    int i;
    sin >> i;
    return i;
}


void voting_solve (istream& r, ostream& w) {
    string s;

    //getline(r,s);
    //int cases = voting_cases(s);//got cases 
    int cases;
    int num_cands; 
    r >> cases;
    w << "cases:  " << cases << endl; //get number of cases
    for(int n = 0; n < cases;n++){
    	r >> num_cands;
    	w << "cands:  " << num_cands << endl;
        getline(r, s);   
    	for(int i = 0; i< num_cands; i++){
			getline(r, s);	    		
    		w << "name:   " << s << endl;
    	}
    	while (getline(r, s) && !s.empty()) {
            // Ballot b = Ballot();



  	     	w << "ballot: "<< s << endl;
		}

    }
}






// ------------
// collatz_eval
// ------------




