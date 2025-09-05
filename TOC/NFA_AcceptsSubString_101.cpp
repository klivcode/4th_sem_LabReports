// Design a NFA that accepts a string if it contains the substring "101".
// cpp program for NFA accepting the string over {0,1}
// that contains the substring 101

#include <iostream>
#include <vector>
using namespace std;

vector<int> states={0, 1, 2, 3};
vector<vector<int>> transition = {
    {{'0', 0}, {'1', 0}, {'1', 1}}, // state 0
    {{'0', 2}},                   // state 1
    {{'1', 3}},                   // state 2
    {{'0',3},{'1',3}}};                            // state 3 (accepting state)


    bool simulate_nfa(string input) 
    {
        // to do
    }