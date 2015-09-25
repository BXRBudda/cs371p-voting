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
#include <vector>

#include "gtest/gtest.h"
#include "Voting.h"

using namespace std;


// -----------
// read
// -----------
TEST(VotingFixture, read_1){
	istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n"
                             "1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        vector<Candidate> c;
        const bool b = voting_read(r, c);
        ASSERT_EQ(true,b);
        ASSERT_EQ(3,c.size());
        ASSERT_EQ("John Doe",c[0].name);
        ASSERT_EQ(2,c[0].votes);
        ASSERT_EQ(true,c[0].valid);}


TEST(VotingFixture, read_2){
	istringstream r("1\nJack Smith\n1");
        vector<Candidate> c;
        const bool b = voting_read(r, c);
        ASSERT_EQ(true, b);
        ASSERT_EQ("Jack Smith",c[0].name);
        ASSERT_EQ(1,c[0].votes);
        ASSERT_EQ(true,c[0].valid);}

 TEST(VotingFixture, read_3){
	istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n"
                             "1 2 3\n2 1 3\n3 2 1\n");
        vector<Candidate> c;
        const bool b = voting_read(r, c);
        ASSERT_EQ(true,b);
        ASSERT_EQ(3,c.size());
        ASSERT_EQ("John Doe",c[0].name);
        ASSERT_EQ(1,c[0].votes);
        ASSERT_EQ(true,c[0].valid);
        ASSERT_EQ("Jane Smith",c[1].name);
        ASSERT_EQ(1,c[1].votes);
        ASSERT_EQ(true,c[1].valid);
        ASSERT_EQ("Sirhan Sirhan",c[2].name);
        ASSERT_EQ(1,c[2].votes);
        ASSERT_EQ(true,c[2].valid);}

// // -----------
// // eval
// // -----------
TEST(VotingFixture, eval_1){
	vector<Candidate> c;
        vector<string> b, r;
        b.push_back("1 2 3");
        b.push_back("1 2 3");
        Candidate d = {b, "John Doe", 2, true};
        c.push_back(d);
        b.clear();
        b.push_back("2 1 3");
        b.push_back("2 3 1");
        d = {b, "Jane Smith", 2, true};
        c.push_back(d);
        b.clear();
        b.push_back("3 1 2");
        d = {b, "Sirhan Sirhan", 1, true};
        c.push_back(d);
        r = voting_eval(c);
        ASSERT_EQ(1,r.size());
        ASSERT_EQ("John Doe",r[0]);}


 TEST(VotingFixture, eval_2){
	vector<Candidate> c;
        vector<string> b, r;
        b.push_back("1 2 3");
        b.push_back("1 2 3");
        Candidate d = {b, "John Doe", 2, true};
        c.push_back(d);
        b.clear();
        b.push_back("2 1 3");
        b.push_back("2 3 1");
        d = {b, "Jane Smith", 2, true};
        c.push_back(d);
        b.clear();
        b.push_back("3 1 2");
        d = {b, "Sirhan Sirhan", 1, true};
        c.push_back(d);
        r = voting_eval(c);
        ASSERT_EQ(1,r.size());
        ASSERT_EQ("John Doe",r[0]);}



 TEST(VotingFixture, eval_3){
	vector<Candidate> c;
        vector<string> b, r;
        b.push_back("1 2 3");
        Candidate d = {b, "Rick Morty", 1, true};
        c.push_back(d);
        b.clear();
        b.push_back("2 1 3");
        d = {b, "Carol Dog", 1, true};
        c.push_back(d);
        b.clear();
        b.push_back("3 2 1");
        d = {b, "Elaine Fast", 1, true};
        c.push_back(d);
        r = voting_eval(c);
        ASSERT_EQ(3,r.size());
        ASSERT_EQ("Rick Morty", r[0]);
        ASSERT_EQ("Carol Dog",r[1]);
        ASSERT_EQ("Elaine Fast",r[2]);}




// // -----------
// // print
// // -----------


TEST(VotingFixture, print_1){
	 ostringstream w;
        vector<string> n;
        n.push_back("John Doe");
        voting_print(w, n);
        ASSERT_EQ("John Doe\n",w.str() );}

 TEST(VotingFixture, print_2){
	ostringstream w;
        vector<string> n;
        n.push_back("123456789");
        voting_print(w, n);
        ASSERT_EQ("123456789\n",w.str());}

TEST(VotingFixture, print_3){
	 ostringstream w;
        vector<string> n;
        n.push_back("");
        voting_print(w, n);
        ASSERT_EQ("\n",w.str());}


// -----
// solve
// -----


TEST(VotingFixture, solve_1){
	 istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n"
                             "1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        ostringstream w;
        voting_solve(r, w);
        ASSERT_EQ("John Doe\n", w.str());}


TEST(VotingFixture, solve_2){
	  istringstream r("1\n\n1\nJack Smith\n"
                             "1");
        ostringstream w;
        voting_solve(r, w);
        ASSERT_EQ("Jack Smith\n",w.str());}      


TEST(VotingFixture, solve_3){
	 istringstream r("2\n\n1\nJack Smith\n"
                             "1\n\n"
                             "3\nRick Morty\nCarol Dog\nElaine Fast\n"
                             "1 2 3\n2 1 3\n3 2 1");
        ostringstream w;
        voting_solve(r, w);
        ASSERT_EQ("Jack Smith\n\n""Rick Morty\nCarol Dog\nElaine Fast\n",w.str());}


  



