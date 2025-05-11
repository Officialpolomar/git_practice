#include "dfa.h"
#include <fstream>


//DFA specification file included with a point of execution for program


DFA::DFA()
{
    states = S0;
}

/*
Allows for DFA to be set into one of its 14 states 
*/

void DFA::set_state(int _state)
{
    bool state_is_set = false;

    while (!state_is_set)
    {
        if (_state >= 0 && _state <= 13)
        {
            states = DFA::DFA_States(_state);
            state_is_set = true;
        }
        else
        {
            std::cout << "input must be between 0 and 13";
        }
    }
}

/*
Method to determine if string is a numeral literal
if states enum finishes in one the final states(S3, S4, S8, S5, S12) then
string is considered a numeral literal

COMPLEXITY: 0(n) one for-loop
*/

bool DFA::in_language(std::string w)
{
    for (int i = 0; i < w.length(); i++)
    {
        switch (states)
        {
            case S0:
                if (w[i] == '+' || w[i] == '-')
                {
                    states = S1;
                } 
                else if (w[i] == '.')
                {
                    states = S2;
                } 
                else if (w[i] >= '0' && w[i] <= '9')
                {
                    states = S3;
                } 
                else 
                {
                    states = SGarbage;
                }
                //std::cout << "Case 0 in state: " << states << std::endl;
                break;

            case S1:
            
                if(w[i] == '.')
                {
                    states = S2;
                } 
                else if (w[i] >= '0' && w[i] <= '9')
                {
                    states = S4;
                }
                else
                {
                    states = SGarbage;
                }
                //std::cout << "Case 1 in state: " << states << std::endl;
                break;

            case S2:
                
                if (w[i] >= '0' && w[i] <= '9')
                {
                    states = S5;
                } 
                else
                {
                    states = SGarbage;
                }
               // std::cout << "Case 2 in state: " << states << std::endl;
            break;

            case S3:
                if(w[i] == '+' || w[i] == '-')
                {
                    states = SGarbage;
                } 
                else if (w[i] == '.')
                {
                    states = S5;
                } 
                else if(w[i] >= '0' && w[i] <= '9')
                {
                    states = S3;
                } 
                else if(w[i] == 'E' || w[i] == 'e')
                {
                    states = S7;
                } 
                else
                {
                    states = SGarbage;
                }
               // std::cout << "Case 3 in state: " << states << std::endl;
                break;
            
            case S4:
                if (w[i] == '+' || w[i] == '-')
                {
                    states = SGarbage;
                } 
                else if (w[i] == '.')
                {
                    states = S8;
                } 
                else if(w[i] >= '0' && w[i] <= '9')
                {
                    states = S4;
                } 
                else if(w[i] == 'E' || w[i] == 'e')
                {
                    states = S10;
                } 
                else
                {
                    states = SGarbage;
                }
               // std::cout << "Case 4 in state: " << states << std::endl;
                break;
            
            case S5: // S5 and S6 can be the same state in the DFA diagram I created
                if (w[i] >= '0' && w[i] <= '9')
                {
                    states = S5;
                } 
                else if (w[i] == 'E' || w[i] == 'e')
                {
                    states = S7;
                } 
                else
                {
                    states = SGarbage;
                }
                //std::cout << "Case 5 in state: " << states << std::endl;
                break;
            
            case S7:
                if(w[i] >= '0' && w[i] <= '9')
                {
                    states = S12;
                } 
                else if(w[i] == '+' || w[i] == '-')
                {
                    states = S9;
                }
                else 
                {
                    states = SGarbage;
                }
                break;
            
            case S8:
                if(w[i] >= '0' && w[i] <= '9')
                {
                    states = S8;
                } 
                else if(w[i] == 'E' || w[i] == 'e')
                {
                    states = S10;
                }
                else 
                {
                    states = SGarbage;
                }
                break;

            case S9: // states S9 and S11 are the same
                if(w[i] >= '0' && w[i] <= '9')
                {
                    states = S12;
                } 
                else 
                {
                    states = SGarbage;
                }
                break;

            case S10:
                if(w[i] == '+' || w[i] == '-')
                {
                    states = S9;
                } 
                else if (w[i] >= '0' && w[i] <= '9')
                {
                    states = S12;
                } 
                else 
                {
                    states = SGarbage;
                }
                break;
            
            case S12:
                if(!(w[i] >= '0' && w[i] <= '9'))
                {
                    states = SGarbage;
                } 
                break;
            
            default:
                break;
        }
    }

    return states == S3 || states == S4 || states == S8 || states == S5 || states == S12; 
}
    
    
/*
Program point of execution:

Program takes in file with strings to test and outputs results into output.txt.
Once program is done, a blue output message appears displaying that the program has finished.
*/
int main()
{
    DFA dfa;
    std::string test_file_name;
    std::string str_input;

    std::cout << "Name of test file --> ";
    getline(std::cin,test_file_name);

    std::ifstream input(test_file_name);
    std::ofstream output("output.txt");


    while (getline(input,str_input))
    {
        if (str_input.empty())
        {
            output << " ";
        }
        else 
        {
            output << str_input;
        }
       
        //add spaces
        for (int i = 0; i < 11 - str_input.length(); i++)
        {
            output << " ";
        }

        if (dfa.in_language(str_input))
        {
            output << "is a valid numeric literal.\n";

        }
        else
        {
            output << "is NOT a valid numeric literal.\n"; 
        }
        
        dfa.set_state(0);
    }
    input.close();
    output.close();

    std::cout << "\033[34m" << "Program is finished. The results are in output.txt." << " \033[0m" << std::endl;
}
