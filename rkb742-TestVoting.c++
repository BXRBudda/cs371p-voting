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
        Candidate d = {b, "Adam Bob", 1, true};
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
        ASSERT_EQ("Adam Bob", r[0]);
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
                             "3\nAdam Bob\nCarol Dog\nElaine Fast\n"
                             "1 2 3\n2 1 3\n3 2 1");
        ostringstream w;
        voting_solve(r, w);
        ASSERT_EQ("Jack Smith\n\n""Adam Bob\nCarol Dog\nElaine Fast\n",w.str());}


  
/*
g++-4.8 -pedantic -std=c++11 -Wall -fprofile-arcs -ftest-coverage Voting.c++ RunVoting.c++ -o RunVoting
./RunVoting < RunVoting.in > RunVoting.tmp
diff RunVoting.tmp RunVoting.out
g++-4.8 -pedantic -std=c++11 -Wall -fprofile-arcs -ftest-coverage Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lgtest_main -pthread
valgrind ./TestVoting                                       >  TestVoting.tmp 2>&1
gcov-4.8 -b Voting.c++     | grep -A 5 "File 'Voting.c++'"     >> TestVoting.tmp
gcov-4.8 -b TestVoting.c++ | grep -A 5 "File 'TestVoting.c++'" >> TestVoting.tmp
cat TestVoting.tmp
==5581== Memcheck, a memory error detector
==5581== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==5581== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
==5581== Command: ./TestVoting
==5581== 
Running main() from gtest_main.cc
[==========] Running 12 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 12 tests from VotingFixture
[ RUN      ] VotingFixture.read_1
[       OK ] VotingFixture.read_1 (60 ms)
[ RUN      ] VotingFixture.read_2
[       OK ] VotingFixture.read_2 (6 ms)
[ RUN      ] VotingFixture.read_3
[       OK ] VotingFixture.read_3 (11 ms)
[ RUN      ] VotingFixture.eval_1
[       OK ] VotingFixture.eval_1 (46 ms)
[ RUN      ] VotingFixture.eval_2
[       OK ] VotingFixture.eval_2 (9 ms)
[ RUN      ] VotingFixture.eval_3
[       OK ] VotingFixture.eval_3 (14 ms)
[ RUN      ] VotingFixture.print_1
[       OK ] VotingFixture.print_1 (7 ms)
[ RUN      ] VotingFixture.print_2
[       OK ] VotingFixture.print_2 (3 ms)
[ RUN      ] VotingFixture.print_3
[       OK ] VotingFixture.print_3 (4 ms)
[ RUN      ] VotingFixture.solve_1
[       OK ] VotingFixture.solve_1 (6 ms)
[ RUN      ] VotingFixture.solve_2
[       OK ] VotingFixture.solve_2 (2 ms)
[ RUN      ] VotingFixture.solve_3
[       OK ] VotingFixture.solve_3 (4 ms)
[----------] 12 tests from VotingFixture (180 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 1 test case ran. (208 ms total)
[  PASSED  ] 12 tests.
==5581== 
==5581== HEAP SUMMARY:
==5581==     in use at exit: 0 bytes in 0 blocks
==5581==   total heap usage: 595 allocs, 595 frees, 72,280 bytes allocated
==5581== 
==5581== All heap blocks were freed -- no leaks are possible
==5581== 
==5581== For counts of detected and suppressed errors, rerun with: -v
==5581== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
File 'Voting.c++'
Lines executed:98.89% of 90
Branches executed:100.00% of 136
Taken at least once:62.50% of 136
Calls executed:83.93% of 112
Creating 'Voting.c++.gcov'
File 'TestVoting.c++'
Lines executed:100.00% of 122
Branches executed:65.83% of 796
Taken at least once:32.91% of 796
Calls executed:53.47% of 894
Creating 'TestVoting.c++.gcov'




*/


