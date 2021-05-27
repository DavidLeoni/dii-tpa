#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>


using std::string;
using std::vector;

template<typename T>
class Stack {

    public:

        /** RETURN the size of the stack

        */
        virtual int size() const = 0;

        /** Return a string like  
            
                Stack: cap=4 elements='ab'
        */
        virtual string as_string() const = 0;

        /** RETURN True if the stack empty, False otherwise
        */
        virtual bool is_empty() const = 0;


        /** Adds item to the top of the stack, if current size is within cap.
                
                - If stack size is already at cap value, new item is silently discarded            
        */
        virtual void push(const T c) = 0;

        /** RETURN the top element in the stack (without removing it!)
                
                - if stack is empty, throw std::runtime_error

        */
        virtual T peek() const = 0;

        /** Removes the top element in the stack and RETURN it.

                - if stack is empty, throw std::runtime_error
        */
        virtual T pop() = 0;

        /**
            RETURN a string with the n top elements, in the order in which they
            were pushed. For example, if the stack is the following: 
            
                e
                d
                c
                b
                a
                
            peekn(3) will return the string 'cde'

            - If there aren't enough element to peek, throw std::invalid_argument
            - If n is negative, throw std::invalid_argument
        */
        virtual vector<T> peekn(const int n) const = 0;

        /**
            Pops the top n elements, and RETURN them as a string, in the order in 
            which they where pushed. For example, with the following stack:
            
                e
                d
                c
                b
                a
            
            popn(3)
            
            will give back 'cde', and stack will become:
            
                b
                a
            
            - If there aren't enough element to pop, throw std::invalid_argument
            - If n is negative, throw std::invalid_argument
        */
        virtual vector<T> popn(const int n) = 0;

};

#endif  // STACK_H