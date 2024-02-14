//
// Created by 7862s on 11-02-2024.
//
//#pragma once

#ifndef STATEMACHINES_STM_H
#define STATEMACHINES_STM_H

namespace stm::nfa {
    class stateMachine;
}
namespace stm::dfa {
    class stateMachine;
}

namespace stm {
    class automata;
    template <typename T>
    class UniqueStack;
    void transform(const nfa::stateMachine &nfa, dfa::stateMachine &dfa);
    void minimize(const automata &dfa);
    std::vector<std::string> tokenize(const std::string& str, char delimiter);
    const char * validateString(const std::string &_in, const stm::dfa::stateMachine &finiteautomata);
    void renameStates(stm::automata &automata);
    bool areEqual(const stm::automata &a1, const stm::automata &a2);
}

#include "src_stm.cpp"
#include "src_utilities.cpp"

#endif //STATEMACHINES_STM_H
