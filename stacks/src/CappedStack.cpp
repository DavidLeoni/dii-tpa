       
#include <Stack.h>
#include <CappedStack.h>
#include <iostream>
#include <string> 

using std::string;
using std::to_string;


CappedStack::CappedStack(const int cap){
    
    //jupman-raise
    if (cap <= 0){
        throw new std::invalid_argument(string("Cap must be positive, found instead: ") + to_string(cap));
    }                
    this->cap = cap;        
    this->elements = string();
    ///jupman-raise
}        

int CappedStack::get_cap() const {
    
    //jupman-raise
    return this->cap;
    ///jupman-raise    
}

std::string CappedStack::as_string() const {
    
    //jupman-raise
    string s = string("CappedStack: cap=");
    s += to_string(this->cap);
    s += " elements= ";
    s += this->elements;
    return s;
    ///jupman-raise
}


void CappedStack::push(const char c){
    //jupman-raise
    if (this->elements.size() < this->cap){
        this->elements.push_back(c);
    }            
    // else fail silently
    ///jupman-raise
}



void CappedStack::set_cap(const int cap){

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