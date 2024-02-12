//
// Created by 7862s on 11-02-2024.
//
#pragma once
#ifndef STATEMACHINES_STATES_H
#define STATEMACHINES_STATES_H


namespace stm::nfa {
    template<typename T>
    struct state;
}

namespace stm::dfa {
    template<class T>
    struct state;
}

#include "src_states.cpp"
#endif //STATEMACHINES_STATES_H
