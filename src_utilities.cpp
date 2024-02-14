//
// Created by 7862s on 14-02-2024.
//
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <vector>
#include <limits>
#include <sstream>
#include <set>
#include <stdexcept>
#include <cstring>
#include "stm.h"
#include "states.h"
namespace stm {
    template <typename T>
    class UniqueStack {
    private:
        std::set<T> elements;
        std::set<T> visited;
    public:
        void push(const T& value) {
            if (visited.find(value) == visited.end())
            {
#ifdef PRINTPATH
                std::cout << "adding " << value.name() << " to stack\n";
#endif
                elements.insert(value);
            }

            visited.insert(value);
        }

        void pop() {
            if (elements.empty()) {
                throw std::underflow_error("Stack is empty");
            }
            elements.erase(--elements.end());
        }

        const T& top() const {
            if (elements.empty()) {
                throw std::underflow_error("Stack is empty");
            }
            return *(--elements.end());
        }

        bool empty() const {
            return elements.empty();
        }

        size_t size() const {
            return elements.size();
        }
        void print() const {
            for(const auto &a : elements)
            {
                std::cout << a.name() << " ";
            }
            std::cout << std::endl;
        }
    };

    std::vector<std::string> tokenize(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;

        while (std::getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }

        return tokens;
    }
    void minimize(const automata &dfa) {
        std::cout << "Minimizing dfa" << std::endl;
    }
    bool validateString(const std::string &_in, const stm::dfa::stateMachine &finiteautomata) {
        auto currentstate =finiteautomata.start_state;
        for (size_t i = 0; i < _in.size(); ++i)
        {
            if (std::find(finiteautomata._inputsignals.begin(), finiteautomata._inputsignals.end(),_in[i]) == finiteautomata._inputsignals.end())
                continue;
#ifdef PRINTPATH
            const auto &name = currentstate->name;
            std::cout << name <<"("<<_in[i]<<")"<< std::setw(10 - name.size());
#endif
            currentstate = currentstate ->where(_in[i]);
#ifdef PRINTPATH
            std::cout << " --> " << currentstate -> name << "\n";
#endif
        }
        return currentstate->isfinal;
    }
    void validate_assignment(std::shared_ptr<dfa::state> &newstate,const stm::mixedState &curr_state,dfa::stateMachine &dfa) {
        const auto &state_ptr1 = dfa._validstates.find(curr_state.name());
        if (state_ptr1 != dfa._validstates.end())
        {
            newstate = state_ptr1 -> second;
//            std::cout << "Found " << newstate -> name << " " << &(newstate -> outputStates) <<std::endl;
        }
        else
        {
            newstate = std::make_shared<dfa::state>(curr_state.name());
            newstate -> isfinal = curr_state.is_final();
//            std::cout << "Creating " << newstate -> name << " " << &(newstate -> outputStates) <<std::endl;
            dfa.add_state(newstate);
        }
    }
    void transform(const nfa::stateMachine &nfa, dfa::stateMachine &dfa) {
        std::cout << "\nTransforming nfa -> dfa" << std::endl;
        dfa.start_state = std::make_shared<dfa::state>(nfa.start_state->name);
        dfa._validstates[nfa.start_state->name] = dfa.start_state;
        dfa._inputsignals = nfa._inputsignals;
        stm::mixedState currentstate(nfa.start_state);

        UniqueStack <stm::mixedState> state_stack;
        std::set<stm::mixedState> visited_states;
        std::set<std::shared_ptr<dfa::state>> visited_dfa_states;

        state_stack.push(currentstate);
        while (!state_stack.empty())
        {
            currentstate = state_stack.top();
            state_stack.pop();
            std::shared_ptr<dfa::state> newstate;
            validate_assignment(newstate, currentstate, dfa);
            for (const auto &a : nfa._inputsignals)
            {
                const auto mixed = currentstate.where(a);
                std::shared_ptr<dfa::state> new_state;

                validate_assignment(new_state, mixed, dfa);
                newstate -> setoutput(a, new_state);
#ifdef PRINTPATH
                std::cout << "Adding " << newstate -> name << " -> " << a << " -> " << new_state -> name << std::endl;
#endif
                state_stack.push(mixed);
            }
#ifdef PRINTPATH
            std::cout << "\nCurrent Stack : "; state_stack.print();
#endif
        }
        dfa.n_states = dfa._validstates.size();
        dfa.n_inputs = dfa._inputsignals.size();
    }
    bool areEqual(const stm::automata &a1, const stm::automata &a2)
    {

    }
    void renameStates(stm::automata &automata) {
        std::cout << "Renaming automata" << std::endl;

    }
}