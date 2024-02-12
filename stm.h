//
// Created by 7862s on 11-02-2024.
//
#pragma once

#ifndef STATEMACHINES_STM_H
#define STATEMACHINES_STM_H

namespace stm::nfa {
    template<typename T>
    class stateMachine;
}
namespace stm::dfa {
    template<class T>
    class stateMachine;
}

namespace stm {
    template<typename T>
    class automata;
    template<class T>
    void transform(const nfa::stateMachine<T> &nfa, dfa::stateMachine<T> &dfa);
    template<class T>
    void minimize(const automata<T> &dfa);
    template<class T>
    bool validatestring(const std::string &_in,const dfa::stateMachine<T> finiteautomata);
}

#include "src_stm.cpp"

#endif //STATEMACHINES_STM_H
