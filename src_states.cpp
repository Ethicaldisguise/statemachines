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
#include <iomanip>
#include <memory>
#include "states.h"
namespace stm::nfa {
    template<typename T>
    struct state {
        state() : name('_') {
        }

        explicit state(const T &_name) : name(_name) {}

        void setoutput(const T &through, state<T> &to) {
            outputStates[through].emplace_back(&to);
//            std::cout << "\n got " << to.name << " through " << through << std::endl;
        }

        auto where(const T &input) {
            auto matches = outputStates[input];
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
                    std::cout << match->name << " ";// << &(match->outputStates);
                }
                std::cout << std::endl;
            }
            std::cout << "\n==============================\n"
                      << std::endl;
        }

        size_t operator()(const state<T> &s) const {
            return std::hash<std::string>{}(s.name);
        }

        bool operator==(const state<T> &s2) const {
            return this->name == s2.name;
        }

        bool isfinal = false;
        std::unordered_map<T, std::vector<state<T> *>> outputStates;
        T name;
    };
}
namespace stm::dfa {
    template<typename T>
    struct state {
        state() : name('_') {
        }

        explicit state(const T &_name) : name(_name) {}

        void setoutput(const T &through, state<T> &to) {
            outputStates[through] = std::make_shared<state<T>>(to);
        }

        [[nodiscard]] auto where(const T &input) const {
            return outputStates.at(input);
        }

        void print() const {
            std::cout << "\nState details ================"
                      << std::endl;
            std::cout << "\nState name :: " << name << " " << &outputStates
                      << std::endl;
            for (const auto &pr: outputStates) {
                pr.print();
            }
            std::cout << "\n==============================\n"
                      << std::endl;
        }

        size_t operator()(const state<T> &s) const {
            return std::hash<std::string>{}(s.name);
        }

        constexpr bool operator==(const state<T> &s2) const {
            return this->name == s2.name;
        }

        bool isfinal = false;
        std::unordered_map<T, std::shared_ptr<state<T>>> outputStates;
        T name;
    };
}
namespace std {
    template<>
    struct hash<stm::dfa::state <int>> {
    std::size_t operator()(const stm::dfa::state<int> &s) const {
        return std::hash<int>()(s.name);
    }
};
}

#endif //STATEMACHINES_SRC_STATES_CPP
