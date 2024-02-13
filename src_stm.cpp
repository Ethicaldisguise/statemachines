//
// Created by 7862s on 12-02-2024.
//

#ifndef STATEMACHINES_SRC_STM_CPP
#define STATEMACHINES_SRC_STM_CPP
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
#define LINE(len) for(int i = 0; i < len; i++ ) std::cout<<"-------";

namespace stm {
    class automata {
    public:
        virtual void print() const = 0;

        virtual void getransition() = 0;
        virtual void get_prerequsites() = 0;
        virtual bool operator==(const automata &cmp) = 0;
//        virtual void add_state(state _in) = 0;
//    protected:
        int n_inputs;
        int n_states;
    };
}
namespace stm::nfa {
    class stateMachine : public stm::automata{
    public:
        int n_states{}, n_inputs{};
        std::shared_ptr<state> start_state;
        std::shared_ptr<state> null = std::make_shared<state>();
        std::unordered_map<std::string, std::shared_ptr<state>> _validstates{};
        std::vector<char> _inputsignals;
        std::vector<std::shared_ptr<state>> _finalstates{};

        stateMachine() : n_inputs(0), n_states(0) {}
        void get_prerequsites() {
            std::cout<<"Enter number valid of states :",std::cin>>n_states,std::cout<<std::endl;
            std::string input;
            std::cout << "Enter starting state name: ",std::cin >> input,std::cout << std::endl;
            start_state = std::make_shared<state>(input);
            _validstates[input] = start_state;
            for(size_t i = 1 ; i < n_states ; i++ )
            {
                std::string _in;
                std::cout << "Enter state (" << i + 1 << ") name: ",std::cin>>_in,std::cout<<std::endl;
                _validstates[_in] = std::make_shared<state>(_in);
            }
            std::cout<<"Enter number of inputs :",std::cin>>n_inputs,std::cout<<std::endl;
            _inputsignals.reserve(n_inputs);
            for(size_t i = 0 ; i < n_inputs ; i++ )
            {
                char _in;
                std::cout << "Enter input(" << i + 1 << "): ",std::cin>>_in,std::cout<<std::endl;
                _inputsignals.emplace_back(_in);
                null -> setoutput(_in,null);
            }
            _validstates["_"] = null;
            int n;
            std::cin.ignore();
            std::cout<<"\nEnter no.of Final States: ",std::cin>>n,std::cout<<std::endl;
            while(n --> 0)
            {
                std::string r;
                std::cout<<"Enter finalstate(" << n << "): ",std::cin >> r;
                _validstates[r] -> isfinal = true;
                _finalstates.emplace_back(_validstates[r]);
            }
            std::cout<<std::endl;
        }
        void getransition(){
            std::cout << "\nEnter transition details of non-deterministic finite automata\n";
            std::cout << "(Fill using spaces for multiple outputs and press enter when you are finished):     \n\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            for (auto &[statename,state] : _validstates)
            {
                if (statename == "_")
                    continue;
                LINE(5) std::cout << "\n\n";
                std::cout << "For state :" << statename<< "\n\n";
                for (const auto &sig : _inputsignals)
                {
                    std::vector<std::string> inputs;
                    char inp[400];
                    std::cout << "Input signal " << sig << ": ";
                    std::cin.getline(inp,400,'\n');
                    std::string input(inp);
                    for(auto &a : stm::tokenize(input, ' '))
                        state -> setoutput(sig, _validstates[a]);
                    std::cout << std::endl;
                }
            }
            LINE(5) std::cout << "\n\n";

        }
        void add_state(std::shared_ptr<state> &_in) {
            _validstates[_in -> name] = _in;
        }
        bool operator==(const stm::automata &cmp){
            return n_inputs == cmp.n_inputs && n_states == cmp.n_states;
        }
        void print() const{
            for(const auto &[k,v]:_validstates)
            {
                v -> print();
            }
        }
    // private:
    };
}
namespace stm::dfa {
    class stateMachine : public stm::automata {
    public:
        int n_states{}, n_inputs{};
        std::shared_ptr<state> start_state{};
        std::shared_ptr<state> null = std::make_shared<state>();
        std::unordered_map<std::string, std::shared_ptr<state>> _validstates{};
        std::vector<char> _inputsignals;
        std::vector<std::shared_ptr<state>> _finalstates{};
        stateMachine() : n_inputs(0), n_states(0){

        }
        void get_prerequsites() {
                std::cout << "Enter number valid of states :", std::cin >> n_states, std::cout << std::endl;
                std::string starting_state_name;
                std::cout << "Enter starting state name: ", std::cin >> starting_state_name, std::cout << std::endl;
                start_state = std::make_shared<state>(starting_state_name);
                _validstates[starting_state_name] = start_state;
//                std::cout << "address of start state : " << &(start_state->outputStates) <<" "<< &(_validstates[starting_state_name]->outputStates) <<std::endl;
//                start_state = _validstates[starting_state_name];
                for (size_t i = 1; i < n_states; i++) {
                    std::string _in;
                    std::cout << "Enter state (" << i + 1 << ") name: ", std::cin >> _in, std::cout << std::endl;
//                    state st(_in);
                    _validstates[_in] = std::make_shared<state>(_in);
//                    _validstates[_in] = st;
                }
                std::cout << "Enter number of inputs :", std::cin >> n_inputs, std::cout << std::endl;
                _inputsignals.reserve(n_inputs);
                for (size_t i = 0; i < n_inputs; i++) {
                    char _in;
                    std::cout << "Enter input(" << i + 1 << "): ", std::cin >> _in, std::cout << std::endl;
                    _inputsignals.emplace_back(_in);
                    null -> setoutput(_in, null);
                }
                _validstates["_"] = null;
                int n;
                std::cin.ignore();
                std::cout << "\nEnter no.of Final States: ", std::cin >> n, std::cout << std::endl;
                while (n-- > 0) {
                    std::string r;
                    std::cout << "Enter finalstate(" << n << "): ", std::cin >> r;
                    _validstates[r] -> isfinal = true;
                    _finalstates.emplace_back(_validstates[r]);
                }
                std::cout << std::endl;
        };
        void getransition() {
            std::cout << "\nSTATES" << std::setw(3);
            for (const auto &sig: _inputsignals) {
                std::cout << "| " << std::setw(3) << sig << std::setw(5);
            }
            std::cout << "|\n---------";
            LINE(n_inputs)
            std::cout << std::endl;
            for (int i = 0; i < n_states; i++) {
                std::string key;
                std::cin >> key;
                auto &key_state = _validstates[key];
                for (const auto &sig: _inputsignals) {
                    std::string r;
                    std::cin >> r;
                    key_state -> setoutput(sig, _validstates[r]);
                }
            }
            std::cout << std::endl;
        }
        void add_state(std::shared_ptr<state> _in) {
            _validstates[_in -> name] = _in;
        }
        bool operator==(const stm::automata &cmp) {
            return n_inputs == cmp.n_inputs && n_states == cmp.n_states;
        }
        void print() const {
            int big_name_length = 0;
            for(const auto &[k,v]:_validstates)
            {
                if (k.size() > big_name_length)
                    big_name_length = k.size();
            }
            LINE(7)
            std::cout << "\nStarting state : " << start_state->name << &(start_state -> outputStates) << std::endl;
            LINE(7)
            std::cout << "\n\nFinal States : ";
            for (const auto &fs: _finalstates) {
                std::cout << fs -> name << std::endl;
            }
            std::cout << "\n";
            LINE(7)
            std::cout << "\n\n";
            std::cout << std::setw(big_name_length)<<"STATES" ;
            for (const auto &sig: _inputsignals) {
                std::cout << "| " << std::setw(big_name_length/2 - 2) << sig << std::setw(big_name_length/2);
            }
            std::cout << "   |\n----------";
            LINE(n_inputs)
            std::cout << std::endl;
            for (const auto &[k, v]: _validstates) {
                std::cout << "   " << k <<" "<< &(v -> outputStates) << std::setw(5);
                for (const auto &sig: _inputsignals) {
                    std::cout << "| " << std::setw(big_name_length/2 - 2) << v -> where(sig)-> name << " " << &(v -> where(sig)-> name)<<std::setw(big_name_length/2);
                }
                std::cout << "|\n";
            }
            std::cout << "----------";
            LINE(n_inputs)
            std::cout << std::endl;
        }

        // private:
    };
}
namespace stm {
    template <typename T>
    class UniqueStack {
    private:
        std::set<T> elements;

    public:
        void push(const T& value) {
            elements.insert(value);
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
    bool validatestring(const std::string &_in, const stm::dfa::stateMachine &finiteautomata) {
        auto currentstate =finiteautomata.start_state;
        for (size_t i = 0; i < _in.size(); ++i)
        {
            if (std::find(finiteautomata._inputsignals.begin(), finiteautomata._inputsignals.end(),_in[i]) == finiteautomata._inputsignals.end())
                continue;

            std::cout <<currentstate->name <<"("<<_in[i]<<")";
            currentstate = currentstate ->where(_in[i]);
            std::cout << " --> " << currentstate -> name << "\t";
        }
        return currentstate->isfinal;
    }
    void validate_assignment(std::shared_ptr<dfa::state> &newstate,const stm::mixedState &curr_state,dfa::stateMachine &dfa) {
        auto state_ptr1 = dfa._validstates.find(curr_state.name());
        if (state_ptr1 != dfa._validstates.end())
        {
            newstate = state_ptr1 -> second;
        }
        else
        {
            newstate = std::make_shared<dfa::state>(curr_state.name());
            dfa.add_state(newstate);
        }
    }
    void transform(const nfa::stateMachine &nfa, dfa::stateMachine &dfa) {
        std::cout << "Transforming nfa -> dfa" << std::endl;
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
//            std::cout << "Current state : " << currentstate.name() << std::endl;
            visited_states.insert(currentstate);
            std::shared_ptr<dfa::state> newstate;
            validate_assignment(newstate, currentstate, dfa);
            for (const auto &a : nfa._inputsignals)
            {
                const auto mixed = currentstate.where(a);
                std::shared_ptr<dfa::state> new_state;
                validate_assignment(new_state, mixed, dfa);
                std::cout << "Setting output for " << newstate -> name << &(newstate -> outputStates)<< std::endl;
                newstate -> setoutput(a, new_state);
                std::cout << "Current state : " << currentstate.name() << " (" << a << ") " << " --> " << mixed.name() << std::endl;
                if (visited_states.find(mixed) == visited_states.end())
                {
                    std::cout << "adding " << mixed.name() << " to stack\n";
                    state_stack.push(mixed);
                }
            }
//            dfa.add_state(newstate);
            state_stack.print();
        }
        dfa.n_states = dfa._validstates.size();
        dfa.n_inputs = dfa._inputsignals.size();
    }
}
#endif //STATEMACHINES_SRC_STM_CPP
/*
2
a
b
2
0
1
1
b
a
a
b
b
b
 _
 //----
2
q0
q1
2
0
1
1
q1
q0 q1
q1
q0 q1
q1
  */