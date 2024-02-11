//
// Created by 7862s on 11-02-2024.
//

#ifndef STATEMACHINES_STATES_H
#define STATEMACHINES_STATES_H
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <iomanip>
#include <hash_set>
#include <set>
    namespace stm::nfa {
        template<typename T>
        struct state {
            state() : name('_') {
            }

            explicit state(const T &_name) : name(_name) {}

            void setoutput(const T &through, state<T> &to) {
                outputStates[through].emplace_back(&to);
                std::cout << "\n got " << to.name << " through " << through << std::endl;
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
        template <typename T>
        struct state
        {
            struct state_component
            {
                T through;
                state<T> &to;

                state_component(const T &_through, state<T> &_to): through(_through),to(_to) {}

                void print() const
                {
                    std::cout << "Through: " << through << " --> " << to.name << '\n';
                }
                size_t operator()(const state_component &sc) const
                {
                    size_t hash1 = std::hash<T>{}(sc.through);
                    size_t hash2 = std::hash<std::string>{}(sc.to.name);
                    return hash1 ^ (hash2 << 1);
                }
                state_component &operator=(const state_component &other)
                {
                    if (this != &other)
                    {
                        through = other.through;
                        to = other.to;
                    }
                    return *this;
                }
            };
            state() : name('_')
            {
            }
            explicit state(const T &_name) : name(_name) {}
            void setoutput(const T &through, state<T> &to){
                state_component _new(through, to);
                outputStates.emplace_back(_new);
            }
            [[nodiscard]] auto where(const T &input) const {
                std::vector<state<T>*> matches;
                for(const auto & outstate : outputStates)
                {
                    if (outstate.through == input)
                        matches.push_back(&outstate.to);
                }
                return matches;
            }
            void print() const
            {
                std::cout << "\nState details ================"
                          << std::endl;
                std::cout << "\nState name :: " << name << " " << &outputStates
                          << std::endl;
                for (const auto &pr : outputStates){
                    pr.print();
                }
                std::cout << "\n==============================\n"
                          << std::endl;
            }
            size_t operator()(const state<T> &s) const
            {
                return std::hash<std::string>{}(s.name);
            }
            bool operator==(const state<T> &s2) const
            {
                return this->name == s2.name;
            }
            bool isfinal = false;
            std::set<state_component> outputStates;
            T name;
        };
}

namespace std {
    template<>
    struct hash<stm::dfa::state < int>> {
    std::size_t operator()(const stm::dfa::state<int> &s) const {
        return std::hash<int>()(s.name);
    }
};
}

#endif //STATEMACHINES_STATES_H
