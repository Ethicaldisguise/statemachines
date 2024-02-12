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
#define LINE(len) for(int i = 0; i < len; i++ ) std::cout<<"-------";


namespace stm::nfa {
    template<class T>
    class stateMachine : public stm::automata<T>{
    public:
        stateMachine(){
            std::cout<<"Enter number valid of states :",std::cin>>n_states,std::cout<<std::endl;
            T input;
            std::cout << "Enter starting state name: ",std::cin >> input,std::cout << std::endl;
            state<T> starting_state(input);
            _validstates[input] = starting_state;
            start_state = &_validstates[input];
            for(size_t i = 1 ; i < n_states ; i++ )
            {
                T _in;
                std::cout << "Enter state (" << i + 1 << ") name: ",std::cin>>_in,std::cout<<std::endl;
                state<T> st(_in);
                _validstates[_in] = st;
            }
            std::cout<<"Enter number of inputs :",std::cin>>n_inputs,std::cout<<std::endl;
            _inputsignals.reserve(n_inputs);
            for(size_t i = 0 ; i < n_inputs ; i++ )
            {
                T _in;
                std::cout << "Enter input(" << i + 1 << "): ",std::cin>>_in,std::cout<<std::endl;
                _inputsignals.emplace_back(_in);
                null.setoutput(_in,null);
            }
            _validstates['_'] = null;
            int n;
            std::cin.ignore();
            std::cout<<"\nEnter no.of Final States: ",std::cin>>n,std::cout<<std::endl;
            while(n --> 0)
            {
                T r;
                std::cout<<"Enter finalstate(" << n << "): ",std::cin >> r;
                _validstates[r].isfinal = true;
                _finalstates.push_back(_validstates[r]);
            }
            std::cout<<std::endl;
        }
        void getransition(){
            std::cout << "\nEnter transition details of non-deterministic finite automata\n";
            std::cout << "(Fill using spaces for multiple outputs and press enter when you are finished):     \n\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            for (auto &[statename,state] : _validstates)
            {
                if (statename == '_')
                    continue;
                std::cout << "For state :" << statename<< std::endl;
                for (const auto &sig : _inputsignals)
                {
                    std::vector<T> inputs;
                    char inp[100];
                    std::cout << "Input signal " << sig << ": ";
                    std::cin.getline(inp,100,'\n');
                    for (size_t i = 0; inp[i]; i++)
                    {
                        if (inp[i] != ' ')
                        {
                            state.setoutput(sig, _validstates[inp[i]]);
                        }
                    }
                    std::cout << std::endl;
                }
            }
        }
        bool operator==(const stm::automata<T> &cmp){
            return 0;
        }
        void print() const{
            for(const auto &[k,v]:_validstates)
            {
                v.print();
            }
        }
    // private:
        int n_states{} ,n_inputs{};
        state<T> *start_state{};
        state<T> null{};
        std::unordered_map<T,state<T>> _validstates{};
        std::vector<T> _inputsignals;
        std::vector<state<T>> _finalstates{};
    };
}
namespace stm::dfa {
    template<class T>
    class stateMachine : public stm::automata<T> {
    public:
        stateMachine() {
            std::cout << "Enter number valid of states :", std::cin >> n_states, std::cout << std::endl;
            T starting_state_name;
            std::cout << "Enter starting state name: ", std::cin >> starting_state_name, std::cout << std::endl;
            state<T> starting_state(starting_state_name);
            _validstates[starting_state_name] = starting_state;
            start_state = &_validstates[starting_state_name];
            for (size_t i = 1; i < n_states; i++) {
                T _in;
                std::cout << "Enter state (" << i + 1 << ") name: ", std::cin >> _in, std::cout << std::endl;
                state<T> st(_in);
                _validstates[_in] = st;
            }
            std::cout << "Enter number of inputs :", std::cin >> n_inputs, std::cout << std::endl;
            _inputsignals.reserve(n_inputs);
            for (size_t i = 0; i < n_inputs; i++) {
                T _in;
                std::cout << "Enter input(" << i + 1 << "): ", std::cin >> _in, std::cout << std::endl;
                _inputsignals.emplace_back(_in);
                null.setoutput(_in, null);
            }
            _validstates['_'] = null;
            int n;
            std::cin.ignore();
            std::cout << "\nEnter no.of Final States: ", std::cin >> n, std::cout << std::endl;
            while (n-- > 0) {
                T r;
                std::cout << "Enter finalstate(" << n << "): ", std::cin >> r;
                _validstates[r].isfinal = true;
                _finalstates.push_back(_validstates[r]);
            }
            std::cout << std::endl;
        }

        void getransition() {
            std::cout << "\nSTATES" << std::setw(3);
            for (const auto &sig: _inputsignals) {
                std::cout << "| " << std::setw(3) << sig << std::setw(5);
            }
            std::cout << "|\n---------";
            LINE(n_inputs)
            std::cout << std::endl;
            for (int i = 0; i < n_states; i++) {
                T key;
                std::cin >> key;
                auto &key_state = _validstates[key];
                for (const auto &sig: _inputsignals) {
                    T r;
                    std::cin >> r;
                    key_state.setoutput(sig, _validstates[r]);
                }
            }
            std::cout << std::endl;
        }
        bool operator==(const stm::automata<T> &cmp) {
            return 0;
        }
        void print() const {
            LINE(7)
            std::cout << "\nStarting state : " << start_state->name << std::endl;
            LINE(7)
            std::cout << "\nFinal States : ";
            for (const auto &fs: _finalstates) {
                std::cout << fs.name << std::endl;
            }
            LINE(7)
            std::cout << "\n";
            std::cout << "\nSTATES" << std::setw(3);
            for (const auto &sig: _inputsignals) {
                std::cout << "| " << std::setw(3) << sig << std::setw(5);
            }
            std::cout << "   |\n----------";
            LINE(n_inputs)
            std::cout << std::endl;
            for (const auto &[k, v]: _validstates) {
                std::cout << "   " <<k << std::setw(5);
                for (const auto &sig: _inputsignals) {
                    std::cout << "| " << std::setw(3) << v.where(sig)-> name << std::setw(5);
                }
                std::cout << "|\n";
            }
            std::cout << "----------";
            LINE(n_inputs)
            std::cout << std::endl;
        }

        // private:
        bool type{};
        int n_states{}, n_inputs{};
        state<T> *start_state{};
        state<T> null{};
        std::unordered_map<T, state<T>> _validstates{};
        std::vector<T> _inputsignals;
        std::vector<state<T>> _finalstates{};
    };
}

namespace stm {
    template<typename T>
    class automata {
    public:
        virtual void print() const= 0;
        virtual void getransition() = 0;
        virtual bool operator==(const automata<T> &cmp) = 0;
    private:
        int n_states{} ,n_inputs{};
    };
    template<class T>
    bool validatestring(const std::string &_in, const stm::dfa::stateMachine<T> &finiteautomata) {
        stm::dfa::state<T> *currentstate = finiteautomata.start_state;
        for (size_t i = 0; i < _in.size(); ++i)
        {
            if (std::find(finiteautomata._inputsignals.begin(), finiteautomata._inputsignals.end(),_in[i]) == finiteautomata._inputsignals.end())
                continue;

            std::cout <<currentstate->name <<"("<<_in[i]<<")";
            for(const auto &state:currentstate->where(_in[i]))
            {
                currentstate = state;
            }
            std::cout << " --> " << currentstate -> name << "\t";
        }
        return currentstate->isfinal;
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

  */