//
// Created by 7862s on 12-02-2024.
//

#ifndef STATEMACHINES_SRC_STATES_CPP
#define STATEMACHINES_SRC_STATES_CPP
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <string_view>
#include <iomanip>
#include <memory>
#include <unordered_set>
#include "states.h"
namespace stm::nfa {
    struct state {
        state() : name("_") {
        }
        state(const state& s) = delete;
        explicit state(const std::string &_name) : name(_name) {}

        void setoutput(const char &through, std::shared_ptr<state> &to) {
            outputStates[through].emplace_back(to);
            std::cout << "\n got " << to -> name << " " << &outputStates << " through " << through << std::endl;
        }

        auto where(const char &input) {
            auto matches = outputStates[input];
//            std::cout << "got " << matches[0] -> name << " matches for inp "<<input << std::endl;
            return matches;
        }

        void print() const {
            std::cout << "\nState details ================"
                      << std::endl;
            std::cout << "\n Name :: " << name << " " << &outputStates
                      << std::endl;
            for (const auto &[k, pr]: outputStates) {
                std::cout << "\n Input " << k << ": ";
                for (const auto &match: pr) {
                    std::cout << match->name << " " << &(match->outputStates) << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "\n==============================\n"
                      << std::endl;
        }

        size_t operator()(const state &s) const {
            return std::hash<std::string>{}(s.name);
        }

        bool operator==(const state &s2) const {
            return this->name == s2.name && this->outputStates == s2.outputStates;
        }

        bool isfinal = false;
        std::unordered_map<char, std::vector<std::shared_ptr<state>>> outputStates;
        std::string name;
    };
}
namespace stm::dfa {
    struct state {
        state() : name("_") {
        }
        state(const state& s) = delete;
        explicit state(const std::string &_name) : name(_name) {}

        void setoutput(const char &through, const std::shared_ptr<state> &to) {
            outputStates[through] = to;
        }

        [[nodiscard]] auto where(const char &input) const {
            return outputStates.at(input);
        }

        void print() const {
            std::cout << "\nState details ================"
                      << std::endl;
            std::cout << "\nState name :: " << name << " " << &outputStates
                      << std::endl;
            for (const auto &[_,pr]: outputStates) {
                pr -> print();
            }
            std::cout << "\n==============================\n"
                      << std::endl;
        }

        size_t operator()(const state &s) const {
            return std::hash<std::string>{}(s.name);
        }

        bool operator==(const state &s2) const {
            return this->name == s2.name && this->outputStates == s2.outputStates;
        }
        bool operator<(const state &s2) const {
            return name < s2.name;
        }
        bool isfinal = false;
        std::unordered_map<char, std::shared_ptr<state>> outputStates;
        std::string name;
    };
}
namespace std {
    template<>
    struct hash<stm::dfa::state> {
    std::size_t operator()(const stm::dfa::state &s) const {
        return std::hash<std::string>()(s.name);
    }
};
}
bool operator<(const stm::dfa::state &cmp1, const stm::dfa::state &cmp2) {
    return cmp1.name < cmp2.name;
}
namespace stm {
    struct mixedState {
        mixedState() : states() {}
        mixedState(const std::shared_ptr<nfa::state> &state) {
            states.insert(state);
        }
        mixedState(std::unordered_set<std::shared_ptr<nfa::state>> states_in) {
            for (auto &st : states_in) {
                states.insert(st);
            }
        }
        mixedState(std::vector<std::shared_ptr<nfa::state>> states_in) {
            for (auto &st : states_in) {
                states.insert(st);
            }
        }
        void add(const std::shared_ptr<nfa::state> &state) {
            states.insert(state);
        }
        auto where(char _inp) {
            mixedState state;
            for(auto &st : states)
            {
//                std::cout << "got " << std::endl;
//                st ->print();
//                std::cout << " through " << _inp << std::endl;
                for(auto a : st -> where(_inp))
                {
                    state.add(a);
                }
            }
            return state;
        }
        auto name() const {
            std::string final_name;
            for(const auto &s : states)
            {
                final_name += s -> name;
            }
            return final_name;
        }
        auto isfinal() {
            for(const auto &s : states)
            {
                if(s -> isfinal)
                {
                    return true;
                }
            }
            return false;
        }
        auto begin() {
            return states.begin();
        }
        auto end() {
            return states.end();
        }
        bool operator==(const mixedState& other) const {
            return states == other.states;
//            return name() == other.name();
        }

        bool operator<(const mixedState& other) const {
            return name() < other.name();
        }
        std::unordered_set<std::shared_ptr<nfa::state>> states;
    };
}

namespace std {
    template<>
    struct hash<stm::mixedState> {
        std::size_t operator()(const stm::mixedState &s) const {
            return std::hash<stm::mixedState>()(s.states);
        }
    };
}
#endif //STATEMACHINES_SRC_STATES_CPP
