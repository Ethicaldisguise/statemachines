//
// Created by 7862s on 11-02-2024.
//
#include <iostream>
#include <unordered_map>
#include <vector>
#include "states.h"
#ifndef STATEMACHINES_STM_H
#define STATEMACHINES_STM_H
namespace stm {

#define LINE(len) for(int i = 0; i < len; i++ ) std::cout<<"-------";
    template<class T>
    class stateMachine{
    public:
        stateMachine(){

            std::cout<<"Enter number valid of states :",std::cin>>n_states,std::cout<<std::endl;
            T _in;
            std::cout << "Enter starting state name: ",std::cin>>_in,std::cout<<std::endl;
            state<T> st(_in);
            _validstates[_in] = st;
            start_state = &_validstates[_in];
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
            std::cout << "\nEnter type of machine non-deterministic/deterministic (0/1) :", std::cin >> this->type;
            if(type)
            {
                std::cout<<"\nSTATES"<<std::setw(3);
                for(const auto &sig : _inputsignals)
                {
                    std::cout<<"| "<<std::setw(3)<<sig<<std::setw(5);
                }
                std::cout<<"|\n---------";
                LINE(n_inputs)
                std::cout<<std::endl;
                for(int i = 0; i < n_states; i++)
                {
                    T key;
                    std::cin>>key;
                    auto &key_state = _validstates[key];
                    for(const auto &sig : _inputsignals)
                    {
                        T r;
                        std::cin>>r;
                        key_state.setoutput(sig, _validstates[r]);
                    }
                }
                std::cout << std::endl;
            }
            else
            {
                std::cout << "\rEnter using spaces and press enter when you are finished     \n";
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
        }
        void print()const {
            LINE(10)
            std::cout<<"\nStarting state : "<<start_state-> name<<std::endl;
            LINE(10)
            std::cout<<"\nFinal States : ";
            for(const auto &fs:_finalstates)
            {
                std::cout<<fs.name<<std::endl;
            }
            LINE(10)
            std::cout<<"\nSTATES"<<std::setw(3);
            for(const auto &sig : _inputsignals )
            {
                std::cout<<"| "<<std::setw(3)<<sig<<std::setw(5);
            }
            std::cout<<"  |\n---------";
            LINE(n_inputs)
            std::cout<<std::endl;
        }
        void printrawstates() const{
            for(const auto &[k,v]:_validstates)
            {
                // std::cout<<k<<std::setw(7)<<":\n";
                v.print();
            }
        }
        bool validatestring(const std::string &_in) {
            state<T> *currentstate = start_state;
            for (size_t i = 0; i < _in.size(); ++i)
            {
                if (std::find(_inputsignals.begin(), _inputsignals.end(),_in[i]) == _inputsignals.end())
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
// private:
        bool type;
        int n_states ,n_inputs;
        state<T> *start_state;
        state<T> null;
        std::unordered_map<T,state<T>> _validstates;
        std::vector<T> _inputsignals;
        std::vector<state<T>> _finalstates;
    };

}











#endif //STATEMACHINES_STM_H
