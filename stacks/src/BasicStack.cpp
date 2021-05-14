       
#include <Stack.h>
#include <BasicStack.h>
#include <iostream>
#include <string> 

using std::string;
using std::to_string;


BasicStack::BasicStack(){    
    //jupman-raise
    this->elements = string();
    ///jupman-raise
}        


int BasicStack::size() const {
    
    //jupman-raise
    return this->elements.size();
    ///jupman-raise
}

std::string BasicStack::as_string() const {
    
    //jupman-raise
    string s = string("BasicStack:");    
    s += " elements= ";
    s += this->elements;
    return s;
    ///jupman-raise
}

bool BasicStack::is_empty() const {    
    //jupman-raise
    return this->elements.size() == 0;
    ///jupman-raise
}


void BasicStack::push(const char c){
    //jupman-raise    
    this->elements.push_back(c);        
    ///jupman-raise
}


char BasicStack::peek() const {    
    //jupman-raise
    if (this->elements.size() == 0){
        throw std::runtime_error("Empty stack !");
    }
    return this->elements.back();
    ///jupman-raise
}

char BasicStack::pop(){
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

string BasicStack::peekn(const int n) const {
    //jupman-raise
    if (n < 0){
        throw std::invalid_argument("Negative n! " + to_string(n));
    } 
    
    if (this->elements.size() >= n){
        int i = this->size() - n;
        string ret = this->elements.substr(i);
        return ret;
    } 

    throw std::invalid_argument(string("Requested to peek ") 
                        + to_string(n) 
                        + string(" elements, but  there are only ")
                        + to_string(this->size())
                        + string(" in the stack! "));

    ///jupman-raise
}



string BasicStack::popn(const int n){
    //jupman-raise
    if (n < 0){
        throw std::invalid_argument(string("Negative n! ") + to_string(n));
    }          

    if (this->size() >= n){
        int i = this->size() - n;
        string ret = this->elements.substr(i);
        this->elements = this->elements.substr(0,i);
        return ret;
    } else {
        throw std::invalid_argument("Requested to pop " + to_string(n) + " elements, but "
                            + " there are only " + to_string(this->size()) + " in the stack! ");
    }
    ///jupman-raise
}

