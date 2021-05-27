#ifndef BASIC_STACK_H
#define BASIC_STACK_H


#include <iostream>
#include <string>       
#include <sstream>      // std::stringstream, std::stringbuf

#include <Stack.h>
#include <vector>
#include <algorithm>

using std::vector;
using std::to_string;

template<typename T>
class BasicStack : public Stack<T> {
    
    protected:
        vector<T> elements;

    public:

        virtual int size() const;

        virtual string as_string() const;

        virtual bool is_empty() const;

        virtual void push(const T c);

        virtual T peek() const;

        virtual T pop();

        virtual vector<T> peekn(const int n) const;

        virtual vector<T> popn(const int n);

        /**
         * Creates an empty BasicStack                   
        */        
        BasicStack();


};


template<typename T>
BasicStack<T>::BasicStack(){    
    //jupman-raise
    this->elements = vector<T>();
    ///jupman-raise
}        

template<typename T>
int BasicStack<T>::size() const {
    
    //jupman-raise
    return this->elements.size();
    ///jupman-raise
}

template<typename T>
std::string BasicStack<T>::as_string() const {
    
    //jupman-raise
    string s = string("BasicStack:");    
    s += " elements= ";
    std::stringstream ss;
    for (int i = 0; i < this->elements.size(); i++){
        ss << this->elements[i];
    }
    s += ss.str();

    
    return s;
    ///jupman-raise
}

template<typename T>
bool BasicStack<T>::is_empty() const {    
    //jupman-raise
    return this->elements.size() == 0;
    ///jupman-raise
}

template<typename T>
void BasicStack<T>::push(const T c){
    //jupman-raise    
    this->elements.push_back(c);        
    ///jupman-raise
}

template<typename T>
T BasicStack<T>::peek() const {    
    //jupman-raise
    if (this->elements.size() == 0){
        throw std::runtime_error("Empty stack !");
    }
    return this->elements.back();
    ///jupman-raise
}

template<typename T>
T BasicStack<T>::pop(){
    //jupman-raise
    if (this->elements.size() == 0){
        throw std::runtime_error("Empty stack !");
    } else {
        char ret = this->elements.back();
        this->elements.pop_back();
        return ret;
    }            
    ///jupman-raise
}

template<typename T>
vector<T> BasicStack<T>::peekn(const int n) const {
    //jupman-raise
    if (n < 0){
        throw std::invalid_argument("Negative n! " + to_string(n));
    } 
    
    if (this->elements.size() >= n){
        int i = this->size() - n;
        vector<T> ret = {this->elements.begin() + i, this->elements.end()};        
        return ret;
    } 

    throw std::invalid_argument(string("Requested to peek ") 
                        + to_string(n) 
                        + string(" elements, but  there are only ")
                        + to_string(this->size())
                        + string(" in the stack! "));

    ///jupman-raise
}


template<typename T>
vector<T> BasicStack<T>::popn(const int n){
    //jupman-raise
    if (n < 0){
        throw std::invalid_argument(string("Negative n! ") + to_string(n));
    }          

    if (this->size() >= n){
        int i = this->size() - n;
        vector<T> ret = {this->elements.begin() + i, this->elements.end()};        
        this->elements.resize(i);
        return ret;
    } else {
        throw std::invalid_argument("Requested to pop " + to_string(n) + " elements, but "
                            + " there are only " + to_string(this->size()) + " in the stack! ");
    }
    ///jupman-raise
}




#endif  // BASIC_STACK_H
