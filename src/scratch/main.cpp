#include <iostream>

//#define PRINTPATH
#include "states.h"
#include "stm.h"
int main() {
    stm::nfa::stateMachine nfa;
    nfa.get_prerequsites();
    nfa.get_transition();
    nfa.print();
    stm::dfa::stateMachine dfa2;
//    dfa2.get_prerequsites();
//    dfa2.get_transition();
    stm::transform(nfa, dfa2);
    dfa2.print();
    while (true)
    {
        std::string str;
        std::cin >> str;
        std::cout << "\n " <<stm::validateString(str, dfa2) << "\n";
    }
    return 0;
}