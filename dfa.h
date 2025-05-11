#include <iostream>
#include <string>

#ifndef DFA_H
#define DFA_H


/*
This is the specification for the DFA object.
includes:
- DFA states enum 

INTERFACE:
- DFA state setter method
- method to see if string is accepted into numeral literal language
*/

class DFA 
{

private:
    enum DFA_States 
    {
        S0 = 0,
        S1 = 1,
        S2 = 2,
        S3 = 3,
        S4 = 4,
        S5 = 5,
        S6 = 6,
        S7 = 7,
        S8 = 8,
        S9 = 9,
        S10 = 10,
        S11 = 11,
        S12 = 12,
        SGarbage = 13,

    };

    DFA_States states;

public:

    DFA();

    bool in_language(std::string w);

    void set_state(int state);
};











#endif