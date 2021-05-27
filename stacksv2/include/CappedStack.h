#ifndef CAPPED_STACK_H
#define CAPPED_STACK_H

#include <iostream>
#include <string>       
#include <sstream>      // std::stringstream, std::stringbuf

#include <Stack.h>
#include <BasicStack.h>

#include <vector>
#include <algorithm>

using std::vector;

template<typename T>
class CappedStack : public BasicStack<T> {
    
    private:
        int cap;

    public:

        /**
         * Creates a CappedStack capped at provided cap. 
            
            - if cap <= 0, throws a std::invalid_argument
        */        
        CappedStack(const int cap);



        /** Return a string like  
            
                CappedStack: cap=4 elements=ab
        */
        virtual string as_string() const;

        /** Adds item to the top of the stack, if current size is within cap.
                
            - If stack size is already at cap value, new item is silently discarded
            
        */
        virtual void push(const T c);


        /** RETURN the cap of the stack 
        */
        int get_cap() const;

        /**
         MODIFIES the cap setting its value to the provided cap. 
            
                If the cap is less then the stack size, all the elements above 
                the cap are removed from the stack.
                
                If cap < 1, throws an std::invalid_argument exception
                Does *not* return anything!
            
                For example, with the following stack, and cap at position 7:
                
                cap ->  7
                        6
                        5  e
                        4  d
                        3  c
                        2  b
                        1  a
                        
                
                calling method set_cap(3) will change the stack to this:
                
                cap ->  3  c
                        2  b
                        1  a                                
                
        */
        void set_cap(const int cap);
};


template<typename T>
CappedStack<T>::CappedStack(const int cap){
    
    //jupman-raise
    if (cap <= 0){
        throw new std::invalid_argument(string("Cap must be positive, found instead: ") + to_string(cap));
    }                
    this->cap = cap;            
    ///jupman-raise
}        

template<typename T>
int CappedStack<T>::get_cap() const {
    
    //jupman-raise
    return this->cap;
    ///jupman-raise    
}

template<typename T>
std::string CappedStack<T>::as_string() const {
    
    //jupman-raise
    string s = string("CappedStack: cap=");
    s += to_string(this->cap);
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
void CappedStack<T>::push(const T c){
    //jupman-raise
    if (this->elements.size() < this->cap){
        this->elements.push_back(c);
    }            
    // else fail silently
    ///jupman-raise
}


template<typename T>
void CappedStack<T>::set_cap(const int cap){

    //jupman-raise
    if (cap < 1){
        throw std::invalid_argument(string("Invalid cap: ") + std::to_string(cap));
    }            
    
    if (cap < this->size()){
        this->popn(this->size() - cap);
    }

    this->cap = cap;
    ///jupman-raise
}

#endif  // CAPPED_STACK_H
